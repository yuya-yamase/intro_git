# coding: utf-8
import configparser
import os
import sys
import bincopy
import zlib
import binascii
import Crypto.Util.Padding as PAD
from Crypto.Cipher import AES
from Crypto.Hash import CMAC, SHA256
from Crypto.PublicKey import RSA
from Crypto.Signature import pkcs1_15, pss
from base64 import b64decode, b64encode

# 複数の Motorola S-record(S3) ファイルを結合する
def s3rec_to_plain():
    if config.getboolean("IN_FILE", "StartFile"):
        data = "S00F0000686F7374202020202020000072" + "\n"
        # 出力ファイル初期化
        with open(config["PLAINTEXT"]["PlainRunFile"], "w") as out_file:
            pass
    else:
        data = ""

    with open(config["IN_FILE"]["SrecFile"], "r") as srec:
        for item in srec:
            if item.startswith("S00"):
                pass
            elif item.startswith("S50"):
                pass
            elif item.startswith("S70"):
                pass
            else:
                data += item

    if config.getboolean("IN_FILE", "EndFile"):
        data += "S70500000000FA" + "\n"

    with open(config["PLAINTEXT"]["PlainRunFile"], "a") as out_file:
        out_file.write(data)

def main():
    for i in range(1, 50):
        ini_file = "config" + str(i) + ".ini"

        if os.path.isfile(ini_file) == False:
            break

        config.read(ini_file, "UTF-8")
        print("===== Combine :", ini_file, "(", config["IN_FILE"]["SrecFile"], ")")

        s3rec_to_plain()

config = configparser.ConfigParser()
main()
