#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include "ExportSingleton.hpp"
#include "Scene.h"
#include "SceneRef.h"

namespace MMMEngine
{
	class MMMENGINE_API SceneManager : public Utility::ExportSingleton<SceneManager>
	{
	private:
		std::unordered_map<std::string, uint32_t> m_sceneNameToID;			// <Name , ID>
		std::vector<std::unique_ptr<Scene>> m_scenes;

		uint32_t m_currentSceneID;
		uint32_t m_nextSceneID;

		std::unique_ptr<Scene> m_dontDestroyOnLoadScene;
	public:
		const SceneRef GetCurrentScene() const;

		Scene* GetSceneRaw(const SceneRef& ref);

		static void ChangeScene(const std::string& name);
		static void ChangeScene(const uint32_t& id);

		void LoadScene(const uint32_t& index);
		void LoadScene(const std::string& Name);

		void StartUp();
		void ShutDown();
		void Update();
	};
}