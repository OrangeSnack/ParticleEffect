#pragma once
#include "ResourceManager.h"
#include "rttr/type"
#include <string>

namespace MMMEngine::Resources
{
	template <typename T>
	ResPtr<T> Load(const std::wstring& path) {
		return ResourceManager::Get().Load<T>(path);
	}

	template <typename T>
	std::string GetTypeName()
	{
		return rttr::type::get<T>().get_name().to_string();
	}
}