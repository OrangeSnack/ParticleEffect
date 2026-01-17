#pragma once
#include "GameObject.h"

namespace MMMEngine::EditorRegistry
{
	inline bool g_editor_hierarchy_window = true;
	inline bool g_editor_inspector_window = true;
	inline ObjPtr<GameObject> g_selectedGameObject = nullptr;
}

