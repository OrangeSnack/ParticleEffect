#pragma once
#include <imgui.h>
#include "Singleton.hpp"

namespace MMMEngine::Editor
{
	class InspectorWindow : public Utility::Singleton<InspectorWindow>
	{
	public:
		void Render();
	};
}