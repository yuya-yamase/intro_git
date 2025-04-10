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

# Motorola S-record(S3) ファイルを以下のファイルに変換する
#  - Text(改行あり)
#  - Binary
def s3rec_to_plain():
    srec = bincopy.BinFile(config["IN_FILE"]["SrecFile"]);
#    print(srec.as_srec())
#    print(srec.as_ti_txt())

    data = ""
    addr = 0
    for item in srec.as_ti_txt().replace(" ", "").split():
        if "@" in item:
            tmp = int("0x" + item.replace("@", ""), 0)
            if addr != 0 and addr < tmp:
                for i in range(tmp - addr):
                    data +="FF" # 0xFF で1バイトずつパディング
            addr = tmp
        elif "q" in item:
            pass
        else:
            data += item
            addr += len(item) // 2;

    with open(config["PLAINTEXT"]["PlainTextFile"], "w") as out_file:
        for i in range(0, len(data), 32):
            out_file.write(data[i : i + 32] + "\n")

    with open(config["PLAINTEXT"]["PlainBinFile"], "wb") as out_file:
        out_file.write(binascii.unhexlify(data))


# PlainBinary から CRC を算出する
def calc_crc():
    with open(config["PLAINTEXT"]["PlainBinFile"], "rb") as in_file:
        crc = zlib.crc32(in_file.read())
        crc = str(format(crc, "08x"))

    print(" CRC  :", crc)

    with open(config["CRC"]["CrcBinFile"], "wb") as out_file:
        out_file.write(bytes.fromhex(crc))


# PlainBinary から CMAC を算出する
def calc_cmac():
    with open(config["PLAINTEXT"]["PlainBinFile"], "rb") as in_file:
        cobj = CMAC.new(binascii.unhexlify(config["CMAC"]["KEY"]), ciphermod=AES)
        cobj.update(in_file.read())

    print(" CMAC :", cobj.hexdigest())

    with open(config["CMAC"]["CmacBinFile"], "wb") as out_file:
        out_file.write(bytes.fromhex(cobj.hexdigest()))


# PlainBinary から署名を算出する
def calc_signature():
    with open(config["SIGNATURE"]["PrivateKey"], "rb") as in_file:
        private_key = RSA.import_key(in_file.read())

    with open(config["PLAINTEXT"]["PlainBinFile"], "rb") as in_file:
        data = in_file.read()

    # アルゴリズムに応じた署名作成
    h1 = SHA256.new(data)
    if config["SIGNATURE"]["Algorithm"] == "PKCS1_v1_5":
        sig = pkcs1_15.new(private_key).sign(h1)
    elif config["SIGNATURE"]["Algorithm"] == "PSS":
        sig = pss.new(private_key).sign(h1)
    else:
        print("Error : signature failed( algorithm =", config["SIGNATURE"]["Algorithm"], ")", file=sys.stderr)
        sys.exit(1)

    # 念のため公開鍵使った署名検証
    h2 = SHA256.new(data)
    try:
        with open(config["SIGNATURE"]["PublicKey"], "rb") as in_file:
            public_key = RSA.import_key(in_file.read())

        if config["SIGNATURE"]["Algorithm"] == "PKCS1_v1_5":
            pkcs1_15.new(public_key).verify(h2, sig)
        else:
            pss.new(public_key).verify(h2, sig)

    except ValueError:
        print("Error : signature failed", file=sys.stderr)
        sys.exit(1)

    print(" SIGN :", sig.hex())

    with open(config["SIGNATURE"]["SigBinFile"], "wb") as out_file:
        out_file.write(sig)

