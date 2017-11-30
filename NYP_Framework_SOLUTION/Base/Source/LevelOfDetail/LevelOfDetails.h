#pragma once
#include "Vector3.h"
#include "Mesh.h"

class CLevelOfDetails
{
public:
	CLevelOfDetails();
	virtual ~CLevelOfDetails();
		
	Mesh* modelMesh_HighDetails;
	Mesh* modelMesh_MidDetails;
	Mesh* modelMesh_LowDetails;

	enum DETAIL_LEVEL
	{
		NO_DETAILS = 0,
		HIGH_DETAILS, 
		MID_DETAILS,
		LOW_DETAILS,
		NUM_DETAIL_LEVEL,
	};

	bool InitLOD(	const std::string& _meshName_High,
					const std::string& _meshName_Mid,
					const std::string& _meshName_Low
				);
	bool DestroyLOD(void);

	void SetLODStatus(const bool _active);
	bool GetLODStatus(void) const;

	bool SetLODMesh(Mesh* _theMesh, const DETAIL_LEVEL _detailLevel);
	Mesh* GetLODMesh(void) const;
	Mesh* GetLODMesh(const DETAIL_LEVEL _detailLevel) const;
	int GetDetailLevel(void) const;
	bool SetDetailLevel(const DETAIL_LEVEL _detailLevel);

protected:
	bool m_bActive;
	DETAIL_LEVEL theDetailLevel;
};
