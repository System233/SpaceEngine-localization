#include "stdafx.h"
#include "ft2build.h"
#include "Font.h"


#include <vector>
class Menu {
	std::vector<std::string> data;
public:
	void Push(std::string A, std::string B) {
		data.push_back(A + B);

	}
	void Show() {
		for (int i = 0;i < data.size();i++)printf("%d: %s\n", i + 1, data[i].c_str());
	}
};
int main() {
	Menu M;
	M.Push("DDDDDDDDDDDDDDDD", "DAWDWFAWFFAAAAAAAA");
	M.Push("DWADWFGAJIGBHYB", "GWGAWJHNUINAAAAAAAA");
	M.Show();

}
//#include FT2BUILD_H_
/*
SEL DChar;
wchar_t *WPstr[9] = { L"File",L"1",L"2",L"3",L"4",L"5",L"6",L"7",L"DEF" };
wchar_t* WGetConfig(int ID, wchar_t* str) {
	wchar_t TMP[256];
	swprintf(TMP, 256, L"Page%s", WPstr[ID]);
	return wcsstr(str, TMP);
}
void WMainInit() {
	FILE *fp;
	fopen_s(&fp, "Config.ini", "rb"); // 读取当前文件mian.c

	if (fp == NULL) {
		wprintf(L"文件不存在");

	}
	fseek(fp, 0, SEEK_END);
	unsigned int len = ftell(fp) / 2;
	wchar_t* Config = new wchar_t[len];

	rewind(fp);
	fseek(fp, 2L, SEEK_SET);
	size_t SIZE = fread(Config, sizeof(wchar_t), len - 1, fp);
	printf("%X %X", Config[0], Config[1]);
	Config[len - 1] = 0;
	int tick = 0;
	int i = 0;
	bool Incom = false, Inread = false, begin = false;
	std::wstring str;
	wchar_t *ps;//, *ps2;
	for (int P = 0;P < 9;P++) {
		if ((ps = WGetConfig(P, Config)) != 0) {
			Inread = true;
		}
		else {
			continue;
		}
		printf("读取:%d\n", P);
		int s = 0, s2 = 0;
		while (Inread) {
			if (ps[s] == '/'&&ps[s + 1] == '/') {
				Incom = true;
				s++, s++;
				continue;
			}
			if (Incom) {
				if (ps[s] == '\n' || ps[s] == '\r') {
					Incom = false;
				}
				s++;
				continue;

			}
			if (ps[s] == '{') {

				begin = true;
				s++;
				continue;
			}
			if (ps[s] == '}') {
				begin = Inread = false;
				str.push_back('\0');
				wchar_t *TMP = new wchar_t[str.size()];
				wcscpy_s(TMP, str.size(), str.c_str());
				printf("%X %X :%X %X\n", str[0], str[1], TMP[0], TMP[1]);
			
				str.clear();
				wprintf(L"\n完成");
				break;
			}
			if (begin) {
				str = str + ps[s];
			}
			s++;
		}

	}
}*/