#include <Engine3D/Scene2D/Entity.h>


namespace Engine3D{

	Entity::Entity(entt::entity handle, Scene* scene) : _entityHandler(handle), _scene(scene) {}
};
