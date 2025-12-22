import sys
import os
from pathlib import Path
import argparse
import pandas as pd

#バージョン
SCRIPT_VERSION = "fdfns version 1-0-0"

#更新履歴
'''
1-0-0 2025/11/17 初版

'''

TARGET_DIR = ''

def getAllFileList(source_dir):
    table = pd.DataFrame()

    dir_path = source_dir  
    file_list = [{'full_path':f.absolute().as_posix(),'name':f.name,'lname':f.name.lower(), 'ext': f'{f.suffix}'} for f in dir_path.rglob('*') if f.is_file()] 
    table = pd.DataFrame(file_list)


    if len(table) < 1:
        print("ファイルが見つかりません")
        sys.exit(0)

    table = table.sort_values(by="full_path", key=lambda col: col.str.lower(), ascending=True)
    table.reset_index(drop=True, inplace=True)
    table['relative_path'] = table['full_path'].map(full2relative)
    table['directory'] = table['relative_path'].map(os.path.dirname)
    table['ext'] = table['ext'].str.lower()

    return table


def full2relative(value):
    full_path = Path(value)
    target_path = Path(TARGET_DIR).parent
    relative_path = full_path.relative_to(target_path)

    return relative_path.as_posix()

def makeGpjFile(filename):
    full_path = Path(TARGET_DIR)
    ghps_file = full_path.joinpath(filename)
    ghps_file.parent.mkdir(parents=True, exist_ok=True)
    ghps_file.touch()
 
    return ghps_file

def dupNamefileList(table):
    dup_list = table[table.duplicated(subset=['lname'], keep=False)] 
    dup_list = dup_list.sort_values(by=["lname", 'directory'], key=lambda col: col.str.lower(), ascending=True)
    for index, data in dup_list.iterrows():
        print('{:<32} : {}'.format(data['name'] if len(data['name'] ) <= 32 else data['name'][:32],data['directory']))
    
    return dup_list


# 引数をパースする関数
def parseArgs(args):
    version_parser = argparse.ArgumentParser(add_help=False)
    version_parser.add_argument('-v', '--version', help='show script version and exit', action="store_true")
    args, unknown = version_parser.parse_known_args()

    if args.version:
        print(SCRIPT_VERSION)
        sys.exit(0)
    
    parser = argparse.ArgumentParser(description='指定されたディレクトリ（サブディレクトリ含む）の同名ファイルのリストを出力する', parents=[version_parser])
    parser.add_argument('DIR_PATH', nargs="?", default='', help='対象ディレクトリパス（省略時：スクリプト実行ディレクトリ）')

    return parser.parse_args(unknown)

def main(args=None) -> None:
    global TARGET_DIR
    args = parseArgs(args)

    #ディレクトリ情報取得
    dir_name = args.DIR_PATH
    if dir_name == '':
        dir_name = os.getcwd()
    if not os.path.exists(dir_name):
        print("ディレクトリは存在しません", dir_name)
        sys.exit(1)
    TARGET_DIR = Path(dir_name).resolve()
    table = getAllFileList(TARGET_DIR)

    #名称重複ファイルリスト出力
    table = dupNamefileList(table)

    # 結果表示
    print('#完了 重複ファイル数：', len(table), '   種類：', len(table['lname'].unique()))


if __name__ == '__main__':

    main()











