#pragma once
#ifndef NOMINMAX
	#define NOMINMAX
#endif

#include "Export.h"
#include <d3d11_4.h>
#include <Material.h>
#include "Object.h"

namespace MMMEngine {
	class MeshRenderer;
	class MMMENGINE_API RendererBase
	{
	protected:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_pVertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer;
		UINT m_IndicesSize;
		std::shared_ptr<Material> m_pMaterial;

		Microsoft::WRL::ComPtr<ID3D11DeviceContext4> m_pDeviceContext;	// 디바이스 컨텍스트 참조
		ObjPtr<MeshRenderer> m_pMeshRenderer;		// 주관 메시렌더러
		
	public:
		RendererBase();

		void SetRenderData(
			Microsoft::WRL::ComPtr<ID3D11Buffer>& _vertex,
			Microsoft::WRL::ComPtr<ID3D11Buffer>& _index,
			UINT _indicesSize,
			std::shared_ptr<Material>& _material
		);

		virtual void Render() = 0;
	};
}


