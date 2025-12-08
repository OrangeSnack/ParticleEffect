#pragma once
#include "delegates/include/delegates/delegates.h"

using namespace delegates;

namespace MMMEngine
{	
	template<typename... Args>
	struct ActionSignature
	{
		using type = void(Args...);
	};

	template<typename...Args>
	using Action = delegate<typename ActionSignature<Args...>::type>;
	
	
	template<typename R, typename... Args>
	struct FuncSignature
	{
		using type = R(Args...);
	};

	template<typename R, typename... Args>
	using Func = delegates::delegate<typename FuncSignature<R, Args...>::type>;
}