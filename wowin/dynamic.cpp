#include "stdafx.h"
#include "callhook.h"
#include "wowentry.h"
#include "dllentry.h"
#include "wowin.h"
#include "anticheck.h"
#include "scout.h"
#include "movement.h"
#include "collide.h"
#include "render.h"
#include "soundnote.h"
#include <tlhelp32.h>
#include <dbghelp.h>
extern int hookType;
/*
	����ʹ�ö�̬�޸ĵķ�������ֱ���޸Ĵ��롣
	����ͨ�����໯��CallChecker���ȷ���������״̬��©���޸�
*/
t_lua CastSpellByName;

int lua_MyCastSpellByName( void* p ){
	int ret;
	ret = ScriptEntry( p );
	if( ret != -1 ){
		return ret;
	}
	ret = CastSpellByName( p );
	CastSpellByNameReturn();
	return ret;
}

t_SwapBuff pSwapBuff;

void __stdcall MySwapBuff(){
	__asm{
		push ecx
	}
	myDraw();
	__asm{
		pop ecx
		call pSwapBuff
	}
}

WNDPROC pwowProc = NULL;

LRESULT CALLBACK myWindowProc(
  HWND hwnd, 
  UINT uMsg, 
  WPARAM wParam, 
  LPARAM lParam
  ){
	  if( !myProc( uMsg,wParam,lParam ) )
		return pwowProc(hwnd,uMsg,wParam,lParam);
	  else
	    return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

DWORD WINAPI subClassProc( LPVOID pvoid ){
	while(1){
		pwowProc = GetWowWndProc();
		if( pwowProc ){
			HWND hwnd = GetWowWnd();
			if( hwnd && pwowProc!=myWindowProc ){
#ifdef _OUT
				printf("call SetWindowLongPtr\n");
#endif
				SetWindowLongPtr(hwnd,GWLP_WNDPROC,(LONG)myWindowProc);
			}
			break;
		}
		Sleep(50);
	}
	return 0;
}

void InitDynamicHook(){
	DWORD op,op2;
	//lua��ע��һ��������ʱ���и�����
	//���������funs={{"CastSpellByName",CastSpellByName},...}
	//������ֱ�ӸĶ�������еĵ�ַ,��Ϊ��λ��.data�Σ��ͱ�����һ�����ݶ�
	//wow����У����Щ�����ĳ�ֵ
	PDWORD pf;
	hookType = 3;

	pf = pdwCastSpellByName;
	VirtualProtect( GET_PAGE(pf),PAGE_SIZE,PAGE_EXECUTE_READWRITE,&op );
	CastSpellByName = (t_lua)(*pf);
	*pf = (DWORD)lua_MyCastSpellByName;
	VirtualProtect( GET_PAGE(pf),PAGE_SIZE,op,&op2 );
	//�ڵ���һ��lua������ʱ��wowҪ������ǲ��ǳ���wow��.text�η�Χ
	//��wow�ĵ��ü�麯��ʹ��һ����Χ�����.text�ķ�Χ
	//[pdwCallCheckerLow,pdwCallCheckerLow+4]�д����Щ��Χ
	//�������ó�0,0xffffffff,��麯����Ƚ����ֵ�Ƿ�Ϊ0
	pf = pdwCallCheckerLow;
	VirtualProtect( GET_PAGE(pf),PAGE_SIZE,PAGE_EXECUTE_READWRITE,&op );
	*pf = 1;
	pf++;
	*pf = 0xffffffff;
	VirtualProtect( GET_PAGE(pf),PAGE_SIZE,op,&op2 );

	//���û��ƹҹ�,������ݴ���.rdata��
	VirtualProtect( GET_PAGE(pdwSwapBuff),PAGE_SIZE,PAGE_EXECUTE_READWRITE,&op );
	pSwapBuff = (t_SwapBuff)(*pdwSwapBuff);
	*pdwSwapBuff = (DWORD)MySwapBuff;
	VirtualProtect( GET_PAGE(pdwSwapBuff),PAGE_SIZE,op,&op2 );

	//�������໯wow���ڣ����¶�λwinproc
	DWORD tid;
	CreateThread(NULL,0,subClassProc,0,0,&tid);
}