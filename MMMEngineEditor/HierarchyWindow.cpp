#include "HierarchyWindow.h"
#include "SceneManager.h"
#include "Transform.h"

#include <optional>

using namespace MMMEngine;
using namespace MMMEngine::Utility;

struct ReparentCmd
{
	MUID child;
	std::optional<MUID> parent; // nullopt => root(nullptr)
};

static std::vector<ReparentCmd> g_reparentQueue;

ObjPtr<GameObject> g_selectedGameObject = nullptr;

MUID GetMuid(const std::string& type)
{
	MUID result = MUID::Empty();

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(type.c_str()))
		{
			if (payload->IsDelivery() && payload->Data && payload->DataSize == sizeof(MUID))
			{
				std::memcpy(&result, payload->Data, sizeof(MUID));
			}
		}
		ImGui::EndDragDropTarget();
	}
	return result;
}

void GiveMuid(std::string type, MUID muid, std::string display)
{
	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload(type.c_str(), &muid, sizeof(MUID));
		ImGui::Text(display.c_str());
		ImGui::EndDragDropSource();
	}
}

void DrawHierarchyMember(ObjPtr<GameObject> obj)
{
	auto sceneRef = SceneManager::Get().GetCurrentScene();

	MUID muid = obj->GetMUID();
	ImGui::PushID(muid.ToString().c_str());

	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;

	if (obj->GetTransform()->GetChildCount() == 0) flags |= ImGuiTreeNodeFlags_Leaf;
	if (g_selectedGameObject == obj) flags |= ImGuiTreeNodeFlags_Selected;
	bool open = ImGui::TreeNodeEx(obj->GetName().c_str(), flags);
	if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) g_selectedGameObject = obj;

	GiveMuid("gameobject_muid", muid, obj->GetName().c_str());

	MUID dragged_muid = GetMuid("gameobject_muid");
	if (dragged_muid.IsValid())
	{
		auto dragged = SceneManager::Get().FindWithMUID(sceneRef, dragged_muid);
		if (dragged.IsValid()) g_reparentQueue.push_back({ dragged_muid, obj->GetMUID() });
	}

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

	ImGui::InvisibleButton("##", ImGui::GetContentRegionAvail());
	MUID muid = GetMuid("gameobject_muid");
	if (muid.IsValid())
	{
		g_reparentQueue.push_back({ muid, std::nullopt }); // root
	}

	ImGui::End();

	if (!g_reparentQueue.empty())
	{
		for (const auto& cmd : g_reparentQueue)
		{
			auto childObj = SceneManager::Get().FindWithMUID(sceneRef, cmd.child);
			if (!childObj.IsValid()) continue;

			if (!cmd.parent.has_value())
			{
				childObj->GetTransform()->SetParent(nullptr);
			}
			else
			{
				auto parentObj = SceneManager::Get().FindWithMUID(sceneRef, *cmd.parent);
				if (!parentObj.IsValid()) continue;

				childObj->GetTransform()->SetParent(parentObj->GetTransform());
			}
		}

		g_reparentQueue.clear();
	}
}
