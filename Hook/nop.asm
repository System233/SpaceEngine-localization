bytes   sequence                            encoding

 1      90H                                 NOP
 2      66 90H                              66 NOP
 3      0F 1F 00H                           NOP DWORD ptr [EAX]
 4      0F 1F 40 00H                        NOP DWORD ptr [EAX + 00H]
 5      0F 1F 44 00 00H                     NOP DWORD ptr [EAX + EAX*1 + 00H]
 6      66 0F 1F 44 00 00H                  NOP DWORD ptr [AX + AX*1 + 00H]
 7      0F 1F 80 00 00 00 00H               NOP DWORD ptr [EAX + 00000000H]
 8      0F 1F 84 00 00 00 00 00H            NOP DWORD ptr [AX + AX*1 + 00000000H]
 9      66 0F 1F 84 00 00 00 00 00H         NOP DWORD ptr [AX + AX*1 + 00000000H]
 10     66 66 0F 1F 84 00 00 00 00 00H      NOP DWORD ptr [AX + AX*1 + 00000000H] 
 11     66 66 66 0F 1F 84 00 00 00 00 00H   NOP DWORD ptr [AX + AX*1 + 00000000H]