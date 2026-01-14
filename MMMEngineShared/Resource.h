#pragma once
#include "Export.h"
#include "MUID.h"
#include "rttr/type"
#include "rttr/registration_friend.h"

namespace MMMEngine
{
	class MMMENGINE_API Resource
	{
	private:
		RTTR_ENABLE()
		RTTR_REGISTRATION_FRIEND
		friend class ResourceManager;
		friend class SceneManager;
		friend class Scene;

		Utility::MUID m_muid;
		void SetMUID(const Utility::MUID& muid);

		std::wstring m_filePath;
		void SetFilePath(const std::wstring& filePath);
	protected:
		virtual bool LoadFromFilePath(const std::wstring& filePath) = 0;
	public:
		virtual ~Resource() = default;

		const std::wstring& GetFilePath() const;
		const Utility::MUID& GetMUID() const;
	};
}