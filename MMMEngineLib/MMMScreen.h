#pragma once
#include "GlobalRegistry.h"
//#include "RenderManager.h"

#include <cassert>

namespace MMMEngine
{
	enum class FullScreenMode
	{
		Windowed,
		FullScreenWindow,
		BorderlessWindow
	};

	namespace Screen
	{
		inline void SetResolution(int width, int height) { assert(g_pApp && "글로벌 레지스트리에 Application이 등록되어있지 않습니다!");  g_pApp->SetWindowSize(width, height); }
		inline void SetResolution(int width, int height, FullScreenMode mode) 
		{ 
			assert(g_pApp && "글로벌 레지스트리에 Application이 등록되어있지 않습니다!");  
			g_pApp->SetWindowSize(width, height); 
			switch (mode)
			{
			case FullScreenMode::Windowed:
				g_pApp->SetDisplayMode(MMMEngine::Utility::App::DisplayMode::Windowed);
				break;
			case FullScreenMode::FullScreenWindow:
				g_pApp->SetDisplayMode(MMMEngine::Utility::App::DisplayMode::Fullscreen);
				break;
			case FullScreenMode::BorderlessWindow:
				g_pApp->SetDisplayMode(MMMEngine::Utility::App::DisplayMode::BorderlessWindowed);
				break;
			}
		}
	}
}
