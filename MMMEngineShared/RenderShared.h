#pragma once
#include <SimpleMath.h>

#define BONE_MAXSIZE 256

enum RenderType {
	SHADOWMAP = 0,
	PREDEPTH = 1,
	SKYBOX = 2,
	TRANSCULANT = 3,
	GEOMETRYY = 4,
	ADDTIVE = 5,
	PARTICLE = 6,
	POSTPROCESS = 7,
	UI = 8,
};

struct Render_CamBuffer {
	DirectX::SimpleMath::Matrix mView = DirectX::SimpleMath::Matrix::Identity;			// 카메라좌표계 변환행렬
	DirectX::SimpleMath::Matrix mProjection = DirectX::SimpleMath::Matrix::Identity;	// ndc좌표계 변환행렬
	DirectX::SimpleMath::Vector4 camPos;
};

struct Render_TransformBuffer
{
	DirectX::SimpleMath::Matrix mWorld;
	DirectX::SimpleMath::Matrix mNormalMatrix;
};

struct Render_LightBuffer {
	DirectX::SimpleMath::Vector4 mLightDir;
	DirectX::SimpleMath::Vector4 mLightColor;
};

struct Render_MaterialBuffer
{
	DirectX::SimpleMath::Vector4 BaseColor;	// 메테리얼 정보

	float Metalic = 0.0f;
	float mRoughness = 0.0f;
	float mAoStrength = 1.0f;
	float mEmissive = 1.0f;
};

struct Render_ShadowBuffer
{
	DirectX::SimpleMath::Matrix ShadowView;
	DirectX::SimpleMath::Matrix ShadowProjection;
};