#include "App.h"

MMMEngine::App::App(HINSTANCE hInstance)
	: m_hInstance(hInstance)
	, m_hWnd(nullptr)
{
	m_windowTitle = L"MMM Engine Application";
}

MMMEngine::App::~App()
{
}

bool MMMEngine::App::Initialize()
{
	return false;
}

void MMMEngine::App::Run()
{
}

void MMMEngine::App::Shutdown()
{
}

bool MMMEngine::App::CreateMainWindow()
{

	return false;
}

LRESULT MMMEngine::App::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
}
