#pragma once

#include "EntityBase.h"
#include "SingletonTemplate.h"
#include "Mesh.h"

class CCameraEffects : public EntityBase, public Singleton<CCameraEffects>
{
public:
	enum SPRITE_RENDERMODE
	{
		MODE_2D,
		MODE_3D,
		NUM_MODE
	};

	CCameraEffects(void);
	virtual ~CCameraEffects(void);

	Mesh* m_CameraEffects_BloodyScreen;
	Mesh* m_CameraEffects_PistolScreen;
	Mesh* m_CameraEffects_SMGScreen;

	// Initialise this class instance
	bool Init(void);

	// Set the BloodScreen
	bool SetBloodScreen(Mesh* aTarget);
	//set 
	bool SetPistolScreen(Mesh* aTarget);
	bool SetSMGScreen(Mesh* aTarget);

	// Get the BloodScreen
	Mesh* GetBloodScreen(void) const;
	//get
	Mesh* GetPistolScreen(void) const;
	Mesh* GetSMGScreen(void) const;

	// Set rotation angle of CCameraEffect
	bool SetAngle(const int angle);
	// Get rotation angle of CCameraEffect
	int GetAngle(void) const;

	// Set boolean flag for BloodScreen
	bool SetStatus_BloodScreen(const bool m_bStatusBloodScreen);
	bool SetStatus_PistolScreen(const bool m_bStatusPistolScreen);
	bool SetStatus_SMGScreen(const bool m_bStatusSMGScreen);
	// Set Countdown Timer for BloodScreen
	bool SetTimer_BloodScreen(const float m_fCountdownTimer_BloodScreen = 2.0f);
	// Get Countdown Timer for BloodScreen
	float GetTimer_BloodScreen(void) const;

	// Update the camera effects
	virtual void Update(const float dt = 0.0333f);
	// Render the UI
	virtual void RenderUI();

protected:
	// Rotation from First Angle
	int m_iAngle;
	// Boolean flag to indicate if the BloodScreen is rendered
	bool m_bStatusBloodScreen, m_bStatusPistolScreen, m_bStatusSMGScreen;
	// Countdown Timer for BloodScreen
	float m_fCountdownTimer_BloodScreen;

	SPRITE_RENDERMODE mode;
};

namespace Create
{
	CCameraEffects* CameraEffects(const bool m_bAddToLibrary = true);
};