#include <iostream>
using namespace std;

#include "MenuState.h"
#include "IntroState.h"
#include "GL\glew.h"
#include "../Application.h"
#include "LoadTGA.h"
#include "GraphicsManager.h"
#include "MeshBuilder.h"
#include "../TextEntity.h"
#include "RenderHelper.h"
#include "../SpriteEntity.h"
#include "../EntityManager.h"

#include "KeyboardController.h"
#include "SceneManager.h"
CMenuState::CMenuState()
{
}

CMenuState::~CMenuState()
{
}

void CMenuState::Init()
{
	//Create and attach the camera to the scene
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	//load all the meshes
	MeshBuilder::GetInstance()->GenerateQuad("MENUSTATE_BKGROUND", Color(1, 1, 1), 1.0f);
	MeshBuilder::GetInstance()->GetMesh("MENUSTATE_BKGROUND")->textureID = LoadTGA("Image//MenuState.tga");
	float halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2.f;
	float halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2.f;
	MenuStateBackground = Create::Sprite2DObject("MENUSTATE_BKGROUND", Vector3(halfWindowWidth, halfWindowHeight, 0.0f), Vector3(800.0f, 600.0f, 0.0f));

	cout << "CMenuState loaded\n" << endl;
}

void CMenuState::Update(double dt)
{
	if (KeyboardController::GetInstance()->IsKeyReleased(VK_SPACE))
	{
		cout << "Loading CGameState" << endl;
		SceneManager::GetInstance()->SetActiveScene("GameState");
	}

	if (KeyboardController::GetInstance()->IsKeyReleased(VK_F1))
	{
		cout << "Loading CInstructionState" << endl;
		SceneManager::GetInstance()->SetActiveScene("InstructionState");
	}

	if (KeyboardController::GetInstance()->IsKeyReleased(VK_F2))
	{
		cout << "Loading CCreditState" << endl;
		SceneManager::GetInstance()->SetActiveScene("CreditState");
	}
}

void CMenuState::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//GraphicsManager::GetInstance()->UpdateLightUniforms();

	// Setup 3D pipeline then render 3D
	GraphicsManager::GetInstance()->SetPerspectiveProjection(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	GraphicsManager::GetInstance()->AttachCamera(&camera);
	EntityManager::GetInstance()->Render();

	// Setup 2D pipeline then render 2D
	GraphicsManager::GetInstance()->SetOrthographicProjection(0, Application::GetInstance().GetWindowWidth(), 0, Application::GetInstance().GetWindowHeight(), -10, 10);

	GraphicsManager::GetInstance()->DetachCamera();

	EntityManager::GetInstance()->RenderUI();
}

void CMenuState::Exit()
{
	//Remove the entity from EntityManager
	EntityManager::GetInstance()->RemoveEntity(MenuStateBackground);

	//Remove the meshes which are specific to CIntroState
	MeshBuilder::GetInstance()->RemoveMesh("MENUSTATE_BKGROUND");

	//Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
}
