#pragma once
#include "Object.h"
#include "MUID.h"

namespace MMMEngine
{
	class GameObject;
	class Scene
	{
	private:
		Utility::MUID m_muid;
		std::vector<ObjPtr<GameObject>> m_gameObjects;
	};
}