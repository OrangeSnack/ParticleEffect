#include "imgui.h"
#include "SceneViewWindow.h"
#include "EditorRegistry.h"

using namespace MMMEngine::Editor;
using namespace MMMEngine;
using namespace MMMEngine::EditorRegistry;

void MMMEngine::Editor::SceneViewWindow::Initialize()
{
	if (m_pCam)
		m_pCam = std::make_unique<EditorCamera>();
}

void MMMEngine::Editor::SceneViewWindow::Render()
{
	if (!g_editor_window_sceneView)
		return;

	ImGuiWindowClass wc;
	// 핵심: 메인 뷰포트에 이 윈도우를 종속시킵니다.
	// 이렇게 하면 메인 창을 클릭해도 이 창이 '메인 창의 일부'로서 취급되어 우선순위를 가집니다.
	wc.ParentViewportId = ImGui::GetMainViewport()->ID;
	wc.ViewportFlagsOverrideSet = ImGuiViewportFlags_NoFocusOnAppearing; // 필요 시 설정

	ImGui::SetNextWindowClass(&wc);

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowMenuButtonPosition = ImGuiDir_None;

	ImGui::Begin(u8"\uf009 씬 뷰", &g_editor_window_sceneView);



	ImGui::End();
}
