#pragma once
#include "Singleton.hpp"
#include "EditorCamera.h"

#include <memory>

#define NOMINMAX
#include <d3d11.h>
#include <wrl/client.h>

#pragma comment (lib, "d3d11.lib")

namespace MMMEngine::Editor
{
	class SceneViewWindow : public Utility::Singleton<SceneViewWindow>
	{
	public:
		void Initialize();
		void Render();
	private:
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pSceneTexture;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pSceneRTV;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSceneSRV;
		std::unique_ptr<EditorCamera> m_pCam;
	};
}