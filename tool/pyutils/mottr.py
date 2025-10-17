# Motorola S-Format *.Mot Trimmer
# coding: utf-8
import os
import sys
import bincopy

def main():

    data = ""
    args = sys.argv
    with open(args[1], "r") as srec:
        for item in srec:
            if item.startswith("S00"):
                pass
            elif item.startswith("S50"):
                pass
            elif item.startswith("S70"):
                pass
            else:
                data += item

    with open(args[2], "a") as out_file:
        out_file.write(data)

main()
