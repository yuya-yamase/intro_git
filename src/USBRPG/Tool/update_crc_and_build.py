import sys
import zlib
import re
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
TEMPLATE_PATH = os.path.join(SCRIPT_DIR, "rh850u2a16_usbrpg.c.template")
USBRPG_C_PATH = os.path.join(SCRIPT_DIR, "..", "config", "rh850u2a16_usbrpg.c")

# CRC32計算関数
def calc_crc32(input_file):
    """Calculate CRC32 for the given binary file"""
    with open(input_file, "rb") as in_file:
        crc = zlib.crc32(in_file.read())
        crc_hex = str(format(crc, "08x"))

    return crc_hex

def reverse_byte_order(crc_hex):
    """Reverse byte order for big-endian (暫定処置)"""
    # "12345678" -> "78563412"
    if len(crc_hex) != 8:
        return crc_hex
    return crc_hex[6:8] + crc_hex[4:6] + crc_hex[2:4] + crc_hex[0:2]

def update_crc_in_c_file(crc_hex, big_endian=False):
    """Update CRC32 value in the C file from template"""
    try:
        # ビッグエンディアン指定時はバイト順を逆転
        if big_endian:
            crc_hex_output = reverse_byte_order(crc_hex)
            endian_note = " (Big-Endian - 暫定処置)"
        else:
            crc_hex_output = crc_hex
            endian_note = " (Little-Endian)"
        
        # Read template
        with open(TEMPLATE_PATH, "r", encoding="utf-8") as f:
            content = f.read()
        
        # Replace {{CRC32}} placeholder
        new_content = content.replace("{{CRC32}}", crc_hex_output.upper())
        
        # Write to actual C file (in config directory)
        with open(USBRPG_C_PATH, "w", encoding="utf-8") as f:
            f.write(new_content)
        
        print(f"CRC32 updated in {USBRPG_C_PATH}: 0x{crc_hex_output.upper()}{endian_note}")
        return True
        
    except FileNotFoundError as e:
        print(f"Error: Template file not found: {TEMPLATE_PATH}")
        return False
    except Exception as e:
        print(f"Error updating C file: {e}")
        return False

if __name__ == "__main__":
    if len(sys.argv) < 2 or len(sys.argv) > 3:
        print("Usage: python update_crc_and_build.py <binary_file> [--big-endian]")
        print("  --big-endian: バイト順を逆転してビッグエンディアン形式で出力 (暫定処置)")
        sys.exit(1)
    
    binary_file = sys.argv[1]
    big_endian = "--big-endian" in sys.argv
    
    # CRC32を計算
    print(f"Calculating CRC32 for: {binary_file}")
    crc_hex = calc_crc32(binary_file)
    
    # C配列を更新
    if update_crc_in_c_file(crc_hex, big_endian):
        print("CRC32 update completed successfully")
    else:
        print("CRC32 update failed")
        sys.exit(1)
