#pragma once

#define READY	0x80000000
#define FORWARD	1
#define BACK	2
#define LEFT	4
#define RIGHT	8
#define TURN_LEFT 16
#define TURN_RIGHT 32
#define WALK	0x100
#define JUMP	0x1000
#define FALL	0x5000

//��������
#define FLYING 1

#define ISMOVING (FORWARD|BACK|LEFT|RIGHT|JUMP)

//����ֵ����������
unsigned long DLLEXPORT GetMovementState();

int lua_IsMoving(void*p);
int lua_TurnBlink(void*p);

#define BORDER	NULL
#define FALLOFF	1
#define IMPASSABILITY 2

#define EAST 0
#define WEST 1
#define SOUTH 2
#define NORTH 3

struct GPoint{ //�����
	float z;
	GPoint* gp[4];
};

struct Ground{
	float x;
	float y;
	float step;
	int size;
	GPoint* pEntry; //�������
	GPoint* pAll; //һ������ڴ�����ȫ��N*N��GPoint
	GPoint* pFree; //���õ����ӱ�
	std::vector<GPoint*> Border[4]; //4�������ϵı߽�

	Ground();
	~Ground();
	bool InitGround( int n,float x,float y );
	void ReleaseGround();
	void ResetAllGPoint();
	GPoint* AllocGPoint();
	void ReExpand( float x,float y,float z ); //���µ�λ��չ��
	void Move( float x,float y ); //
};
