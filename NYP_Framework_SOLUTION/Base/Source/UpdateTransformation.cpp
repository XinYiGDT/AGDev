#include "UpdateTransformation.h"

CUpdateTransformation::CUpdateTransformation()
	: curSteps(0)
	, deltaSteps(1)
	, minSteps(0)
	, maxSteps(0)
{
	Update_Mtx.SetToIdentity();
	Update_Mtx_REVERSED.SetToIdentity();
}

CUpdateTransformation::~CUpdateTransformation()
{
}

void CUpdateTransformation::Reset(void)
{
	Update_Mtx.SetToIdentity();
	Update_Mtx_REVERSED.SetToIdentity();
}

void CUpdateTransformation::Update(void)
{
	curSteps += deltaSteps;
	if ((curSteps >= maxSteps) || (curSteps <= minSteps))
	{
		deltaSteps += -1;
	}
}

void CUpdateTransformation::ApplyUpdate(const float dx, const float dy, const float dz)
{
	Update_Mtx.SetToTranslation(dx, dy, dz);
	Update_Mtx_REVERSED.SetToTranslation(dx, dy, dz);
}

void CUpdateTransformation::ApplyUpdate(const float angle, const float rx, const float ry, const float rz)
{
	Update_Mtx.SetToRotation(angle, rx, ry, rz);
	Update_Mtx_REVERSED.SetToRotation(angle, rx, ry, rz);
}

//void CUpdateTransformation::ApplyUpdate(const float sx, const float sy, const float sz,bool scale)
//{
//	if (scale==true)
//	{
//		Update_Mtx.SetToScale(sx, sy, sz);
//		Update_Mtx_REVERSED.SetToScale(sx, sy, sz);
//	}
//	/*else
//	{
//		Update_Mtx.SetToTranslation(sx, sy, sz);
//		Update_Mtx_REVERSED.SetToTranslation(sx, sy, sz);
//	}*/
//}

void CUpdateTransformation::SetSteps(const int minSteps, const int maxSteps)
{
	this->minSteps = minSteps;
	this->maxSteps = maxSteps;
}

void CUpdateTransformation::GetSteps(int & minSteps, int & maxSteps)
{
	minSteps = this->minSteps;
	maxSteps = this->maxSteps;
}

bool CUpdateTransformation::GetDirection(void) const
{
	if (deltaSteps == -1)
		return false;
	return true;
}

Mtx44 CUpdateTransformation::GetUpdateTransformation(void)
{
	if (deltaSteps == -1)
		return Update_Mtx_REVERSED;
	return Update_Mtx;
}
