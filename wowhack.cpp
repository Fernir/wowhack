#include "stdafx.h"
#include "wowhack.h"
#include "Tlhelp32.h"
// HKEY_LOCAL_MACHINE/SHOFTWARE/Blizzard Entertainment/InstallPath
char* wow_dir = "D:\\WOW\\World of Warcraft\\";
//char* wow_dir = "E:\\games\\World of Warcraft\\";
char* wow_dir_tw = "D:\\WOW\\wowtw\\";

#ifndef _OUT
char* sdll = "wowin_cn.dll";
#else
char* sdll = "wowin_cn_out.dll";
#endif

char* sdll_tw = "wowin_tw.dll";

/*
	ReadDll��������dll����
	WriteDll������dll��������д��ȥ
*/
static char* pdll = NULL;
static char* pstack = NULL;
static MODULEENTRY32 me ={sizeof(me)};
static DWORD crtheap_size = 0;
static LPVOID crtheap_base = 0;

void EerrorMessage( char* msg ){
	MessageBox( NULL,msg,"error",MB_ICONERROR|MB_OK );
}

//wowin.dll����Լ���_crtheapд�뵽0x80000��λ��
LPVOID GetCrtHeapBase(){
	__try{
		LPDWORD pcrtheap = (LPDWORD)0x80000;
		crtheap_base = (LPVOID)pcrtheap[0];
		crtheap_size = pcrtheap[1];
	}__except(EXCEPTION_EXECUTE_HANDLER){
		crtheap_base = NULL;
	}
	return crtheap_base;
}

BOOL ReadDll(HANDLE hProcess,char* lib_name){
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,GetProcessId(hProcess) );
	if( hSnapshot ==NULL ){
		EerrorMessage("CreateToolhelp32Snapshot return NULL");
		return FALSE;
	}
	BOOL fFound = FALSE;
	BOOL fMoreMods = Module32First( hSnapshot,&me );
	for(;fMoreMods;fMoreMods = Module32Next(hSnapshot,&me)){
		fFound = (lstrcmpi(me.szModule,lib_name)==0)||(lstrcmpi(me.szExePath,lib_name)==0);
		if( fFound )break;
	}
	if( fFound ){
		SIZE_T size;
		pdll = new char[me.modBaseSize];
		if( !ReadProcessMemory(hProcess,me.modBaseAddr,pdll,me.modBaseSize,&size) ){
			EerrorMessage("ReadDll��ʹ��ReadProcessMemory��ȡģ��ʱ���ش���");
			return FALSE;
		}
		crtheap_base = GetCrtHeapBase();
		MEMORY_BASIC_INFORMATION mbi;
		if( VirtualQueryEx( hProcess,crtheap_base,&mbi,sizeof(mbi) ) ){
			crtheap_size = (DWORD)mbi.RegionSize;
			pstack = new char[crtheap_size];
			if( !ReadProcessMemory(hProcess,(LPVOID)crtheap_base,pstack,crtheap_size,&size) ){
				DWORD dw = GetLastError();
				EerrorMessage("ReadDll��ʹ��ReadProcessMemory��ȡ��ʱ���ش���");
				return FALSE;
			}
		}else{
			EerrorMessage("ReadDll��ʹ��VirtualQueryEx��ѯ�ڴ�ߴ�ʱ��������");
			return FALSE;
		}

		return TRUE;
	}
	EerrorMessage("ReadDll���ܷ���Ҫ��ȡ��ģ��");
	return FALSE;
}

BOOL WriteDll(HANDLE hProcess,char* sDll){
	SIZE_T size;
	LPVOID pd;
	if( pdll ){
		pd = VirtualAllocEx(hProcess,me.modBaseAddr,me.modBaseSize,MEM_RESERVE,PAGE_EXECUTE_READWRITE);
		pd = VirtualAllocEx(hProcess,me.modBaseAddr,me.modBaseSize,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
		if( pd ){
			//����ɾ��dll��PE head
			memset(pdll,0,0x1000);
			if( !WriteProcessMemory(hProcess,pd,pdll,me.modBaseSize,&size) )
				EerrorMessage("WriteDll��ʹ��WriteProcessMemoryд��ģ��ʱ���ش���");
		}else{
			EerrorMessage("WriteDll��ʹ��VirtualAllocEx����ģ��ռ�ʱ���ش���");
			return FALSE;
		}
	}else return FALSE;

	if( pstack ){
		pd = VirtualAllocEx(hProcess,(LPVOID)crtheap_base,crtheap_size,MEM_RESERVE,PAGE_READWRITE);
		pd = VirtualAllocEx(hProcess,(LPVOID)crtheap_base,crtheap_size,MEM_COMMIT,PAGE_READWRITE);
		if( pd ){
			if( !WriteProcessMemory(hProcess,pd,pstack,crtheap_size,&size) ){
				EerrorMessage("WriteDll��ʹ��WriteProcessMemoryд���ʱ���ش���");
			}
		}else{
			EerrorMessage("WriteDll��ʹ��VirtualAllocEx����ѿռ�ʱ���ش���");
			return FALSE;
		}
	}else return FALSE;

	return TRUE;
}

#ifndef _CONSOLE
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
	char* wowdir;
	char sDll[256];
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

	GetCurrentDirectory(256,sDll);
	strcat(sDll,"\\");
	if( strcmp( lpCmdLine,"-tw" ) == 0 ){
		wowdir = wow_dir_tw;
		strcat(sDll,sdll_tw);
	}else{
		wowdir = wow_dir;
		strcat(sDll,sdll);
	}
//	if( strcmp(  lpCmdLine,"-sn" ) == 0 ){
//		InitSoundNote(hInstance,NULL);
//		return 0;
//	}
	SetCurrentDirectory(wowdir);
//	if( CreateProcess( "wow.exe","wow.exe -opengl",NULL,NULL,FALSE,CREATE_SUSPENDED,NULL,NULL,&si,&pi ) ){
	if( CreateProcess( "wow.exe","wow.exe",NULL,NULL,FALSE,CREATE_SUSPENDED,NULL,NULL,&si,&pi ) ){
		if( InjectLib( pi.dwProcessId,pi.hProcess,sDll ) == 0 ){
#ifndef _OUT
			//���ض�̬��
			if( ReadDll( pi.hProcess,sDll ) ){
				EjectLib( pi.dwProcessId,sDll );
				WriteDll( pi.hProcess,sDll );
			}
#endif
		}else{
			EerrorMessage("InjectLib û�гɹ���ע�붯̬��");
		}
		ResumeThread(pi.hThread);
		//����������ʾ����
		//InitSoundNote(hInstance,pi.hProcess);
	}else{
		EerrorMessage("��������wow.exe");
	}
	return 0;
}
#else
int _tmain(int argc, _TCHAR* argv[])
{
	DWORD pid;
	HWND hWnd;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
//	si.dwFlags = STARTF_USESTDHANDLES;
//	si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
//	si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
//	si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    ZeroMemory( &pi, sizeof(pi) );
	
	if( CreateProcess( "wow.exe","wow.exe -opengl",NULL,NULL,TRUE,CREATE_SUSPENDED,NULL,NULL,&si,&pi ) ){
		std::cout<<"Inject wowin.dll"<<std::endl;
		InjectLib( pi.dwProcessId,pi.hProcess,sDll );
		ResumeThread (pi.hThread);
		std::cout<<"Resume wow main thread"<<std::endl;
		//AttachConsole( pi.dwProcessId );
		WaitForSingleObject( pi.hProcess,INFINITE );
	}else{
		std::cout<<"Can't create wow process!"<<std::endl;
	}

	return 0;
}
#endif