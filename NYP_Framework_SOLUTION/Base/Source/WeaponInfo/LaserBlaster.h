#pragma once
#include "WeaponInfo.h"

class CplayerInfo;

class CLaserBlaster :
	public CWeaponInfo
{
public:
	CLaserBlaster();
	virtual ~CLaserBlaster();

	//Initialise this instance to default values
	void Init(void);
	//Discharge this weapon
	void Discharge(Vector3 postion, Vector3 target, CPlayerInfo* _source = NULL);

};

