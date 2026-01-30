import sys
import os
import re
from types import SimpleNamespace
from pathlib import Path
import argparse
from datetime import datetime
import pandas as pd
from ruamel.yaml import YAML

#バージョン
SCRIPT_VERSION = "ghsprj version 1-0-0"

#更新履歴
'''
1-0-0 2025/11/12 初版
'''

_LINE_SEP_ = '# ' + '-' * 130     # 行セパレータ
SUB_LINKER_OPT  = "_____SUB_LINKER_OPT_____"
INCLUDE_FILE    = '_____INCLUDE_FILE_____'
SUBPROJECT_FILE = '_____SUBPROJECT_FILE_____'
SOURCES_FILE    = '_____SOURCES_FILE_____'
LIB_LD_FILE     = '_____LIB_LD_FILE_____'

#出力テンプレート配列 [[Type=Program, Library, Subproject, Options], テンプレート文字列]
template = [
[[1,1,1,1], '#!gbuild'],
[[1,1,0,0], r'gbuildDir=C:\GHS\RH850_V.R9144\comp_201715'],
[[1,1,0,0], 'primaryTarget=v800_standalone.tgt'],
[[1,1,1,1], '[$GPJ_TYPE$]'],
[[0,0,1,0], '    :sourceDir=../'],
[[1,1,0,0], '    :optionsFile=../ghs_ccal_rh850g4mh.opt'],
[[1,1,0,0], '    -object_dir=obj/$GPJ_NAME$'],
[[1,1,1,1], ''],
[[1,0,0,0], '    -o dst/$GPJ_NAME$.elf'],
[[0,1,0,0], '    -o dst/$GPJ_NAME$.a'],
[[1,1,1,0], ''],
[[1,1,1,0], ''],
[[1,0,0,0], '#    :macro=GSR_CLI="gsrec -sort -S3 -noS5 -bytes 16"'],
[[1,0,0,0], '#    :macro=GSR_PAR="-pad1 0x003c0000 0x003fffff 0xff -start 0x003c0000 -end 0x003fffff"'],
[[1,0,0,0], '#    :postexec="${GSR_CLI} ${GSR_PAR}                     -o dst/$GPJ_NAME$_ac.mot dst/$GPJ_NAME$.elf"'],
[[1,0,0,0], '#    :postexec="${GSR_CLI} ${GSR_PAR} -romaddr 0x023c0000 -o dst/$GPJ_NAME$_bd.mot dst/$GPJ_NAME$.elf"'],
[[1,0,0,0], ''],
[[1,1,0,0], SUB_LINKER_OPT],
[[1,1,0,1], INCLUDE_FILE],
[[1,1,0,0], SUBPROJECT_FILE],
[[1,1,1,0], SOURCES_FILE],
[[1,0,1,0], LIB_LD_FILE],
[[1,1,1,1], _LINE_SEP_],
[[1,1,1,1], '# $SCRIPT_VERSION$'],
[[1,1,1,1], '# Date generated: $DATE_GENERATED$'],
[[1,1,1,1], _LINE_SEP_],
[[1,1,1,1], '']
]

TOP_DIR = os.getcwd()

# 再帰的に辞書を SimpleNamespace に変換する。
def convert_nested_dict_to_namespace(data):
    if isinstance(data, dict):
        for key, value in data.items():
            data[key] = convert_nested_dict_to_namespace(value)
        return SimpleNamespace(**data)
    else:
        return data
    
class BuildConfig:
    def __init__(self, file):
        yaml = YAML(typ='safe')
        with open(Path(file), 'r', encoding='utf-8') as f:
            data = yaml.load(f)
        self.config = convert_nested_dict_to_namespace(data)

    def checkparam(self):
        pass

def getAllFileList(dirs):
    table = pd.DataFrame()

    for sub_dir in dirs:
        source_dir = os.path.join(TOP_DIR, sub_dir)
        dir_path = Path(source_dir)  
        file_list = [{'full_path':f.absolute().as_posix(),'name':f.name, 'ext': f'{f.suffix}'} for f in dir_path.rglob('*') if f.is_file()] 
        file_table = pd.DataFrame(file_list)
        table = pd.concat([table, file_table])

    table = table.sort_values(by="full_path", key=lambda col: col.str.lower(), ascending=True)
    table.reset_index(drop=True, inplace=True)
    table['relative_path'] = table['full_path'].map(full2relative)
    table['directory'] = table['relative_path'].map(os.path.dirname)
    table['ext'] = table['ext'].str.lower()

    return table


def full2relative(value):
    full_path = Path(value)
    relative_path = full_path.relative_to(TOP_DIR)

    return relative_path.as_posix()

def makeGpjFile(filename):
    full_path = Path(TOP_DIR)
    ghps_file = full_path.joinpath(filename)
    ghps_file.parent.mkdir(parents=True, exist_ok=True)
    ghps_file.touch()
 
    return ghps_file

def addLinkoptions(file, sub):
    print(_LINE_SEP_, file=file)
    print('# Subprojects : C Compiler/Assembler/Linker Options', file=file)
    print(_LINE_SEP_, file=file)
    for opt in sub:
        print(f'    :optionsFile={opt}.opt', file=file)
    print('', file=file)

