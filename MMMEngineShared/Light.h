#pragma once
#include "Export.h"
#include "Component.h"
#include "rttr/type"

namespace MMMEngine {
	class MMMENGINE_API Light : public Component
	{
		RTTR_ENABLE(Component)
		RTTR_REGISTRATION_FRIEND
	public:


		void Initialize() override;
		void UnInitialize() override;

		void Render();
	};
}


