#pragma once

#define CMD_NONOTE (WM_USER+1)
#define CMD_ATTACK (WM_USER+2) //����Ŀ��
#define CMD_DEFANCE (WM_USER+3) //������Ŀ��
#define CMD_YUN (WM_USER+4) //����
#define CMD_ZHIYOU (WM_USER+5) //������
#define CMD_TARGET_HEAL (WM_USER+6) //Ŀ���Ѫ��
#define CMD_NOTARGET (WM_USER+7) //û����ȷ����
#define CMD_STRING (WM_USER+32)

extern void PostSoudNote( UINT cmd,UINT p1,UINT p2 );
extern int lua_SoundNote(void*p);
extern int lua_PlaySound(void*p);