#!/usr/bin/python2.7
# -*- coding: utf-8 -*-  
import re, json
import locale
locale.setlocale(locale.LC_COLLATE, 'CHS')#Windowsœﬁ∂®°£LX:'zh_CN.UTF8'

def pp(fmt,*args):
    try:
        print fmt%(args)
    except:
        pass
def readx(file):
    map={}
    with open(file,'rb') as fp:
        p=re.compile(r'"([^\"]+)"\s*"([^\"]+)"')
        for line in fp:
            m=p.match(line.decode('utf-8'))
            if m:
                #pp ("line:%sAAA",m.group(2))
                #map.append((m.group(1),m.group(2)))
                map[m.group(1)]=m.group(2)
    return map
map=readx('chs-gui2.cfg')
chs=set()
for k,v in map.items():
    chs.update(v)
cfg=json.loads(open("localization.json").read().decode('utf-8'))
cfg_map=cfg['Language']['chs']['texture'][1]['map']
cfg_set=set()
for i in cfg_map:
    cfg_set.update(i)
for i in cfg_set:
    if i in chs:
        chs.remove(i)
chs=list(chs)
chs.sort(lambda x, y: locale.strcoll(x, y))
print "".join(chs)