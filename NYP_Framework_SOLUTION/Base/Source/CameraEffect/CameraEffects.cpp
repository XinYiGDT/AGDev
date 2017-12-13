#include "CameraEffects.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "../EntityManager.h"
#include "GL\glew.h"

CCameraEffects::CCameraEffects(void)
	: m_iAngle(-90)
	, m_bStatusBloodScreen(false)
	, m_CameraEffects_BloodyScreen(NULL)
	, m_CameraEffects_PistolScreen(NULL)
	, m_CameraEffects_SMGScreen(NULL)
	, m_fCountdownTimer_BloodScreen(2.0f)
	, mode(MODE_2D)
{
	Init();
}
CCameraEffects::~CCameraEffects(void)
{
	if (m_CameraEffects_BloodyScreen)
	{
		delete m_CameraEffects_BloodyScreen;
		m_CameraEffects_BloodyScreen = NULL;
	}
	if (m_CameraEffects_PistolScreen)
	{
		delete m_CameraEffects_PistolScreen;
		m_CameraEffects_PistolScreen = NULL;
	}
	if (m_CameraEffects_SMGScreen)
	{
		delete m_CameraEffects_SMGScreen;
		m_CameraEffects_SMGScreen = NULL;
	}
}

// Initialise this class instance
bool CCameraEffects::Init(void)
{
	m_iAngle = -90;
	position.Set(0.0f, 0.0f, 0.0f);
	scale.Set(800.0f, 600.0f, 100.0f);

	return true;
}

bool CCameraEffects::SetBloodScreen(Mesh* aBloodScreen)
{
	if(aBloodScreen != NULL)
	{
		m_CameraEffects_BloodyScreen = aBloodScreen;
		return true;
	}
	return false;
}
bool CCameraEffects::SetPistolScreen(Mesh * aTarget)
{
	if (aTarget != NULL)
	{
		m_CameraEffects_PistolScreen = aTarget;
		return true;
	}
	return false;
}
bool CCameraEffects::SetSMGScreen(Mesh * aTarget)
{
	if (aTarget != NULL)
	{
		m_CameraEffects_SMGScreen = aTarget;
		return true;
	}
	return false;
}
Mesh* CCameraEffects::GetBloodScreen(void) const
{
	return m_CameraEffects_BloodyScreen;
}

Mesh * CCameraEffects::GetPistolScreen(void) const
{
	return m_CameraEffects_PistolScreen;
}

Mesh * CCameraEffects::GetSMGScreen(void) const
{
	return m_CameraEffects_SMGScreen;
}

// Set m_iAngle of avatar
bool CCameraEffects::SetAngle(const int m_iAngle)
{
	this->m_iAngle = m_iAngle;
	return true;
}
// Get m_iAngle
int CCameraEffects::GetAngle(void) const
{
	return m_iAngle;
}

// Set boolean flag for BloodScreen
bool CCameraEffects::SetStatus_BloodScreen(const bool m_bStatusBloodScreen)
{
	this->m_bStatusBloodScreen = m_bStatusBloodScreen;
	return true;
}

bool CCameraEffects::SetStatus_PistolScreen(const bool m_bStatusPistolScreen)
{
	this->m_bStatusPistolScreen = m_bStatusPistolScreen;
	return true;
}

bool CCameraEffects::SetStatus_SMGScreen(const bool m_bStatusSMGScreen)
{
	this->m_bStatusSMGScreen = m_bStatusSMGScreen;
	return true;
}

// Set Countdown Timer for BloodScreen
bool CCameraEffects::SetTimer_BloodScreen(const float m_fCountdownTimer_BloodScreen)
{
	this->m_fCountdownTimer_BloodScreen = m_fCountdownTimer_BloodScreen;
	return true;
}

// Get Countdown Timer for BloodScreen
float CCameraEffects::GetTimer_BloodScreen(void) const
{
	return m_fCountdownTimer_BloodScreen;
}

// Update the camera effects
void CCameraEffects::Update(const float dt)
{
	//if (m_bStatusBloodScreen)
	//{
	//	m_fCountdownTimer_BloodScreen -= dt;
	//	if (m_fCountdownTimer_BloodScreen <= 0.0f)
	//	{
	//		// Set the bool flag for Render BloodScreen to false
	//		//m_bStatusBloodScreen = false;
	//		// Reset the countdown timer to the default value
	//		m_fCountdownTimer_BloodScreen = 2.0f;
	//	}
	//}
}

// Render the UI
void CCameraEffects::RenderUI()
{
	if (mode == MODE_3D)
		return;

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();

	// Push the current transformation into the modelStack
	modelStack.PushMatrix();
		// Translate the current transformation
		modelStack.Translate(position.x, position.y, position.z);
		// Scale the current transformation
		modelStack.Scale(scale.x, scale.y, scale.z);

		// Push the current transformation into the modelStack
		modelStack.PushMatrix();
			// Display the Avatar
			/*if ((m_bStatusBloodScreen) && (m_CameraEffects_BloodyScreen))
			{
				RenderHelper::RenderMesh(m_CameraEffects_BloodyScreen);
			}*/
			if ((m_bStatusPistolScreen) && (m_CameraEffects_PistolScreen))
			{
				RenderHelper::RenderMesh(m_CameraEffects_PistolScreen);
			}
			else if ((m_bStatusSMGScreen) && (m_CameraEffects_SMGScreen))
			{
				RenderHelper::RenderMesh(m_CameraEffects_SMGScreen);
			}
		modelStack.PopMatrix();

	modelStack.PopMatrix();

}

CCameraEffects* Create::CameraEffects(const bool m_bAddToLibrary)
{
	CCameraEffects* result = CCameraEffects::GetInstance();
	if (m_bAddToLibrary)
		EntityManager::GetInstance()->AddEntity(result);
	return result;
}
