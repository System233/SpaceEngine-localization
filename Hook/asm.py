# coding:utf-8
# Asm÷ÿ∂®Œª
import re
asmfile="Hook.in.asm"
fin=open(asmfile,'rb')
data=fin.read()
#print data
loc_map=set()
def repl(m):
    loc_map.add(m.group(3))
    #print m.group(1)
    return "%s loc_%s"%(m.group(1),m.group(3))
 
data=re.sub(r"(j\w+)\s+(SpaceEngine\.exe\+)(\w+)",repl,data)
for i in loc_map:
    m="SpaceEngine.exe+%s"%i
    data=data.replace(m,"\t\t\t\tloc_%s:\n%s"%(i,m))
    
call_map=set()
def repl_call(m):
    call_map.add(m.group(1))
    return "call [call_%s]"%(m.group(1))
data=re.sub(r"call\s+SpaceEngine\.exe\+(\w+)",repl_call,data)
mov_map=set()
def repl_mov(m):
    mov_map.add(m.group(2))
    return "mov %s,[gol_%s]"%(m.group(1),m.group(2))
data=re.sub(r"mov\s+(\w+)\s*,\s*SpaceEngine\.exe\+(\w+)",repl_mov,data)
#movp_map=set()
def repl_movp(m):
    mov_map.add(m.group(2))
    return "mov %s,[gol_%s]\n\t\t\t\t\tmov %s,[%s]"%(m.group(1),m.group(2),m.group(1),m.group(1))
data=re.sub(r"mov\s+(e\w+)\s*,\s*\[\s*SpaceEngine\.exe\+(\w+)\s*\]",repl_movp,data)
movx_map=set()
def repl_movx(m):
    mov_map.add(m.group(3))
    return "mov eax,[gol_%s]\n\t\t\t\t\t%s %s,[eax]"%(m.group(3),m.group(1),m.group(2))
data=re.sub(r"(mov\w+)\s+(\w+)\s*,\s*\[\s*SpaceEngine\.exe\+(\w+)\s*\]",repl_movp,data)
def repl_movx(m):
    mov_map.add(m.group(2))
    return "mov eax,[gol_%s]\n\t\t\t\t\t%s %s,[eax]"%(m.group(2),m.group(1),m.group(3))
data=re.sub(r"(mov\w+)\s+\[\s*SpaceEngine\.exe\+(\w+)\s*\]\s*,\s*(\w+)",repl_movx,data)
#with open("Hook.out.asm")
print data