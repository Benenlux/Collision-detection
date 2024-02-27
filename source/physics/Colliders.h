#pragma once
#include <glm/glm.hpp>
#include "../graphics/Object.h"

class Collider{
protected:
	bool CheckCollisionCircletoCircle(Object* obj1, Object* obj2);
	bool CheckCollisionSquareToCircle(Object* obj1, Object* obj2);
	bool CheckCollisionSquaretoSquare(Object* obj1, Object* obj2);
	
	void ResolveCollisionCircleToCircle(Object* obj1, Object* obj2);
	void ResolveCollisionSquareToCircle(Object* obj1, Object* obj2);
	void ResolveCollisionSquaretoSquare(Object* obj1, Object* obj2);
	void CheckIfGrounded(Object* obj);
};

