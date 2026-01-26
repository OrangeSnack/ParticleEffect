#pragma once
#include "Export.h"
#include "Component.h"
#include "rttr/type"

namespace MMMEngine {
	enum LightType {
		Directional = 0,
		Point = 1,
	};

	class RenderManager;
	class MMMENGINE_API Light : public Component
	{
		RTTR_ENABLE(Component)
		RTTR_REGISTRATION_FRIEND
		friend class RenderManager;
	private:
		LightType lightType;
		int lightIndex = -1;

	public:
		LightType GetLightType() { return lightType; }
		void SetLightType(LightType _type) { lightType = _type; }

		void Initialize() override;
		void UnInitialize() override;

		void Render();
	};
}


