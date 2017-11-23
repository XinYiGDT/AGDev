#include "GranadeThrow.h"
#include "../Projectile/Grenade.h"

CGrenadeThrow::CGrenadeThrow()
{
}

CGrenadeThrow::~CGrenadeThrow()
{
}

void CGrenadeThrow::Init(void)
{
	//call the parent's init method
	CWeaponInfo::Init();

	//the number of ammunition in a magazine for this weapon
	magRounds = 1;
	// maximum number of ammunition in a magazine for this weapon
	maxMagRounds = 1;
	//the current total number of rounds currently carried by this player
	totalRounds = 2;
	//the max total number of rounds currently carried by this player
	maxTotalRounds = 2;

	// the time between shots
	timeBetweenShots = 1.0;
	// the elapsed time (between shots)
	elapsedTime = 0.0;
	// boolean flag to indicate if the weapon can fire now
	bFire = true;
}

void CGrenadeThrow::Discharge(Vector3 position, Vector3 target, CPlayerInfo * _source)
{
	if (bFire)
	{
		if (magRounds > 0)
		{
			//Create a projectile
			CProjectile* aProjectile = Create::Grenade("sphere",
				position,
				(target - position).Normalized(),
				7.0f,
				8.0f,
				_source);

			aProjectile->SetCollider(true);
			aProjectile->SetAABB(Vector3(0.5f, 0.5, 0.5f), Vector3(-0.5f, -0.5, -0.5f));
			bFire = false;
			magRounds--;
		}
	}
}
