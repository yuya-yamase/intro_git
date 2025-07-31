import os
import chardet
import re
import sys

if len(sys.argv) > 1:
    arg1 = sys.argv[1]
    print(f"引数として受け取った値: {arg1}")
else:
    print("引数が渡されていません。")

# 置換後の文字列
replace_value1 = arg1+":/"
replace_value2 = arg1+":\\\\"

# 対象ファイルリスト（相対パス）
filelist = [
    r"..\..\tool\MemAnalysis\SectionAnalysis.py",
    r"..\..\tool\MemAnalysis\Sub.py",
    r"..\..\src\DevRRPG\Tool\CombineMOT\config1.ini",
    r"..\..\src\DevRRPG\Tool\CombineMOT\config2.ini",
    r"..\..\src\DevRRPG\Tool\CombineMOT\config3.ini",
    r"..\..\src\DevRRPG\Tool\CombineMOT\config4.ini",
    r"..\..\src\DevRRPG\Tool\CombineMOT\config5.ini",
    r"..\..\src\DevRRPG\Tool\CombineMOT\config6.ini",
    r"..\..\src\DevRRPG\Tool\Converter\config1.ini",
    r"..\..\src\DevRRPG\Tool\Converter\config2.ini",
    r"..\..\src\DevRRPG\Tool\TS-WriterData\config1.ini",
    r"..\..\src\DevRRPG\Tool\TS-WriterData\config2.ini",
    r"..\..\src\DevRRPG\Tool\TS-WriterData\config3.ini",
    r"..\..\src\DevRRPG\Tool\TS-WriterData\config4.ini",
    r"..\..\src\DevRRPG\Tool\TS-WriterData\config5.ini",
    r"..\..\src\DevRRPG\Tool\TS-WriterData\config6.ini",
    r"..\..\src\DevRRPG\Tool\TS-WriterData\config7.ini"
]

def detect_encoding(filepath, sample_size=4096):
    with open(filepath, 'rb') as f:
        raw_data = f.read(sample_size)
    result = chardet.detect(raw_data)
    return result['encoding'] or 'utf-8'

def process_file(filepath):
    print(f"処理中: {filepath}")
    
    encoding = detect_encoding(filepath)

    with open(filepath, "r", encoding=encoding, errors="ignore") as f:
        lines = f.readlines()

    new_lines = []
    for line in lines:
        stripped = line.rstrip("\r\n")

        if stripped.strip() == "":
            # 空行 or スペースだけの行 → そのまま
            new_lines.append(line)
        else:
            # w:/ or w:\（大文字小文字問わず）を置換
            replaced = re.sub(r'w:/', replace_value1, stripped, flags=re.IGNORECASE)
            replaced = re.sub(r'w:\\', replace_value2, replaced, flags=re.IGNORECASE)
            new_lines.append(replaced + "\n")

    with open(filepath, "w", encoding=encoding, errors="ignore") as f:
        f.writelines(new_lines)

for path in filelist:
    if os.path.isfile(path):
        process_file(path)
    else:
        print(f"スキップ（存在しない）: {path}")

print("完了")
