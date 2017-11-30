#include "LevelOfDetails.h"
#include "MeshBuilder.h"

CLevelOfDetails::CLevelOfDetails()
	: modelMesh_HighDetails(NULL)
	, modelMesh_MidDetails(NULL)
	, modelMesh_LowDetails(NULL)
	, m_bActive(false)
	, theDetailLevel(HIGH_DETAILS)
{
}

CLevelOfDetails::~CLevelOfDetails()
{
	modelMesh_HighDetails = NULL;
	modelMesh_MidDetails = NULL;
	modelMesh_LowDetails = NULL;
}

bool CLevelOfDetails::InitLOD(const std::string & _meshName_High
							, const std::string & _meshName_Mid
							, const std::string & _meshName_Low)
{
	//retrieve the meshes from meshBuilder's library and assign to the 3 mesh pointers
	modelMesh_HighDetails = MeshBuilder::GetInstance()->GetMesh(_meshName_High);
	modelMesh_MidDetails = MeshBuilder::GetInstance()->GetMesh(_meshName_Mid);
	modelMesh_LowDetails = MeshBuilder::GetInstance()->GetMesh(_meshName_Low);

	//if any of the mesh is not loaded, then return false and avoid setting the LOD to active
	if (modelMesh_HighDetails == nullptr ||
		modelMesh_MidDetails == nullptr ||
		modelMesh_LowDetails == nullptr)
	{
		return false;
	}

	SetLODStatus(true);
	return true;
}

bool CLevelOfDetails::DestroyLOD(void)
{
	if (modelMesh_HighDetails)
	{
		delete modelMesh_HighDetails;
		modelMesh_HighDetails = NULL;
	}
	if (modelMesh_MidDetails)
	{
		delete modelMesh_MidDetails;
		modelMesh_MidDetails = NULL;
	}
	if (modelMesh_LowDetails)
	{
		delete modelMesh_LowDetails;
		modelMesh_LowDetails = NULL;
	}
	return false;
}

void CLevelOfDetails::SetLODStatus(const bool _active)
{
	m_bActive = _active;
}

bool CLevelOfDetails::GetLODStatus(void) const
{
	return m_bActive;
}

bool CLevelOfDetails::SetLODMesh(Mesh * _theMesh, const DETAIL_LEVEL _detailLevel)
{
	if (_detailLevel == HIGH_DETAILS)
		modelMesh_HighDetails = _theMesh;
	else if (_detailLevel == MID_DETAILS)
		modelMesh_MidDetails = _theMesh;
	else if (_detailLevel == LOW_DETAILS)
		modelMesh_LowDetails = _theMesh;
	else
		return false;

	return true;
}

Mesh * CLevelOfDetails::GetLODMesh(void) const
{
	if (theDetailLevel == HIGH_DETAILS)
		return modelMesh_HighDetails;
	if (theDetailLevel == MID_DETAILS)
		return modelMesh_MidDetails;
	if (theDetailLevel == LOW_DETAILS)
		return modelMesh_LowDetails;

	return NULL;
}

Mesh * CLevelOfDetails::GetLODMesh(const DETAIL_LEVEL _detailLevel) const
{
	if (_detailLevel == HIGH_DETAILS)
		return modelMesh_HighDetails;
	if (_detailLevel == MID_DETAILS)
		return modelMesh_MidDetails;
	if (_detailLevel == LOW_DETAILS)
		return modelMesh_LowDetails;

	return NULL;
}

int CLevelOfDetails::GetDetailLevel(void) const
{
	return theDetailLevel;
}

bool CLevelOfDetails::SetDetailLevel(const DETAIL_LEVEL _detailLevel)
{
	if ((_detailLevel >= NO_DETAILS) && (_detailLevel < NUM_DETAIL_LEVEL))
	{
		this->theDetailLevel = _detailLevel;
		return true;
	}
	return false;
}
