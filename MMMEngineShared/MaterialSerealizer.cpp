#include "MaterialSerealizer.h"
#include <rttr/type>

#include "Material.h"
#include "VShader.h"
#include "PShader.h"

using json = nlohmann::json;

json MMMEngine::MaterialSerealizer::ObjToJson(rttr::instance obj)
{
	json j;
	rttr::type t = obj.get_type();

	for (auto& prop : t.get_properties())
	{
		rttr::variant val = prop.get_value(obj);
		if (!val) continue;

		// 문자열 변환 가능하면 그대로 저장
		if (val.can_convert<std::string>())
		{
			j[prop.get_name().to_string()] = val.to_string();
		}
		else if (val.is_type<std::unordered_map<std::wstring, MMMEngine::PropertyValue>>())
		{
			// m_properties 처리
			json props = json::object();
			auto& mapVal = val.get_value<std::unordered_map<std::wstring, MMMEngine::PropertyValue>>();
			for (auto& [key, pval] : mapVal)
			{
				std::string skey(key.begin(), key.end());
				json pv;
				std::visit([&](auto&& arg) {
					using T = std::decay_t<decltype(arg)>;
					if constexpr (std::is_same_v<T, int>)
						pv = { {"type","int"}, {"value",arg} };
					else if constexpr (std::is_same_v<T, float>)
						pv = { {"type","float"}, {"value",arg} };
					else if constexpr (std::is_same_v<T, DirectX::SimpleMath::Vector3>)
						pv = { {"type","Vector3"}, {"value",{arg.x,arg.y,arg.z}} };
					else if constexpr (std::is_same_v<T, DirectX::SimpleMath::Matrix>)
						pv = { {"type","Matrix"}, {"value",{
							arg._11,arg._12,arg._13,arg._14,
							arg._21,arg._22,arg._23,arg._24,
							arg._31,arg._32,arg._33,arg._34,
							arg._41,arg._42,arg._43,arg._44
						}} };
					else if constexpr (std::is_same_v<T, ResPtr<MMMEngine::Texture2D>>)
						pv = { {"type","Texture2D"}, {"file", arg ? arg->GetFilePath() : L""} };
					}, pval);
				props[skey] = pv;
			}
			j[prop.get_name().to_string()] = props;
		}
	}
	return j;

}

bool MMMEngine::MaterialSerealizer::Serealize(ResPtr<Material> _material, std::wstring _path)
{
	json snapshot;
	auto matMUID = _material->GetMUID().IsEmpty() ? Utility::MUID::NewMUID() : _material->GetMUID();

	snapshot["MUID"] = matMUID.ToString();
	snapshot["Name"] = _material->GetName();

	json props = json::object();
	for (const auto& [key, value] : _material->m_properties) {
		
	}
	

	return true;
}
