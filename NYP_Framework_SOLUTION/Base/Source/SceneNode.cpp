#include "SceneNode.h"
#include "EntityManager.h"
#include "SceneGraph.h"
#include <algorithm>



CSceneNode::CSceneNode(void)
{
}

CSceneNode::~CSceneNode()
{
}

void CSceneNode::Destroy(void)
{
	//destroy children
	std::vector<CSceneNode*>::iterator it;
	for (it = theChildren.begin();  it != theChildren.end(); ++it)
	{
		(*it)->Destroy();
		delete *it;
		theChildren.erase(it);
	}

	theEntity = NULL;
	theParent = NULL;
}

void CSceneNode::SetID(const int ID)
{
	this->ID = ID;
}

int CSceneNode::GetID(void) const
{
	return this->ID;
}

bool CSceneNode::SetEntity(EntityBase * theEntity)
{
	if (theEntity)
	{
		this->theEntity = theEntity;
		return true;
	}

	return false;
}

EntityBase * CSceneNode::GetEntity(void) const
{
	return this->theEntity;
}

void CSceneNode::SetParent(CSceneNode * theParent)
{
	this->theParent = theParent;
}

CSceneNode * CSceneNode::GetParent(void) const
{
	return this->theParent;
}

//-----------start of Child related
CSceneNode * CSceneNode::AddChild(EntityBase * theEntity)
{
	if (theEntity)
	{
		//create a new scene node
		CSceneNode* aNewNode = new CSceneNode();
		//set the entity to this new scene node
		aNewNode->SetEntity(theEntity);
		//set the parent for the new node
		aNewNode->SetParent(this);
		aNewNode->SetID(CSceneGraph::GetInstance()->GenerateID());  //<---scene graph missing
		//add the new node into the vector
		this->theChildren.push_back(aNewNode);
		//return this new node
		return aNewNode;
	}
	return NULL;
}

bool CSceneNode::DeleteChild(EntityBase * theEntity)
{
	//if this node contains theEntity, thne we proceed to delete all its children
	if (this->theEntity == theEntity)
	{
		//if this node has children, then we proceed to delete them
		if (theChildren.size() != 0)
		{
			//iterate through all the children and delete all of their children and grand children etc
			vector<CSceneNode*>::iterator it = theChildren.begin();
			while (it != theChildren.end())
			{
				if ((*it)->DeleteAllChildren())
				{
					cout << "CSceneNode::DeleteChild: Deleted child nodes for theEntity." << endl;
				}
				(*it)->GetEntity()->SetIsDone(true); 
				delete *it;
				it = theChildren.erase(it);
			}
		}
		return true;
	}
	else
	{
		//search the children for this particular theEntity
		if (theChildren.size() != 0)
		{
			std::vector<CSceneNode*>::iterator it;
			for (it = theChildren.begin(); it != theChildren.end(); ++it)
			{
				//check if this child is the one containing theEntity
				if ((*it)->DeleteChild(theEntity))
				{
					//if DeleteChild method call above DID remove theEntity
					//then we should proceed to removed this child from
					(*it)->GetEntity()->SetIsDone(true);
					delete *it;
					theChildren.erase(it);
					break;	//stop deleting since found the entity
				}
			}
		}
	}

	return false;
}

bool CSceneNode::DeleteChild(const int ID)
{
	//if this node contains theEntity, then we proceed to delete all its children
	if (this->ID == ID)
	{
		//if this node has children, then we proceed to delete them.
		if (theChildren.size() != 0)
		{
			//iterate through all the children and delete all of their children and grand children etc
			vector <CSceneNode*>::iterator it = theChildren.begin();
			while (it != theChildren.end())
			{
				if ((*it)->DeleteAllChildren())
				{
					cout << "CSceneNode::DeleteChild: Deleted child nodes for ID=" << ID << endl;
				}
				(*it)->GetEntity()->SetIsDone(true);
				delete *it;
				it = theChildren.erase(it);
			}
		}
		return true;	//return true to say that this node contains theEntity
	}
	else
	{
		//Search the children for this particular theEntity
		if (theChildren.size() != 0)
		{
			std::vector<CSceneNode*>::iterator it;
			for (it = theChildren.begin(); it != theChildren.end(); ++it)
			{
				//check if this child is the one containing theEntity
				if ((*it)->DeleteChild(theEntity))
				{
					//if deleteChild method call above DID remove theEntity
					//then we should proceed to removed this child from our vector of children
					(*it)->GetEntity()->SetIsDone(true);
					delete *it;
					theChildren.erase(it);
					break;		//stop deleting since we have already found and delted theEntity
				}
			}
		}

	}
	return false;
}

