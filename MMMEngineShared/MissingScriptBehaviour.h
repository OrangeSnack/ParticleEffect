#pragma once
#include "ScriptBehaviour.h"

namespace MMMEngine
{
	class MMMENGINE_API MissingScriptBehaviour : public ScriptBehaviour
	{
	private:
		RTTR_ENABLE(ScriptBehaviour)
		RTTR_REGISTRATION_FRIEND
	public:
		MissingScriptBehaviour() = default;
		virtual ~MissingScriptBehaviour() = default;
	};
}