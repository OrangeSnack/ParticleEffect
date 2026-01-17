#pragma once
#include <imgui.h>
#include "Singleton.hpp"

namespace MMMEngine::Editor
{
	class HierarchyWindow : public Utility::Singleton<HierarchyWindow>
	{
	public: 
		void Render();
	};
}