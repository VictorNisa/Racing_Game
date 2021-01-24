#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = Dark_Gray;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();

	//BASE
	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();
	chassis.color = Red;
	vec3 rot(0, -1, 0);
	//FRONT
	Cube front(info.front_size.x, info.front_size.y, info.front_size.z);
	front.SetRotation(20, vec3(-1, 0, 0));
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&front.transform);
	btVector3 offset_f(info.front_offset.x, info.front_offset.y, info.front_offset.z);
	offset_f = offset_f.rotate(q.getAxis(), q.getAngle());
	
	front.transform.M[12] += offset_f.getX();
	front.transform.M[13] += offset_f.getY();
	front.transform.M[14] += offset_f.getZ();
	front.color = Dark_Red;

	//BACK
	Cube back(info.back_size.x, info.back_size.y, info.back_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&back.transform);
	btVector3 offset_b(info.back_offset.x, info.back_offset.y, info.back_offset.z);
	offset_b = offset_b.rotate(q.getAxis(), q.getAngle());

	back.transform.M[12] += offset_b.getX();
	back.transform.M[13] += offset_b.getY();
	back.transform.M[14] += offset_b.getZ();
	back.color = Black;

	chassis.Render();
	front.Render();
	back.Render();
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}

vec3 PhysVehicle3D::ForwardVec3() const
{
	btVector3 h = vehicle->getForwardVector();
	vec3 ret;
	ret.Set(h.getX(), h.getY(), h.getZ());
	return ret;
}

void PhysVehicle3D::orient(float angle_r)
{

	float matrix[16];
	memset(matrix, 0.0f, sizeof(matrix));
	vec3 p = GetPos();
	matrix[12] = p.x;
	matrix[13] = p.y;
	matrix[14] = p.z;
	matrix[15] = 1;
	matrix[0] = cos(angle_r);
	matrix[2] = -sin(angle_r);
	matrix[5] = 1;
	matrix[8] = sin(angle_r);
	matrix[10] = cos(angle_r);
	SetTransform(matrix);

}