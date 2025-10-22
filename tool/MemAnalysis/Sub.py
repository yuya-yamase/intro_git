import json
import re
from collections import defaultdict
import pprint
import pandas as pd
import sys


# Function to parse the .map file and return relevant lines
def extract_lines_from_map(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    start_extracting = False
    extracted_lines = []

    for line in lines:
        if "Module Summary" in line:
            start_extracting = True
        elif "Global Symbols" in line:
            start_extracting = False
        if start_extracting and not line.startswith("Module Summary"):
            extracted_lines.append(line)
    
    return extracted_lines[1:]  # 先頭のヘッダー行をスキップする

# Function to parse each line and return the components and section sizes
def parse_line(line):
    if '->' in line:
        parts = line.split('->')
        prefix = parts[0].strip()
        new_section, module = parts[-1].strip().split()
        match = re.match(r"(\w+)\+(\w+)\s+(\.[\w_]+)", prefix)
        if match:
            origin, size, section = match.groups()
            size = int(size, 16)  # 16進数のサイズを整数に変換する
            module_name = module.split('(')[0].strip('<>') if '(' in module else module.strip('<>')
            section = new_section
            return module_name, section, size
    else:
        match = re.match(r"(\w+)\+(\w+)\s+(\.[\w_.]+)\s+([\w.\(\)<>]+)", line)
        if match:
            origin, size, section, module = match.groups()
            size = int(size, 16)  # 16進数のサイズを整数に変換する
            module_name = module.split('(')[0].strip('<>') if '(' in module else module.strip('<>')
            return module_name, section, size
    return None, None, None

# Aggregate section sizes by category and component
def aggregate_section_sizes(extracted_lines):
    section_component_sizes = defaultdict(lambda: defaultdict(int))
    category_component_sizes = defaultdict(lambda: defaultdict(int))

    for line in extracted_lines:
        module_name, section, size = parse_line(line)
        if module_name and section and size:
            component = module_name
            section_component_sizes[sortkey_section + section][component] += size
            if section not in SECTION_DICT.keys():
                category_component_sizes['<.Unknown>'][component] += size

    for category in CATEGORY_LIST:
        for section in SECTION_DICT.keys():
            if category == SECTION_DICT[section]:
                for component, size in section_component_sizes[sortkey_section + section].items():
                    category_component_sizes[category][component] += size

    #未使用のセクション含む全セクションを列に追加
    for section in SECTION_DICT.keys():
        section_component_sizes[sortkey_section + section][component] += 0

    #未使用のカテゴリ含む全カテゴリを列に追加（容量0のカテゴリを除く）
    for category in CATEGORY_LIST:
        if category != "<.Unknown>":
            if category == "<.text>" or category == "<.rodata>":
                if CAPACITY_DICT["Capacity<.CodeFlash> (= <.text> + <.rodata>)"] != 0:
                    category_component_sizes[category][component] += 0
            else:
                 if CAPACITY_DICT['Capacity' + category] != 0:
                    category_component_sizes[category][component] += 0

    return section_component_sizes, category_component_sizes


def map_file_analyze(json_file, file_path, sheet_name,output_file):
    global SECTION_INFO, CATEGORY_LIST, SECTION_DICT, COMPONENT_LIST, CAPACITY_DICT

    # JSON設定ファイルの読み込み
    with open(json_file, 'r') as f:
        config = json.load(f)

    SECTION_INFO = config["SECTION_INFO"]
    CATEGORY_LIST = SECTION_INFO["CATEGORY_LIST"]
    SECTION_DICT = SECTION_INFO["SECTION_DICT"]
    COMPONENT_LIST = config["COMPONENT_LIST"]
    CAPACITY_DICT = SECTION_INFO["CAPACITY_DICT"]

    extracted_lines = extract_lines_from_map(file_path)
    section_component_sizes, category_component_sizes = aggregate_section_sizes(extracted_lines)
    section_component_sizes = section_component_sizes | category_component_sizes
#    pprint.pprint(section_component_sizes)

    # COMPONENT_LIST内の各ファイルのサイズを集計する
    component_sizes = defaultdict(lambda: defaultdict(int))
    matched_components = []

    for sections, module_names in section_component_sizes.items():
        for module_name, size in module_names.items():
            for component in COMPONENT_LIST:
                if component.endswith(('.c', '.850', '.a')):
                    file_name = ''
                    if component.endswith('.c'):
                        file_name = module_name.replace('.o', '.c')
                    elif component.endswith('.850'):
                        file_name = module_name.replace('.o', '.850')
                    elif component.endswith('.a'):
                        file_name = module_name
                    if file_name in component:
                        for directory in COMPONENT_LIST:
                            if component.startswith(directory):
                                # ディレクトリの場合、その配下のすべてのモジュールを含む
                                if directory not in matched_components:
                                    matched_components.append(directory)
                                component_sizes[directory][sections] += size

    #pprint.pprint(matched_components)
    #pprint.pprint(component_sizes)

    # セクションごとにファイル毎のサイズを出力する
    # for section in SECTION_DICT.keys():
    #    print(f"Section: {section}")
    #    for component, size in section_component_sizes[section].items():
    #        print(f"  Component: {component}, Size: {size} (0x{size:X})")
    #    print()

    # カテゴリごとにサイズを集計して出力する
    # for category in CATEGORY_LIST:
    #    print(f"Category: {category}")
    #    for component, size in section_component_sizes[category].items():
    #       print(f"  Component: {component}, Size: {size} (0x{size:X})")
    #    print()

    # セクションごとにファイル毎のサイズを出力する??
    #for component in COMPONENT_LIST:
    #    print(f"Component: {component}")
    #    for section, size in component_sizes[component].items():
    #        print(f"  Section: {section}, Size: {size} (0x{size:X})")
    #    print()

    # データを平坦化してリストに変換
    data_list = []
    for component, sizes in component_sizes.items():
        #CodeFlash領域の使用量集計のリセット
        codeflash_value = 0
        for size_type, size_value in sizes.items():
            if size_type.replace(sortkey_section, "") in SECTION_DICT.keys() or size_type in CATEGORY_LIST:
                data_list.append({'Component': component, 'Section': size_type, 'Size': size_value})
                #使用してるカテゴリの容量、使用率の計算（CodeFlash領域除く）
                capacity_name = 'Capacity' + size_type
                usagerate_name = 'UsageRate' + size_type
                if size_type == "<.text>" or size_type == "<.rodata>":
                    #CodeFlash領域の使用量の集計
                    codeflash_value += size_value
                elif capacity_name in CAPACITY_DICT:
                    #容量の列追加
                    data_list.append({'Component': component, 'Section': capacity_name, 'Size': CAPACITY_DICT[capacity_name]})
                    #使用率の計算、列追加
                    data_list.append({'Component': component, 'Section': usagerate_name, 'Size': size_value / CAPACITY_DICT[capacity_name] * 100})
        #CodeFlash領域の容量、使用率の計算
        capacity_name_codeflash = "Capacity<.CodeFlash> (= <.text> + <.rodata>)"
        usagerate_name_codeflash = "UsageRate<.CodeFlash> (= <.text> + <.rodata>)"
        #CodeFlashの容量の列追加
        data_list.append({'Component': component, 'Section': capacity_name_codeflash, 'Size': CAPACITY_DICT[capacity_name_codeflash]})
        #CodeFlashの使用率の計算、列追加
        data_list.append({'Component': component, 'Section': usagerate_name_codeflash, 'Size': codeflash_value / CAPACITY_DICT[capacity_name_codeflash] * 100})

    # DataFrameに変換
    df = pd.DataFrame(data_list)
#    pprint.pprint(df)

    # 'Section'を先頭行に移動
    df = df.pivot(index='Component', columns='Section', values='Size').reset_index()

    # カテゴリの容量の空白セルを埋める
    for col in df.columns:
        if col in CAPACITY_DICT.keys():
            df[col] = CAPACITY_DICT[col]
    # 空白セルを0で埋める
    df.fillna(0, inplace=True)

    #ソート用に付与したラベルの削除
    new_columns = []
    for col in df.columns:
        if sortkey_section in col:
            new_columns.append(col.replace(sortkey_section, ""))
        else:
            new_columns.append(col)
    df.columns = new_columns

    # DataFrameをExcelファイルに書き出し
    df.to_excel(output_file, sheet_name=sheet_name, index=False)

#セクションの使用量が一番左に並ぶよう、列名の先頭に付与するラベル
sortkey_section = ".section_"

args = sys.argv

json_files = ['EHVM_data.json', 'PE0VM0_data.json', 'PE1VM1_data.json', 'PE2VM2_data.json', 'PE3VM3_data.json']
# .mapファイルを読み込んで処理する

file_paths = [r"..\..\prj\Ren_U2A16_373_{}\EHVM\dst\EHVM.map".format(args[1]),
              r"..\..\prj\Ren_U2A16_373_{}\PE0VM0\dst\PE0VM0.map".format(args[1]),
              r"..\..\prj\Ren_U2A16_373_{}\PE1VM1\dst\PE1VM1.map".format(args[1]),              
              r"..\..\prj\Ren_U2A16_373_{}\PE2VM2\dst\PE2VM2.map".format(args[1]),
              r"..\..\prj\Ren_U2A16_373_{}\PE3VM3\dst\PE3VM3.map".format(args[1]) ]

sheet_names = ['EHVM', 'PE0VM0', 'PE1VM1', 'PE2VM2', 'PE3VM3']
output_files = ['Section_Size_EHVM.xlsx', 'Section_Size_PE0VM0.xlsx', 'Section_Size_PE1VM1.xlsx', 'Section_Size_PE2VM2.xlsx', 'Section_Size_PE3VM3.xlsx']
for json_file,file_path,sheet_name,output_file in zip(json_files, file_paths, sheet_names,output_files):
    map_file_analyze(json_file, file_path, sheet_name, output_file)