def addSubprojects(file, sub):
    print(_LINE_SEP_, file=file)
    print('# Subprojects : Sources/Libraries/Linker Directives', file=file)
    print(_LINE_SEP_, file=file)
    for opt in sub:
        print(f'{opt}.gpj', file=file)
    print('', file=file)

def addIncludes(file, ext, table):
    print(_LINE_SEP_, file=file)
    print('# includes', file=file)
    print(_LINE_SEP_, file=file)
    header_file_table = table[table['ext'].isin([word.lower() for word in ext])]
    dir_list = header_file_table['directory'].drop_duplicates()
    for num, item in dir_list.items():
        print('    -I' + item, file=file)
    print('', file=file)

def addBuildFiles(file, ext, table):
    src_list = table[table['ext'].isin([word.lower() for word in ext])]
    for num, item in src_list.iterrows():
        print(item['relative_path'], file=file)

def addSourceFiles(file, ext, table):
    print(_LINE_SEP_, file=file)
    print('# sources', file=file)
    print(_LINE_SEP_, file=file)
    addBuildFiles(file, ext, table)
    print('', file=file)

def addLinkFiles(file, ext, table):
    print(_LINE_SEP_, file=file)
    print('# libraries and linker directives', file=file)
    print(_LINE_SEP_, file=file)
    addBuildFiles(file, ext, table)
    print('', file=file)

def getType(type):
    type_num = 0
    if type.casefold() == 'program'.casefold():
        type_num = 0
    elif type.casefold() == 'library'.casefold():
        type_num = 1
    elif type.casefold() == 'subproject'.casefold():
        type_num = 2
    else:
        print('ERRPR: 無効なtypeです。')
        sys.exit(1)
    return type_num

def findDollarStrings(text):
    pattern = r"\$(.*?)\$"
    matches = re.findall(pattern, text, flags=re.DOTALL)
    return matches

# GPJファイル生成
def outputGpj(config):
    DATE_GENERATED = datetime.now().strftime("%Y/%m/%d %H:%M:%S")

    for item in config.gpj:
        table = None
        gpj = convert_nested_dict_to_namespace(item)
        type_num = getType(gpj.type)

        filenames = ['sub/' + gpj.name + '.gpj', 'sub/' + gpj.name + '.opt'] if gpj.type == 'subproject' else [gpj.name + '.gpj']
        for filename in filenames:
            ghps_file = makeGpjFile(filename)
            GPJ_NAME = gpj.name
            GPJ_TYPE = gpj.type.capitalize()
            if ghps_file.suffix == '.opt':
                type_num = 3
                GPJ_TYPE = 'Options File'

            if hasattr(gpj, "root"):
                table = getAllFileList(gpj.root)

            with open(ghps_file, 'w', encoding='utf-8') as file:
                for line in template:
                    if line[0][type_num] == 1:
                        output_text = line[1]
                        if output_text == SUB_LINKER_OPT:
                            if hasattr(gpj, "sub"):
                                addLinkoptions(file, gpj.sub)
                        elif output_text == INCLUDE_FILE:
                            if table is not None:
                                addIncludes(file, config.inc_ext, table)
                        elif output_text == SUBPROJECT_FILE:
                            if hasattr(gpj, "sub"):
                                addSubprojects(file, gpj.sub)
                        elif output_text == SOURCES_FILE:
                            if table is not None:
                                addSourceFiles(file, config.src_ext, table)
                        elif output_text == LIB_LD_FILE:
                            if table is not None:
                                addLinkFiles(file, config.lal_ext, table)
                        else:
                            for text in findDollarStrings(output_text):
                                if text == 'GPJ_NAME':
                                    output_text = re.sub(r"\$GPJ_NAME\$", GPJ_NAME, output_text)
                                if text == 'GPJ_TYPE':
                                    output_text = re.sub(r"\$GPJ_TYPE\$", GPJ_TYPE, output_text)
                                if text == 'SCRIPT_VERSION':
                                    output_text = re.sub(r"\$SCRIPT_VERSION\$", SCRIPT_VERSION, output_text)
                                if text == 'DATE_GENERATED':
                                    output_text = re.sub(r"\$DATE_GENERATED\$", DATE_GENERATED, output_text)
                        
                            print(output_text, file=file)


# 引数をパースする関数
def parseArgs(args):
    version_parser = argparse.ArgumentParser(add_help=False)
    version_parser.add_argument('-v', '--version', help='show script version and exit', action="store_true")
    args, unknown = version_parser.parse_known_args()

    if args.version:
        print(SCRIPT_VERSION)
        sys.exit(0)
    
    parser = argparse.ArgumentParser(description='ymlコンフィグファイルを元にgpjファイルを生成する', parents=[version_parser])
    parser.add_argument('CONFIG_FILE', help='ymlコンフィグファイル')

    return parser.parse_args(unknown)

def main(args=None) -> None:
    args = parseArgs(args)

    #yamlファイル読み込み
    bc = BuildConfig(args.CONFIG_FILE)

    #yamlファイルデータチェック
    bc.checkparam()

    #GPJファイル出力
    outputGpj(bc.config)

    # 結果表示
    print('#生成完了:')


if __name__ == '__main__':

    main()










