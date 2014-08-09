#pragma once

#define NONE -1
#define MAX_UNIT 32
#define YARD40 800.0f

#define UNKNOW 0
//ְҵ
#define ROGUE	1
#define MAGE	2
#define DEATHNIGHT	3
#define DRUID	4
#define WARRIOR	5
#define HUNTER	6
#define WARLOCK	7
#define PALADIN	8
#define PRIEST	9

//����
#define TROLL	1
#define ORC	2
#define TAUREN	3
#define UNDEAD	4
#define BLOODELF	5
#define NIGHTELF	6
#define GNOME	7
#define HUMAN	8
#define DWARF	9
#define DREANEI	10

#define POWER_HEALTH -2
#define POWER_MANA	0
#define POWER_RAGE	1
#define POWER_FOCUS	2
#define POWER_ENERGY	3

//����
struct DLLEXPORT Skill{
	std::string name; //����
	std::string rank; //����,ֱ��������ħ��û�зֽ�
	std::string icon; //����ͼ��
	int id; //�����ڼ������е�λ��
	int powerType; //ʩ����Ҫ������-2����,0Mana,1Rage,2Focus,3Energy
	int powerCost; //�ͷ�����
	int minRang;//������С����
	int maxRang;//����������
	int castingTime;//ʩ����Ҫ��ʱ��,����
	bool bPet;//Pet

	Skill();
	Skill( std::string n,std::string r,std::string icon_,
			int id_,int powertype,int powercost,int minrang,int maxrang,
			int castingtime,bool bpet);
};

//Buff or Debuff
struct DLLEXPORT BUFF{
	std::string name; //����
	int count;//����

	float timeLeft;//����ʱ��,��λ��
	float duration;//���Գ�������ʱ��,��λ��
};

//�ݽ����ű���������ħ������slot��Cooldown
struct DLLEXPORT Cooldown{
	int spell; //ħ������,��Skill�е�id������ͬ����,IN
	bool pet; //�ǲ��ǳ���ħ��,IN
	float start; //��ʼ��ȴʱ��,��λ����,OUT
	float duration;//����ʱ��,OUT
	bool enable; //�Ƿ�����ȴ��,OUT
	bool iscurrent; //�ǲ��Ǳ�ѡ��
	Cooldown();
	Cooldown(int s,bool p );
};

//���󣬰�����Һ�NPC,����
struct DLLEXPORT Unit{
	//�������ֱ��ȡ��
	bool bValid;   //�����Ƿ���Ч
	long long id; //���id
	float pos[3]; //����λ��
	float direct[3];//������
	float distance;//����Ҿ����ƽ��
	int   type; //����NPC,�������

	//����ͨ��luaȡ��
	unsigned int uStaticUpdateTime;//��̬���ݸ�������,����GetTickCount����
	unsigned int uUpdateTime; //�������ݱ����µ�ʱ��
	bool bStatic; //��̬����û�и���
	std::string sName;//����
	int iRace; //����
	int iClass;//ְҵ
	int iLevel;//����
	int iMaxHealth; //�������
	int iMaxMana; //���ħ��ֵ
	bool bCanAttack; //Ŀ���Ƿ���Թ���

	int iHealth;    //Ŀǰ����
	int iMana;	//ħ��ֵ
	std::string sTarget;//����Ŀ������
	std::string sSpell; //�����ͷŵ�ħ��
	float SpellBegin; //ħ���ͷſ�ʼʱ��,��λ��
	float SpellEnd;	//ħ���ͷŽ���ʱ��,��λ��
	bool bWarring; //�ж�
	bool bPlayer; //�ǲ������
	bool bCombat; //�Ƿ�ս��״̬
	bool bDeath; //�ǲ�������
	bool bGhost; //�ǲ�������״̬
	bool bCasting;//�Ƿ���ʩ��
	int  iBuff; //buff����
	int  iDebuff;//Debuff����
	BUFF Buff[32];
	BUFF Debuff[32];

	void Init();
};

#define CMD_NONE 0
//���������������½�ɫ����
#define CMD_UPDATE_SKILL 1
#define CMD_UPDATE_STATIC 2

//���������������ƽ�ɫ�ƶ�
#define CMD_LEFT 3 //��ƽ��
#define CMD_LEFT_STOP 4
#define CMD_RIGHT 5 //��ƽ��
#define CMD_RIGHT_STOP 6
#define CMD_FORWARD 7 //ǰ��
#define CMD_FORWARD_STOP 8
#define CMD_BACK 9 //����
#define CMD_BACK_STOP 10
#define CMD_TURNLEFT 11 //��ת
#define CMD_TURNLEFT_STOP 12
#define CMD_TURNRIGHT 13//��ת
#define CMD_TURNRIGHT_STOP 14
#define CMD_JUMP 15 //��Ծ
#define CMD_JUMP_STOP 16
#define CMD_TOGGLE_RUN 17 //һֱ��ǰ

//�������������ͷż���
#define CMD_CASTSPELL 18 //ʩ��ħ��

struct DLLEXPORT AI{
	//������
	//======
	std::string sRegion; //�����������
	std::string sSubReg; //�������������
	std::vector<Skill> vSkill; //��ɫ��ȫ������
	std::vector<Cooldown> vCD; //һ����Ҫ���ļ�����ȴ��
	int iPlayer; //��Ҷ�������
	float Pos[3];  //���λ��
	float Direct[3];//��ҷ���
	unsigned long uMoveState;//����ƶ�״̬
	int iCurrent; //�����ڸ���״̬ʱ����ʱ����
	float time;//Lua GetTime��ʱ��ֵ,��λ��
	Unit vUNIT[MAX_UNIT]; //������Ŀ

