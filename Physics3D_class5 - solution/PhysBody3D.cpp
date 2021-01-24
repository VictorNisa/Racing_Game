#include "PhysBody3D.h"
#include "glmath.h"
#include "Globals.h"

#include "Primitive.h"
#include "glmath.h"
#include "Bullet/include/btBulletDynamicsCommon.h"
#include "Application.h"

// =================================================

PhysBody3D::PhysBody3D()
	: body(nullptr)
	, colShape(nullptr)
	, motionState(nullptr)
	, Pparent(nullptr)
	, collision_listeners()
{

}

PhysBody3D::PhysBody3D(btRigidBody* body) : body(body)
{
	body->setUserPointer(this);
}

// ---------------------------------------------------------
PhysBody3D::~PhysBody3D()
{
	if (HasBody() == true)
	{
		delete body;
		delete colShape;
		delete motionState;
	}
}

senType	PhysBody3D::GetsType() const
{
	return stype;
}


void PhysBody3D::SetBody(Sphere* primitive, float mass, bool sensor, senType stype)
{
	SetBody(new btSphereShape(primitive->GetRadius()), primitive, mass, sensor, stype);
}

void PhysBody3D::SetBody(Cube* primitive, float mass, bool sensor, senType stype)
{
	btVector3 tmp = { primitive->GetSize().x ,primitive->GetSize().y ,primitive->GetSize().z };

	SetBody(new btBoxShape(tmp / 2), primitive, mass, sensor, stype);
}

void PhysBody3D::SetBody(Cylinder* primitive, float mass, bool sensor, senType type)
{
	btVector3 tmp = { primitive->GetHeight() / 2, primitive->GetRadius(), 0.0f };

	SetBody(new btCylinderShape(tmp), primitive, mass, sensor, stype);
}

bool PhysBody3D::HasBody() const
{
	return body != nullptr;
}

btRigidBody * PhysBody3D::GetBody() const
{
	return body;
}

// ---------------------------------------------------------

// ---------------------------------------------------------
void PhysBody3D::GetTransform(float* matrix) const
{
	if (HasBody() == false)
		return;
	if(body != NULL && matrix != NULL)
	{
		body->getWorldTransform().getOpenGLMatrix(matrix);
	}
}

// ---------------------------------------------------------
void PhysBody3D::SetTransform(const float* matrix) const
{
	if(body != NULL && matrix != NULL)
	{
		btTransform t;
		t.setFromOpenGLMatrix(matrix);
		body->setWorldTransform(t);
		body->activate();
	}
}

// ---------------------------------------------------------
void PhysBody3D::SetPos(float x, float y, float z)
{
	btTransform t = body->getWorldTransform();
	t.setOrigin(btVector3(x, y, z));
	body->setWorldTransform(t);
	body->activate();
}

void PhysBody3D::Push(float x, float y, float z)
{
	body->applyCentralImpulse(btVector3(x, y, z));
}

const vec3 PhysBody3D::GetPos() const
{
	btTransform t = body->getWorldTransform();
	btVector3 v = t.getOrigin();
	vec3 ret; ret.Set(v.getX(), v.getY(), v.getZ());
	return ret;
}

void PhysBody3D::SetBody(btCollisionShape * shape, Primitive* parent, float mass, bool sensor, senType stype)
{
	assert(HasBody() == false);

	Pparent = parent;

	colShape = shape;

	btTransform startTransform;
	startTransform.setFromOpenGLMatrix(&parent->transform);

	btVector3 localInertia(0, 0, 0);
	if (mass != 0.f)
		colShape->calculateLocalInertia(mass, localInertia);

	motionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, colShape, localInertia);

	body = new btRigidBody(rbInfo);

	body->setUserPointer(this);

	if (sensor)
	{
		body->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	}

	if (sensor)
	{
		//this->collision_listeners.add(App->player);
	}

	this->stype = stype;

	//App->physics->AddBodyToWorld(body);
}
