#pragma once
#include "Behaviour.h"
#include <SimpleMath.h>

namespace MMMEngine {
	class MMMENGINE_API EditorCamera : public Behaviour
	{
	public:
		EditorCamera();

		ObjPtr<Transform> m_CamTrans;
		DirectX::SimpleMath::Vector3 m_Rotation;	//  z는 Roll 해당되므로 사용안함.
		DirectX::SimpleMath::Vector3 m_PositionInitial = { 0,0,0 };
		DirectX::SimpleMath::Vector3 m_Position;

		DirectX::SimpleMath::Vector3 m_InputVector;
		float m_MoveSpeed = 20.0f;
		float m_RotationSpeed = 0.004f;	// rad per sec

		DirectX::SimpleMath::Vector3 GetForward();
		DirectX::SimpleMath::Vector3 GetRight();

		void Reset();
		void Update(float elapsedTime);
		void GetViewMatrix(DirectX::SimpleMath::Matrix& out);
		void AddInputVector(const DirectX::SimpleMath::Vector3& input);
		void SetSpeed(float speed) { m_MoveSpeed = speed; }
		void AddPitch(float value);
		void AddYaw(float value);
	};
}


