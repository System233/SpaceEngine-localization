SpaceEngine.exe+217580 - 55                    - push ebp { 函数起始 };UNICODE方案不可行,改UTF8方案
SpaceEngine.exe+217581 - 8B EC                 - mov ebp,esp
SpaceEngine.exe+217583 - 83 E4 F0              - and esp,-10 { 240 }
SpaceEngine.exe+217586 - 83 EC 48              - sub esp,48 { 72 }
SpaceEngine.exe+217589 - 80 7D 0C 00           - cmp byte ptr [ebp+0C],00 { 0 };参数bool
SpaceEngine.exe+21758D - 56                    - push esi
SpaceEngine.exe+21758E - 57                    - push edi
SpaceEngine.exe+21758F - F3 0F11 5C 24 28      - movss [esp+28],xmm3
SpaceEngine.exe+217595 - 8B F9                 - mov edi,ecx
SpaceEngine.exe+217597 - F3 0F11 54 24 24      - movss [esp+24],xmm2
SpaceEngine.exe+21759D - 74 2A                 - je SpaceEngine.exe+2175C9
SpaceEngine.exe+21759F - 8B 87 D0000000        - mov eax,[edi+000000D0]
SpaceEngine.exe+2175A5 - F3 0F11 8F BC000000   - movss [edi+000000BC],xmm1
SpaceEngine.exe+2175AD - 66 0F6E 44 87 70      - movd xmm0,[edi+eax*4+70]
SpaceEngine.exe+2175B3 - 0F5B C0               - cvtdq2ps xmm0,xmm0
SpaceEngine.exe+2175B6 - F3 0F59 47 14         - mulss xmm0,[edi+14]
SpaceEngine.exe+2175BB - F3 0F5C D0            - subss xmm2,xmm0
SpaceEngine.exe+2175BF - F3 0F11 97 C0000000   - movss [edi+000000C0],xmm2
SpaceEngine.exe+2175C7 - EB 3E                 - jmp SpaceEngine.exe+217607
SpaceEngine.exe+2175C9 - 0F28 C1               - movaps xmm0,xmm1
SpaceEngine.exe+2175CC - E8 4FD8E1FF           - call SpaceEngine.exe+34E20
SpaceEngine.exe+2175D1 - 8B 87 D0000000        - mov eax,[edi+000000D0]
SpaceEngine.exe+2175D7 - F3 0F10 4C 24 24      - movss xmm1,[esp+24]
SpaceEngine.exe+2175DD - F3 0F11 87 BC000000   - movss [edi+000000BC],xmm0
SpaceEngine.exe+2175E5 - 66 0F6E 44 87 70      - movd xmm0,[edi+eax*4+70]
SpaceEngine.exe+2175EB - 0F5B C0               - cvtdq2ps xmm0,xmm0
SpaceEngine.exe+2175EE - F3 0F59 47 14         - mulss xmm0,[edi+14]
SpaceEngine.exe+2175F3 - F3 0F5C C8            - subss xmm1,xmm0
SpaceEngine.exe+2175F7 - 0F28 C1               - movaps xmm0,xmm1
SpaceEngine.exe+2175FA - E8 21D8E1FF           - call SpaceEngine.exe+34E20
SpaceEngine.exe+2175FF - F3 0F11 87 C0000000   - movss [edi+000000C0],xmm0
SpaceEngine.exe+217607 - 0F10 87 A8000000      - movups xmm0,[edi+000000A8]
SpaceEngine.exe+21760E - 8D 44 24 30           - lea eax,[esp+30]
SpaceEngine.exe+217612 - 8B 75 08              - mov esi,[ebp+08]; { 取得字符串参数 }
SpaceEngine.exe+217615 - F3 0F10 B7 BC000000   - movss xmm6,[edi+000000BC]
SpaceEngine.exe+21761D - B9 E090D200           - mov ecx,SpaceEngine.exe+4F90E0 { [00000566] }
SpaceEngine.exe+217622 - F3 0F10 BF C0000000   - movss xmm7,[edi+000000C0]
SpaceEngine.exe+21762A - 50                    - push eax
SpaceEngine.exe+21762B - F3 0F11 74 24 18      - movss [esp+18],xmm6
SpaceEngine.exe+217631 - F3 0F11 7C 24 14      - movss [esp+14],xmm7
SpaceEngine.exe+217637 - 0F11 44 24 34         - movups [esp+34],xmm0
SpaceEngine.exe+21763C - E8 DF5DF9FF           - call SpaceEngine.exe+1AD420
SpaceEngine.exe+217641 - 8B D6                 - mov edx,esi;mov edx,esi
SpaceEngine.exe+217643 - 8A 02                 - mov ax,[edx];mov al,[edx];<<<===Decode(esi)
SpaceEngine.exe+217645 - 88 44 24 0F           - ;mov [esp+0F],al
SpaceEngine.exe+217649 - 84 C0                 - test ax,ax;test al,al
SpaceEngine.exe+21764B - 0F84 F7080000         - je SpaceEngine.exe+217F48
SpaceEngine.exe+217651 - F3 0F10 0D 447EBD00   - movss xmm1,[SpaceEngine.exe+3A7E44] { [0.50] }
SpaceEngine.exe+217659 - F3 0F10 1D 087FBD00   - movss xmm3,[SpaceEngine.exe+3A7F08] { [0.75] }
SpaceEngine.exe+217661 - F3 0F10 25 348EBD00   - movss xmm4,[SpaceEngine.exe+3A8E34] { [255.00] }
SpaceEngine.exe+217669 - 0F1F 80 00000000      - nop [eax+00000000];填充指令
SpaceEngine.exe+217670 - 46                    - inc esi;循环头
SpaceEngine.exe+217671 - 8B CE                 - mov ecx,esi
SpaceEngine.exe+217673 - 89 74 24 24           - mov [esp+24],esi
SpaceEngine.exe+217677 - 2B CA                 - sub ecx,edx;取得下标
SpaceEngine.exe+217679 - 0FB6 D0               - movzx edx,ax;movzx edx,al
SpaceEngine.exe+21767C - 89 54 24 2C           - mov [esp+2C],edx;不明,待删X;可用变量位置
SpaceEngine.exe+217680 - 8D 42 FF              - lea eax,[edx-01];国际惯例
SpaceEngine.exe+217683 - 83 F8 0E              - cmp eax,0E { 14 }
SpaceEngine.exe+217686 - 0F87 34030000         - ja SpaceEngine.exe+2179C0;如果大于0xE default
SpaceEngine.exe+21768C - FF 24 85 507FA400     - jmp dword ptr [eax*4+SpaceEngine.exe+217F50];switch跳转表
SpaceEngine.exe+217693 - 8B 47 24              - mov eax,[edi+24];取得字体大小
SpaceEngine.exe+217696 - 83 F8 02              - cmp eax,02 { 2 }
SpaceEngine.exe+217699 - 7D 04                 - jnl SpaceEngine.exe+21769F
SpaceEngine.exe+21769B - 40                    - inc eax
SpaceEngine.exe+21769C - 89 47 24              - mov [edi+24],eax
SpaceEngine.exe+21769F - 80 7D 0C 00           - cmp byte ptr [ebp+0C],00 { 0 };参数bool
SpaceEngine.exe+2176A3 - 0F85 8E080000         - jne SpaceEngine.exe+217F37
SpaceEngine.exe+2176A9 - F3 0F58 F1            - addss xmm6,xmm1
SpaceEngine.exe+2176AD - 0F28 C6               - movaps xmm0,xmm6
SpaceEngine.exe+2176B0 - E8 6BD7E1FF           - call SpaceEngine.exe+34E20
SpaceEngine.exe+2176B5 - 0F28 F0               - movaps xmm6,xmm0
SpaceEngine.exe+2176B8 - E9 56080000           - jmp SpaceEngine.exe+217F13
SpaceEngine.exe+2176BD - 8B 47 24              - mov eax,[edi+24]
SpaceEngine.exe+2176C0 - 85 C0                 - test eax,eax
SpaceEngine.exe+2176C2 - 7E DB                 - jle SpaceEngine.exe+21769F
SpaceEngine.exe+2176C4 - 48                    - dec eax
SpaceEngine.exe+2176C5 - EB D5                 - jmp SpaceEngine.exe+21769C
SpaceEngine.exe+2176C7 - 80 7F 19 00           - cmp byte ptr [edi+19],00 { 0 }
SpaceEngine.exe+2176CB - C7 87 CC000000 00000000 - mov [edi+000000CC],00000000 { 0 }
SpaceEngine.exe+2176D5 - C7 47 20 FFFFFFFF     - mov [edi+20],FFFFFFFF { -1 }
SpaceEngine.exe+2176DC - C7 47 1C FFFFFFFF     - mov [edi+1C],FFFFFFFF { -1 }
SpaceEngine.exe+2176E3 - C7 87 D0000000 00000000 - mov [edi+000000D0],00000000 { 0 };字体宽度
SpaceEngine.exe+2176ED - C7 47 10 0000403F     - mov [edi+10],3F400000 { 0.75 }
SpaceEngine.exe+2176F4 - C7 47 14 0000403F     - mov [edi+14],3F400000 { 0.75 }
SpaceEngine.exe+2176FB - C7 87 D4000000 00008041 - mov [edi+000000D4],41800000 { 16.00 }
SpaceEngine.exe+217705 - C7 07 00005841        - mov [edi],41580000 { 13.50 }
SpaceEngine.exe+21770B - 74 0A                 - je SpaceEngine.exe+217717
SpaceEngine.exe+21770D - C7 87 D0000000 01000000 - mov [edi+000000D0],00000001 { 1 }
SpaceEngine.exe+217717 - 8B 87 D0000000        - mov eax,[edi+000000D0]
SpaceEngine.exe+21771D - C1 E0 04              - shl eax,04 { 4 } ;<<-???????????????
SpaceEngine.exe+217720 - 0F10 84 38 E4180000   - movups xmm0,[eax+edi+000018E4]
SpaceEngine.exe+217728 - 0F11 87 94000000      - movups [edi+00000094],xmm0
SpaceEngine.exe+21772F - E9 6BFFFFFF           - jmp SpaceEngine.exe+21769F
SpaceEngine.exe+217734 - 80 7F 18 00           - cmp byte ptr [edi+18],00 { 0 }
SpaceEngine.exe+217738 - C7 87 CC000000 01000000 - mov [edi+000000CC],00000001 { 1 }
SpaceEngine.exe+217742 - C7 47 20 FFFFFFFF     - mov [edi+20],FFFFFFFF { -1 }
SpaceEngine.exe+217749 - C7 47 1C FFFFFFFF     - mov [edi+1C],FFFFFFFF { -1 }
SpaceEngine.exe+217750 - C7 07 00009041        - mov [edi],41900000 { 18.00 }
SpaceEngine.exe+217756 - 74 24                 - je SpaceEngine.exe+21777C
SpaceEngine.exe+217758 - C7 87 D0000000 00000000 - mov [edi+000000D0],00000000 { 0 }
SpaceEngine.exe+217762 - C7 47 10 0000803F     - mov [edi+10],3F800000 { 1.00 }
SpaceEngine.exe+217769 - C7 47 14 0000803F     - mov [edi+14],3F800000 { 1.00 }
SpaceEngine.exe+217770 - C7 87 D4000000 00008041 - mov [edi+000000D4],41800000 { 16.00 }
SpaceEngine.exe+21777A - EB 22                 - jmp SpaceEngine.exe+21779E
SpaceEngine.exe+21777C - C7 87 D0000000 02000000 - mov [edi+000000D0],00000002 { 2 }
SpaceEngine.exe+217786 - C7 47 10 CDCC0C3F     - mov [edi+10],3F0CCCCD { 0.55 }
SpaceEngine.exe+21778D - C7 47 14 CDCC0C3F     - mov [edi+14],3F0CCCCD { 0.55 }
SpaceEngine.exe+217794 - C7 87 D4000000 00000042 - mov [edi+000000D4],42000000 { 32.00 }
SpaceEngine.exe+21779E - 80 7F 19 00           - cmp byte ptr [edi+19],00 { 0 }
SpaceEngine.exe+2177A2 - 0F84 6FFFFFFF         - je SpaceEngine.exe+217717
SpaceEngine.exe+2177A8 - 83 BF D0000000 00     - cmp dword ptr [edi+000000D0],00 { 0 }
SpaceEngine.exe+2177AF - 0F85 62FFFFFF         - jne SpaceEngine.exe+217717
SpaceEngine.exe+2177B5 - E9 53FFFFFF           - jmp SpaceEngine.exe+21770D
SpaceEngine.exe+2177BA - C7 87 CC000000 02000000 - mov [edi+000000CC],00000002 { 2 }
SpaceEngine.exe+2177C4 - C7 47 10 0000403F     - mov [edi+10],3F400000 { 0.75 }
SpaceEngine.exe+2177CB - C7 47 14 0000403F     - mov [edi+14],3F400000 { 0.75 }
SpaceEngine.exe+2177D2 - C7 87 D0000000 02000000 - mov [edi+000000D0],00000002 { 2 }
SpaceEngine.exe+2177DC - C7 47 1C FFFFFFFF     - mov [edi+1C],FFFFFFFF { -1 }
SpaceEngine.exe+2177E3 - C7 47 20 FFFFFFFF     - mov [edi+20],FFFFFFFF { -1 }
SpaceEngine.exe+2177EA - C7 87 D4000000 00000042 - mov [edi+000000D4],42000000 { 32.00 }
SpaceEngine.exe+2177F4 - C7 07 00001042        - mov [edi],42100000 { 36.00 }
SpaceEngine.exe+2177FA - 0F10 87 04190000      - movups xmm0,[edi+00001904]
SpaceEngine.exe+217801 - 0F11 87 94000000      - movups [edi+00000094],xmm0
SpaceEngine.exe+217808 - E9 92FEFFFF           - jmp SpaceEngine.exe+21769F
SpaceEngine.exe+21780D - C7 87 CC000000 03000000 - mov [edi+000000CC],00000003 { 3 }
SpaceEngine.exe+217817 - C7 47 10 0000803F     - mov [edi+10],3F800000 { 1.00 }
SpaceEngine.exe+21781E - C7 47 14 0000803F     - mov [edi+14],3F800000 { 1.00 }
SpaceEngine.exe+217825 - EB AB                 - jmp SpaceEngine.exe+2177D2
SpaceEngine.exe+217827 - 8B 4C 24 24           - mov ecx,[esp+24]
SpaceEngine.exe+21782B - 8D 97 2C190000        - lea edx,[edi+0000192C]
SpaceEngine.exe+217831 - E8 BAEEFFFF           - call SpaceEngine.exe+2166F0
SpaceEngine.exe+217836 - 0FB6 87 2C190000      - movzx eax,byte ptr [edi+0000192C]
SpaceEngine.exe+21783D - B9 E090D200           - mov ecx,SpaceEngine.exe+4F90E0 { [00000566] }
SpaceEngine.exe+217842 - C7 44 24 3C 0000803F  - mov [esp+3C],3F800000 { 1.00 }
SpaceEngine.exe+21784A - 66 0F6E D0            - movd xmm2,eax
SpaceEngine.exe+21784E - 0FB6 87 2D190000      - movzx eax,byte ptr [edi+0000192D]
SpaceEngine.exe+217855 - 0F5B D2               - cvtdq2ps xmm2,xmm2
SpaceEngine.exe+217858 - 66 0F6E C8            - movd xmm1,eax
SpaceEngine.exe+21785C - 0FB6 87 2E190000      - movzx eax,byte ptr [edi+0000192E]
SpaceEngine.exe+217863 - 0F5B C9               - cvtdq2ps xmm1,xmm1
SpaceEngine.exe+217866 - 66 0F6E C0            - movd xmm0,eax
SpaceEngine.exe+21786A - 8D 44 24 40           - lea eax,[esp+40]
SpaceEngine.exe+21786E - 0F5B C0               - cvtdq2ps xmm0,xmm0
SpaceEngine.exe+217871 - 50                    - push eax
SpaceEngine.exe+217872 - F3 0F5E CC            - divss xmm1,xmm4
SpaceEngine.exe+217876 - F3 0F5E C4            - divss xmm0,xmm4
SpaceEngine.exe+21787A - F3 0F5E D4            - divss xmm2,xmm4
SpaceEngine.exe+21787E - F3 0F11 4C 24 38      - movss [esp+38],xmm1
SpaceEngine.exe+217884 - F3 0F10 8F B8000000   - movss xmm1,[edi+000000B8]
SpaceEngine.exe+21788C - F3 0F11 44 24 3C      - movss [esp+3C],xmm0
SpaceEngine.exe+217892 - F3 0F11 54 24 34      - movss [esp+34],xmm2
SpaceEngine.exe+217898 - 0F28 44 24 34         - movaps xmm0,[esp+34]
SpaceEngine.exe+21789D - 0FC6 C9 00            - shufps xmm1,xmm1,00 { 0 }
SpaceEngine.exe+2178A1 - 0F59 C1               - mulps xmm0,xmm1
SpaceEngine.exe+2178A4 - 0F11 44 24 44         - movups [esp+44],xmm0
SpaceEngine.exe+2178A9 - E8 725BF9FF           - call SpaceEngine.exe+1AD420
SpaceEngine.exe+2178AE - 8B 74 24 24           - mov esi,[esp+24]
SpaceEngine.exe+2178B2 - 83 C6 06              - add esi,06 { 6 }
SpaceEngine.exe+2178B5 - E9 65060000           - jmp SpaceEngine.exe+217F1F
SpaceEngine.exe+2178BA - 0F10 8F A8000000      - movups xmm1,[edi+000000A8]
SpaceEngine.exe+2178C1 - 8D 44 24 40           - lea eax,[esp+40]
SpaceEngine.exe+2178C5 - B9 E090D200           - mov ecx,SpaceEngine.exe+4F90E0 { [00000566] }
SpaceEngine.exe+2178CA - F3 0F10 87 B8000000   - movss xmm0,[edi+000000B8]
SpaceEngine.exe+2178D2 - 0FC6 C0 00            - shufps xmm0,xmm0,00 { 0 }
SpaceEngine.exe+2178D6 - 0F29 4C 24 30         - movaps [esp+30],xmm1
SpaceEngine.exe+2178DB - 0F59 C8               - mulps xmm1,xmm0
SpaceEngine.exe+2178DE - 50                    - push eax
SpaceEngine.exe+2178DF - 0F11 4C 24 44         - movups [esp+44],xmm1
SpaceEngine.exe+2178E4 - E8 375BF9FF           - call SpaceEngine.exe+1AD420
SpaceEngine.exe+2178E9 - E9 31060000           - jmp SpaceEngine.exe+217F1F
SpaceEngine.exe+2178EE - 66 0F6E 47 0C         - movd xmm0,[edi+0C]
SpaceEngine.exe+2178F3 - F3 0F58 35 1C80BD00   - addss xmm6,[SpaceEngine.exe+3A801C] { [1.00] }
SpaceEngine.exe+2178FB - 66 0F6E 4F 08         - movd xmm1,[edi+08]
SpaceEngine.exe+217900 - 0F5B C0               - cvtdq2ps xmm0,xmm0
SpaceEngine.exe+217903 - 0F5B C9               - cvtdq2ps xmm1,xmm1
SpaceEngine.exe+217906 - F3 0F5C F0            - subss xmm6,xmm0
SpaceEngine.exe+21790A - F3 0F5E F1            - divss xmm6,xmm1
SpaceEngine.exe+21790E - 0F28 C6               - movaps xmm0,xmm6
SpaceEngine.exe+217911 - E8 BA62E3FF           - call SpaceEngine.exe+4DBD0
SpaceEngine.exe+217916 - 0F28 F0               - movaps xmm6,xmm0
SpaceEngine.exe+217919 - 66 0F6E 47 08         - movd xmm0,[edi+08]
SpaceEngine.exe+21791E - 0F5B C0               - cvtdq2ps xmm0,xmm0
SpaceEngine.exe+217921 - F3 0F59 F0            - mulss xmm6,xmm0
SpaceEngine.exe+217925 - 66 0F6E 47 0C         - movd xmm0,[edi+0C]
SpaceEngine.exe+21792A - 0F5B C0               - cvtdq2ps xmm0,xmm0
SpaceEngine.exe+21792D - F3 0F58 F0            - addss xmm6,xmm0
SpaceEngine.exe+217931 - E9 DD050000           - jmp SpaceEngine.exe+217F13
SpaceEngine.exe+217936 - FF B7 CC000000        - push [edi+000000CC]
SpaceEngine.exe+21793C - 8B CF                 - mov ecx,edi
SpaceEngine.exe+21793E - C6 47 19 01           - mov byte ptr [edi+19],01 { 1 }
SpaceEngine.exe+217942 - E8 E9790000           - call SpaceEngine.exe+21F330
SpaceEngine.exe+217947 - E9 EB050000           - jmp SpaceEngine.exe+217F37
SpaceEngine.exe+21794C - FF B7 CC000000        - push [edi+000000CC]
SpaceEngine.exe+217952 - 8B CF                 - mov ecx,edi
SpaceEngine.exe+217954 - C6 47 19 00           - mov byte ptr [edi+19],00 { 0 }
SpaceEngine.exe+217958 - E8 D3790000           - call SpaceEngine.exe+21F330
SpaceEngine.exe+21795D - E9 D5050000           - jmp SpaceEngine.exe+217F37
SpaceEngine.exe+217962 - 8A 06                 - mov ax,[esi];mov al,[esi];<<<===Decode(esi)
SpaceEngine.exe+217964 - 3C 30                 - cmp ax,30;cmp al,30 { 48 }
SpaceEngine.exe+217966 - 0F8C CB050000         - jl SpaceEngine.exe+217F37
SpaceEngine.exe+21796C - 3C 3A                 - cmp ax,3A;cmp al,3A { 58 }
SpaceEngine.exe+21796E - 7C 08                 - jl SpaceEngine.exe+217978
SpaceEngine.exe+217970 - 3C 3F                 - cmp ax,3F;cmp al,3F { 63 }
SpaceEngine.exe+217972 - 0F8E BF050000         - jng SpaceEngine.exe+217F37
SpaceEngine.exe+217978 - 3C 5B                 - cmp ax,5B;cmp al,5B { 91 }
SpaceEngine.exe+21797A - 7C 08                 - jl SpaceEngine.exe+217984
SpaceEngine.exe+21797C - 3C 5F                 - cmp ax,5F;cmp al,5F { 95 }
SpaceEngine.exe+21797E - 0F8E B3050000         - jng SpaceEngine.exe+217F37
SpaceEngine.exe+217984 - 3C 7B                 - cmp ax,7B;cmp al,7B { 123 }
SpaceEngine.exe+217986 - 7C 08                 - jl SpaceEngine.exe+217990
SpaceEngine.exe+217988 - 3C 7E                 - cmp ax,7E;cmp al,7E { 126 }
SpaceEngine.exe+21798A - 0F8E A7050000         - jng SpaceEngine.exe+217F37
SpaceEngine.exe+217990 - 46                    - add esi,2;inc esi
SpaceEngine.exe+217991 - EB CF                 - jmp SpaceEngine.exe+217962
SpaceEngine.exe+217993 - F3 0F10 BF C0000000   - movss xmm7,[edi+000000C0]
SpaceEngine.exe+21799B - F3 0F58 3F            - addss xmm7,[edi]
SpaceEngine.exe+21799F - F3 0F10 B7 BC000000   - movss xmm6,[edi+000000BC]
SpaceEngine.exe+2179A7 - F3 0F11 74 24 14      - movss [esp+14],xmm6
SpaceEngine.exe+2179AD - F3 0F11 7C 24 10      - movss [esp+10],xmm7
SpaceEngine.exe+2179B3 - F3 0F11 BF C0000000   - movss [edi+000000C0],xmm7
SpaceEngine.exe+2179BB - E9 77050000           - jmp SpaceEngine.exe+217F37
SpaceEngine.exe+2179C0 - 8B 87 D0000000        - mov eax,[edi+000000D0]
SpaceEngine.exe+2179C6 - F3 0F10 8F D4000000   - movss xmm1,[edi+000000D4]
SpaceEngine.exe+2179CE - F3 0F59 4F 14         - mulss xmm1,[edi+14]
SpaceEngine.exe+2179D3 - C1 E0 08              - shl eax,08 { 8 }
SpaceEngine.exe+2179D6 - 03 C2                 - add eax,edx
SpaceEngine.exe+2179D8 - F3 0F11 4C 24 24      - movss [esp+24],xmm1
SpaceEngine.exe+2179DE - F3 0F10 AC 87 D8000000  - movss xmm5,[edi+eax*4+000000D8]
SpaceEngine.exe+2179E7 - 8B 47 24              - mov eax,[edi+24]
SpaceEngine.exe+2179EA - F3 0F59 6F 10         - mulss xmm5,[edi+10]
SpaceEngine.exe+2179EF - 83 E8 00              - sub eax,00 { 0 }
SpaceEngine.exe+2179F2 - 74 0A                 - je SpaceEngine.exe+2179FE
SpaceEngine.exe+2179F4 - 83 E8 01              - sub eax,01 { 1 }
SpaceEngine.exe+2179F7 - 74 09                 - je SpaceEngine.exe+217A02
SpaceEngine.exe+2179F9 - 83 E8 01              - sub eax,01 { 1 }
SpaceEngine.exe+2179FC - 75 10                 - jne SpaceEngine.exe+217A0E
SpaceEngine.exe+2179FE - F3 0F59 EB            - mulss xmm5,xmm3
SpaceEngine.exe+217A02 - F3 0F58 EE            - addss xmm5,xmm6
SpaceEngine.exe+217A06 - F3 0F11 6C 24 1C      - movss [esp+1C],xmm5
SpaceEngine.exe+217A0C - EB 06                 - jmp SpaceEngine.exe+217A14
SpaceEngine.exe+217A0E - F3 0F10 6C 24 1C      - movss xmm5,[esp+1C]
SpaceEngine.exe+217A14 - 0F28 C5               - movaps xmm0,xmm5
SpaceEngine.exe+217A17 - F3 0F5C 87 BC000000   - subss xmm0,[edi+000000BC]
SpaceEngine.exe+217A1F - 0F2F 44 24 28         - comiss xmm0,[esp+28]
SpaceEngine.exe+217A24 - 0F87 1E050000         - ja SpaceEngine.exe+217F48
SpaceEngine.exe+217A2A - 8D 41 FF              - lea eax,[ecx-01]
SpaceEngine.exe+217A2D - 3B 47 1C              - cmp eax,[edi+1C]
SpaceEngine.exe+217A30 - 7C 74                 - jl SpaceEngine.exe+217AA6
SpaceEngine.exe+217A32 - 3B 47 20              - cmp eax,[edi+20]
SpaceEngine.exe+217A35 - 7F 6F                 - jg SpaceEngine.exe+217AA6
SpaceEngine.exe+217A37 - F3 0F11 7C 24 18      - movss [esp+18],xmm7
SpaceEngine.exe+217A3D - B9 E090D200           - mov ecx,SpaceEngine.exe+4F90E0 { [00000566] }
SpaceEngine.exe+217A42 - F3 0F10 3F            - movss xmm7,[edi]
SpaceEngine.exe+217A46 - F3 0F58 7C 24 10      - addss xmm7,[esp+10]
SpaceEngine.exe+217A4C - 68 A0AFD200           - push SpaceEngine.exe+4FAFA0 { [0.10] }
SpaceEngine.exe+217A51 - F3 0F11 7C 24 24      - movss [esp+24],xmm7
SpaceEngine.exe+217A57 - E8 C459F9FF           - call SpaceEngine.exe+1AD420
SpaceEngine.exe+217A5C - F3 0F10 54 24 10      - movss xmm2,[esp+10]
SpaceEngine.exe+217A62 - 0F28 DD               - movaps xmm3,xmm5
SpaceEngine.exe+217A65 - 51                    - push ecx
SpaceEngine.exe+217A66 - 0F28 CE               - movaps xmm1,xmm6
SpaceEngine.exe+217A69 - F3 0F11 3C 24         - movss [esp],xmm7
SpaceEngine.exe+217A6E - E8 6D55F9FF           - call SpaceEngine.exe+1ACFE0
SpaceEngine.exe+217A73 - 8D 44 24 30           - lea eax,[esp+30]
SpaceEngine.exe+217A77 - B9 E090D200           - mov ecx,SpaceEngine.exe+4F90E0 { [00000566] }
SpaceEngine.exe+217A7C - 50                    - push eax
SpaceEngine.exe+217A7D - E8 9E59F9FF           - call SpaceEngine.exe+1AD420
SpaceEngine.exe+217A82 - F3 0F10 6C 24 1C      - movss xmm5,[esp+1C]
SpaceEngine.exe+217A88 - F3 0F10 74 24 14      - movss xmm6,[esp+14]
SpaceEngine.exe+217A8E - F3 0F10 4C 24 24      - movss xmm1,[esp+24]
SpaceEngine.exe+217A94 - F3 0F10 7C 24 10      - movss xmm7,[esp+10]
SpaceEngine.exe+217A9A - F3 0F10 1D 087FBD00   - movss xmm3,[SpaceEngine.exe+3A7F08] { [0.75] }
SpaceEngine.exe+217AA2 - 8B 54 24 2C           - mov edx,[esp+2C];ch
SpaceEngine.exe+217AA6 - 8B 47 24              - mov eax,[edi+24]
SpaceEngine.exe+217AA9 - 83 E8 00              - sub eax,00 { 0 }
SpaceEngine.exe+217AAC - 74 38                 - je SpaceEngine.exe+217AE6
SpaceEngine.exe+217AAE - 83 E8 01              - sub eax,01 { 1 }
SpaceEngine.exe+217AB1 - 74 1E                 - je SpaceEngine.exe+217AD1
SpaceEngine.exe+217AB3 - 83 E8 01              - sub eax,01 { 1 }
SpaceEngine.exe+217AB6 - 75 52                 - jne SpaceEngine.exe+217B0A
SpaceEngine.exe+217AB8 - 0F28 D1               - movaps xmm2,xmm1
SpaceEngine.exe+217ABB - F3 0F11 7C 24 18      - movss [esp+18],xmm7
SpaceEngine.exe+217AC1 - F3 0F59 D3            - mulss xmm2,xmm3
SpaceEngine.exe+217AC5 - F3 0F58 D7            - addss xmm2,xmm7
SpaceEngine.exe+217AC9 - F3 0F11 54 24 20      - movss [esp+20],xmm2
SpaceEngine.exe+217ACF - EB 3F                 - jmp SpaceEngine.exe+217B10
SpaceEngine.exe+217AD1 - 0F28 D1               - movaps xmm2,xmm1
SpaceEngine.exe+217AD4 - F3 0F11 7C 24 18      - movss [esp+18],xmm7
SpaceEngine.exe+217ADA - F3 0F58 D7            - addss xmm2,xmm7
SpaceEngine.exe+217ADE - F3 0F11 54 24 20      - movss [esp+20],xmm2
SpaceEngine.exe+217AE4 - EB 2A                 - jmp SpaceEngine.exe+217B10
SpaceEngine.exe+217AE6 - 0F28 C1               - movaps xmm0,xmm1
SpaceEngine.exe+217AE9 - 0F28 D1               - movaps xmm2,xmm1
SpaceEngine.exe+217AEC - F3 0F59 05 3C7DBD00   - mulss xmm0,[SpaceEngine.exe+3A7D3C] { [0.25] }
SpaceEngine.exe+217AF4 - F3 0F58 D7            - addss xmm2,xmm7
SpaceEngine.exe+217AF8 - F3 0F58 C7            - addss xmm0,xmm7
SpaceEngine.exe+217AFC - F3 0F11 54 24 20      - movss [esp+20],xmm2
SpaceEngine.exe+217B02 - F3 0F11 44 24 18      - movss [esp+18],xmm0
SpaceEngine.exe+217B08 - EB 06                 - jmp SpaceEngine.exe+217B10
SpaceEngine.exe+217B0A - F3 0F10 54 24 20      - movss xmm2,[esp+20]
SpaceEngine.exe+217B10 - 8B 8F D0000000        - mov ecx,[edi+000000D0];字体大小
SpaceEngine.exe+217B16 - 8B C1                 - mov eax,ecx
SpaceEngine.exe+217B18 - C1 E0 08              - shl eax,08 { 8 }
SpaceEngine.exe+217B1B - 03 D0                 - add edx,eax
SpaceEngine.exe+217B1D - F3 0F10 8C 8F D8180000  - movss xmm1,[edi+ecx*4+000018D8];单位字进 1/行字数
SpaceEngine.exe+217B26 - 8A 4C 24 0F           - mov cx,[esi];mov cl,[esp+0F] <<====重写此处
SpaceEngine.exe+217B2A - F3 0F10 A4 97 D80C0000  - movss xmm4,[edi+edx*4+00000CD8];字左偏0/1/2|ch
SpaceEngine.exe+217B33 - 8A C1                 - movzx eax,cx;mov al,cl
SpaceEngine.exe+217B35 - F3 0F10 9C 97 D8000000  - movss xmm3,[edi+edx*4+000000D8];//字宽0/1/2|ch
SpaceEngine.exe+217B3E - 24 0F                 - and eax,0FF { 15 };and ax,0F { 15 } ;横坐标
SpaceEngine.exe+217B40 - 8B 15 18CFD200        - mov edx,[SpaceEngine.exe+4FCF18] { [00D2CE40] }
SpaceEngine.exe+217B46 - 0FB6 C0               - ;movzx eax,al
SpaceEngine.exe+217B49 - C0 E9 04              - shr cx,08 { 4 };shr cl,04 { 4 } ;纵坐标
SpaceEngine.exe+217B4C - F3 0F59 E1            - mulss xmm4,xmm1
SpaceEngine.exe+217B50 - 66 0F6E C0            - movd xmm0,eax
SpaceEngine.exe+217B54 - 0FB6 C1               -movzx eax,cx; movzx eax,cl
SpaceEngine.exe+217B57 - 0F5B C0               - cvtdq2ps xmm0,xmm0
SpaceEngine.exe+217B5A - 66 0F6E F8            - movd xmm7,eax
SpaceEngine.exe+217B5E - F3 0F59 05 147CBD00   - mulss xmm0,[SpaceEngine.exe+3A7C14] { [0.06] }
SpaceEngine.exe+217B66 - 8B 42 14              - mov eax,[edx+14]
SpaceEngine.exe+217B69 - 0F5B FF               - cvtdq2ps xmm7,xmm7
SpaceEngine.exe+217B6C - F3 0F58 E0            - addss xmm4,xmm0
SpaceEngine.exe+217B70 - F3 0F59 D9            - mulss xmm3,xmm1
SpaceEngine.exe+217B74 - F3 0F59 3D 147CBD00   - mulss xmm7,[SpaceEngine.exe+3A7C14] { [0.06] }
SpaceEngine.exe+217B7C - F3 0F58 DC            - addss xmm3,xmm4
SpaceEngine.exe+217B80 - 0F28 CF               - movaps xmm1,xmm7
SpaceEngine.exe+217B83 - F3 0F58 0D 147CBD00   - addss xmm1,[SpaceEngine.exe+3A7C14] { [0.06] }
SpaceEngine.exe+217B8B - 3B 42 10              - cmp eax,[edx+10]
SpaceEngine.exe+217B8E - 0F8D 8C000000         - jnl SpaceEngine.exe+217C20
SpaceEngine.exe+217B94 - F3 0F10 44 24 18      - movss xmm0,[esp+18]
SpaceEngine.exe+217B9A - F3 0F11 05 24CED200   - movss [SpaceEngine.exe+4FCE24],xmm0 { [256.00] }
SpaceEngine.exe+217BA2 - F3 0F10 05 7C4DE000   - movss xmm0,[SpaceEngine.exe+5D4D7C] { [0.50] }
SpaceEngine.exe+217BAA - F3 0F59 C4            - mulss xmm0,xmm4
SpaceEngine.exe+217BAE - F3 0F11 35 20CED200   - movss [SpaceEngine.exe+4FCE20],xmm6 { [504.00] }
SpaceEngine.exe+217BB6 - F3 0F58 05 744DE000   - addss xmm0,[SpaceEngine.exe+5D4D74] { [0.00] }
SpaceEngine.exe+217BBE - F3 0F59 05 2890BD00   - mulss xmm0,[SpaceEngine.exe+3A9028] { [32767.00] }
SpaceEngine.exe+217BC6 - F3 0F2C C0            - cvttss2si eax,xmm0
SpaceEngine.exe+217BCA - F3 0F10 05 804DE000   - movss xmm0,[SpaceEngine.exe+5D4D80] { [0.50] }
SpaceEngine.exe+217BD2 - F3 0F59 C7            - mulss xmm0,xmm7
SpaceEngine.exe+217BD6 - 66 A3 28CED200        - mov [SpaceEngine.exe+4FCE28],ax { [053F57FF] }
SpaceEngine.exe+217BDC - F3 0F58 05 784DE000   - addss xmm0,[SpaceEngine.exe+5D4D78] { [0.50] }
SpaceEngine.exe+217BE4 - F3 0F59 05 2890BD00   - mulss xmm0,[SpaceEngine.exe+3A9028] { [32767.00] }
SpaceEngine.exe+217BEC - F3 0F2C C0            - cvttss2si eax,xmm0
SpaceEngine.exe+217BF0 - 66 A3 2ACED200        - mov [SpaceEngine.exe+4FCE2A],ax { [63] }
SpaceEngine.exe+217BF6 - 8B 42 14              - mov eax,[edx+14]
SpaceEngine.exe+217BF9 - 0F10 05 20CED200      - movups xmm0,[SpaceEngine.exe+4FCE20] { [504.00] }
SpaceEngine.exe+217C00 - 8D 0C 40              - lea ecx,[eax+eax*2]
SpaceEngine.exe+217C03 - 8B 42 1C              - mov eax,[edx+1C]
SpaceEngine.exe+217C06 - 0F11 04 C8            - movups [eax+ecx*8],xmm0
SpaceEngine.exe+217C0A - F3 0F7E 05 30CED200   - movq xmm0,[SpaceEngine.exe+4FCE30] { [02A10566] }
SpaceEngine.exe+217C12 - 66 0FD6 44 C8 10      - movq [eax+ecx*8+10],xmm0
SpaceEngine.exe+217C18 - A1 18CFD200           - mov eax,[SpaceEngine.exe+4FCF18] { [00D2CE40] }
SpaceEngine.exe+217C1D - FF 40 14              - inc [eax+14]
SpaceEngine.exe+217C20 - 8B 15 18CFD200        - mov edx,[SpaceEngine.exe+4FCF18] { [00D2CE40] }
SpaceEngine.exe+217C26 - 8B 42 14              - mov eax,[edx+14]
SpaceEngine.exe+217C29 - 3B 42 10              - cmp eax,[edx+10]
SpaceEngine.exe+217C2C - 0F8D 86000000         - jnl SpaceEngine.exe+217CB8
SpaceEngine.exe+217C32 - F3 0F10 05 7C4DE000   - movss xmm0,[SpaceEngine.exe+5D4D7C] { [0.50] }
SpaceEngine.exe+217C3A - F3 0F59 C4            - mulss xmm0,xmm4
SpaceEngine.exe+217C3E - F3 0F11 35 20CED200   - movss [SpaceEngine.exe+4FCE20],xmm6 { [504.00] }
SpaceEngine.exe+217C46 - F3 0F11 15 24CED200   - movss [SpaceEngine.exe+4FCE24],xmm2 { [256.00] }
SpaceEngine.exe+217C4E - F3 0F58 05 744DE000   - addss xmm0,[SpaceEngine.exe+5D4D74] { [0.00] }
SpaceEngine.exe+217C56 - F3 0F59 05 2890BD00   - mulss xmm0,[SpaceEngine.exe+3A9028] { [32767.00] }
SpaceEngine.exe+217C5E - F3 0F2C C0            - cvttss2si eax,xmm0
SpaceEngine.exe+217C62 - F3 0F10 05 804DE000   - movss xmm0,[SpaceEngine.exe+5D4D80] { [0.50] }
SpaceEngine.exe+217C6A - F3 0F59 C1            - mulss xmm0,xmm1
SpaceEngine.exe+217C6E - 66 A3 28CED200        - mov [SpaceEngine.exe+4FCE28],ax { [053F57FF] }
SpaceEngine.exe+217C74 - F3 0F58 05 784DE000   - addss xmm0,[SpaceEngine.exe+5D4D78] { [0.50] }
SpaceEngine.exe+217C7C - F3 0F59 05 2890BD00   - mulss xmm0,[SpaceEngine.exe+3A9028] { [32767.00] }
SpaceEngine.exe+217C84 - F3 0F2C C0            - cvttss2si eax,xmm0
SpaceEngine.exe+217C88 - 66 A3 2ACED200        - mov [SpaceEngine.exe+4FCE2A],ax { [63] }
SpaceEngine.exe+217C8E - 8B 42 14              - mov eax,[edx+14]
SpaceEngine.exe+217C91 - 0F10 05 20CED200      - movups xmm0,[SpaceEngine.exe+4FCE20] { [504.00] }
SpaceEngine.exe+217C98 - 8D 0C 40              - lea ecx,[eax+eax*2]
SpaceEngine.exe+217C9B - 8B 42 1C              - mov eax,[edx+1C]
SpaceEngine.exe+217C9E - 0F11 04 C8            - movups [eax+ecx*8],xmm0
SpaceEngine.exe+217CA2 - F3 0F7E 05 30CED200   - movq xmm0,[SpaceEngine.exe+4FCE30] { [02A10566] }
SpaceEngine.exe+217CAA - 66 0FD6 44 C8 10      - movq [eax+ecx*8+10],xmm0
SpaceEngine.exe+217CB0 - A1 18CFD200           - mov eax,[SpaceEngine.exe+4FCF18] { [00D2CE40] }
SpaceEngine.exe+217CB5 - FF 40 14              - inc [eax+14]
SpaceEngine.exe+217CB8 - 8B 15 18CFD200        - mov edx,[SpaceEngine.exe+4FCF18] { [00D2CE40] }
SpaceEngine.exe+217CBE - 8B 42 14              - mov eax,[edx+14]
SpaceEngine.exe+217CC1 - 3B 42 10              - cmp eax,[edx+10]
SpaceEngine.exe+217CC4 - 0F8D 86000000         - jnl SpaceEngine.exe+217D50
SpaceEngine.exe+217CCA - F3 0F10 05 7C4DE000   - movss xmm0,[SpaceEngine.exe+5D4D7C] { [0.50] }
SpaceEngine.exe+217CD2 - F3 0F59 C3            - mulss xmm0,xmm3
SpaceEngine.exe+217CD6 - F3 0F11 2D 20CED200   - movss [SpaceEngine.exe+4FCE20],xmm5 { [504.00] }
SpaceEngine.exe+217CDE - F3 0F11 15 24CED200   - movss [SpaceEngine.exe+4FCE24],xmm2 { [256.00] }
SpaceEngine.exe+217CE6 - F3 0F58 05 744DE000   - addss xmm0,[SpaceEngine.exe+5D4D74] { [0.00] }
SpaceEngine.exe+217CEE - F3 0F59 05 2890BD00   - mulss xmm0,[SpaceEngine.exe+3A9028] { [32767.00] }
SpaceEngine.exe+217CF6 - F3 0F2C C0            - cvttss2si eax,xmm0
SpaceEngine.exe+217CFA - F3 0F10 05 804DE000   - movss xmm0,[SpaceEngine.exe+5D4D80] { [0.50] }
SpaceEngine.exe+217D02 - F3 0F59 C1            - mulss xmm0,xmm1
SpaceEngine.exe+217D06 - 66 A3 28CED200        - mov [SpaceEngine.exe+4FCE28],ax { [053F57FF] }
SpaceEngine.exe+217D0C - F3 0F58 05 784DE000   - addss xmm0,[SpaceEngine.exe+5D4D78] { [0.50] }
SpaceEngine.exe+217D14 - F3 0F59 05 2890BD00   - mulss xmm0,[SpaceEngine.exe+3A9028] { [32767.00] }
SpaceEngine.exe+217D1C - F3 0F2C C0            - cvttss2si eax,xmm0
SpaceEngine.exe+217D20 - 66 A3 2ACED200        - mov [SpaceEngine.exe+4FCE2A],ax { [63] }
SpaceEngine.exe+217D26 - 8B 42 14              - mov eax,[edx+14]
SpaceEngine.exe+217D29 - 0F10 05 20CED200      - movups xmm0,[SpaceEngine.exe+4FCE20] { [504.00] }
SpaceEngine.exe+217D30 - 8D 0C 40              - lea ecx,[eax+eax*2]
SpaceEngine.exe+217D33 - 8B 42 1C              - mov eax,[edx+1C]
SpaceEngine.exe+217D36 - 0F11 04 C8            - movups [eax+ecx*8],xmm0
SpaceEngine.exe+217D3A - F3 0F7E 05 30CED200   - movq xmm0,[SpaceEngine.exe+4FCE30] { [02A10566] }
SpaceEngine.exe+217D42 - 66 0FD6 44 C8 10      - movq [eax+ecx*8+10],xmm0
SpaceEngine.exe+217D48 - A1 18CFD200           - mov eax,[SpaceEngine.exe+4FCF18] { [00D2CE40] }
SpaceEngine.exe+217D4D - FF 40 14              - inc [eax+14]
SpaceEngine.exe+217D50 - 8B 15 18CFD200        - mov edx,[SpaceEngine.exe+4FCF18] { [00D2CE40] }
SpaceEngine.exe+217D56 - 8B 42 14              - mov eax,[edx+14]
SpaceEngine.exe+217D59 - 3B 42 10              - cmp eax,[edx+10]
SpaceEngine.exe+217D5C - 0F8D 88000000         - jnl SpaceEngine.exe+217DEA
SpaceEngine.exe+217D62 - F3 0F10 05 7C4DE000   - movss xmm0,[SpaceEngine.exe+5D4D7C] { [0.50] }
SpaceEngine.exe+217D6A - F3 0F59 C3            - mulss xmm0,xmm3
SpaceEngine.exe+217D6E - F3 0F11 15 24CED200   - movss [SpaceEngine.exe+4FCE24],xmm2 { [256.00] }
SpaceEngine.exe+217D76 - F3 0F10 15 2890BD00   - movss xmm2,[SpaceEngine.exe+3A9028] { [32767.00] }
SpaceEngine.exe+217D7E - F3 0F58 05 744DE000   - addss xmm0,[SpaceEngine.exe+5D4D74] { [0.00] }
SpaceEngine.exe+217D86 - F3 0F11 2D 20CED200   - movss [SpaceEngine.exe+4FCE20],xmm5 { [504.00] }
SpaceEngine.exe+217D8E - F3 0F59 C2            - mulss xmm0,xmm2
SpaceEngine.exe+217D92 - F3 0F2C C0            - cvttss2si eax,xmm0
SpaceEngine.exe+217D96 - F3 0F10 05 804DE000   - movss xmm0,[SpaceEngine.exe+5D4D80] { [0.50] }
SpaceEngine.exe+217D9E - F3 0F59 C1            - mulss xmm0,xmm1
SpaceEngine.exe+217DA2 - 66 A3 28CED200        - mov [SpaceEngine.exe+4FCE28],ax { [053F57FF] }
SpaceEngine.exe+217DA8 - F3 0F58 05 784DE000   - addss xmm0,[SpaceEngine.exe+5D4D78] { [0.50] }
SpaceEngine.exe+217DB0 - F3 0F59 C2            - mulss xmm0,xmm2
SpaceEngine.exe+217DB4 - F3 0F2C C0            - cvttss2si eax,xmm0
SpaceEngine.exe+217DB8 - 66 A3 2ACED200        - mov [SpaceEngine.exe+4FCE2A],ax { [63] }
SpaceEngine.exe+217DBE - 8B 42 14              - mov eax,[edx+14]
SpaceEngine.exe+217DC1 - 0F10 05 20CED200      - movups xmm0,[SpaceEngine.exe+4FCE20] { [504.00] }
SpaceEngine.exe+217DC8 - 8D 0C 40              - lea ecx,[eax+eax*2]
SpaceEngine.exe+217DCB - 8B 42 1C              - mov eax,[edx+1C]
SpaceEngine.exe+217DCE - 0F11 04 C8            - movups [eax+ecx*8],xmm0
SpaceEngine.exe+217DD2 - F3 0F7E 05 30CED200   - movq xmm0,[SpaceEngine.exe+4FCE30] { [02A10566] }
SpaceEngine.exe+217DDA - 66 0FD6 44 C8 10      - movq [eax+ecx*8+10],xmm0
SpaceEngine.exe+217DE0 - A1 18CFD200           - mov eax,[SpaceEngine.exe+4FCF18] { [00D2CE40] }
SpaceEngine.exe+217DE5 - FF 40 14              - inc [eax+14]
SpaceEngine.exe+217DE8 - EB 08                 - jmp SpaceEngine.exe+217DF2
SpaceEngine.exe+217DEA - F3 0F10 15 2890BD00   - movss xmm2,[SpaceEngine.exe+3A9028] { [32767.00] }
SpaceEngine.exe+217DF2 - 8B 15 18CFD200        - mov edx,[SpaceEngine.exe+4FCF18] { [00D2CE40] }
SpaceEngine.exe+217DF8 - F3 0F10 4C 24 18      - movss xmm1,[esp+18]
SpaceEngine.exe+217DFE - 8B 42 14              - mov eax,[edx+14]
SpaceEngine.exe+217E01 - 3B 42 10              - cmp eax,[edx+10]
SpaceEngine.exe+217E04 - 7D 7E                 - jnl SpaceEngine.exe+217E84
SpaceEngine.exe+217E06 - F3 0F10 05 7C4DE000   - movss xmm0,[SpaceEngine.exe+5D4D7C] { [0.50] }
SpaceEngine.exe+217E0E - F3 0F59 C3            - mulss xmm0,xmm3
SpaceEngine.exe+217E12 - F3 0F11 2D 20CED200   - movss [SpaceEngine.exe+4FCE20],xmm5 { [504.00] }
SpaceEngine.exe+217E1A - F3 0F11 0D 24CED200   - movss [SpaceEngine.exe+4FCE24],xmm1 { [256.00] }
SpaceEngine.exe+217E22 - F3 0F58 05 744DE000   - addss xmm0,[SpaceEngine.exe+5D4D74] { [0.00] }
SpaceEngine.exe+217E2A - F3 0F59 C2            - mulss xmm0,xmm2
SpaceEngine.exe+217E2E - F3 0F2C C0            - cvttss2si eax,xmm0
SpaceEngine.exe+217E32 - F3 0F10 05 804DE000   - movss xmm0,[SpaceEngine.exe+5D4D80] { [0.50] }
SpaceEngine.exe+217E3A - F3 0F59 C7            - mulss xmm0,xmm7
SpaceEngine.exe+217E3E - 66 A3 28CED200        - mov [SpaceEngine.exe+4FCE28],ax { [053F57FF] }
SpaceEngine.exe+217E44 - F3 0F58 05 784DE000   - addss xmm0,[SpaceEngine.exe+5D4D78] { [0.50] }
SpaceEngine.exe+217E4C - F3 0F59 C2            - mulss xmm0,xmm2
SpaceEngine.exe+217E50 - F3 0F2C C0            - cvttss2si eax,xmm0
SpaceEngine.exe+217E54 - 66 A3 2ACED200        - mov [SpaceEngine.exe+4FCE2A],ax { [63] }
SpaceEngine.exe+217E5A - 8B 42 14              - mov eax,[edx+14]
SpaceEngine.exe+217E5D - 0F10 05 20CED200      - movups xmm0,[SpaceEngine.exe+4FCE20] { [504.00] }
SpaceEngine.exe+217E64 - 8D 0C 40              - lea ecx,[eax+eax*2]
SpaceEngine.exe+217E67 - 8B 42 1C              - mov eax,[edx+1C]
SpaceEngine.exe+217E6A - 0F11 04 C8            - movups [eax+ecx*8],xmm0
SpaceEngine.exe+217E6E - F3 0F7E 05 30CED200   - movq xmm0,[SpaceEngine.exe+4FCE30] { [02A10566] }
SpaceEngine.exe+217E76 - 66 0FD6 44 C8 10      - movq [eax+ecx*8+10],xmm0
SpaceEngine.exe+217E7C - A1 18CFD200           - mov eax,[SpaceEngine.exe+4FCF18] { [00D2CE40] }
SpaceEngine.exe+217E81 - FF 40 14              - inc [eax+14]
SpaceEngine.exe+217E84 - 8B 15 18CFD200        - mov edx,[SpaceEngine.exe+4FCF18] { [00D2CE40] }
SpaceEngine.exe+217E8A - 8B 42 14              - mov eax,[edx+14]
SpaceEngine.exe+217E8D - 3B 42 10              - cmp eax,[edx+10]
SpaceEngine.exe+217E90 - 7D 7E                 - jnl SpaceEngine.exe+217F10
SpaceEngine.exe+217E92 - F3 0F10 05 7C4DE000   - movss xmm0,[SpaceEngine.exe+5D4D7C] { [0.50] }
SpaceEngine.exe+217E9A - F3 0F59 C4            - mulss xmm0,xmm4
SpaceEngine.exe+217E9E - F3 0F11 35 20CED200   - movss [SpaceEngine.exe+4FCE20],xmm6 { [504.00] }
SpaceEngine.exe+217EA6 - F3 0F11 0D 24CED200   - movss [SpaceEngine.exe+4FCE24],xmm1 { [256.00] }
SpaceEngine.exe+217EAE - F3 0F58 05 744DE000   - addss xmm0,[SpaceEngine.exe+5D4D74] { [0.00] }
SpaceEngine.exe+217EB6 - F3 0F59 C2            - mulss xmm0,xmm2
SpaceEngine.exe+217EBA - F3 0F2C C0            - cvttss2si eax,xmm0
SpaceEngine.exe+217EBE - F3 0F10 05 804DE000   - movss xmm0,[SpaceEngine.exe+5D4D80] { [0.50] }
SpaceEngine.exe+217EC6 - F3 0F59 C7            - mulss xmm0,xmm7
SpaceEngine.exe+217ECA - 66 A3 28CED200        - mov [SpaceEngine.exe+4FCE28],ax { [053F57FF] }
SpaceEngine.exe+217ED0 - F3 0F58 05 784DE000   - addss xmm0,[SpaceEngine.exe+5D4D78] { [0.50] }
SpaceEngine.exe+217ED8 - F3 0F59 C2            - mulss xmm0,xmm2
SpaceEngine.exe+217EDC - F3 0F2C C0            - cvttss2si eax,xmm0
SpaceEngine.exe+217EE0 - 66 A3 2ACED200        - mov [SpaceEngine.exe+4FCE2A],ax { [63] }
SpaceEngine.exe+217EE6 - 8B 42 14              - mov eax,[edx+14]
SpaceEngine.exe+217EE9 - 0F10 05 20CED200      - movups xmm0,[SpaceEngine.exe+4FCE20] { [504.00] }
SpaceEngine.exe+217EF0 - 8D 0C 40              - lea ecx,[eax+eax*2]
SpaceEngine.exe+217EF3 - 8B 42 1C              - mov eax,[edx+1C]
SpaceEngine.exe+217EF6 - 0F11 04 C8            - movups [eax+ecx*8],xmm0
SpaceEngine.exe+217EFA - F3 0F7E 05 30CED200   - movq xmm0,[SpaceEngine.exe+4FCE30] { [02A10566] }
SpaceEngine.exe+217F02 - 66 0FD6 44 C8 10      - movq [eax+ecx*8+10],xmm0
SpaceEngine.exe+217F08 - A1 18CFD200           - mov eax,[SpaceEngine.exe+4FCF18] { [00D2CE40] }
SpaceEngine.exe+217F0D - FF 40 14              - inc [eax+14]
SpaceEngine.exe+217F10 - 0F28 F5               - movaps xmm6,xmm5
SpaceEngine.exe+217F13 - F3 0F10 7C 24 10      - movss xmm7,[esp+10]
SpaceEngine.exe+217F19 - F3 0F11 74 24 14      - movss [esp+14],xmm6
SpaceEngine.exe+217F1F - F3 0F10 25 348EBD00   - movss xmm4,[SpaceEngine.exe+3A8E34] { [255.00] }
SpaceEngine.exe+217F27 - F3 0F10 0D 447EBD00   - movss xmm1,[SpaceEngine.exe+3A7E44] { [0.50] }
SpaceEngine.exe+217F2F - F3 0F10 1D 087FBD00   - movss xmm3,[SpaceEngine.exe+3A7F08] { [0.75] }
SpaceEngine.exe+217F37 - 8A 06                 - mov al,[esi];<<<===Decode(esi)
SpaceEngine.exe+217F39 - 8B 55 08              - mov edx,[ebp+08]
SpaceEngine.exe+217F3C - 88 44 24 0F           - mov [esp+0F],al
SpaceEngine.exe+217F40 - 84 C0                 - test al,al
SpaceEngine.exe+217F42 - 0F85 28F7FFFF         - jne SpaceEngine.exe+217670
SpaceEngine.exe+217F48 - 5F                    - pop edi
SpaceEngine.exe+217F49 - 5E                    - pop esi
SpaceEngine.exe+217F4A - 8B E5                 - mov esp,ebp
SpaceEngine.exe+217F4C - 5D                    - pop ebp
SpaceEngine.exe+217F4D - C2 0800               - ret 0008 { 8 }
SpaceEngine.exe+217F50 - 93                    - xchg eax,ebx;函数跳转表:可能需要修正
;SpaceEngine.exe+217693  1
;SpaceEngine.exe+2176BD  2
;SpaceEngine.exe+2176C7  3
;SpaceEngine.exe+217734  4
;SpaceEngine.exe+2177BA  5
;SpaceEngine.exe+21780D  6
;SpaceEngine.exe+217827  7
;SpaceEngine.exe+2178BA  8
;SpaceEngine.exe+2178EE  9
;SpaceEngine.exe+217993  a
;SpaceEngine.exe+217936  b
;SpaceEngine.exe+21794C  c
;SpaceEngine.exe+2179C0  d
;SpaceEngine.exe+2179C0  e
;SpaceEngine.exe+217962  f
SpaceEngine.exe+217F51 - 76 A4                 - jna SpaceEngine.exe+217EF7
SpaceEngine.exe+217F53 - 00 BD 76A400C7        - add [ebp-38FF5B8A],bh
SpaceEngine.exe+217F59 - 76 A4                 - jna SpaceEngine.exe+217EFF
SpaceEngine.exe+217F5B - 00 34 77              - add [edi+esi*2],dh
SpaceEngine.exe+217F5E - A4                    - movsb 
SpaceEngine.exe+217F5F - 00 BA 77A4000D        - add [edx+0D00A477],bh
SpaceEngine.exe+217F65 - 78 A4                 - js SpaceEngine.exe+217F0B
SpaceEngine.exe+217F67 - 00 27                 - add [edi],ah
SpaceEngine.exe+217F69 - 78 A4                 - js SpaceEngine.exe+217F0F
SpaceEngine.exe+217F6B - 00 BA 78A400EE        - add [edx-11FF5B88],bh
SpaceEngine.exe+217F71 - 78 A4                 - js SpaceEngine.exe+217F17
SpaceEngine.exe+217F73 - 00 93 79A40036        - add [ebx+3600A479],dl
SpaceEngine.exe+217F79 - 79 A4                 - jns SpaceEngine.exe+217F1F
SpaceEngine.exe+217F7B - 00 4C 79 A4           - add [ecx+edi*2-5C],cl
SpaceEngine.exe+217F7F - 00 C0                 - add al,al
SpaceEngine.exe+217F81 - 79 A4                 - jns SpaceEngine.exe+217F27
SpaceEngine.exe+217F83 - 00 C0                 - add al,al
SpaceEngine.exe+217F85 - 79 A4                 - jns SpaceEngine.exe+217F2B
SpaceEngine.exe+217F87 - 00 62 79              - add [edx+79],ah
SpaceEngine.exe+217F8A - A4                    - movsb 
SpaceEngine.exe+217F8B - 00 CC                 - add ah,cl
SpaceEngine.exe+217F8D - CC                    - int 3 
SpaceEngine.exe+217F8E - CC                    - int 3 
