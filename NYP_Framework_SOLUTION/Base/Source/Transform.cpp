#include "Transform.h"
#include <iostream>

CTransform::CTransform()
	: theUpdateTransformation(NULL)
{
	if (theUpdateTransformation)
	{
		delete theUpdateTransformation;
		theUpdateTransformation = NULL;
	}

	Mtx.SetToIdentity();
	DefaultMtx.SetToIdentity();
}

CTransform::CTransform(const float dx, const float dy, const float dz)
{
	Mtx.SetToTranslation(dx, dy, dz);
}

CTransform::~CTransform()
{
}

void CTransform::ApplyTranslate(const float dx, const float dy, const float dz)
{
	Mtx44 TempMtx;
	TempMtx.SetToTranslation(dx, dy, dz);
	Mtx = Mtx * TempMtx;
}

void CTransform::GetTranslate(float & x, float & y, float & z)
{
	x = Mtx.a[12];
	y = Mtx.a[13];
	z = Mtx.a[14];
}

void CTransform::ApplyRotate(const float angle, const float rx, const float ry, const float rz)
{
	Mtx44 TempMtx;
	TempMtx.SetToRotation(angle, rx, ry, rz);
	Mtx = Mtx * TempMtx;
}

float CTransform::GetRotate(const AXIS theAxis)
{
	if (theAxis == X_AXIS)
	{
		float y = acos(Mtx.a[5]);
		float z = asin(-Mtx.a[9]);

		if (abs(y - z) < Math::EPSILON)
			return y;
	}
	else if (theAxis == Y_AXIS)
	{
		float x = acos(Mtx.a[0]);
		float z = asin(Mtx.a[8]);

		if (abs(x - z) < Math::EPSILON)
			return x;
	}
	else if (theAxis == Z_AXIS)
	{
		float x = acos(Mtx.a[0]);
		float y = asin(-Mtx.a[4]);

		if (abs(x - y) < Math::EPSILON)
			return x;
	}
	return 0.0f;
}

void CTransform::SetScale(const float sx, const float sy, const float sz)
{
	float scaleX = sx, scaleY = sy, scaleZ = sz;
	if (scaleX == 0.0f)
		scaleX = 1.0f;
	if (scaleY == 0.0f)
		scaleY = 1.0f;
	if (scaleZ == 0.0f)
		scaleZ = 1.0f;

	Mtx.SetToScale(scaleX, scaleY, scaleZ);
}

void CTransform::GetScale(float & x, float & y, float & z)
{
	x = Mtx.a[0];
	y = Mtx.a[5];
	z = Mtx.a[10];
}

void CTransform::ApplyTransform(Mtx44 newMTX)
{
	Mtx = Mtx * newMTX;
}

void CTransform::Reset(void)
{
	Mtx.SetToIdentity();
}

Mtx44 CTransform::GetTransform(void)
{
	return Mtx;
}

void CTransform::SetUpdateToTransformation(CUpdateTransformation * theUpdateTransformation)
{
	this->theUpdateTransformation = theUpdateTransformation;
}

Mtx44 CTransform::GetUpdateTransformation(void)
{
	if (theUpdateTransformation == NULL)
		return DefaultMtx;

	//update theUpdateTransformation
	theUpdateTransformation->Update();

	return theUpdateTransformation->GetUpdateTransformation();
}

void CTransform::PrintSelf(void) const
{
	std::cout << "======================================================================" << std::endl;
	std::cout << "CTransform::PrintSelf" << std::endl;
	std::cout << "----------------------------------------------------------------------" << std::endl;
	std::cout << "[\t" << Mtx.a[0] << "\t" << Mtx.a[4] << "\t" << Mtx.a[8] << "\t" << Mtx.a[12] << "\t]" << std::endl;
	std::cout << "[\t" << Mtx.a[1] << "\t" << Mtx.a[5] << "\t" << Mtx.a[9] << "\t" << Mtx.a[13] << "\t]" << std::endl;
	std::cout << "[\t" << Mtx.a[2] << "\t" << Mtx.a[6] << "\t" << Mtx.a[10] << "\t" << Mtx.a[14] << "\t]" << std::endl;
	std::cout << "[\t" << Mtx.a[3] << "\t" << Mtx.a[7] << "\t" << Mtx.a[11] << "\t" << Mtx.a[15] << "\t]" << std::endl;
	std::cout << "======================================================================" << std::endl;
}
