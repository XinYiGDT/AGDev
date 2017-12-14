#include "LaserBlaster.h"
#include "../Laser.h"

CLaserBlaster::CLaserBlaster()
{
}

CLaserBlaster::~CLaserBlaster()
{
}

void CLaserBlaster::Init(void)
{
	//call the parent's inti method
	CWeaponInfo::Init();

	//The number of ammunition in a magazine for this weapon
	magRounds = 5;
	//The maxium number of ammunition for this magazine for this weapon
	maxMagRounds = 5;
	//The current total number of rounds currently carried by this player
	totalRounds = 10;
	//the max total number of rounds currently carried by this player
	maxTotalRounds = 10;

	//The time between shots
	timeBetweenShots = 0.1667;
	//The Elapsed time(between shots)
	elapsedTime = 0.0;
	//Boolean flag to indicate if weapon can fire now
	bFire = true;

}

void CLaserBlaster::Discharge(Vector3 postion, Vector3 target, CPlayerInfo * _source)
{
	if (bFire)
	{
		//if there is still ammo in the magazine, then fire
		if (magRounds > 0)
		{
			Vector3 _direction = (target - postion).Normalized();
			//Create a laser with a laser mesh. The length is 10.0f, mesh is also set at 10.0f
			CLaser* aLaser = Create::Laser("laser", postion, _direction, 10.0f, 10.0f, 100.0f, _source);

			aLaser->SetIsLaser(true);
			aLaser->SetCollider(false);
			//aLaser->SetCollider(true);
			//aLaser->SetAABB(Vector3(0.5f, 0.5f, 0.5f), Vector3(-0.5f, -0.5f, -0.5f));
			bFire = false;
			magRounds--;
		}
	}
}
