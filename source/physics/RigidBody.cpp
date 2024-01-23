#include "RigidBody.h"

void RigidBody::SetGravity(bool gravityEnabled) {
	properties.gravityEnabled = gravityEnabled;
}

void Rigidbody::Update()