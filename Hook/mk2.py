import re

def repl(data):
    data=re.sub(r"\s+"," ",data)
    data=re.sub(r"(\w{2})(?!\s)",lambda m:m.group(1)+' ',data).strip(' ')
    data='\\x'+re.sub(r"\s",r"\\x",data)
    while data:
        print '"%s"'%data[:64]
        data=data[64:]
while True:
    data=raw_input(">")
    repl(data)