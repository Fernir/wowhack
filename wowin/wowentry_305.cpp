#include "stdafx.h"
#include "callhook.h"
#include "wowentry.h"
#include <stdio.h>

#ifdef _WOW_3_05_
extern const char* sPlayer;

#define NOMASK {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

//ħ�ް汾3.09����
//ħ�ް汾3.05����
//=====================================
//MainCheckHack WOW�ڵ�½��ʱ��ؼ���Լ��Ƿ񱻸ı�,�ҽ��������ڼ��ʱ��ȫ���޸�ȥ��
//��MainCheckHack���Լ��ͨ����Ȼ���ڹҽӺ���
FunEntry feMainCheckHack = { "MainCheckHack",(void*)0x00602460,0,
							{0X55,0X8B,0XEC,0X8B,0X45,0X0C,0X8B,0X4D,0X08,0X81,0XEC,0X70,0X01,0X00,0X00,0X56},NOMASK };
//RegistALLFuncs WOWÿ��reloadui��������ע��lua����
FunEntry feRegistALLFuncs= { "RegistALLFuncs",(void*)0x0049e6a0,36,
							{0X33,0XF6,0XEB,0X08,0X8D,0XA4,0X24,0X00,0X00,0X00,0X00,0X90,0X8B,0X86,0X9C,0X65},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1} };
//WOWʹ��RegistFunction����ע��c�����lua
FunEntry feRegistFunction= { "RegistFunction",(void*)0x0077d290,0,
							{0X55,0X8B,0XEC,0X8B,0X45,0X0C,0X56,0X8B,0X35,0XFC,0X98,0X2E,0X01,0X6A,0X00,0X50},
							{0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0} };
//WOW�ڵ��ýű�c������ʱ����CallChecker������ǲ��ǳ�WOW Moudle�ĵ�ַ��Χ
//WOW��������ֹHacker
FunEntry feCallChecker	 = { "CallChecker",(void*)0x007cb790,14,
							{0X83,0XEC,0X40,0X85,0XC0,0X74,0X04,0X85,0XC9,0X75,0X10,0XE8,0X52,0XFF,0XFF,0XFF},
							{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1} };
//WOWʹ��DeniedOpenProcess����ֹ�ⲿ����ʹ��OpenProcess����WOW���̾��
FunEntry feDeniedOpenProcess= { "DeniedOpenProcess",(void*)0x007cb5b0,0,
							{0X55,0X8B,0XEC,0X81,0XEC,0X1C,0X02,0X00,0X00,0X53,0X33,0XDB,0X56,0X57,0X88,0X5D},NOMASK };
//WOWʹ��CheckProhibitFunc���ж�Lua c����Ȩ��
FunEntry feCheckProhibitFunc= { "CheckProhibitFunc",(void*)0x004a4480,10,
								{0X8B,0X4D,0X08,0XA1,0XC0,0X68,0X0A,0X01,0X74,0X65,0X83,0XF9,0X13,0X77,0X60,0X0F},
								{0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1} };
//������һ��lua����
FunEntry felua_isstring={ "lua_isstring",(void*)0x007ade60,19,
								{0X74,0X0D,0X8B,0X40,0X08,0X83,0XF8,0X04,0X74,0X09,0X83,0XF8,0X03,0X74,0X04,0X33},
								NOMASK };
FunEntry felua_tolstring={ "lua_tolstring",(void*)0x007adfe0,0,
								{0X55,0X8B,0XEC,0X56,0X8B,0X75,0X08,0X57,0X8B,0X7D,0X0C,0X8B,0XC7,0X8B,0XCE,0XE8},
								NOMASK };
FunEntry felua_isnumber={ "lua_isnumber",(void*)0x007ade20,37,
								{0XC0,0X75,0X04,0X8B,0XE5,0X5D,0XC3,0XB8,0X01,0X00,0X00,0X00,0X8B,0XE5,0X5D,0XC3},
								NOMASK };
FunEntry felua_tonumber={ "lua_tonumber",(void*)0x007adf30,33,
								{0X83,0XC4,0X08,0X85,0XC0,0X75,0X06,0XD9,0XEE,0X8B,0XE5,0X5D,0XC3,0XDD,0X00,0X8B},
								NOMASK };
