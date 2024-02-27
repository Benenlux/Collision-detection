#include "Transform.h"

void Transform::Translate(float x, float y) {
	position = position + glm::vec2(x, y);
}