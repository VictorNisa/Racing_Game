#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"
#include "glmath.h"

class btRigidBody;
class btCollisionShape;
struct btDefaultMotionState;
class Module;
class vec3;
class Module;
class Sphere;
class Cube;
class Cylinder;
class Plane;
class Primitive;

enum class senType 
{
	VEHICLE,
	SPECIAL,
	OTHER

};
// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D();
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	senType stype;
	btRigidBody* body;

	void SetBody(Sphere* primitive, float mass, bool sensor = false, senType type = senType::OTHER);
	void SetBody(Cube* primitive, float mass, bool sensor = false, senType type = senType::OTHER);
	void SetBody(Cylinder* primitive, float mass, bool sensor = false, senType type = senType::OTHER);
	bool HasBody() const;
	btRigidBody* GetBody() const;
	senType GetsType() const;

	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	const vec3 GetPos() const;
	void Push(float x, float y, float z);
private:


	void SetBody(btCollisionShape* shape, Primitive* parent, float mass, bool sensor = false, senType stype = senType::OTHER);


	btCollisionShape* colShape;
	btDefaultMotionState* motionState;
public:

	Primitive* Pparent;
	p2List<Module*> collision_listeners;
	bool			is_sensor;
	float			rotation;
};

#endif // __PhysBody3D_H__