# PlainBinary を圧縮する
def compress():
    command = config["COMPRESS"]["emCompressUtilExe"]
    command += " "
    command += "-ws=" + config["COMPRESS"]["emCompressOpt_ws"]
    command += " "
    command += "-lc=" + config["COMPRESS"]["emCompressOpt_lc"]
    command += " "
    command += "-lp=" + config["COMPRESS"]["emCompressOpt_lp"]
    command += " "
    command += "-pb=" + config["COMPRESS"]["emCompressOpt_pb"]
    command += " "
    command += config["PLAINTEXT"]["PlainBinFile"]
    command += " "
    command += config["COMPRESS"]["CompBinFile"]

    print(" COMPRESS :", command)
    os.system(command)

    #     | +0 | +1 | +2 | +3 | +4 | +5 | +6 | +7 | +8 | +9 | +A | +B | +C | +D | +E | +F |
    #     ---------------------------------------------------------------------------------
    # +00 | 圧縮データサイズ  |                  Reserved                                 |
    #     ---------------------------------------------------------------------------------
    # +10 |                               圧縮データ                                      |
    #     |                                   :                                           |
    # +xx |                                   :                                           |
    #     ---------------------------------------------------------------------------------
    with open(config["COMPRESS"]["CompSizePlainBinFile"], "wb") as out_file:
        # 先頭 16byte の書き込み
        # zero padding
        out_file.write(os.path.getsize(config["COMPRESS"]["CompBinFile"]).to_bytes(4, "big"))
        pad = 0
        out_file.write(pad.to_bytes(12, "big"))
        # pkcs#7 padding
        # size = os.path.getsize(config["COMPRESS"]["CompBinFile"]).to_bytes(4, "big")
        # size_pad = PAD.pad(size, 16, "pkcs7")
        # out_file.write(size_pad)

        # 圧縮データを書き込み
        with open(config["COMPRESS"]["CompBinFile"], "rb") as in_file:
            out_file.write(in_file.read())

    with open(config["COMPRESS"]["CompSizePlainBinFile"], "rb") as in_file:
        compdata = in_file.read()
        compdatahex = compdata.hex()

        with open(config["COMPRESS"]["CompSizePlainTextFile"], "w") as out_file:
            for i in range(0, len(compdatahex), 32):
                out_file.write(compdatahex[i : i + 32] + "\n")

# 暗号化して､以下のファイルを出力する
#  - Text(改行あり)
#  - Binary
def encryption():
    in_keyword  = [["PLAINTEXT", "PlainBinFile"],
                   ["COMPRESS",  "CompSizePlainBinFile"]]
    out_keyword = [["ENCRYPT",   "CipherBinFile",         "CipherTextFile"        ],
                   ["COMPRESS",  "CompSizeCipherBinFile", "CompSizeCipherTextFile"]]

    loop_max = 1
    if config.getboolean("COMPRESS", "emCompress"):
        loop_max = 2

    for i in range(loop_max):
        if config.getboolean("ENCRYPT", "PKCS7PAD") == False:
            print(" Encryption(PKCS#7 padding : off)  InputFile =", config[in_keyword[i][0]][in_keyword[i][1]])
            size = os.path.getsize(config[in_keyword[i][0]][in_keyword[i][1]])
            if size % AES.block_size != 0:
                # PKCS#7 padding 無効 & サイズが 16byte アラインでない時はエラー
                print("Error : encryption failed( PKCS#7PAD = False, InputFileSize =", size, config[in_keyword[i][0]][in_keyword[i][1]], ")", file=sys.stderr)
                continue
        else:
            print(" Encryption(PKCS#7 padding : on) InputFile =", config[in_keyword[i][0]][in_keyword[i][1]])

        with open(config[in_keyword[i][0]][in_keyword[i][1]], "rb") as in_file:
            data = in_file.read()
            if config.getboolean("ENCRYPT", "PKCS7PAD") == True:
                # PKCS#7 padding
                data = PAD.pad(data, 16, "pkcs7")

        # 暗号化
        cipher = AES.new(binascii.unhexlify(config["ENCRYPT"]["KEY"]), AES.MODE_CBC, binascii.unhexlify(config["ENCRYPT"]["IV"]))
        ciphertext = cipher.encrypt(data)
        ciphertexthex = ciphertext.hex()

        with open(config[out_keyword[i][0]][out_keyword[i][1]], "wb") as out_file:
            out_file.write(ciphertext)

        with open(config[out_keyword[i][0]][out_keyword[i][2]], "w") as out_file:
            for i in range(0, len(ciphertexthex), 32):
                out_file.write(ciphertexthex[i : i + 32] + "\n")

def main():
    for i in range(1, 50):
        ini_file = "config" + str(i) + ".ini"

        if os.path.isfile(ini_file) == False:
            break

        config.read(ini_file, "UTF-8")
        print("===== Convert :", ini_file, "(", config["IN_FILE"]["SrecFile"], ")")

        s3rec_to_plain()

        if config.getboolean("CRC", "Calc"):
            calc_crc()

        if config.getboolean("CMAC", "Calc"):
            calc_cmac()

        if config.getboolean("SIGNATURE", "Calc"):
            calc_signature()

        if config.getboolean("COMPRESS", "emCompress"):
            compress()

        if config.getboolean("ENCRYPT", "CBC"):
            encryption()

config = configparser.ConfigParser()
main()
