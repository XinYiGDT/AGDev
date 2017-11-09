#include "SceneGraph.h"
#include "MeshBuilder.h"
#include "EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"

CSceneGraph::CSceneGraph(void):ID(0),theRoot(NULL)
{
	theRoot = new CSceneNode();
	//assign the first ID to the root. Dedfault is 0
	theRoot->SetID(this->GenerateID());
}

CSceneGraph::~CSceneGraph()
{
}

void CSceneGraph::Destroy()
{
	if (theRoot)
	{
		theRoot->DeleteAllChildren();
		delete theRoot;
	}
	Singleton<CSceneGraph>::Destroy();
}

CSceneNode * CSceneGraph::GetRoot()
{
	return theRoot;
}

CSceneNode * CSceneGraph::AddNode(EntityBase * theEntity)
{
	CSceneNode* aNewSceneNode = theRoot->AddChild(theEntity);
	//aNewSceneNode->SetID(this->GenerateID());
	return aNewSceneNode;
}

//delete a node from this scene graph using the pointer to the node
bool CSceneGraph::DeleteNode(EntityBase * theEntity)
{
	return theRoot->DeleteChild(theEntity);
}

bool CSceneGraph::DeleteNode(const int ID)
{
	return theRoot->DeleteChild(ID);
}

//detach a node from this scene graph using the pointer to the node
CSceneNode * CSceneGraph::DetachNode(CSceneNode * theNode)
{
	return NULL;	//theRoot->DetachChild(theNode);
}

//detach a node from this scene graph using its ID
CSceneNode * CSceneGraph::DetachNode(const int ID)
{
	return theRoot->DetachChild(ID);
}

//Get a node using the pointer to the node
CSceneNode * CSceneGraph::GetNode(EntityBase * theEntity)
{
	return theRoot->GetEntity(theEntity);
}

//get a node using its ID
CSceneNode * CSceneGraph::GetNode(const int ID)
{
	return theRoot->GetEntity(ID);
}

//return the number of nodes in this scene graph
int CSceneGraph::GetNumOfNode(void)
{
	return theRoot->GetNumOfChild();
}

int CSceneGraph::GenerateID(void)
{
	//return the ID and increment the value by 1
	return ID++;
}

void CSceneGraph::PrintSelf(void)
{
	theRoot->PrintSelf();
}
