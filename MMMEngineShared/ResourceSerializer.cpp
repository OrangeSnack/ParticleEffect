#include "ResourceSerializer.h"
#include "json/json.hpp"
#include "StaticMesh.h"
#include "RenderShared.h"
#include "rttr/type"

#include <filesystem>

DEFINE_SINGLETON(MMMEngine::ResourceSerializer);

namespace fs = std::filesystem;
using json = nlohmann::json;
using namespace MMMEngine;
using namespace rttr;


json SerializeVariant(const rttr::variant& var) {
	type t = var.get_type();
}

json SerializeVertex(const std::vector<Mesh_Vertex>& submesh)
{
	json meshJson;
	type subt = type::get(submesh);
	meshJson["Type"] = subt.get_name().to_string();

	for (auto& vertex : submesh)
	{
		type vert = type::get(vertex);
		meshJson[subt.get_name().to_string()]["Type"] = vert.get_name().to_string();

		for (auto& value : vert.get_properties(
			rttr::filter_item::instance_item |
			rttr::filter_item::public_access |
			rttr::filter_item::non_public_access))
		{
			auto string = vert.get_name().to_string();
			if (value.is_readonly())
				continue;

			rttr:variant var = value.get_value(vertex);
			meshJson[vert.get_name().to_string()]["Vertex"] = SerializeVariant(var);
			//TODO::json 출력 보면서 다시 만들기
		}
	}
}

void MMMEngine::ResourceSerializer::Serialize_StaticMesh(const StaticMesh* _in, std::wstring _path)
{
	json snapshot;

	auto meshMUID = _in->GetMUID().IsEmpty() ? Utility::MUID::NewMUID() : _in->GetMUID();

	snapshot["MUID"] = meshMUID.ToString();

	json meshData = json::array();
	for (auto& submesh : _in->meshData.vertices) {
		json subData = json::array();
		subData.push_back(SerializeVertex(submesh));
	}
}

void MMMEngine::ResourceSerializer::DeSerialize_StaticMesh(const StaticMesh* _out, std::wstring _path)
{

}
