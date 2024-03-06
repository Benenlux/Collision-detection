#pragma once
#include <glm/glm.hpp>
#include "../graphics/Object.h"

class Collider{
protected:

	void CheckCollision(Object* obj1, Object* obj2);
	void CheckIfGrounded(Object* obj);
	void CheckIfOnEnd(Object* obj);

private:
	void ResolveCollision(Object* obj1, Object* obj2, float distance, float sumRadius);
};