FunEntry felua_pushnumber={"lua_pushnumber",(void*)0X007AE1A0,18,
								{0XDD,0X18,0X89,0X50,0X0C,0XC7,0X40,0X08,0X03,0X00,0X00,0X00,0X83,0X41,0X0C,0X10},
								NOMASK};
FunEntry felua_pushnil={"lua_pushnil",(void*)0X007AE180,0,
								{0X55,0X8B,0XEC,0X8B,0X45,0X08,0X8B,0X48,0X0C,0X8B,0X15,0X40,0XB4,0X2E,0X01,0X89},
								{0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0} };
FunEntry feGetUnitByName={"GetUnitByName",(void*)0X00566F40,0,
								{0X55,0X8B,0XEC,0X8B,0X4D,0X08,0X83,0XEC,0X08,0X56,0X33,0XF6,0X56,0X8D,0X45,0XF8},
								NOMASK};
//��ײ���ԣ�����һ����ײ���������б�
FunEntry feHitWrap={"HitWrap",(void*)0X006F1A90,0,
								{0X55,0X8B,0XEC,0X53,0X8B,0X5D,0X0C,0X56,0X57,0X33,0XF6,0X56,0X8B,0XCB,0XE8,0X5D},
								{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}};
//WOWʹ��CreateGXInterface������ͼ�����������Բ���D3D��OpenGL����
FunEntry feCreateGXInterface={"CreateGXInterface",(void*)0X005D04D0,0,
								{0X55,0X8B,0XEC,0X8B,0X45,0X08,0X83,0XE8,0X00,0X74,0X11,0X83,0XE8,0X01,0X75,0X18},
								NOMASK};
FunEntry feSetEyeMatrix={"SetEyeMatrix",(void*)0X00707110,0,
								{0X55,0X8B,0XEC,0X8B,0X0D,0X58,0XEF,0X27,0X01,0X81,0XEC,0XB4,0X00,0X00,0X00,0X53},
								{0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0}};
FunEntry feEnumUint={"EnumUnit",(void*)0X0046D8A0,16,
								{0X56,0X8B,0X34,0X81,0X8B,0X86,0X08,0X00,0X00,0X00,0X05,0XA8,0X00,0X00,0X00,0X8B},
								NOMASK};
FunEntry feGetUnit={"GetUnit",(void*)0X0046DB20,16,
								{0X14,0X81,0X8B,0X8A,0X08,0X00,0X00,0X00,0X83,0XEC,0X08,0X85,0XC9,0X74,0X2D,0X8B},
								NOMASK};
FunEntry feUnitFocus={"UnitFocus",(void*)0X004AA500,0,
								{0X55,0X8B,0XEC,0XA1,0X00,0X69,0X0A,0X01,0X56,0X8B,0X75,0X08,0X8B,0X0E,0X3B,0XC8},
								{0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0}};
FunEntry feSwapBuff={"SwapBuff",(void*)0X005EDA90,0,
								{0X56,0X8B,0XF1,0X57,0X8B,0XBE,0X18,0X28,0X00,0X00,0XE8,0XF1,0X45,0XFE,0XFF,0X85},
								{0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,0}};

FunEntry feGetCamera={"GetCamera",(void*)0X004B3DE0,0,
								{0XA1,0X8C,0X10,0X17,0X01,0X85,0XC0,0X74,0X07,0X8B,0X80,0X34,0X78,0X00,0X00,0XC3},
								{0,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0}};
FunEntry feTurnCamera={"TurnCamera",(void*)0X0055B370,0,
								{0X55,0X8B,0XEC,0X83,0XEC,0X18,0X56,0X8B,0XF1,0XF7,0X86,0X98,0X00,0X00,0X00,0X00},
								NOMASK};
FunEntry feDirectCamera={"DirectCamer",(void*)0X0055B670,0,
								{0X55,0X8B,0XEC,0X83,0XEC,0X0C,0X53,0X56,0X57,0X68,0XB9,0X0F,0X00,0X00,0X8B,0XF1},
								NOMASK};

