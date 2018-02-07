#include <iostream>
using namespace std;

#include "WinState.h"
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

CWinState::CWinState()
{
}

CWinState::~CWinState()
{
}

void CWinState::Init()
{
	//Create and attach the camera to the scene
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	//load all the meshes
	MeshBuilder::GetInstance()->GenerateQuad("WINSTATE_BKGROUND", Color(1, 1, 1), 1.0f);
	MeshBuilder::GetInstance()->GetMesh("WINSTATE_BKGROUND")->textureID = LoadTGA("Image//IntroState.tga");
	float halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2.f;
	float halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2.f;
	WinStateBackground = Create::Sprite2DObject("WINSTATE_BKGROUND", Vector3(halfWindowWidth, halfWindowHeight, 0.0f), Vector3(800.0f, 600.0f, 0.0f));

	cout << "CWinState loaded\n" << endl;
}

void CWinState::Update(double dt)
{
	if (KeyboardController::GetInstance()->IsKeyReleased(VK_SPACE))
	{
		cout << "Loading MenuState" << endl;
		SceneManager::GetInstance()->SetActiveScene("MenuState");
	}
}

void CWinState::Render()
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

void CWinState::Exit()
{
	//Remove the entity from EntityManager
	EntityManager::GetInstance()->RemoveEntity(WinStateBackground);

	//Remove the meshes which are specific to CIntroState
	MeshBuilder::GetInstance()->RemoveMesh("INTROSTATE_BKGROUND");

	//Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
}
