#pragma once

#include "Vector3.h"
#include <vector>
using namespace std;

#include "EntityBase.h"
#include "Transform.h"

class CEnemy;

class CSceneNode: public CTransform
{
public:
	CSceneNode(void);
	virtual ~CSceneNode();

	CEnemy* theSource;
	void SetSource(CEnemy* _source);
	CEnemy* GetSource(void);

	//Release all memory for thsi node and its children
	void Destroy(void);

	//Set the ID for this node
	void SetID(const int ID);
	//Get the ID for this node
	int GetID(void) const;

	//set the entity for this node
	bool SetEntity(EntityBase* theEntity);
	//Get the ID for this node
	EntityBase* GetEntity(void) const;

	//set a parent to this node
	void SetParent(CSceneNode* theParent);
	//Get parent of this node
	CSceneNode* GetParent(void) const;

	//Add a child to this node
	CSceneNode* AddChild(EntityBase* theEntity = NULL);
	//Delete a child from this node using the pointer to the entity
	bool DeleteChild(EntityBase* theEntity = NULL);
	//delete a child from this node using its ID
	bool DeleteChild(const int ID);
	//Delete all children from this node using its ID
	bool DeleteAllChildren(void);
	//detach a child from this node using the pointer to the node
	CSceneNode* DetachChild(EntityBase* theEntity = NULL);
	//detach a child from this node using its ID
	CSceneNode* DetachChild(const int ID);
	//Get the entity inside this Scene graph
	CSceneNode* GetEntity(EntityBase* theEntity);
	//get the entity inside this scene graph using its ID
	CSceneNode* GetEntity(const int ID);
	//Return the number of children in this group
	int GetNumOfChild(void);

	//update
	void Update(void);
	//render
	void Render(void);

	//Printself for debugging
	void PrintSelf(const int numTabs = 0);

	

protected:
	int	ID;
	EntityBase* theEntity;
	CSceneNode* theParent;

	vector<CSceneNode*> theChildren;
};
