#pragma once
#include "Behaviour.h"

namespace MMMEngine
{
	class MMMENGINE_API ScriptBehaviour : public Behaviour
	{
	private:
		RTTR_ENABLE(Behaviour)
		RTTR_REGISTRATION_FRIEND
	public:
		ScriptBehaviour() = default;
		virtual ~ScriptBehaviour() = default;
	};
}