unsigned int *g_pdwProhibitSpell = NULL;
//GetTable����ȡ��һ��ȫ�ֱ�,�洢�ж����б�
//FunEntry feGetTable={"GetTable",(void*)0X46C1D0,5,
//								{0X64,0X8B,0X0D,0X2C,0X00,0X00,0X00,0X8B,0X14,0X81,0X8B,0X82,0X08,0X00,0X00,0X00},
//								NOMASK};
//FunEntry feGetMovementInfo={"GetMovementInfo",(void*)0X0046C2B0,12,
//								{0X8B,0X14,0X81,0X8B,0X82,0X08,0X00,0X00,0X00,0X85,0XC0,0X75,0X01,0XC3,0X8B,0X80},
//								NOMASK};
//FunEntry fePlayerDirection={"PlayerDirection",(void*)0X008D7410,0,
//								{0X55,0X8B,0XEC,0X83,0XEC,0X40,0X56,0X8B,0XF1,0X8B,0X4E,0X38,0X8B,0X56,0X3C,0X8B},
//								NOMASK};
//FunEntry feUnitDirector={"UnitDirector",(void*)0X0063B590,0,
//								{0X8B,0X89,0X10,0X01,0X00,0X00,0XD9,0X41,0X1C,0X51,0XD9,0X1C,0X24,0XE8,0XCE,0XAB},
//								{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1}};

//dwProhibitSpell WOWʹ�������жϺ�����ִ��Ȩ��0�Ϳ���ִ��
//#define pdwProhibitSpell	((DWORD*)0x012EB440)

callhook g_chCheckHash(&feMainCheckHack);
callhook g_chRegistALLFuncs(&feRegistALLFuncs);
callhook g_chCallChecker(&feCallChecker);

callhook g_chRegistFunction(&feRegistFunction);
callhook g_chCheckProhibitFunc(&feCheckProhibitFunc);
callhook g_ch_lua_isnumber(&felua_isnumber);
callhook g_ch_lua_isstring(&felua_isstring);
callhook g_ch_lua_tonumber(&felua_tonumber);
callhook g_ch_lua_tolstring(&felua_tolstring);
callhook g_ch_lua_pushnumber(&felua_pushnumber);
callhook g_ch_lua_pushnil(&felua_pushnil);
callhook g_chGetUnitByName(&feGetUnitByName);
callhook g_chHitWrap(&feHitWrap);
callhook g_chCreateGXInterface(&feCreateGXInterface);
callhook g_chSetEyeMatrix(&feSetEyeMatrix);
callhook g_chEnumUnit(&feEnumUint);
callhook g_chGetUnit(&feGetUnit);
callhook g_chUnitFocus(&feUnitFocus);
callhook g_chSwapBuff(&feSwapBuff);

callhook g_chGetCamera(&feGetCamera);
callhook g_chTurnCamera(&feTurnCamera);
callhook g_chDirectCamera(&feDirectCamera);
//callhook g_chDeniedOpenProcess(&feDeniedOpenProcess);
//callhook g_chGetTable(&feGetTable);
//callhook g_chGetMovementInfo(&feGetMovementInfo);
//callhook g_chPlayerDirection(&fePlayerDirection);
//callhook g_chUnitDirector(&feUnitDirector);

void CheckHookEntry( callhook& ch ){
#ifdef _DEBUG
	printf("=================================================\n");
#endif
	if( !ch.check() && !ch.research() ){
		if( ch.pFunInfo ){
			char s[255];
			char ss[16];
			sprintf(s,"Can't found function:%s\naddrass:%08X\noffset:%d\ncode:{",ch.pFunInfo->name,ch.pFunInfo->func,ch.pFunInfo->off );
			for( int i = 0;i < sizeof(ch.pFunInfo->code);i++ ){
				if( i == sizeof(ch.pFunInfo->code)-1 )
					sprintf( ss,"%02X}",ch.pFunInfo->code[i] );
				else
					sprintf( ss,"%02X,",ch.pFunInfo->code[i] );
				strcat( s,ss );
			}
			MessageBox(NULL,s,"wowhack",MB_OK|MB_ICONERROR );
		}
	}
}

