#include "Light.h"
#include "RenderManager.h"

#include "rttr/registration.h"

RTTR_REGISTRATION{
	using namespace rttr;
	using namespace MMMEngine;

	registration::class_<Light>("Light")
		(metadata("wrapper_type", rttr::type::get<ObjPtr<Light>>()))
		.property("LightType", &Light::GetLightType, &Light::SetLightType);

	registration::class_ <ObjPtr<Light>>("ObjPtr<Light>")
		.constructor<>(
			[]() {
				return Object::NewObject<Light>();
			});

	type::register_wrapper_converter_for_base_classes<MMMEngine::ObjPtr<Light>>();
}

void MMMEngine::Light::Initialize()
{
	lightIndex = RenderManager::Get().AddLight(this);
}

void MMMEngine::Light::UnInitialize()
{
	RenderManager::Get().RemoveLight(lightIndex);
}

void MMMEngine::Light::Render()
{

}
