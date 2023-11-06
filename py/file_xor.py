# 文件字节异或加密

def handle(file, key=0x34):
    with open(file, 'r+b') as file:
        while True:
            byte = file.read(1)
            if not byte:
                break
            file.seek(-1, 1)
            num = int.from_bytes(byte)
            file.write((num ^ key).to_bytes())


handle('CAN.zip')
print('Done.')