bool CSceneNode::DeleteAllChildren(void)
{
	bool bResult = false;

	vector <CSceneNode*>::iterator it = theChildren.begin();
	while (it != theChildren.end())
	{
		if ((*it)->DeleteAllChildren())
		{
			cout << "CSceneNode::DeleteChild: Delete child nodes." << endl;
		}
		(*it)->GetEntity()->SetIsDone(true);
		delete *it;
		it = theChildren.erase(it);
		bResult = true;
	}

	return bResult;
}

CSceneNode * CSceneNode::DetachChild(EntityBase * theEntity)
{
	//if it is inside this node, then return this node
	if (this->theEntity == theEntity)
		return this;

	if (theChildren.size() != 0)
	{
		vector <CSceneNode*>::iterator it = theChildren.begin();
		while (it != theChildren.end())
		{
			CSceneNode* theNode = (*it)->DetachChild(theEntity);
			if (theNode)
			{
				//remove this node from the children
				theChildren.erase(it);
				return theNode;
			}
			it++;
		}
	}
	return NULL;
}

CSceneNode * CSceneNode::DetachChild(const int ID)
{
	//if it is indie this node, then return this node
	if (this->ID == ID)
		return this;

	if (theChildren.size() != 0)
	{
		vector <CSceneNode*>::iterator it = theChildren.begin();
		while (it != theChildren.end())
		{
			CSceneNode* theNode = (*it)->DetachChild(theEntity);
			if (theNode)
			{
				//remove this node from the children
				theChildren.erase(it);
				return theNode;
			}
			it++;
		}
	}
	return NULL;
}
//-----------end of Child related

CSceneNode * CSceneNode::GetEntity(EntityBase * theEntity)
{
	if (this->theEntity == theEntity)
	{
		return this;
	}

	if (theChildren.size() != 0)
	{
		std::vector<CSceneNode*>::iterator it;
		for (it = theChildren.begin(); it != theChildren.end(); ++it)
		{
			CSceneNode* theNode = (*it)->GetEntity(theEntity);
			if (theNode)
			{
				return theNode;
			}
		}
	}
	return NULL;
}

CSceneNode * CSceneNode::GetEntity(const int ID)
{
	if (this->ID == ID)
	{
		return this;
	}

	if (theChildren.size() != 0)
	{
		std::vector<CSceneNode*>::iterator it;
		for (it = theChildren.begin(); it != theChildren.end(); ++it)
		{
			CSceneNode* theNode = (*it)->GetEntity(ID);
			if (theNode)
			{
				return theNode;
			}
		}
	}
	return NULL;
}

int CSceneNode::GetNumOfChild(void)
{
	//start with this node's children
	int NumOfChild = theChildren.size();

	//Ask the children to feedback how many children they have
	std::vector<CSceneNode*>::iterator it;
	for (it = theChildren.begin(); it != theChildren.end(); ++it)
	{
		NumOfChild += (*it)->GetNumOfChild();
	}
	return NumOfChild;
}

void CSceneNode::PrintSelf(const int numTabs)
{
	if (numTabs == 0)
	{
		cout << "==============================" << endl << "Start of theRoot::PrintSelf()" << endl;
		cout << "CSceneNode::PrintSelf: ID=" << ID << "/Children=" << theChildren.size() << endl;
		cout << "Printing out the Children: " << endl;
		std::vector<CSceneNode*>::iterator it = theChildren.begin();
		while (it != theChildren.end())
		{
			(*it)->PrintSelf((numTabs + 1));
			it++;
		}
		cout << "End of theRoot::PrintSelf()" << endl << "=====================================" << endl;
	}
	else
	{
		for (int i = 0; i < numTabs; i++)
			cout << "\t";
		cout << "CSceneNode::PrintSelf: ID-" << ID << "/theEntity-" << theEntity << "/Children-" << theChildren.size() << endl;
		for (int i = 0; i < numTabs; i++)
			cout << "\t";
		cout << "Printing out the Children: " << endl;
		std::vector<CSceneNode*>::iterator it = theChildren.begin();
		while (it != theChildren.end())
		{
			(*it)->PrintSelf((numTabs + 1));
			it++;
		}
	}
}
