#include "HierarchyWindow.h"
#include "SceneManager.h"
#include "Transform.h"

using namespace MMMEngine;
using namespace MMMEngine::Utility;

ObjPtr<GameObject> selectedGameObject = nullptr;

void DrawHierarchyMember(ObjPtr<GameObject> obj)
{
	MUID muid = obj->GetMUID();
	ImGui::PushID(muid.ToString().c_str());

	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;

	if (obj->GetTransform()->GetChildCount() == 0) flags |= ImGuiTreeNodeFlags_Leaf;
	if (selectedGameObject == obj) flags |= ImGuiTreeNodeFlags_Selected;
	bool open = ImGui::TreeNodeEx(obj->GetName().c_str(), flags);
	if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) selectedGameObject = obj;

	if (open)
	{
		auto pt = obj->GetTransform();
		auto child_size = pt->GetChildCount();

		for(size_t i = 0; i < child_size; ++i)
		{
			DrawHierarchyMember(pt->GetChild(i)->GetGameObject());
		}
		ImGui::TreePop();
	}

	ImGui::PopID();
}

void MMMEngine::Editor::HierarchyWindow::Render()
{
  	auto sceneRef = SceneManager::Get().GetCurrentScene();
	auto sceneRaw = SceneManager::Get().GetSceneRaw(sceneRef);

	ImGui::Begin(u8"하이어라키");

	if (ImGui::Button(u8"오브젝트 생성"))
	{
		Object::NewObject<GameObject>();
	}

	const auto& gameObjects = SceneManager::Get().GetAllGameObjectInCurrentScene();

	for (auto& go : gameObjects)
	{
		if (go->GetTransform()->GetParent() == nullptr) DrawHierarchyMember(go);
	}

	ImGui::End();
}
