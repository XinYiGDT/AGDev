#include "SceneText.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>
#include "KeyboardController.h"
#include "MouseController.h"
#include "SceneManager.h"
#include "GraphicsManager.h"
#include "ShaderProgram.h"
#include "EntityManager.h"

#include "GenericEntity.h"
#include "GroundEntity.h"
#include "TextEntity.h"
#include "SpriteEntity.h"
#include "Light.h"
#include "SkyBox/SkyBoxEntity.h"
#include "SceneNode.h"
#include "SceneGraph.h"
#include "Waypoint\Waypoint.h"
#include "Waypoint\WaypointManager.h"

#include <iostream>
using namespace std;

//SceneText* SceneText::sInstance = new SceneText(SceneManager::GetInstance());

SceneText::SceneText()
{
}

//SceneText::SceneText(SceneManager* _sceneMgr)
//{
//	_sceneMgr->AddScene("Start", this);
//}

SceneText::~SceneText()
{
	CSceneGraph::GetInstance()->Destroy();
}

void SceneText::Init()
{
	

	lights[0] = new Light();
	GraphicsManager::GetInstance()->AddLight("lights[0]", lights[0]);
	lights[0]->type = Light::LIGHT_DIRECTIONAL;
	lights[0]->position.Set(0, 20, 0);
	lights[0]->color.Set(1, 1, 1);
	lights[0]->power = 1;
	lights[0]->kC = 1.f;
	lights[0]->kL = 0.01f;
	lights[0]->kQ = 0.001f;
	lights[0]->cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0]->cosInner = cos(Math::DegreeToRadian(30));
	lights[0]->exponent = 3.f;
	lights[0]->spotDirection.Set(0.f, 1.f, 0.f);
	lights[0]->name = "lights[0]";

	lights[1] = new Light();
	GraphicsManager::GetInstance()->AddLight("lights[1]", lights[1]);
	lights[1]->type = Light::LIGHT_DIRECTIONAL;
	lights[1]->position.Set(1, 1, 0);
	lights[1]->color.Set(1, 1, 0.5f);
	lights[1]->power = 0.4f;
	lights[1]->name = "lights[1]";

	
	
	// Create the playerinfo instance, which manages all information about the player
	playerInfo = CPlayerInfo::GetInstance();
	playerInfo->Init();

	// Create and attach the camera to the scene
	//camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	camera.Init(playerInfo->GetPos(), playerInfo->GetTarget(), playerInfo->GetUp());
	playerInfo->AttachCamera(&camera);
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	// Load all the meshes
	MeshBuilder::GetInstance()->GenerateAxes("reference");
	MeshBuilder::GetInstance()->GenerateCrossHair("crosshair");
	MeshBuilder::GetInstance()->GenerateQuad("quad", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("quad")->textureID = LoadTGA("Image//calibri.tga");
	MeshBuilder::GetInstance()->GenerateText("text", 16, 16);
	MeshBuilder::GetInstance()->GetMesh("text")->textureID = LoadTGA("Image//calibri.tga");
	MeshBuilder::GetInstance()->GetMesh("text")->material.kAmbient.Set(1, 0, 0);
	MeshBuilder::GetInstance()->GenerateOBJ("Chair", "OBJ//chair.obj");
	MeshBuilder::GetInstance()->GetMesh("Chair")->textureID = LoadTGA("Image//chair.tga");
	MeshBuilder::GetInstance()->GenerateRing("ring", Color(1, 0, 1), 36, 1, 0.5f);
	MeshBuilder::GetInstance()->GenerateSphere("lightball", Color(1, 1, 1), 18, 36, 1.f);
	MeshBuilder::GetInstance()->GenerateSphere("sphere", Color(1, 0, 0), 18, 36, 0.5f);
	MeshBuilder::GetInstance()->GenerateSphere("sphere2", Color(0, 1, 0), 9, 18, 0.5f);
	MeshBuilder::GetInstance()->GenerateSphere("sphere3", Color(0, 0, 1), 4, 9, 0.5f);

	MeshBuilder::GetInstance()->GenerateCone("cone", Color(0.5f, 1, 0.3f), 36, 10.f, 10.f);
	MeshBuilder::GetInstance()->GenerateCube("cube", Color(1.0f, 1.0f, 0.0f), 1.0f);
	MeshBuilder::GetInstance()->GetMesh("cone")->material.kDiffuse.Set(0.99f, 0.99f, 0.99f);
	MeshBuilder::GetInstance()->GetMesh("cone")->material.kSpecular.Set(0.f, 0.f, 0.f);
	MeshBuilder::GetInstance()->GenerateQuad("GRASS_DARKGREEN", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("GRASS_DARKGREEN")->textureID = LoadTGA("Image//grass_darkgreen.tga");
	MeshBuilder::GetInstance()->GenerateQuad("GEO_GRASS_LIGHTGREEN", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("GEO_GRASS_LIGHTGREEN")->textureID = LoadTGA("Image//grass_lightgreen.tga");

	MeshBuilder::GetInstance()->GenerateQuad("SKYBOX_FRONT", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("SKYBOX_BACK", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("SKYBOX_LEFT", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("SKYBOX_RIGHT", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("SKYBOX_TOP", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("SKYBOX_BOTTOM", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("SKYBOX_FRONT")->textureID = LoadTGA("Image//SkyBox//desertsky_ft.tga");
	MeshBuilder::GetInstance()->GetMesh("SKYBOX_BACK")->textureID = LoadTGA("Image//SkyBox//desertsky_bk.tga");
	MeshBuilder::GetInstance()->GetMesh("SKYBOX_LEFT")->textureID = LoadTGA("Image//SkyBox//desertsky_lf.tga");
	MeshBuilder::GetInstance()->GetMesh("SKYBOX_RIGHT")->textureID = LoadTGA("Image//SkyBox//desertsky_rt.tga");
	MeshBuilder::GetInstance()->GetMesh("SKYBOX_TOP")->textureID = LoadTGA("Image//SkyBox//desertsky_up.tga");
	MeshBuilder::GetInstance()->GetMesh("SKYBOX_BOTTOM")->textureID = LoadTGA("Image//SkyBox//desertsky_dn.tga");
	MeshBuilder::GetInstance()->GenerateRay("laser", 10.0f);
	MeshBuilder::GetInstance()->GenerateCube("cubeSG", Color(1.0f, 0.64f, 0.0f), 1.0f);
	MeshBuilder::GetInstance()->GenerateQuad("GRIDMESH", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GenerateCube("cubeHead", Color(1.0f, 0.8f, 0.0f), 1.0f);

	MeshBuilder::GetInstance()->GenerateOBJ("house", "OBJ//house.obj");
	MeshBuilder::GetInstance()->GetMesh("house")->textureID = LoadTGA("Image//house.tga");

	MeshBuilder::GetInstance()->GenerateOBJ("log", "OBJ//WoodLog.obj");
	MeshBuilder::GetInstance()->GetMesh("log")->textureID = LoadTGA("Image//wood.tga");

	MeshBuilder::GetInstance()->GenerateOBJ("tree", "OBJ//tree.obj");
	MeshBuilder::GetInstance()->GetMesh("tree")->textureID = LoadTGA("Image//tree.tga");


	//set up the spatial partition and pass it to the entityManager to manage
	CSpatialPartition::GetInstance()->Init(100, 100, 10, 10);
	CSpatialPartition::GetInstance()->SetMesh("GRIDMESH");
	CSpatialPartition::GetInstance()->SetCamera(&camera);
	CSpatialPartition::GetInstance()->SetLevelOfDetails(10000.0f, 30000.0f);//sets the distance for lod 
	EntityManager::GetInstance()->SetSpatialPartition(CSpatialPartition::GetInstance());


	// Create entities into the scene
	//Create::Entity("reference", Vector3(0.0f, 0.0f, 0.0f)); // Reference
	//Create::Entity("lightball", Vector3(lights[0]->position.x, lights[0]->position.y, lights[0]->position.z)); // Lightball
	
	//-----week6 -  spatial partition
	/*for (int i = 0; i < 10; ++i)
	{
		
	}*/

	Create::Entity("house", Vector3(0, -10.f, -200.f), Vector3(0.09f,0.09f,0.09f));
	Create::Entity("house", Vector3(300.f, -10.f, -200.f), Vector3(0.09f, 0.09f, 0.09f));
	Create::Entity("house", Vector3(-300.f, -10.f, -200.f), Vector3(0.09f, 0.09f, 0.09f));
	Create::Entity("house", Vector3(300.f, -10.f, 200.f), Vector3(0.09f, 0.09f, 0.09f));
	Create::Entity("house", Vector3(-300.f, -10.f, 200.f), Vector3(0.09f, 0.09f, 0.09f));

	Create::Entity("log", Vector3(30.f, -13.f, -200.f), Vector3(5.f, 5.f, 5.f));
	Create::Entity("log", Vector3(330.f, -10.f, -200.f), Vector3(10.f, 10.f, 10.f));
	Create::Entity("log", Vector3(-330.f, -10.f, -200.f), Vector3(5.f, 5.f, 5.f));
	Create::Entity("log", Vector3(330.f, -10.f, 200.f), Vector3(10.f, 10.f, 10.f));
	Create::Entity("log", Vector3(-330.f, -10.f, 200.f), Vector3(5.f, 5.f, 5.f));

	Create::Entity("tree", Vector3(30.f, -30.f, -150.f), Vector3(5.f, 5.f, 5.f));
	Create::Entity("tree", Vector3(230.f, -30.f, -200.f), Vector3(5.f, 5.f, 5.f));
	Create::Entity("tree", Vector3(-230.f, -30.f, -100.f), Vector3(5.f, 5.f, 5.f));
	Create::Entity("tree", Vector3(230.f, -30.f, 300.f), Vector3(5.f, 5.f, 5.f));
	Create::Entity("tree", Vector3(-230.f, -30.f, 100.f), Vector3(5.f, 5.f, 5.f));
	//------
	//-----scene graph - week5
	GenericEntity* baseCube = Create::Asset("cube", Vector3(0.0f, 0.0f, 0.0f));
	CSceneNode* baseNode = CSceneGraph::GetInstance()->AddNode(baseCube);

	GenericEntity* childCube = Create::Asset("cubeSG", Vector3(0.0f, 0.0f, 0.0f));
	CSceneNode* childNode = baseNode->AddChild(childCube);
	childNode->ApplyTranslate(0.0f, 2.0f, 0.0f);

	GenericEntity* grandChildCube = Create::Asset("cubeHead", Vector3(0.0f, 0.0f, 0.0f));
	CSceneNode*grandChildNode = childNode->AddChild(grandChildCube);
	grandChildNode->ApplyTranslate(0.0f, -1.0f, 0.0f);
	CUpdateTransformation* aRotateMtx = new CUpdateTransformation();
	aRotateMtx->ApplyUpdate(1.0f, 0.0f, 0.0f, 1.0f);
	aRotateMtx->SetSteps(-120, 60);
	grandChildNode->SetUpdateToTransformation(aRotateMtx);

	//Created a Waypoint inside WaypointManager
	lua_getglobal(CLuaInterface::GetInstance()->theLuaState, "Waypoint_A_1");
	int aWaypoint = CWaypointManager::GetInstance()->AddWaypoint(Vector3(CLuaInterface::GetInstance()->GetField("x"), 
																			CLuaInterface::GetInstance()->GetField("y"), 
																			CLuaInterface::GetInstance()->GetField("z")));

	lua_getglobal(CLuaInterface::GetInstance()->theLuaState, "Waypoint_A_2");
	int anotherWaypoint = CWaypointManager::GetInstance()->AddWaypoint(aWaypoint,Vector3(CLuaInterface::GetInstance()->GetField("x"),
																						CLuaInterface::GetInstance()->GetField("y"),
																						CLuaInterface::GetInstance()->GetField("z")));

	lua_getglobal(CLuaInterface::GetInstance()->theLuaState, "Waypoint_A_3");
	CWaypointManager::GetInstance()->AddWaypoint(anotherWaypoint,Vector3(CLuaInterface::GetInstance()->GetField("x"),
																		CLuaInterface::GetInstance()->GetField("y"),
																		CLuaInterface::GetInstance()->GetField("z")));
	CWaypointManager::GetInstance()->PrintSelf();


	//Create a CEnemy instance
	theEnemy = new CEnemy();
	theEnemy->Init();
	theEnemy->SetPos(Vector3(10, 1.1f, -20.0f));

	movingEnemy = new CEnemy();
	movingEnemy->Init(true);
	movingEnemy->SetPos(Vector3(-10.0f, 1.1f, -20.0f));

	enemyModel(); //body parts of theEnemy
	//enemy2Model();
	//enemy3Model();

	groundEntity = Create::Ground("SKYBOX_BOTTOM", "SKYBOX_BOTTOM");
//	Create::Text3DObject("text", Vector3(0.0f, 0.0f, 0.0f), "DM2210", Vector3(10.0f, 10.0f, 10.0f), Color(0, 1, 1));
	Create::Sprite2DObject("crosshair", Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 10.0f, 10.0f));

	//CameraEffects
	cameraEffects = Create::CameraEffects(true);
	cameraEffects->SetPistolScreen(MeshBuilder::GetInstance()->GenerateQuad("pistol", Color(1, 1, 1), 1.0f));
	cameraEffects->GetPistolScreen()->textureID = LoadTGA("Image//pistol.tga");
	cameraEffects->SetSMGScreen(MeshBuilder::GetInstance()->GenerateQuad("smg", Color(1, 1, 1), 1.0f));
	cameraEffects->GetSMGScreen()->textureID = LoadTGA("Image//smg.tga");
	cameraEffects->SetStatus_PistolScreen(true);
	cameraEffects->SetStatus_SMGScreen(false);

	SkyBoxEntity* theSkyBox = Create::SkyBox("SKYBOX_FRONT", "SKYBOX_BACK",
											 "SKYBOX_LEFT", "SKYBOX_RIGHT",
											 "SKYBOX_TOP", "SKYBOX_BOTTOM");

	// Customise the ground entity
	groundEntity->SetPosition(Vector3(0, -10, 0));
	groundEntity->SetScale(Vector3(100.0f, 100.0f, 100.0f));
	groundEntity->SetGrids(Vector3(10.0f, 1.0f, 10.0f));
	playerInfo->SetTerrain(groundEntity);


	theEnemy->SetTerrain(groundEntity);
	movingEnemy->SetTerrain(groundEntity);

	MovePosition.Set(10.0f, 0.0f, 0.0f);
	target.Set(10.0f, 0.0f, 450.0f);

	// Setup the 2D entities
	float halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2.0f;
	float halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2.0f;
	float fontSize = 25.0f;
	float halfFontSize = fontSize / 2.0f;
	for (int i = 0; i < 3; ++i)
	{
		textObj[i] = Create::Text2DObject("text", Vector3(-halfWindowWidth, -halfWindowHeight + fontSize*i + halfFontSize, 1.0f), "", Vector3(fontSize, fontSize, fontSize), Color(0.0f,1.0f,0.0f));
	}
	textObj[0]->SetText("HELLO WORLD");
}

void SceneText::Update(double dt)
{
	// Update our entities
	EntityManager::GetInstance()->Update(dt);

	// THIS WHOLE CHUNK TILL <THERE> CAN REMOVE INTO ENTITIES LOGIC! Or maybe into a scene function to keep the update clean
	if(KeyboardController::GetInstance()->IsKeyDown('1'))
		glEnable(GL_CULL_FACE);
	if(KeyboardController::GetInstance()->IsKeyDown('2'))
		glDisable(GL_CULL_FACE);
	if(KeyboardController::GetInstance()->IsKeyDown('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(KeyboardController::GetInstance()->IsKeyDown('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	

	//Debug
	if (KeyboardController::GetInstance()->IsKeyDown('M'))
	{
		CSceneNode* theNode = CSceneGraph::GetInstance()->GetNode(1);
		Vector3 pos = theNode->GetEntity()->GetPosition();
		theNode->GetEntity()->SetPosition(Vector3(pos.x + 50.0f, pos.y, pos.z + 50.0f));
	}
	if (KeyboardController::GetInstance()->IsKeyDown('N'))
	{
		CSpatialPartition::GetInstance()->PrintSelf();
	}

	if(KeyboardController::GetInstance()->IsKeyDown('5'))
	{
		lights[0]->type = Light::LIGHT_POINT;
	}
	else if(KeyboardController::GetInstance()->IsKeyDown('6'))
	{
		lights[0]->type = Light::LIGHT_DIRECTIONAL;
	}
	else if(KeyboardController::GetInstance()->IsKeyDown('7'))
	{
		lights[0]->type = Light::LIGHT_SPOT;
	}

	if(KeyboardController::GetInstance()->IsKeyDown('I'))
		lights[0]->position.z -= (float)(10.f * dt);
	if(KeyboardController::GetInstance()->IsKeyDown('K'))
		lights[0]->position.z += (float)(10.f * dt);
	if(KeyboardController::GetInstance()->IsKeyDown('J'))
		lights[0]->position.x -= (float)(10.f * dt);
	if(KeyboardController::GetInstance()->IsKeyDown('L'))
		lights[0]->position.x += (float)(10.f * dt);
	if(KeyboardController::GetInstance()->IsKeyDown('O'))
		lights[0]->position.y -= (float)(10.f * dt);
	if(KeyboardController::GetInstance()->IsKeyDown('P'))
		lights[0]->position.y += (float)(10.f * dt);

	// if the left mouse button was released
	if (MouseController::GetInstance()->IsButtonReleased(MouseController::LMB))
	{
		cout << "Left Mouse Button was released!" << endl;
	}
	if (MouseController::GetInstance()->IsButtonReleased(MouseController::RMB))
	{
		cout << "Right Mouse Button was released!" << endl;
	}
	if (MouseController::GetInstance()->IsButtonReleased(MouseController::MMB))
	{
		cout << "Middle Mouse Button was released!" << endl;
	}
	if (MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_XOFFSET) != 0.0)
	{
		cout << "Mouse Wheel has offset in X-axis of " << MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_XOFFSET) << endl;
	}
	/*if (MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) != 0.0)
	{
		cout << "Mouse Wheel has offset in Y-axis of " << MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) << endl;
	}*/
	// <THERE>

	// Update the player position and other details based on keyboard and mouse inputs
	playerInfo->Update(dt);

	//camera.Update(dt); // Can put the camera into an entity rather than here (Then we don't have to write this)

	GraphicsManager::GetInstance()->UpdateLights(dt);

	// Update the 2 text object values. NOTE: Can do this in their own class but i'm lazy to do it now :P
	// Eg. FPSRenderEntity or inside RenderUI for LightEntity
	std::ostringstream ss;
	ss.precision(5);
	float fps = (float)(1.f / dt);
	ss << "FPS: " << fps;
	textObj[1]->SetText(ss.str());

	std::ostringstream ss1;
	ss1.precision(4);
	ss1 << "Player:" << playerInfo->GetPos();
	textObj[2]->SetText(ss1.str());

	if (playerInfo->m_iCurrentWeapon == 0)
	{
		cameraEffects->SetStatus_PistolScreen(true);
		cameraEffects->SetStatus_SMGScreen(false);
	}
	else if (playerInfo->m_iCurrentWeapon == 1)
	{
		cameraEffects->SetStatus_PistolScreen(false);
		cameraEffects->SetStatus_SMGScreen(true);
	}
}

void SceneText::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GraphicsManager::GetInstance()->UpdateLightUniforms();

	// Setup 3D pipeline then render 3D
	GraphicsManager::GetInstance()->SetPerspectiveProjection(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	GraphicsManager::GetInstance()->AttachCamera(&camera);
	EntityManager::GetInstance()->Render();

	// Setup 2D pipeline then render 2D
	int halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2;
	int halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2;
	GraphicsManager::GetInstance()->SetOrthographicProjection(-halfWindowWidth, halfWindowWidth, -halfWindowHeight, halfWindowHeight, -10, 10);
	GraphicsManager::GetInstance()->DetachCamera();
	EntityManager::GetInstance()->RenderUI();

	for (int i = 0; i < 3; i++)
	{
		textObj[i]->RenderUI();
	}
	
}

void SceneText::enemyModel()
{
	GenericEntity* headCube = Create::Entity("sphere", Vector3(theEnemy->GetPos().x, theEnemy->GetPos().y + 4, theEnemy->GetPos().z), Vector3(2.0f, 2.0f, 2.0f));
	headCube->SetCollider(true);
	headCube->SetAABB(Vector3(1.f, 1.f, 1.f), Vector3(-1.f, -1.f, -1.f));
	headCube->InitLOD("sphere", "sphere2", "sphere3"); //high, mid, low

	GenericEntity* rightArmCube = Create::Entity("sphere", Vector3(theEnemy->GetPos().x + 2, theEnemy->GetPos().y, theEnemy->GetPos().z), Vector3(1.0f, 4.0f, 2.0f));
	rightArmCube->SetCollider(true);
	rightArmCube->SetAABB(Vector3(0.5f, 2.0f, 1.0f), Vector3(-0.5f, -2.0f, -1.0f));
	rightArmCube->InitLOD("sphere", "sphere2", "sphere3"); //high, mid, low

	GenericEntity* leftArmCube = Create::Entity("sphere", Vector3(theEnemy->GetPos().x - 2, theEnemy->GetPos().y, theEnemy->GetPos().z), Vector3(1.0f, 4.0f, 2.0f));
	leftArmCube->SetCollider(true);
	leftArmCube->SetAABB(Vector3(0.5f, 2.f, 1.f), Vector3(-0.5f, -2.f, -1.f));
	leftArmCube->InitLOD("sphere", "sphere2", "sphere3"); //high, mid, low

	theEnemy->theMainNode->AddChild(headCube); //add head to body
	theEnemy->theMainNode->AddChild(leftArmCube); //add leftarm to body
	theEnemy->theMainNode->AddChild(rightArmCube); //add rightarm to body

}

void SceneText::enemy2Model()
{
	GenericEntity* headCube = Create::Entity("cubeHead", Vector3(-100.0f, -2.0f, -10.0f), Vector3(3.0f, 3.0f, 3.0f));
	headCube->SetCollider(true);
	headCube->SetAABB(Vector3(1.f, 1.f, 1.f), Vector3(-1.f, -1.f, -1.f));
	headCube->InitLOD("cubeHead", "sphere", "cubeSG"); //high, mid, low

													   //add the pointer to this new entity to the scene graph
													   //CSceneNode* theNode = CSceneGraph::GetInstance()->AddNode(headCube);
	CSceneNode* theNode = CSceneGraph::GetInstance()->AddNode(headCube);
	if (theNode == NULL)
	{
		cout << "EntityManager::AddEntity: Unable to add to scene graph!" << endl;
	}

	CUpdateTransformation* movement = new CUpdateTransformation();
	movement->ApplyUpdate(1, 0, 0);
	movement->SetSteps(-60, 60);
	theNode->SetUpdateToTransformation(movement);


	GenericEntity* bodyCube = Create::Entity("cube", Vector3(-100.0f, -5.f, -10.0f), Vector3(4.0f, 4.0f, 4.0f));
	bodyCube->SetCollider(true);
	bodyCube->SetAABB(Vector3(1.5f, 3.f, 1.5f), Vector3(-1.5f, -3.f, -1.5f));
	//add the pointer to this new entity to the scene graph
	CSceneNode* anotherNode = theNode->AddChild(bodyCube);
	if (anotherNode == NULL)
	{
		cout << "EntityManager::AddEntity: Unable to add to scene graph!" << endl;
	}
}

void SceneText::enemy3Model()
{
	GenericEntity* headCube = Create::Entity("cubeHead", Vector3(100.0f, -5.f, -10.0f), Vector3(3.0f, 6.0f, 3.0f));
	headCube->SetCollider(true);
	headCube->SetAABB(Vector3(1.f, 1.f, 1.f), Vector3(-1.f, -1.f, -1.f));
	headCube->InitLOD("cubeHead", "sphere", "cubeSG"); //high, mid, low

													   //add the pointer to this new entity to the scene graph
													   //CSceneNode* theNode = CSceneGraph::GetInstance()->AddNode(headCube);
	CSceneNode* theNode = CSceneGraph::GetInstance()->AddNode(headCube);
	if (theNode == NULL)
	{
		cout << "EntityManager::AddEntity: Unable to add to scene graph!" << endl;
	}

	GenericEntity* bodyCube = Create::Entity("cube", Vector3(100.0f, -2.0f, -10.0f), Vector3(5.0f, 5.0f, 5.0f));
	bodyCube->SetCollider(true);
	bodyCube->SetAABB(Vector3(1.5f, 3.f, 1.5f), Vector3(-1.5f, -3.f, -1.5f));
	//add the pointer to this new entity to the scene graph
	CSceneNode* anotherNode = theNode->AddChild(bodyCube);
	if (anotherNode == NULL)
	{
		cout << "EntityManager::AddEntity: Unable to add to scene graph!" << endl;
	}

	
}

void SceneText::Exit()
{
	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
	playerInfo->DetachCamera();

	if (playerInfo->DropInstance() == false)
	{
#if _DEBUGMODE==1
		cout << "Unable to drop PlayerInfo class" << endl;
#endif
	}

	// Delete the lights
	delete lights[0];
	delete lights[1];
}


