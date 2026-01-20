#include "StaticMesh.h"
#include <rttr/registration.h>

RTTR_REGISTRATION
{
	using namespace rttr;
	using namespace MMMEngine;

	registration::class_<StaticMesh>("StaticMesh")
		.property("castShadows", &StaticMesh::castShadows)
		.property("receiveShadows", &StaticMesh::receiveShadows)
		.property("meshData", &StaticMesh::meshData)
		.property("meshGroupData", &StaticMesh::meshGroupData);
}

bool MMMEngine::StaticMesh::LoadFromFilePath(const std::wstring& filePath)
{
	return true;
}
