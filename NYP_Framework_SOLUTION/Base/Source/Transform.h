#pragma once
#include "Mtx44.h"
#include "UpdateTransformation.h"

class CTransform
{
public:
	enum AXIS
	{
		X_AXIS = 0,
		Y_AXIS = 0,
		Z_AXIS = 0,
		NUM_AXIS = 0,
	};

	CTransform();
	CTransform(const float dx, const float dy, const float dz);
	~CTransform();

	//Apply a translation to the Transformation Matrix
	void ApplyTranslate(const float dx, const float dy, const float dz);
	//Get the translation from the Transformation Matrix
	void GetTranslate(float& x, float& y, float& z);

	//Apply a  rotation to the Transformation Matrix
	void ApplyRotate(const float angle, const float rx, const float ry, const float rz);
	//Get the rotation from the Transformation Matrix
	float GetRotate(const AXIS theAxis);

	//Set the scale of the Transformation Matrix
	void SetScale(const float sx, const float sy, const float sz);
	//Get the scale from the Transformation Matrix
	void GetScale(float& x, float& y, float& z);

	//Apply a Transformation Matrix to the Transformation Matrix here
	void ApplyTransform(Mtx44 newMTX);

	//Reset the Transformation matriix to identity matrix
	void Reset(void);

	//Get the transformtion matrix
	Mtx44 GetTransform(void);

	//Set the update transformation
	void SetUpdateToTransformation(CUpdateTransformation* theUpdateTransformation = NULL);
	//Get the update transformation matrix
	Mtx44 GetUpdateTransformation(void);

	//Print Self
	void PrintSelf(void) const;

protected:
	Mtx44 Mtx, DefaultMtx;
	CUpdateTransformation* theUpdateTransformation;
};