// ConsoleApplication3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "cmdline.h"
HANDLE hHandle;
class GetOff {

public:
	GetOff(std::string Path, std::string O, std::string F) {
		std::ifstream IF(Path);
		std::string L;
		char Line[256],*str=new char[1024];
		int T = 0;
		std::ofstream OF(O);
		if(F.find("%s")!=std::string::npos)T=1;
		else if (F.find("%d") != std::string::npos|| F.find("%X") != std::string::npos)T = 2;
		while (IF.getline(Line, 256)) {
			L = Line;
			char *P = 0,*P2=0;
			if ((P = strstr(Line, "<Address>")) != 0) {
				P += 9;
				if ((P2 = strstr(Line, "</Address>")) != 0)*P2 = 0;
				
			
				if (T == 2) {
					if ((P = strstr(Line, "+")) != 0) { P += 1; 
					snprintf(str, 1024, F.c_str(), strtol(P,0,16));
					printf(" %s\n", str);
					OF << str << std::endl;
					}

				}
				else {
					snprintf(str, 1024, F.c_str(), P);
					printf(" %s\n", str);
					OF << str << std::endl;
				}
				
				
			}

		}
		delete[] str;
	};

};
#include<set>
Localization local;
class Reader{
	
	enum Token
	{
		Escape,
		Key,
		Value,
		Start,
		End,
		Escaping
	};
public:
	typedef std::vector<std::pair<std::wstring, std::wstring>> RMap;
	RMap Param,Map;
	template<class _Ty>
	bool Parse(_Ty &file) {
		return Parse(std::ifstream(file, std::ios::binary));
	};
	auto begin() {
		return Map.begin();
	}
	auto end() {
		return Map.end();
	}
	bool Parse(std::ifstream &Input) {
		if (Input) {
		 Parse(Map, Param, Input);
		 return true;
		}
		return (false);
	}
	static std::set<std::wstring> Parse(RMap&Map, RMap&Param,std::ifstream &Input,bool onKey=false) {
		std::set<std::wstring>Set;
		if(Input){
			size_t id = 0;
		std::stringstream ss;
		ss << Input.rdbuf();
		std::wstring &ws = UTF::Decode(ss.str());
		Token state(Start),token(Start);
		bool isParam(false);
		std::wstring key, val,tmp;
		wchar_t unicode(0),bits(0);
		for (auto ch : ws) {
			switch (state)
			{
			case Start: {
				switch (ch)
				{
				case '\\':state = Escape; break;
				case '"':
					switch (token) {
					case Start:token = Key; break;
					case Key:key = std::move(tmp), token = End; if (onKey)Set.insert(key); break;
					case Value:val = std::move(tmp), state=End; break;
					case End:token = Value; break;
					}
					break;
				case '\r':
				case '\n':token = Start; isParam = 0, val.clear(), key.clear();
					
					break;
				
				default:
					if (isParam&&token != End&&(ch == ' ' || ch == '\t'))key = std::move(tmp),token = End;
					else if (token == Key || token == Value)tmp += ch;
					else if(token == Start&&ch!=' '&&ch !='\t')token=Key,isParam = 1,tmp+=ch;
					break;
				}
			}break;
			case Escape:{
				state = Start;
				auto T = ch;
				switch (T)
				{
				case 'a':T = '\a'; break;
				case 'b':T = '\b'; break;
				case 't':T = '\t'; break;
				case 'n':T = '\n'; break;
				case 'v':T = '\v'; break;
				case 'f':T = '\f'; break;
				case 'r':T = '\r'; break;
				case '"':T = '\"'; break;
				case '\\':T = '\\'; break;
				case 'x': state = Escaping, bits = 2, unicode = 0; break;
				case 'u':state = Escaping, bits=4,unicode = 0;break;
				default:
					msgmgr(MsgType::Error, L"无效转义:%c", ch);
					break;
				}
				if (state != Escaping)tmp += T;
			}break;
			case Escaping: {
				if(isxdigit(ch)){
				wchar_t T(0);
				if (ch >= 'a' && ch <= 'f')
					T = ch - 'a' + 0xA;
				else if (ch >= 'A' && ch <= 'F')
					T = ch - 'A' + 0xA;
				else T = ch - '0';
				(unicode<<=4)+=T;
				if(--bits<=0)tmp+= unicode,state = Start;
				}
				else { 
					msgmgr(MsgType::Error, L"无效转义:%c", ch); 
					state = Start;
				}
			}break;
			case End: {
				
				if(!key.empty()&&!onKey){
				if (!Set.insert(key).second) { msgmgr(MsgType::Warning, L"重复:%s", key.c_str()); }
				else if(!onKey)(isParam?Param:Map).push_back(std::pair<std::wstring,std::wstring>(std::move(key), std::move(val)));
				}
				isParam = 0;
				state = Start;
			}break;
			default:
				break;
			}

		}
		}
		return Set;
	}

};
const char*lang = "lang", *input="input",*output="output", *tex = "tex", *texSz = "texSz",*help="help",*rm="remove",*exclude="exclude",*add="add",
*size="fontSz",*font="font",*outline="outline",*fontCol="fontCol",*outlineCol="lineCol",*base="base",*selcfg="cfg",*pageid="page";
HMODULE hInst;
char slang[100], sinput[100], sfcfg[100], soutput[100], stex[100], stexSz[100], shelp[100], srm[100], sexclude[100], sadd[100], sselcfg[100],
ssize[100], sfont[100], sioerr[100], weout[100],soutline[100],sfontCol[100],soutlineCol[100],sbase[100], snewpage[100], srefid[100],spage[100];
wchar_t uncfg[100], unused[100];
#define LoadA(id,x)LoadStringA(hInst,id,x,100)
#define LoadW(id,x)LoadStringW(hInst,id,x,100)
int main(int argc, char *argv[])
{
	//setlocale(LC_ALL,"chs");
	hInst = GetModuleHandle(0);
	LoadA(IDS_IAOERR, sioerr);
	LoadA(IDS_SLANG, slang);
	LoadA(IDS_SINPUT, sinput);
	LoadA(IDS_STEX, stex);
	LoadA(IDS_SOUTPUT, soutput);
	LoadA(IDS_SFONT, sfont);
	LoadA(IDS_STEXWH, stexSz);
	LoadA(IDS_SFONTWH, ssize);
	LoadA(IDS_SADD, sadd);
	LoadA(IDS_SREMOVE, srm);
	LoadA(IDS_SEXC, sexclude);
	LoadA(IDS_SHELP, shelp);
	LoadW(IDS_SUNCFG, uncfg);
	LoadW(IDS_SUNUSE, unused);
	LoadA(IDS_SWEOUT, weout);
	LoadA(IDS_SOUTLINE, soutline);
	LoadA(IDS_SOUTLINECOL, soutlineCol);
	LoadA(IDS_SFONTCOL, sfontCol);
	LoadA(IDS_SBASE, sbase);
	LoadA(IDS_SNEWPAGE, snewpage);
	LoadA(IDS_SSELCFG, sselcfg);
	LoadA(IDS_SREFID, srefid);
	LoadA(IDS_SPAGE, spage);
	cmdline::parser pser;

	pser.add<std::string>(lang, 'l', slang, true);
	pser.add<std::string>(selcfg, 'm', sselcfg, false, "localization.json");
	pser.add<std::string>(input, 'i', sinput, false);
	pser.add<std::string>(output, 'o', soutput, false);

	pser.add<std::string>(tex, 't', stex, false);
	pser.add<std::string>(pageid, 'p', spage, false);
	pser.add<std::string>(font, 'f', sfont, false, "msyh.ttc");
	pser.add<std::string>(texSz, 'z', stexSz, false, "256*256");
	pser.add<std::string>(size, 's', ssize, false, "12*12");
	pser.add<float>(outline, 'w', soutline, false, 0);
	pser.add<std::string>(outlineCol, 'u', soutlineCol, false, "0x64646464");
	pser.add<std::string>(fontCol, 'c', sfontCol, false, "0xFFFFFFFF");
	pser.add<long>(base, 'b', sbase, false);

	pser.add<std::string>(add, 'a', sadd, false);
	pser.add<std::string>(rm, 'r', srm, false);
	pser.add<std::string>(exclude, 'e', sexclude, false);
	pser.add(help, '?', shelp);
	HRSRC help = FindResource(NULL, MAKEINTRESOURCE(IDR_CONFIG), L"HELP");
	if (help) {
		HGDIOBJ res = LoadResource(NULL, help);
if (res) {
	size_t sz = SizeofResource(NULL, help);
	std::unique_ptr<char[]> data(new char[sz + 1024]);
	std::string format(sz, '\0');
	LPVOID lp = LockResource(res);
	memcpy((LPVOID)format.data(), lp, sz);
	snprintf(data.get(), sz + 1024, format.c_str(), argv[0], argv[0], argv[0], argv[0], argv[0], argv[0], argv[0], argv[0]);
	pser.footer(data.get());
	data.reset(nullptr);
	UnlockResource(lp);
	FreeResource(res);
}
	}


	pser.parse_check(argc, argv);
	const std::string&Lang = pser.get<std::string>(lang),&cfgpath= pser.get<std::string>(selcfg);
	std::ifstream Input(cfgpath, std::ios::binary);
	auto getMap = [](Json::Value&maps)->std::string {
		std::string map;
		if (maps.isArray())for (auto &v : maps)map += v.asString();
		else if (maps.isString())map += maps.asString();
		return map;
	};
	auto MBToWideChar = [](const std::string &src)->std::wstring {
		std::wstring ws;
		ws.resize(MultiByteToWideChar(CP_ACP, 0, src.c_str(), src.size(), 0, 0));
		MultiByteToWideChar(CP_ACP, 0, src.c_str(), src.size(), (wchar_t*)ws.data(), ws.size());
		return ws;
	};
	Json::Value val;
	if (Input) {
		size_t curPID = 1;
		
		Json::Reader reader;
		reader.parse(Input, val);
		Input.close();

	}
	else openErr(MBToWideChar(cfgpath));
		auto&pages = val["Language"][Lang]["Pages"];
		if (pser.exist(tex)) {
			size_t w, h, fw, fh, i;
			const std::string &tw = pser.get<std::string>(texSz);
			const std::string &texN = pser.get<std::string>(tex);
			i = tw.find('*');
		
			w = std::atoi(tw.c_str());
			h = (i != std::string::npos&&i != tw.size() - 1) ? atoi(&tw[i + 1]) : w;
			const std::string &fwh = pser.get<std::string>(size);
			i = fwh.find('*');
			fw = std::atoi(fwh.c_str());
			fh = (i != std::string::npos&&i != fwh.size() - 1) ? atoi(&fwh[i + 1]) : fw;
			float ow = pser.get<float>(outline);
			auto hex = [](const std::string&str)->uint32_t {
				uint32_t hex = 0;
				size_t i = str.find_first_not_of("0x", 0), bit = 8, e(4);
				while (bit--&&i < str.size())hex = (hex << 4) + (str[i] - (str[i] <= '9' ? '0' : ((str[i] <= 'F' ? 'A' : 'a') - 0xA))), i++;

				return hex;
			};

			uint32_t oc = hex(pser.get<std::string>(outlineCol)), fc = hex(pser.get<std::string>(fontCol));
			FreeType::Pixel32 poc(oc), pfc(fc);
			std::swap(pfc.r, pfc.b);
			FreeType ft(pser.get<std::string>(font), fw, fh, w, h, pser.exist(base) ? pser.get<long>(base) : h / 16 * .75);

			std::string map;
			size_t cid(0);
			std::stringstream  ss,s2;
			std::set<size_t>texid;
			if (pser.exist(pageid)) {
				;
				s2.str(pser.get<std::string>(pageid));
				size_t id(0);
				while (s2 >> id)texid.insert(id);
			}
			for (Json::Value &sub : pages) {
				ss.str("");
				map = getMap(sub["Maps"]);
				cid++;
				size_t id = sub["Id"].isInt() ? sub["Id"].asInt() : cid;
				ss << texN << id << ".png";
				if (texid.empty() || texid.find(id) != texid.end()){
				if(ow)ft.RenderOutline(UTF::Decode(std::move(map)), ss.str().c_str(), pfc, poc, ow);
				else ft.Render(UTF::Decode(std::move(map)), ss.str().c_str());
				}
				map.clear();

			};



		}
		auto split = [](std::wstring&ws, std::wstring&map, Json::Value&val) {
			size_t i = 256 - map.size(), lp(0);
			i = i > ws.size() ? ws.size() : i;
			if (i)
			{
				map += ws.substr(0, i);
				ws.erase(0, i);
			}
			while (lp < map.size()) {
				val.append(UTF::Encode(map.substr(lp, map.size() - lp < 16 ? map.size() - lp : 16)));
				lp += 16;
			}
		};
		local.MainInit(Lang, val);
		bool badd = pser.exist(add), brm = pser.exist(rm), bin = pser.exist(input);
		if (pser.exist(output)) {
			std::ofstream out(pser.get<std::string>(output), std::ios::binary);
			auto outfile = [&out, &val]() {
				Json::StyledWriter sw;
				out << sw.write(val);
				out.close();
			};
			if (bin) {
				std::vector<std::pair<std::string, std::string>>list;
				Reader reader;
				reader.Parse(pser.get<std::string>(input));
				std::set<std::wstring>exclist;
				if (pser.exist(exclude)) {
					std::ifstream exc(pser.get<std::string>(exclude), std::ios::binary);
					if(exc){
					exclist = Reader::Parse(Reader::RMap(), Reader::RMap(), exc, true);
				//	for (auto&ws : exclist)std::wcout << ws << '\n';
					exc.close();
					}
				}

				std::map<wchar_t, size_t>err;
				for (auto &loc : reader) {
					std::string str;
					for (auto v : loc.second) {
						auto &ws = local.GetCharCfg(v);
						if (!ws.use) err[v]++;
						else {
							for (uint8_t c : ws.str)if (c)str += c;
							ws.refCnt++;
						}
					}
					if (!str.empty() && exclist.find(loc.first) == exclist.end())list.push_back(std::make_pair(UTF::Encode(loc.first), std::move(str)));
				}
				auto &refmap = err;
				auto sortA = [&refmap](wchar_t l, wchar_t r)->bool {
					return refmap[l] > refmap[r];
				};
				std::wstring ws;
				if (!err.empty()) {
					
				
					for (auto &ch : err)ws += ch.first;
					std::sort(ws.begin(), ws.end(), sortA);
					msgmgr(MsgType::Error, uncfg, ws.c_str());
				}
				ws.clear();
				for (size_t i(0); i < 1 << 16; i++) {
					auto &wcfg = local.GetCharCfg(i);
					if (wcfg.use && !wcfg.refCnt)ws+=i;
				}
				if (!ws.empty())msgmgr(MsgType::Info, unused, ws.c_str());
				for (auto &sub : reader.Param) out << UTF::Encode(sub.first) << "  \"" << UTF::Encode(sub.second) << "\"\n";
				for (auto &sub : list) out << '"' << sub.first << "\"  \"" << sub.second << "\"\n";
				out.close();
			}
			else if (badd || brm) {
				std::set<wchar_t>mset;
				if (brm) {
					std::wstring &ws = MBToWideChar(pser.get<std::string>(rm));

					for (auto ch : ws)mset.insert(ch);
					for (auto&sub : pages) {
						auto &val = sub["Maps"];
						//std::locale::global(std::locale("chs"));
						std::wstring map = UTF::Decode(getMap(val));
						//std::wcout << map.size() << L":" << map << std::endl;
						for (size_t i(0); i < map.size();) {
							if (mset.find(map[i]) != mset.end())map.erase(i, 1);
							else i++;
						}
						val.clear();
						split(map, std::wstring(), val);

					}

				}
				if (badd) {
					std::wstring &ws = MBToWideChar(pser.get<std::string>(add));
					for (auto ch : ws)if (!local.GetCharCfg(ch).use)mset.insert(ch);
					ws.clear();
					for (auto ch : mset)ws += ch;
					for (auto&sub : pages) {
						auto &sval = sub["Maps"];
						std::wstring &map = UTF::Decode(getMap(sval));

						if (map.size() < 256) {
							sval.clear(); split(ws, map, sval);
						}
					}
					std::stringstream ss;
					for (size_t i(0); i < 256; i++)ss << 0 << ' ' << 12 << ' ';
					while (!ws.empty()) {
						Json::Value sval;
						int id;
						std::cout << snewpage << std::endl;
						while (std::cout << "Id:", std::cin >> id, local.Page[id].use)std::cout << srefid << std::endl;
						sval["Id"] = id;
						std::cout << "Font:";
						std::string str;
						std::cin.ignore();
						std::getline(std::cin, str);
						sval["Font"] = str;
						split(ws, std::wstring(L"???????????"), sval["Maps"]);
						sval["Params"] = ss.str();
						pages.append(sval);
					}

				}
				outfile();
			}

		}
		else if (badd || brm || bin)printf(sioerr);
	if (wngCnt || errCnt)printf(weout, wngCnt, errCnt);
    return (wngCnt<<sizeof(size_t)*4)|errCnt;
}