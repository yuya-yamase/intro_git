アプリの個別セクションがある場合、該当VMの*_data.jsonファイルの<SECTION_DICT>に、セクション名とそのカテゴリの追加をお願いします。

w_sb.batを実行する
pip installを使って、不足するLibraryをインストール
 - re
 - defaultdict
 - pandas
 - tkinter

MemAnalysisフォルダに移動し、python命令を実施する。
python SectionAnalysis.py

6仕向けから解析必要な仕向けを選択する。（事前にビルド完了してください）
Section_Size_EHVM/PE0VM0/PE1VM1/PE2VM2/PE3VM3.xlsxファイルが生成されます。
- xlsxファイル：
 - 左からの列：LDファイル内定義した各sectionの使用量
 - 右からの列：下記のようなカテゴリの合計値
　- "<.text>",
　- "<.rodata>",
　- "<.Local_RAM0>",
　- "<.Local_RAM1>",
　- "<.Local_RAM2>",
　- "<.Local_RAM3>",
　- "<.Local_RAM_SELF>",
　- "<.Cluster_RAM0>",
　- "<.Cluster_RAM1>",
　- "<.Cluster_RAM2>",
　- "<.Cluster_RAM2_SHARE>",
　- "<.Retention_RAM>",
