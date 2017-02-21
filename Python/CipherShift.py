shift = 2
encrypted = "g fmnc wms bgblr rpylqjyrc gr zw fylb. rfyrq ufyr amknsrcpq ypc dmp. bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm jmle. sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. lmu ynnjw ml rfc spj."
unencrypted = []
for letter in encrypted:
    code = ord(letter)
    if code > (122 - shift):
        code = code - 26
    elif code == 32:
        unencrypted.append(" ")
        continue
    elif code < 97:
        unencrypted.append(letter)
        continue
    code += shift
    unencrypted.append(chr(code))
new_string = "".join(unencrypted)
print(new_string)
