#pragma once

//ȡ���ӽ�ʸ��
extern void DLLEXPORT GetCameraDirection( float* v );
//ת���ӽ�xˮƽ�Ƕȣ�y��ֱ�Ƕȵ�λ��
extern void DLLEXPORT TurnCamera( float x,float y );
//ʹ�ý�ɫ�ķ�����ӽ�һ��
extern void DLLEXPORT FaceCamera();

int lua_TurnCamera( void* p );