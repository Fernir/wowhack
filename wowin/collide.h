#pragma once

struct Triangle{
	float n[4]; //�����η�ƽ�淽��,n[0],n[1],n[2]��һ��ƽ�淨����
				//ƽ��Ϊ����n[0]*x + n[1]*y + n[2]*z + n[3] = 0
	float a[3]; //�����ε�3����
	float b[3];
	float c[3];
};

struct DLLEXPORT Collide{
	int	iDownMax;
	int iDownCount;
	Triangle* pDowns;
	int iDownMax2;  //�ô�δ֪

	int iUpMax;
	int iUpCount;
	Triangle* pUps;
	int iUpMax2;    //�ô�δ֪

	Collide( int down,Triangle* pdowns,int up,Triangle* pups );
};

DLLEXPORT Collide* CalcCollide( float p[6] );
int lua_IsCollide( void* p );