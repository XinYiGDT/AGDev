#include "Waypoint.h"
#include <limits>
#include <iostream>
using namespace std;

CWaypoint::CWaypoint()
	:position(Vector3(0.0f, 0.0f, 0.0f))
	, m_iID(-1)
{
	relatedWaypoints.clear();
}

CWaypoint::~CWaypoint()
{
	//we clear the relatedWaypoints without deleting
	//as waypointmanager's destructor will delete the memory
	relatedWaypoints.clear();
}

void CWaypoint::SetPosition(Vector3 position)
{
	this->position = position;
}

Vector3 CWaypoint::GetPosition(void) const
{
	return position;
}

void CWaypoint::SetID(const int m_iID)
{
	this->m_iID = m_iID;
}

int CWaypoint::GetID(void) const
{
	return m_iID;
}

void CWaypoint::AddRelatedWaypoint(CWaypoint * relatedWaypoint)
{
	relatedWaypoints.push_back(relatedWaypoint);
}

bool CWaypoint::RemoveRelatedWaypoint(const int m_iID)
{
	//if waypoints has related waypoints, then we proceed to search
	if (relatedWaypoints.size() != 0)
	{
		//iterate through all the waypoints
		std::vector<CWaypoint*>::iterator it = relatedWaypoints.begin();

		while (it != relatedWaypoints.end())
		{
			if ((*it)->GetID() == m_iID)
			{
				//erase from the vector, relatedWaypoints, only. not delete
				it = relatedWaypoints.erase(it);
				return true;
			}
			it++;
		}
	}

	return false;
}

CWaypoint * CWaypoint::GetNearestWaypoint(void)
{
	CWaypoint* theNearestWaypoint = NULL;
	float m_fDistance = numeric_limits<float>::max();

	//if waypoints has related waypoints, we proceed to search
	if (relatedWaypoints.size() != 0)
	{
		//iterate through all waypoints
		std::vector<CWaypoint*>::iterator it = relatedWaypoints.begin();

		while (it != relatedWaypoints.end())
		{
			Vector3 aRelatedWaypoint = (*it)->GetPosition();

			float xDistance = position.x - aRelatedWaypoint.x;
			float zDistance = position.z - aRelatedWaypoint.z;
			float distanceSquared = (float)(xDistance*xDistance + zDistance*zDistance);

			if (m_fDistance > distanceSquared)
			{
				m_fDistance = distanceSquared;
				theNearestWaypoint = (CWaypoint*)(*it);
			}
			it++;
		}
	}
	return theNearestWaypoint;
}

int CWaypoint::GetNumberOfWaypoints(void) const
{
	return relatedWaypoints.size();
}

void CWaypoint::PrintSelf(void)
{
	cout << "Waypoint ID    : " << m_iID << endl;
	cout << " position      : " << position << endl;
	cout << " related waypoints : ";

	//if waypoints has related waypoints, proceed to search
	if (relatedWaypoints.size() != 0)
	{
		//iterate through all waypoints
		std::vector<CWaypoint*>::iterator it = relatedWaypoints.begin();
		while (it != relatedWaypoints.end())
		{
			cout << (*it)->GetID() << endl;
			it++;
		}
	}
	else
	{
		cout << "NIL" << endl;
	}
}