//��λһЩwowʹ�õ�ȫ�ֱ���
static void HookGlobalToLocal(){
	//����ʹ�ú���SetEyeMatrix��λȫ�ֱ���g_eye_position��g_eye_lookat
	//004F8003 mov     eye_position_x, eax
	//Ӳ������A3 2C 6B 0B 01
	//wow3.11�ο�λ��004F8003
	//==============================================
	if( *((unsigned char*)g_chSetEyeMatrix.pEntryFunc+0x33)==0xa3 ){
		g_eye_position = *((float**)((char*)g_chSetEyeMatrix.pEntryFunc+0x33+1));
#ifdef _OUT
		printf("eye_position:%X PASS\n",g_eye_position);
#endif
		g_eye_lookat = g_eye_position+3;
#ifdef _OUT		
		printf("eye_lookat:%X PASS\n",g_eye_lookat );
#endif
	}else{
#ifdef _OUT
		printf("Local eye_position FALSE\n");
#endif
	}
	//����ʹ�ú���SetEyeMatrix��λȫ�ֱ���matrix_eye
	//������mov ecx, offset matrix_eye
	//Ӳ������B9 38 BC FD 00
	//0x1e8�Ǵ�SetEyeMatrix��mov ecx ...��ƫ��
	//==============================================
	if( *((unsigned char*)g_chSetEyeMatrix.pEntryFunc+0x1e8)==0xb9 ){
		g_matrix_eye = *((float**)((char*)g_chSetEyeMatrix.pEntryFunc+0x1e8+1));
		printf("matrix_eye:%X PASS\n",g_matrix_eye);
		g_matrix_projection = g_matrix_eye+16;
#ifdef _OUT
		printf("matrix_projection:%X PASS\n",g_matrix_projection);
#endif
	}else{
#ifdef _OUT
		printf("Local matrix_eye FALSE\n");
#endif
	}
	//����ͨ��g_chCheckProhibitFunc����λdwProhibitSpell
	//cmp dwProhibitSpell,0
	//Ӳ������83 3D ,40 B4 2E  01 00,����dwProhibitSpell��01 2E B4 40
	//���Կ���83 3D�ȼ���cmp,�м���dwProhibitSpell
	if( *((unsigned char*)g_chCheckProhibitFunc.pEntryFunc+3)==0x83 &&
		*((unsigned char*)g_chCheckProhibitFunc.pEntryFunc+4)==0x3d ){
		g_pdwProhibitSpell = *((unsigned int**)((unsigned char*)g_chCheckProhibitFunc.pEntryFunc+5));
#ifdef _OUT
		printf("g_pdwProhibitSpell=%X PASS\n",g_pdwProhibitSpell);
#endif
	}else{
#ifdef _OUT
		printf("Local dwProhibitSpell FALSE\n");
#endif
	}
	//����ͨ��g_chUnitFocus����λg_pFocusID
	//mov     eax, dword_10A6900
	//Ӳ������A1 00 69 0A 01
	if( *((unsigned char*)g_chUnitFocus.pEntryFunc+3)==0xa1 ){
		g_pFocusID = *((long long**)((unsigned char*)g_chUnitFocus.pEntryFunc+4));
#ifdef _OUT
		printf("g_pFocusID=%X PASS\n",g_pFocusID);
#endif
	}else{
#ifdef _OUT
		printf("Local g_pFocusID FALSE\n");
#endif
	}
}

