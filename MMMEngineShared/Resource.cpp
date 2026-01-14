#include "Resource.h"

#include "rttr/registration"
#include "rttr/detail/policies/ctor_policies.h"

RTTR_REGISTRATION
{
	using namespace rttr;
	using namespace MMMEngine;

	registration::class_<Resource>("Resource")
		.property("MUID", &Resource::GetMUID, &Resource::SetMUID, registration::private_access)
		.property("FilePath", &Resource::GetFilePath, &Resource::SetFilePath, registration::private_access)
		.method("LoadFromFilePath", &Resource::LoadFromFilePath, registration::private_access);
}

void MMMEngine::Resource::SetMUID(const Utility::MUID& muid)
{
	m_muid = muid;
}

void MMMEngine::Resource::SetFilePath(const std::wstring& filePath)
{
	m_filePath = filePath;
}

const std::wstring& MMMEngine::Resource::GetFilePath() const
{
	return m_filePath;
}

const MMMEngine::Utility::MUID& MMMEngine::Resource::GetMUID() const
{ 
	return m_muid;
}