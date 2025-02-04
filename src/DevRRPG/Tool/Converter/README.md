## 出来ること
Motorola S-record を INPUT にして、以下を生成する。

   | No | 出力ファイル                           | Reprog Canoeへの<BR>INPUT 対象 | 備考                                                                    |
   |----|----------------------------------------|--------------------------------|-------------------------------------------------------------------------|
   | 1  | 平文ファイル 【binary】                | ○                             | －                                                                      |
   | 2  | 平文ファイル 【text】                  | －                             | －                                                                      |
   | 3  | 暗号ファイル 【binary】                | ◯                             | No.1 を AES128 CBC 暗号化したもの<BR>PKCS#7 Padding 有/無は選択可       |
   | 4  | 暗号ファイル 【text】                  | －                             | －                                                                      |
   | 5  | 圧縮ファイル 【binary】                | －                             | No.1 を emCompress 圧縮したもの                                         |
   | 6  | 圧縮転送ファイル 【binary】            | ○                             | No.5 の先頭 16byte にサイズを追加したもの                               |
   | 7  | 圧縮転送ファイル 【text】              | －                             | －                                                                      |
   | 8  | 暗号圧縮転送ファイル 【binary】        | ○                             | No.6 を AES128 CBC 暗号化したもの<BR>PKCS#7 Padding 有/無は選択可だけど、無だと失敗する可能性大<BR>(サイズが 16byte 単位でないと暗号化できない) |
   | 9  | 暗号圧縮転送ファイル 【text】          | －                             | －                                                                      |
   | 10 | CRC32 ファイル 【binary】              | ○                             | No.1 を CRC32 算出したもの                                              |
   | 11 | CMAC ファイル 【binary】               | ○                             | No.1 を AES128 CMAC 算出したもの                                        |
   | 12 | 署名 ファイル 【binary】               | ○                             | No.1 をデジタル署名したもの<BR>アルゴリズム PKCS1_v1_5 / PSS は選択可   |


## 環境準備
 1. python 準備(https://1st.aubswdev.com/epw/boards/107/topics/1964 を参照)

 1. 以下のパッケージが追加で必要かも。
    ~~~bash
    > pip install bincopy
    > pip install pycryptodome
    ~~~


## 使い方
 1. configX.ini に各種設定を行う( X は数字の 1 から連番で)。

 1. 以下のコマンドで実行
    ~~~bash
    > python ReprogTargetConverter.py
    ~~~

## 補足
RSA 方式のデジタル署名用の秘密鍵(署名生成キー)と公開鍵(署名検証キー)は、cygwin とかで OpenSSL 使って作成可能です。

~~~bash
# 2048ビットの秘密鍵(binary)作成
> openssl genrsa 2048 > private-key.pem
   or
# 3072ビットの秘密鍵(binary)作成
> openssl genrsa 3072 > private-key.pem

# 秘密鍵の binary → text 変換
> openssl rsa -in private-key.pem -text -out private-key.txt

# 公開鍵(binary)作成
> openssl rsa -in private-key.pem -pubout -out public-key.pem

# 公開鍵の binary → text 変換
> openssl rsa -pubin -in public-key.pem -text -out public-key.txt
~~~


