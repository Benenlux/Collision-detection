#include "Colliders.h"



void Collider::CheckCollision(Object* obj1, Object* obj2){
	float distance = glm::distance(obj1->position, obj2->position);
	float sumRadius = obj1->radius + obj2->radius;
	
	if (distance < sumRadius)
	{
		ResolveCollision(obj1, obj2, distance, sumRadius);
	}
}

void Collider::ResolveCollision(Object* obj1, Object* obj2, float distance, float sumRadius){
	float overlap = sumRadius - distance;
	glm::vec2 direction = glm::normalize(obj1->position - obj2->position);
	
	if (obj1->isOnGround) {
		obj2->position -= direction * overlap;
	}
	else if (obj2->isOnGround) {
		obj1->position += direction * overlap;
	}
	else {
		obj1->position += direction * overlap * 0.5f;
		obj2->position -= direction * overlap * 0.5f;
	}
	
}


void Collider::CheckIfGrounded(Object* obj) {
	if (obj->position.y - obj->radius == -1.0f) {
		obj->isOnGround = true;
	}
	else if (obj->position.y - obj->radius < -1.0f) {
		float distance = (obj->position.y - obj->radius) + 1.0f;
		obj->position.y -= distance;
	}
	else {
		obj->isOnGround = false;
	}
}