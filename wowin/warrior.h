#pragma once

class Warrior:public Player{
protected:
	bool bInit;
	int iZhandaoZhiTai;//ս����̬
	int iKuangBaoZhiTai;//����̬
	int iGongJi; //����
public:
	Warrior( AI* ai );
	virtual ~Warrior();
	virtual void Think();
	void InitWarrior();
	void AutoAttack();
	int WatchCD( std::string skill );
};