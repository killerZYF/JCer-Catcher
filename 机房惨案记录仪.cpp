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
string filename="��¼�ļ�.txt";
ofstream file(filename);
MSG msg;
// 0 ��ɫ 1 ���� 2 ���� 3 ���� 4 ��ɫ 5 ���� 6 ���� 7 ��ɫ
// 8 ��ɫ 9 ��ɫ a ���� b ��ɫ c ǳ�� d ��ɫ e ���� f ����
void out(string s,int id=7,int tim=0){ // �����ɫ����
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
void HideCursor(){ // ���ع��
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void setp(int x,int y){ // ���ù��λ��
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord={short(y*2),short(x)};
	SetConsoleCursorPosition(handle,coord);
}
int lh=151,lw=160,test=1;
void setsz(int h,int w){ // ���ô��ڴ�С
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
string getTime(){ // ��ȡʱ�� 
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
pair<int,int>getPoint(){ // ��ȡ���λ�� 
	POINT mpoint;
	GetCursorPos(&mpoint);
	return make_pair(mpoint.x,mpoint.y);
}
void neverStop(int sig_num){
	signal(SIGINT,neverStop);
	file<<"["<<getTime()<<"] �յ� "<<sig_num<<" �ر��ź�.\n"; 
	ot.push_back(make_pair("[�رյ�Ԫ] ��⵽��ͼ�ر�.     ",12));
}
void neverClose(){ // �������Ͻǹرշ�ʽ 
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
void noChoose(){ // ����ѡ��ģʽ��������ѡ��ģʽ���µĳ�����ͣ 
    SystemParametersInfo(SPI_SETSELECTIONFADE,TRUE,NULL,0);
}
LRESULT CALLBACK KeyboardProc(int nCode,WPARAM wParam,LPARAM lParam){ // ���������� 
    if(nCode>=0){
        if(wParam==WM_KEYDOWN){
            KBDLLHOOKSTRUCT* kbdData=reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
            int keyCode=kbdData->vkCode;
            if(keyCode==162){ // ���� Ctrl 
				ot.push_back(make_pair("[��ص�Ԫ] ��⵽���� Ctrl.    ",14));++dd;
				ot.push_back(make_pair("[���ӵ�Ԫ] �ɹ����� Ctrl.      ",11));++dd;
				file<<"["<<getTime()<<"] ���� Ctrl.\n"; 
				return 1;
            }
            if(keyCode==91){ // ���� Win
				ot.push_back(make_pair("[��ص�Ԫ] ��⵽���� Win.     ",14));++dd;
				ot.push_back(make_pair("[���ӵ�Ԫ] �ɹ����� Win.       ",11));++dd;
				file<<"["<<getTime()<<"] ���� Win.\n"; 
				return 1;
            }
            if(keyCode==161||keyCode==160){ // ���� Shift 
				ot.push_back(make_pair("[��ص�Ԫ] ��⵽���� Shift.   ",14));++dd;
				ot.push_back(make_pair("[���ӵ�Ԫ] �ɹ����� Shift.     ",11));++dd;
				file<<"["<<getTime()<<"] ���� Shift.\n"; 
				return 1;				
			} 
            if(keyCode==27){ // ���� Esc 
				ot.push_back(make_pair("[��ص�Ԫ] ��⵽���� Esc.     ",14));++dd;
				ot.push_back(make_pair("[���ӵ�Ԫ] �ɹ����� Esc.       ",11));++dd;
				file<<"["<<getTime()<<"] ���� Esc.\n"; 
				return 1;				
			} 
			if(nCode==HSHELL_ENDTASK){ // ���κ�� 
				ot.push_back(make_pair("[��ص�Ԫ] ��⵽���¹ر�.     ",14));++dd;
				ot.push_back(make_pair("[���ӵ�Ԫ] �ɹ����عر�.       ",11));++dd;		
				return 1;		
			}
        }
    }
    return CallNextHookEx(NULL,nCode,wParam,lParam);
}
string st,tit;
signed main(){ // ��� 
	tit="title JC ��¼�� v"+VER;
	system(tit.c_str()); 
    setsz(500,500);
    HideCursor();
    neverClose();
    noChoose();
    HHOOK hook=SetWindowsHookEx(WH_KEYBOARD_LL,KeyboardProc,NULL,0);
    signal(SIGINT,neverStop); // ��׽�ر��ź� 
	file<<"\n--------------������-------------\n";
	file<<"["<<getTime()<<"] �������� "<<VER<<" �汾.\n"; 
	out("--------------------------------------\n",6);
	out("|",6);out("[��ʾ��Ԫ] ");out("�����Ѿ������Զ����ģʽ.",10);out("|\n",6);
	out("|",6);out("[��ʾ��Ԫ] ");out("�����ڻ����뿪ʱʹ�õ���.",12);out("|\n",6);
	for(int i=1;i<=10;i++){ot.push_back(make_pair("[��ص�Ԫ] ��ص�Ԫ�Ѿ�λ.     ",10));++dd;}
    if(hook==NULL){ot.push_back(make_pair("[���ӵ�Ԫ] �޷�ע�ṳ��.       ",12));++dd;}
	else{ot.push_back(make_pair("[���ӵ�Ԫ] ���ӵ�Ԫ�Ѿ�λ.     ",10));++dd;}
	while(1){
		m=getPoint();
		signal(SIGINT,neverStop); // ��׽�ر��ź� 
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if(m!=pm){ // ��걻�ƶ� 
			file<<"["<<getTime()<<"] ���� ("<<pm.first<<","<<pm.second<<") λ���Ƶ� ("<<m.first<<","<<m.second<<") λ��.\n"; 
			// cout<<"["<<getTime()<<"] ���� ("<<pm.first<<","<<pm.second<<") λ���Ƶ� ("<<m.first<<" "<<m.second<<") λ��.\n";
			if(pm.first==0&&pm.second==0){ot.push_back(make_pair("[��ص�Ԫ] �������ʼ��.     ",11));}
			else{if(ot[int(ot.size()-1)].first!="[��ص�Ԫ] ��⵽����ƶ�.     ")ot.push_back(make_pair("[��ص�Ԫ] ��⵽����ƶ�.     ",11));}
			++dd;
  		}
		for(int i=0;i<256;i++){
			if(KEY_DOWN(i)){
				if(i==0x01){
					file<<"["<<getTime()<<"] ����� ("<<m.first<<","<<m.second<<") λ�õ��.\n";
					// cout<<"["<<getTime()<<"] ����� ("<<m.first<<","<<m.second<<") λ�õ��.\n";
					if(ot[int(ot.size()-1)].first!="[��ص�Ԫ] ��⵽�����.     ")ot.push_back(make_pair("[��ص�Ԫ] ��⵽�����.     ",14));++dd;
				}else if(i==0x02){
					file<<"["<<getTime()<<"] ����� ("<<m.first<<","<<m.second<<") λ�ð����Ҽ�.\n";
					// cout<<"["<<getTime()<<"] ����� ("<<m.first<<","<<m.second<<") λ�ð����Ҽ�.\n";
					ot.push_back(make_pair("[��ص�Ԫ] ��⵽����һ�.     ",14));++dd;
				}else if(i==0x08){
					file<<"["<<getTime()<<"] ��⵽���� BackSpace ��.\n";
					// cout<<"["<<getTime()<<"] ��⵽���� BackSpace ��.\n";
					if(ot[int(ot.size()-1)].first!="[��ص�Ԫ] ��⵽�����˸�.     ")ot.push_back(make_pair("[��ص�Ԫ] ��⵽�����˸�.     ",14));++dd;
				}else if(i==0x0d){
					file<<"["<<getTime()<<"] ��⵽���� Enter ��.\n";
					// cout<<"["<<getTime()<<"] ��⵽���� Enter ��.\n";
					if(ot[int(ot.size()-1)].first!="[��ص�Ԫ] ��⵽���»س�.     ")ot.push_back(make_pair("[��ص�Ԫ] ��⵽���»س�.     ",14));++dd;
				}else if(i==0x1b){
					file<<"["<<getTime()<<"] ��⵽���� Esc ��.\n";
					// cout<<"["<<getTime()<<"] ��⵽���� Esc ��.\n";
					if(ot[int(ot.size()-1)].first!="[��ص�Ԫ] ��⵽���� Esc.     ")ot.push_back(make_pair("[��ص�Ԫ] ��⵽���� Esc.     ",14));++dd;
				}else if(i==0x20){
					file<<"["<<getTime()<<"] ��⵽���¿ո��.\n";
					// cout<<"["<<getTime()<<"] ��⵽���¿ո��.\n";
					if(ot[int(ot.size()-1)].first!="[��ص�Ԫ] ��⵽���¿ո�.     ")ot.push_back(make_pair("[��ص�Ԫ] ��⵽���¿ո�.     ",11));++dd;
				}else if(i==0x12){
					file<<"["<<getTime()<<"] ��⵽���� Alt ��.\n";
					// cout<<"["<<getTime()<<"] ��⵽���� Alt ��.\n";
					if(ot[int(ot.size()-1)].first!="[��ص�Ԫ] ��⵽���� Alt.     ")ot.push_back(make_pair("[��ص�Ԫ] ��⵽���� Alt.     ",11));++dd;
				}else if(i>=int('0')&&i<=int('9')){
					file<<"["<<getTime()<<"] ��⵽���� "<<char(i)<<" ��.\n";
					// cout<<"["<<getTime()<<"] ��⵽���� "<<char(i)<<" ��.\n";
					if(ot[int(ot.size()-1)].first!="[��ص�Ԫ] ��⵽����.         "&&ot[int(ot.size()-1)].second!=11)ot.push_back(make_pair("[��ص�Ԫ] ��⵽����.         ",11));++dd;
				}else if(i>=int('A')&&i<=int('Z')){
					file<<"["<<getTime()<<"] ��⵽���� "<<char(i)<<" ��.\n";
					// cout<<"["<<getTime()<<"] ��⵽���� "<<char(i)<<" ��.\n";
					if(ot[int(ot.size()-1)].first!="[��ص�Ԫ] ��⵽����.         "&&ot[int(ot.size()-1)].second!=14)ot.push_back(make_pair("[��ص�Ԫ] ��⵽����.         ",14));++dd;
				}else if(i==0x11){
					file<<"["<<getTime()<<"] ��⵽���� Ctrl ��.\n";
					// cout<<"["<<getTime()<<"] ��⵽���� Ctrl ��.\n";
					ot.push_back(make_pair("[��ص�Ԫ] ��⵽���� Ctrl.    ",14));++dd;
				}else if(i>=0x70&&i<=0x7b){
					file<<"["<<getTime()<<"] ��⵽���� F"<<(i-0x70+1)<<" ��.\n";
					// cout<<"["<<getTime()<<"] ��⵽���� F"<<(i-0x70+1)<<" ��.\n";
					if(ot[int(ot.size()-1)].first!="[��ص�Ԫ] ��⵽���� F ���ܼ�.")ot.push_back(make_pair("[��ص�Ԫ] ��⵽���� F ���ܼ�.",14));++dd;
				}else if(i>=0x60&&i<=0x69){
					file<<"["<<getTime()<<"] ��⵽���� "<<(i-0x60)<<" ��.\n";
					// cout<<"["<<getTime()<<"] ��⵽���� "<<(i-0x60)<<" ��.\n";
					if(ot[int(ot.size()-1)].first!="[��ص�Ԫ] ��⵽����С����.   ")ot.push_back(make_pair("[��ص�Ԫ] ��⵽����С����.   ",11));++dd;
				}else if(i==0xa0||i==0xa1){
					file<<"["<<getTime()<<"] ��⵽���� Shift ��.\n";
					// cout<<"["<<getTime()<<"] ��⵽���� Shift ��.\n";
					ot.push_back(make_pair("[��ص�Ԫ] ��⵽���� Shift.   ",14));++dd;
				}else if(i==91||i==92){
					file<<"["<<getTime()<<"] ��⵽���� Win ��.\n";
					// cout<<"["<<getTime()<<"] ��⵽���� Win ��.\n";
					ot.push_back(make_pair("[��ص�Ԫ] ��⵽���� Win.     ",14));++dd;
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
				setp(14,0);out("|",6);out("[�ļ���Ԫ] ");out("�ļ��޷���.       ",12,atm);out("     |\n",6);
		    }else{
				setp(14,0);out("|",6);out("[�ļ���Ԫ] ");out("�ļ�����.           ",10,atm);out("     |\n",6);
			}
			// setsz(500,500);
		}
		if(ot.size()>1000){ // ��ֹ�ڴ汬ը 
			for(int i=max(0,int(ot.size())-1-10),j=0;i<(int)ot.size();i++,j++){cot.push_back(ot[i]);}	
			ot.clear(); 
			for(auto v:cot)ot.push_back(v);
			ot.push_back(make_pair("[�ļ���Ԫ] �ڴ���������.     ",10));
		}
		setp(15,0);out("|",6);
		st=getTime(); 
		out("[ʱ�䵥Ԫ] ");out(st,3);for(int i=1;i<=25-int(st.size());i++)cout<<" ";
		out("|\n",6);
		pm=m;pdd=dd;
	}
    UnhookWindowsHookEx(hook); // ж�ع��� 
    return 0;
}
//note: v1.11 �汾�����ԣ���ѧУ���ԣ��޸� BUG & ���ϼ��Ե���ʾ 
