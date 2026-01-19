#pragma once
#include "ExportSingleton.hpp"
#include <string>
#include "ResourceManager.h"

#include "json/json.hpp"
#include <rttr/type>

namespace MMMEngine {
	class Material;
	class MMMENGINE_API MaterialSerealizer : public Utility::ExportSingleton<MaterialSerealizer>
	{
	private:
		json ObjToJson(rttr::instance _obj);

	public:
		bool Serealize(ResPtr<Material> _material, std::wstring _path);
	};
}


