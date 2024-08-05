//2022tysc0819
#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h> 
#define cls system("cls")
#define KEY_DOWN(VK_NONAME)((GetAsyncKeyState(VK_NONAME)&0x8000)?1:0)
using namespace std;
//#define int long long
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=1e6+10,M=1010,P=1e9+7,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
const string VER="1.11";
int n,sys[6],dd,pdd,pr,atm;
pair<int,int>pm,m;
vector<pair<string,int> >ot,cot;
string prt,cut1,cut2;
string filename="记录文件.txt";
ofstream file(filename);
MSG msg;
// 0 黑色 1 深蓝 2 深绿 3 天蓝 4 红色 5 深紫 6 土黄 7 白色
// 8 灰色 9 蓝色 a 草绿 b 青色 c 浅红 d 紫色 e 亮黄 f 亮白
void out(string s,int id=7,int tim=0){ // 输出彩色的字
    HANDLE handle=::GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle,&info);
    WORD colorBak=info.wAttributes;
    SetConsoleTextAttribute(handle,id);
    for(int i=0;i<(int)s.size();i++){cout<<s[i];Sleep(tim);}
    SetConsoleTextAttribute(handle,colorBak);
    return;
}
void tout(string s,int id=7,int tim=0){
	int i=0;cut1=cut2="";
	for(;i<(int)s.size();i++){if(s[i]==' '){break;}cut1+=s[i];}
	for(;i<(int)s.size();i++){cut2+=s[i];}
	out(cut1);out(cut2,id,tim);
}
void HideCursor(){ // 隐藏光标
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void setp(int x,int y){ // 设置光标位置
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord={short(y*2),short(x)};
	SetConsoleCursorPosition(handle,coord);
}
int lh=151,lw=160,test=1;
void setsz(int h,int w){ // 设置窗口大小
    POINT point;
    HWND target,parent;
	GetCursorPos(&point);
	target=WindowFromPoint(point);
	if(target!=NULL&&target!=INVALID_HANDLE_VALUE) {
	    parent=GetParent(target);
		while(parent!=NULL&&parent!=INVALID_HANDLE_VALUE){
	    	target=parent;
	        parent=GetParent(target);
	    }
	    RECT rect;
	    GetWindowRect(target,&rect);
	    MoveWindow(target,rect.left,rect.top,w,h,true);
	}
}
string getTime(){ // 获取时间 
	time_t now=time(NULL);
	tm *tm_t=localtime(&now);
	sys[0]=tm_t->tm_year+1900;
	sys[1]=tm_t->tm_mon+1;
	sys[2]=tm_t->tm_mday;
	sys[3]=tm_t->tm_hour;
	sys[4]=tm_t->tm_min;
	sys[5]=tm_t->tm_sec;
	return to_string(sys[0])+"."+to_string(sys[1])+"."+to_string(sys[2])+" "+to_string(sys[3])+":"+to_string(sys[4])+":"+to_string(sys[5]);
}
pair<int,int>getPoint(){ // 获取鼠标位置 
	POINT mpoint;
	GetCursorPos(&mpoint);
	return make_pair(mpoint.x,mpoint.y);
}
void neverStop(int sig_num){
	signal(SIGINT,neverStop);
	file<<"["<<getTime()<<"] 收到 "<<sig_num<<" 关闭信号.\n"; 
	ot.push_back(make_pair("[关闭单元] 监测到试图关闭.     ",12));
}
void neverClose(){ // 屏蔽左上角关闭方式 
	HWND hwnd=GetConsoleWindow();
	HMENU hmenu=GetSystemMenu(hwnd,false);
	RemoveMenu(hmenu,SC_CLOSE,MF_BYCOMMAND);
	LONG style=GetWindowLong(hwnd,GWL_STYLE);
	style&=~(WS_MINIMIZEBOX);
	SetWindowLong(hwnd,GWL_STYLE,style);
	SetWindowPos(hwnd,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	ShowWindow(hwnd,SW_SHOWNORMAL);
	DestroyMenu(hmenu);
	ReleaseDC(hwnd,NULL);
} 
void noChoose(){ // 禁用选择模式，避免因选择模式导致的程序暂停 
    SystemParametersInfo(SPI_SETSELECTIONFADE,TRUE,NULL,0);
}
LRESULT CALLBACK KeyboardProc(int nCode,WPARAM wParam,LPARAM lParam){ // 钩子主函数 
    if(nCode>=0){
        if(wParam==WM_KEYDOWN){
            KBDLLHOOKSTRUCT* kbdData=reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
            int keyCode=kbdData->vkCode;
            if(keyCode==162){ // 屏蔽 Ctrl 
				ot.push_back(make_pair("[监控单元] 监测到按下 Ctrl.    ",14));++dd;
				ot.push_back(make_pair("[钩子单元] 成功拦截 Ctrl.      ",11));++dd;
				file<<"["<<getTime()<<"] 拦截 Ctrl.\n"; 
				return 1;
            }
            if(keyCode==91){ // 屏蔽 Win
				ot.push_back(make_pair("[监控单元] 监测到按下 Win.     ",14));++dd;
				ot.push_back(make_pair("[钩子单元] 成功拦截 Win.       ",11));++dd;
				file<<"["<<getTime()<<"] 拦截 Win.\n"; 
				return 1;
            }
            if(keyCode==161||keyCode==160){ // 屏蔽 Shift 
				ot.push_back(make_pair("[监控单元] 监测到按下 Shift.   ",14));++dd;
				ot.push_back(make_pair("[钩子单元] 成功拦截 Shift.     ",11));++dd;
				file<<"["<<getTime()<<"] 拦截 Shift.\n"; 
				return 1;				
			} 
            if(keyCode==27){ // 屏蔽 Esc 
				ot.push_back(make_pair("[监控单元] 监测到按下 Esc.     ",14));++dd;
				ot.push_back(make_pair("[钩子单元] 成功拦截 Esc.       ",11));++dd;
				file<<"["<<getTime()<<"] 拦截 Esc.\n"; 
				return 1;				
			} 
			if(nCode==HSHELL_ENDTASK){ // 屏蔽红叉 
				ot.push_back(make_pair("[监控单元] 监测到按下关闭.     ",14));++dd;
				ot.push_back(make_pair("[钩子单元] 成功拦截关闭.       ",11));++dd;		
				return 1;		
			}
        }
    }
    return CallNextHookEx(NULL,nCode,wParam,lParam);
}
string st,tit;
signed main(){ // 监测 
	tit="title JC 记录仪 v"+VER;
	system(tit.c_str()); 
    setsz(500,500);
    HideCursor();
    neverClose();
    noChoose();
    HHOOK hook=SetWindowsHookEx(WH_KEYBOARD_LL,KeyboardProc,NULL,0);
    signal(SIGINT,neverStop); // 捕捉关闭信号 
	file<<"\n--------------新运行-------------\n";
	file<<"["<<getTime()<<"] 程序运行 "<<VER<<" 版本.\n"; 
	out("--------------------------------------\n",6);
	out("|",6);out("[显示单元] ");out("电脑已经设置自动监控模式.",10);out("|\n",6);
	out("|",6);out("[显示单元] ");out("请勿在机主离开时使用电脑.",12);out("|\n",6);
	for(int i=1;i<=10;i++){ot.push_back(make_pair("[监控单元] 监控单元已就位.     ",10));++dd;}
    if(hook==NULL){ot.push_back(make_pair("[钩子单元] 无法注册钩子.       ",12));++dd;}
	else{ot.push_back(make_pair("[钩子单元] 钩子单元已就位.     ",10));++dd;}
	while(1){
		m=getPoint();
		signal(SIGINT,neverStop); // 捕捉关闭信号 
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if(m!=pm){ // 鼠标被移动 
			file<<"["<<getTime()<<"] 鼠标从 ("<<pm.first<<","<<pm.second<<") 位置移到 ("<<m.first<<","<<m.second<<") 位置.\n"; 
			// cout<<"["<<getTime()<<"] 鼠标从 ("<<pm.first<<","<<pm.second<<") 位置移到 ("<<m.first<<" "<<m.second<<") 位置.\n";
			if(pm.first==0&&pm.second==0){ot.push_back(make_pair("[监控单元] 鼠标侦测初始化.     ",11));}
			else{if(ot[int(ot.size()-1)].first!="[监控单元] 监测到鼠标移动.     ")ot.push_back(make_pair("[监控单元] 监测到鼠标移动.     ",11));}
			++dd;
  		}
		for(int i=0;i<256;i++){
			if(KEY_DOWN(i)){
				if(i==0x01){
					file<<"["<<getTime()<<"] 鼠标在 ("<<m.first<<","<<m.second<<") 位置点击.\n";
					// cout<<"["<<getTime()<<"] 鼠标在 ("<<m.first<<","<<m.second<<") 位置点击.\n";
					if(ot[int(ot.size()-1)].first!="[监控单元] 监测到鼠标点击.     ")ot.push_back(make_pair("[监控单元] 监测到鼠标点击.     ",14));++dd;
				}else if(i==0x02){
					file<<"["<<getTime()<<"] 鼠标在 ("<<m.first<<","<<m.second<<") 位置按下右键.\n";
					// cout<<"["<<getTime()<<"] 鼠标在 ("<<m.first<<","<<m.second<<") 位置按下右键.\n";
					ot.push_back(make_pair("[监控单元] 监测到鼠标右击.     ",14));++dd;
				}else if(i==0x08){
					file<<"["<<getTime()<<"] 监测到按下 BackSpace 键.\n";
					// cout<<"["<<getTime()<<"] 监测到按下 BackSpace 键.\n";
					if(ot[int(ot.size()-1)].first!="[监控单元] 监测到按下退格.     ")ot.push_back(make_pair("[监控单元] 监测到按下退格.     ",14));++dd;
				}else if(i==0x0d){
					file<<"["<<getTime()<<"] 监测到按下 Enter 键.\n";
					// cout<<"["<<getTime()<<"] 监测到按下 Enter 键.\n";
					if(ot[int(ot.size()-1)].first!="[监控单元] 监测到按下回车.     ")ot.push_back(make_pair("[监控单元] 监测到按下回车.     ",14));++dd;
				}else if(i==0x1b){
					file<<"["<<getTime()<<"] 监测到按下 Esc 键.\n";
					// cout<<"["<<getTime()<<"] 监测到按下 Esc 键.\n";
					if(ot[int(ot.size()-1)].first!="[监控单元] 监测到按下 Esc.     ")ot.push_back(make_pair("[监控单元] 监测到按下 Esc.     ",14));++dd;
				}else if(i==0x20){
					file<<"["<<getTime()<<"] 监测到按下空格键.\n";
					// cout<<"["<<getTime()<<"] 监测到按下空格键.\n";
					if(ot[int(ot.size()-1)].first!="[监控单元] 监测到按下空格.     ")ot.push_back(make_pair("[监控单元] 监测到按下空格.     ",11));++dd;
				}else if(i==0x12){
					file<<"["<<getTime()<<"] 监测到按下 Alt 键.\n";
					// cout<<"["<<getTime()<<"] 监测到按下 Alt 键.\n";
					if(ot[int(ot.size()-1)].first!="[监控单元] 监测到按下 Alt.     ")ot.push_back(make_pair("[监控单元] 监测到按下 Alt.     ",11));++dd;
				}else if(i>=int('0')&&i<=int('9')){
					file<<"["<<getTime()<<"] 监测到按下 "<<char(i)<<" 键.\n";
					// cout<<"["<<getTime()<<"] 监测到按下 "<<char(i)<<" 键.\n";
					if(ot[int(ot.size()-1)].first!="[监控单元] 监测到输入.         "&&ot[int(ot.size()-1)].second!=11)ot.push_back(make_pair("[监控单元] 监测到输入.         ",11));++dd;
				}else if(i>=int('A')&&i<=int('Z')){
					file<<"["<<getTime()<<"] 监测到按下 "<<char(i)<<" 键.\n";
					// cout<<"["<<getTime()<<"] 监测到按下 "<<char(i)<<" 键.\n";
					if(ot[int(ot.size()-1)].first!="[监控单元] 监测到输入.         "&&ot[int(ot.size()-1)].second!=14)ot.push_back(make_pair("[监控单元] 监测到输入.         ",14));++dd;
				}else if(i==0x11){
					file<<"["<<getTime()<<"] 监测到按下 Ctrl 键.\n";
					// cout<<"["<<getTime()<<"] 监测到按下 Ctrl 键.\n";
					ot.push_back(make_pair("[监控单元] 监测到按下 Ctrl.    ",14));++dd;
				}else if(i>=0x70&&i<=0x7b){
					file<<"["<<getTime()<<"] 监测到按下 F"<<(i-0x70+1)<<" 键.\n";
					// cout<<"["<<getTime()<<"] 监测到按下 F"<<(i-0x70+1)<<" 键.\n";
					if(ot[int(ot.size()-1)].first!="[监控单元] 监测到按下 F 功能键.")ot.push_back(make_pair("[监控单元] 监测到按下 F 功能键.",14));++dd;
				}else if(i>=0x60&&i<=0x69){
					file<<"["<<getTime()<<"] 监测到按下 "<<(i-0x60)<<" 键.\n";
					// cout<<"["<<getTime()<<"] 监测到按下 "<<(i-0x60)<<" 键.\n";
					if(ot[int(ot.size()-1)].first!="[监控单元] 监测到按下小键盘.   ")ot.push_back(make_pair("[监控单元] 监测到按下小键盘.   ",11));++dd;
				}else if(i==0xa0||i==0xa1){
					file<<"["<<getTime()<<"] 监测到按下 Shift 键.\n";
					// cout<<"["<<getTime()<<"] 监测到按下 Shift 键.\n";
					ot.push_back(make_pair("[监控单元] 监测到按下 Shift.   ",14));++dd;
				}else if(i==91||i==92){
					file<<"["<<getTime()<<"] 监测到按下 Win 键.\n";
					// cout<<"["<<getTime()<<"] 监测到按下 Win 键.\n";
					ot.push_back(make_pair("[监控单元] 监测到按下 Win.     ",14));++dd;
				}
			}
		} 
		if(dd!=pdd){
			if(pdd==0)atm=2;
			else atm=0;
			for(int i=max(0,int(ot.size())-1-10),j=0;i<(int)ot.size();i++,j++){
				setp(j+3,0);
				out("|",6);tout(ot[i].first,ot[i].second,atm);out("     |\n",6);
				setp(j+3,0);
			}
			setp(16,0);out("--------------------------------------\n",6);
		    if(!file.is_open()){
				setp(14,0);out("|",6);out("[文件单元] ");out("文件无法打开.       ",12,atm);out("     |\n",6);
		    }else{
				setp(14,0);out("|",6);out("[文件单元] ");out("文件正常.           ",10,atm);out("     |\n",6);
			}
			// setsz(500,500);
		}
		if(ot.size()>1000){ // 防止内存爆炸 
			for(int i=max(0,int(ot.size())-1-10),j=0;i<(int)ot.size();i++,j++){cot.push_back(ot[i]);}	
			ot.clear(); 
			for(auto v:cot)ot.push_back(v);
			ot.push_back(make_pair("[文件单元] 内存清空已完成.     ",10));
		}
		setp(15,0);out("|",6);
		st=getTime(); 
		out("[时间单元] ");out(st,3);for(int i=1;i<=25-int(st.size());i++)cout<<" ";
		out("|\n",6);
		pm=m;pdd=dd;
	}
    UnhookWindowsHookEx(hook); // 卸载钩子 
    return 0;
}
//note: v1.11 版本新特性：来学校测试，修复 BUG & 加上简略的显示 
