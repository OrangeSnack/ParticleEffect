#include "SceneManager.h"

DEFINE_SINGLETON(MMMEngine::SceneManager)


const MMMEngine::SceneRef MMMEngine::SceneManager::GetCurrentScene() const
{
	return { m_currentSceneID , false };
}

MMMEngine::Scene* MMMEngine::SceneManager::GetSceneRaw(const SceneRef& ref)
{
	if (m_scenes.size() <= ref.id && !ref.id_DDOL)
		return nullptr;

	if (ref.id_DDOL)
		return m_dontDestroyOnLoadScene.get();

	return m_scenes[ref.id].get();
}

void MMMEngine::SceneManager::ChangeScene(const std::string& name)
{
}

void MMMEngine::SceneManager::ChangeScene(const uint32_t& id)
{
}

void MMMEngine::SceneManager::LoadScene(const uint32_t& index)
{
}

void MMMEngine::SceneManager::LoadScene(const std::string& Name)
{
}


void MMMEngine::SceneManager::StartUp()
{
	// 고정된 경로로 json 바이너리를 읽고 씬파일경로들과 씬이름과 ID를 해쉬맵에 등록
	// 아래는 임시 코드
	m_scenes.push_back(std::make_unique<Scene>());
	m_currentSceneID = 0;
}

void MMMEngine::SceneManager::Update()
{
}

void MMMEngine::SceneManager::ShutDown()
{
}