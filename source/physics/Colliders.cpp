#include "Colliders.h"
#include <iostream>


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
	
	obj2->position.x -= direction.x * overlap * obj1->is_on_ground;
	obj2->position.y -= direction.y * overlap * obj1->is_on_ground;

	obj1->position += direction.x * overlap * obj2->is_on_ground;
	obj1->position.y += direction.y * overlap * obj2->is_on_ground;

	//Only apply the overlap to the object that is not on either end to prevent it from going through the side
	obj2->position.x -= direction.x * overlap * obj1->is_on_end;
	obj2->position.y -= direction.y * overlap * obj1->is_on_end;

	obj1->position.x += direction.x * overlap * obj2->is_on_ground;
	obj1->position.y += direction.y * overlap * obj2->is_on_ground;

	//If both objects are not on the ground or on the end, apply the overlap to both objects equally
	if ((!obj1->is_on_ground && !obj1->is_on_end) && (!obj2->is_on_ground && !obj1->is_on_end))   {
		obj1->position += direction * overlap * 0.5f;
		obj2->position -= direction * overlap * 0.5f;
	}
	
}


void Collider::CheckIfGrounded(Object* obj) {
	
	float distance = obj->position.y - obj->radius + 1.0f;
	
	if (distance < -0.0f) {
		obj->Translate(0.0f, -distance);
		obj->is_on_ground = true;
	}
	else if (distance == 0.0f) {
		obj->is_on_ground = true;
	}
	else {
		obj->is_on_ground = false;
	}
}

void Collider::CheckIfOnEnd(Object* obj, float ratio) {
	//Check if the object is on the end of the screen, 1.78 is the width of the screen due to the aspect ratio
	if (obj->position.x - obj->radius <= -ratio) {
		obj->is_on_end = true;	
		float distance = obj->position.x - obj->radius + ratio;
		obj->Translate(-distance, 0.0f);
		
	}
	else if (obj->position.x + obj->radius >= ratio) {
		obj->is_on_end = true;
		float distance = obj->position.x + obj->radius - ratio;
		obj->Translate(-distance, 0.0f);
	}
	else {
		obj->is_on_end = false;
	}
}