void CheckAllHookEntry(){
	CheckHookEntry( g_chCheckHash ); //hook:������������hash code
	CheckHookEntry( g_chRegistALLFuncs ); //hook:���������ע��lua����
	CheckHookEntry( g_chCallChecker ); //hook:���������������lua�����ĵ�ַ�ռ��ǲ���wow��
//	CheckHookEntry( g_chDeniedOpenProcess ); //hook:�ر�OpenProcess
	CheckHookEntry( g_chCheckProhibitFunc ); //hook:���lua�����ǲ�������
	CheckHookEntry( g_chRegistFunction ); //call:����ע��lua����
	CheckHookEntry( g_ch_lua_isnumber ); //call
	CheckHookEntry( g_ch_lua_isstring ); //call
	CheckHookEntry( g_ch_lua_tonumber ); //call
	CheckHookEntry( g_ch_lua_tolstring ); //call
	CheckHookEntry( g_ch_lua_pushnumber ); //call
	CheckHookEntry( g_ch_lua_pushnil ); //call
	CheckHookEntry( g_chGetUnitByName ); //call
	CheckHookEntry( g_chHitWrap ); //call
	CheckHookEntry( g_chCreateGXInterface ); //hook:����ͼ������
	CheckHookEntry( g_chSetEyeMatrix ); //local:��λmatrix_eye �� matrix_projcation
	CheckHookEntry( g_chEnumUnit ); //call:ö��ȫ������
	CheckHookEntry( g_chGetUnit ); //call:ȡ�ö���ָ��
	CheckHookEntry( g_chUnitFocus ); //local:��λg_pFocusID
	CheckHookEntry( g_chSwapBuff ); //local:��λSwapBuff�ڽӿڵ�λ��
	CheckHookEntry( g_chGetCamera ); //call:ȡ���ӽǶ���
	CheckHookEntry( g_chTurnCamera );//call:��ת�ӽ�
	CheckHookEntry( g_chDirectCamera );//call:ʹ��ɫ������ӽ��غ�
	CheckHookEntry( g_chScanDLLStart );
	HookGlobalToLocal();

//	CheckHookEntry( g_chGetTable );
//	CheckHookEntry( g_chGetMovementInfo );
//	CheckHookEntry( g_chPlayerDirection );
//	CheckHookEntry( g_chUnitDirector );
}

//�ο�����:Lua_CheckInteractDistance(004A5BF0) wow3.09
//�ο�λ��:004A5CCA
//ȡ�ö������꣬��������λ��0x20
void GetUnitPosition( void* p,float* v ){
	__asm{
		mov ecx,p
		mov eax,[ecx]
		mov eax,[eax+0x20]
		mov edx,v
		push edx
		call eax
	}
}

//�ο�����:GetUnitAngle(004B5D50) wow3.09
//�ο�λ��:004B5D58
//ȡ�ö���ĳ�����������λ��0x24
float GetUnitAngle( void* p ){
	float a;
	__asm{
		mov ecx,p
		mov eax,[ecx]
		mov eax,[eax+0x24]
		call eax
		fstp a;
	}
	return a;
}

//ȡ�ö�������ͣ���������λ��2,2
//�ο�����:UnitTracking(004D7C60) ħ�ް汾3.09
//�ο�λ��:004D7CF2
int UnitType( void* punit ){
	void* pa = *((void**)punit+2);
	return (int)(*((void**)pa+2));
}

//ȡ����ҵĿ���״̬������
//�ο�����:AnyTest(00673490) ħ�ް汾3.09
//�ο�λ��:00673E88
unsigned long GetMovementState(){
	void* s = GetUnitByName(sPlayer);
	if( s ){
		char* ebx = *((char**)s+0x110/4);
		if( ebx ){
			unsigned long state = *((unsigned long*)(ebx+0x40));
			return state;
		}
	}
	return 0;
}

void TurnCamera( float x,float y ){
	void* pcam = GetCamera();
	if( pcam ){
		float xx = x*32/9;
		float yy = y*32/9;
		__asm{
			mov ecx,pcam
			push yy
			push xx
			call g_chTurnCamera.pEntryFunc
		}
	}
}

void FaceCamera(){
	void* pcam = GetCamera();
	__asm{
		mov ecx,pcam
		call g_chDirectCamera.pEntryFunc
	}
}
//===========================================
// render.cpp �е�SetRenderHook��������İ汾
//===========================================

/*
void GetUnitDirection( void* p,float* v ){
	void* pfunc = g_chPlayerDirection.pEntryFunc;
	__asm{
		mov esi,p
		mov eax,pfunc
		mov edx,v
		push edx
		lea ecx,[esi+0x7c0]
		call eax
	}
}
*/
#endif
