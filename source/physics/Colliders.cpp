#include "Colliders.h"



bool Collider::CheckCollisionCircletoCircle(Object* obj1, Object* obj2){
	float distance = glm::distance(obj1->transform.position, obj2->transform.position);
	float sumRadius = obj1->radius + obj2->radius;
	float correctDisance = glm::sqrt( glm::pow(obj1->transform.position.x - obj2->transform.position.x, 2) + glm::pow(obj1->transform.position.y - obj2->transform.position.y, 2));
	
	
	if (distance < sumRadius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Collider::CheckCollisionSquareToCircle(Object* obj1, Object* obj2){
	return false;
}

bool Collider::CheckCollisionSquaretoSquare(Object* obj1, Object* obj2){
	return false;
}

void Collider::ResolveCollisionCircleToCircle(Object* obj1, Object* obj2){
	float distance = glm::distance(obj1->transform.position, obj2->transform.position);
	float sumRadius = obj1->radius + obj2->radius;
	float overlap = sumRadius - distance;
	glm::vec2 direction = glm::normalize(obj1->transform.position - obj2->transform.position);
	
	if (obj1->isOnGround) {
		std::cout << (direction.x * overlap) << " " << direction.y * overlap << std::endl;
		obj2->transform.position -= direction * overlap;
	}
	else if (obj2->isOnGround) {
		obj1->transform.position += direction * overlap;
	}
	else {
		obj1->transform.position += direction * overlap * 0.5f;
		obj2->transform.position -= direction * overlap * 0.5f;
	}
	
}

void Collider::ResolveCollisionSquareToCircle(Object* obj1, Object* obj2){

}

void Collider::ResolveCollisionSquaretoSquare(Object* obj1, Object* obj2){

}

void Collider::CheckIfGrounded(Object* obj) {
	if (obj->shape == Shape::CIRCLE) {
		if (obj->transform.position.y - obj->radius < -1.0f) {
			obj->isOnGround = true;
		}
		else {
			obj->isOnGround = false;
		}
	}
	else if (obj->shape == Shape::SQUARE) {
		if (obj->transform.position.y - obj->height < -1.0f) {
			obj->isOnGround = true;
			obj->transform.position.y = -1.0;
		}
		else {
			obj->isOnGround = false;
		}
	}
}