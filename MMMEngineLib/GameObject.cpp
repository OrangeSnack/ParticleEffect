#include "GameObject.h"
#include "rttr/registration"
#include "rttr/detail/policies/ctor_policies.h"
#include "Component.h"
#include "Transform.h"
#include <cmath>

RTTR_REGISTRATION
{
	using namespace rttr;
	using namespace MMMEngine;

    registration::class_<GameObject>("GameObject");

	registration::class_<ObjectPtr<GameObject>>("ObjectPtr<GameObject>")
		.constructor(
   			[](const std::string& name) {
   				return Object::CreatePtr<GameObject>(name);
   			})
   	    .constructor<>(
   		    []() {
   			    return Object::CreatePtr<GameObject>();
   		    });
}

void MMMEngine::GameObject::RegisterComponent(ObjectPtr<Component> comp)
{
    m_components.push_back(comp);
}

void MMMEngine::GameObject::UnRegisterComponent(ObjectPtr<Component> comp)
{
    auto it = std::find(m_components.begin(), m_components.end(), comp);
    if (it != m_components.end()) {
        *it = std::move(m_components.back()); // ¸¶Áö¸· ¿ø¼Ò¸¦ µ¤¾î¾¸
        m_components.pop_back();
    }
}

MMMEngine::GameObject::GameObject(std::string name)
{
	SetName(name);
}
