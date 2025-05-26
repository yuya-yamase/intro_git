import os
import json
import tkinter as tk
import subprocess
import sys

def find_files_and_folders(base_path, extensions, include_pattern, exclude_pattern):
    path_list = []
    folders_to_include = set()

    for root, _, files in os.walk(base_path):
        for file in files:
            if any(file.endswith(ext) for ext in extensions):
                relative_file_path = os.path.relpath(os.path.join(root, file), base_path).replace('\\', '/')
                path_list.append(relative_file_path)
                
                # Add all parent directories to the set
                relative_folder_path = os.path.relpath(root, base_path).replace('\\', '/')
                while relative_folder_path:
                    folders_to_include.add(relative_folder_path)
                    relative_folder_path = os.path.dirname(relative_folder_path)

    # Include folders that contain relevant files
    path_list.extend(folders_to_include)

    filtered_folders = [folder for folder in path_list if any(pattern in folder for pattern in include_pattern) and all(pattern not in folder for pattern in exclude_pattern) or "config_CDC_" not in folder]

    exclude_elements = ["u2a6", "u2a8"]
    # 除外した後のリストを作成
    filtered_folders = [item for item in filtered_folders if not any(sub in item for sub in exclude_elements)]

    # Sort paths alphabetically
    return sorted(filtered_folders)

def create_json(VM_keyword, path_list):
    updated_list = [VM_keyword + '/' + s for s in path_list]

    component_list = [VM_keyword] + updated_list
    json_data = {
        "COMPONENT_LIST": component_list
    }
    return json_data

def save_to_json(json_data, output_file):
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(json_data, f, ensure_ascii=False, indent=4)

def save_selection():
    global selected_variation
    selected_variation = var.get()
    root.destroy()

def analysis_file(base_path, existing_json_file, include_pattern, options, VM_keyword):
    extensions = ['.c', '.850', '.a']

    path_list = find_files_and_folders(base_path, extensions, include_pattern, options)

    # 既存のJSONファイルを読み込む
    with open(existing_json_file, 'r') as f:
        existing_data = json.load(f)
    json_data = create_json(VM_keyword, path_list)
    existing_data.update(json_data)

    # 変更したデータを同じJSONファイルに書き込む（上書き）
    with open(existing_json_file, 'w') as f:
        json.dump(existing_data, f, indent=4)
    f.close()


args = sys.argv

## GUI 選択ターブル
options = ["CDC_1SUS", "CDC_1SJP", "CDC_1SOT", "CDC_1MUS", "CDC_1MJP", "CDC_1MOT"]

"""
root = tk.Tk()
root.title("仕向け選択")

var = tk.StringVar()
var.set(options[0])  # デフォルトの選択

for option in options:
    radio_button = tk.Radiobutton(root, text=option, variable=var, value=option)
    radio_button.pack(anchor=tk.W)

button = tk.Button(root, text="決定", command=save_selection)
button.pack()

root.mainloop()
"""
selected_variation = args[1]
print(f"選択されたオプション: {selected_variation}")
include_pattern = [selected_variation[:-2],selected_variation]
options.remove(selected_variation)
#print(f"フィルタオプション(include): {include_pattern}")
#print(f"フィルタオプション(除外): {options}")

# 使用するフォルダパスと拡張子リストを指定してください
base_paths = ['W:\src\EHVM',  # 例: '/path/to/your/folder'
             'W:\src\PE0VM0',
             'W:\src\PE1VM1',
             'W:\src\PE2VM2',
             'W:\src\PE3VM3'
            ]
VM_keywords = ['EHVM','PE0VM0','PE1VM1','PE2VM2','PE3VM3']
# 既存のJSONファイルのパス
existing_json_files = ['./EHVM_data.json',
                      './PE0VM0_data.json',
                      './PE1VM1_data.json',
                      './PE2VM2_data.json',
                      './PE3VM3_data.json'
                    ]

for path,json_file,VM_keyword in zip(base_paths, existing_json_files,VM_keywords):
    analysis_file(path, json_file, include_pattern, options, VM_keyword)


result = subprocess.run(['python', "Sub.py" , selected_variation])

if result.returncode == 0:
    print("SectionAnalysis Success")