	//�����ƶ��Ŀ���״̬
	//==================
	int iLeft,cmdLeft; //0 û���� 1 Left 2 Left_stop
	int iRight,cmdRight;
	int iForward,cmdForward;
	int iBack,cmdBack;
	int iTurnLeft,cmdTurnLeft;
	int iTurnRight,cmdTurnRight;
	int iJump,cmdJump;
	float fTurnArg;
	int cmdTarget; //����ѡ��Ŀ�������
	int cmdCastSpellID;//����ʩ��ħ��������
	bool cmdCastSpellPet;
	int cmdCastStop;//ֹͣʩ��

	HMODULE hBot; //bot��̬����
	PROC pfnThink; //bot˼������
	PROC pfnChatEvent; //�����¼�

	//��ʱ������
	//===========
	long long oldFocusID;
	unsigned int frameTickCount;
	void* pPlayer; //��ʹ��������iPlayer
	//===========

	//��������
	//==========
	AI();
	//����ĺ�������Lua���ã������ռ���Ϸ���ݵ�
	//=========================================
	void UnitSearch( float time ); //������Χ��Unit,��һ���ռ��Ŀ�ʼʱ��Lua GetTime
	int IsUpdate( int i ); //��i�������Ƿ���Ҫ����

	void UpdateStatic( std::string name,int race,int clas,int level,bool bwarring,bool canattack); //���¾�̬���ݣ���Բ��������
	//����״̬,����������ħ��
	void UpdateHealth( int health,int mana,int maxhealth,int maxmana );
	//��������
	void UpdateRegion( std::string reg,std::string sub );
	//�����Ƿ��꣬�Ƿ��������Ƿ�����
	void UpdateState( bool ghost,bool death,bool taxi );
	//����ʩ��״̬��ħ�����ƣ�ʩ��ʱ�䣬����ʱ��
	void UpdateCasting( std::string spell,unsigned int begin,unsigned int end );
	//���¶����Ŀ��
	void UpdateTarget( std::string target );
	//����Ŀ�����ϵ�Buff
	void UpdateBuff( std::string buff,int count,float timeleft,float duration,int i );
	//����Ŀ�����ϵ�Debuff
	void UpdateDebuff( std::string buff,int count,float timeleft,float duration,int i );
	//�ָ�����Ŀ��
	void ResumeFocus();
	
	//����Ĵ�����Lua���������¼�����ȴ���
	//=====================================
	int GetCooldownListSize(); //ȡ��vCD�ߴ�
	int GetCooldownSpell(int i); //ȡ�õ�i��Cooldown��Spell
	bool GetCooldownPet(int i);
	void UpdateCooldown(int i,float start,float duration,bool enable,bool iscurr); //���µ�i��Cooldown��Ϣ

	//���溯��Lua���ã������ռ���ҽ�ɫ��Ϣ
	//=====================================
	//������ҵļ�����Ϣ
	void ClearSkill(); //�������
	void AddSkill( std::string sill,std::string rank,std::string icon,
					int id,int powertype,int powercost,int minrang,int maxrang,
					int castingtime,bool isfunnel ); //����һ�����ü���
	//���溯��Lua���ã�������������
	//=====================================
	void ChatEvent( const char* sender,const char* msg,const char* channel );

	void Think(); //Lua���������������AI

	//C++ bot ��̬�����
	//==================
	bool LoadBot( std::string bot ); //����һ��ai
	void FreeBot(); //ж�ص�ǰai

	//C++������������Cooldown
	void AddCooldownTrack( int spell,bool pet );
	void ClearCooldownTrack();
	//C++���������ƶ���ɫ
	//===================
	void MoveLeft(); //��ƽ��
	void MoveRight();//��ƽ��
	void MoveForward(); //��ǰ
	void MoveBack(); //����
	void MoveJump(); //��
	void MoveTurnLeft(); //��ת
	void MoveTurnRight();//��ת
	void MoveLRStop(); //ֹͣ�����ƶ�
	void MoveFBStop(); //ֹͣǰ���ƶ�
	void MoveTurnStop(); //ֹͣת��
	void MoveTurn( float a ); //������תһ���Ƕ�
	//C++��������ѡ��Ŀ����ͷŷ���
	//=============================
	void Target(long long id);//���õ�λΪ���Ŀ��
	void CastSpell(int id,bool pet); //�ͷ�һ��ħ����b=true��ʾ�ǳ���ħ��
	void SpellStopCasting(); //ֹͣ�ͷ�

	Render* GetRender();
	Way*	GetWay();
	Cross*	GetCross();
};

/*
template class DLLEXPORT std::vector<Cooldown>;
template class DLLEXPORT std::vector<Skill>;
*/

int lua_UnitSearch(void*);
int lua_IsUpdate(void*);
int lua_UpdateStatic(void*);
int lua_UpdateHealth(void*p);
int lua_UpdateState(void*);
int lua_UpdateCasting(void*);
int lua_UpdateTarget(void*);
int lua_UpdateBuff(void*);
int lua_UpdateDebuff(void*);
int lua_AIResumeFocus(void*p);
int lua_AIClearSkill(void*p);
int lua_AIAddSkill(void*p);
int lua_AILoadBot(void*);
int lua_AIFreeBot(void*);
int lua_AIThink(void*);
int lua_AIGetCooldownListSize(void*p);
int lua_AIGetCooldownSpell(void*p);
int lua_AIUpdateCooldown(void*p);
int lua_AIMove(void*);
int lua_AITurn(void*p);
int lua_AIUpdateRegion(void*p);
int lua_AIAction(void*p);
int lua_AIBotIsReady(void*p);
int lua_AIChatEvent(void*p);