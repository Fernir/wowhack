// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// ��Ŀ�ض��İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// �� Windows ��ͷ���ų�����ʹ�õ�����
#endif

// ���������ʹ��������ָ����ƽ̨֮ǰ��ƽ̨�����޸�����Ķ��塣
// �йز�ͬƽ̨����Ӧֵ��������Ϣ����ο� MSDN��
#ifndef WINVER				// ����ʹ�� Windows 95 �� Windows NT 4 ����߰汾���ض����ܡ�
#define WINVER 0x0400		//Ϊ Windows98 �� Windows 2000 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#ifndef _WIN32_WINNT		// ����ʹ�� Windows NT 4 ����߰汾���ض����ܡ�
#define _WIN32_WINNT 0x0400		//Ϊ Windows98 �� Windows 2000 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif						

#ifndef _WIN32_WINDOWS		// ����ʹ�� Windows 98 ����߰汾���ض����ܡ�
#define _WIN32_WINDOWS 0x0410 //Ϊ Windows Me �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#ifndef _WIN32_IE			// ����ʹ�� IE 4.0 ����߰汾���ض����ܡ�
#define _WIN32_IE 0x0400	//Ϊ IE 5.0 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ��������������ȫ���Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ���ĺͱ�׼���
#include <afxext.h>         // MFC ��չ
#include <afxdisp.h>        // MFC �Զ�����

#include <afxdtctl.h>		// Internet Explorer 4 �����ؼ��� MFC ֧��
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Windows �����ؼ��� MFC ֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <vector>
#include <string>
#include <fstream>

#define M_PI 3.1415926535897932384626433832795

int memcmp_mask( void* ps,const void* pcode,const void* pmask,int size );
void* ScreechFunctionEntry( void* ps,void* pe,const unsigned char code[16],const unsigned char mask[16] );
void vector_sub( float a[3],float b[3],float c[3] );
float vector_mod( float a[3] );
float vector_mod2( float a[3] );
float vector_dot( float b[3],float c[3] );
float vector_angle( float v[3] );