
#pragma once
#include "glmath.h"
#include "Color.h"
#include "PhysBody3D.h"

enum PrimitiveTypes
{
	Primitive_Point,
	Primitive_Line,
	Primitive_Plane,
	Primitive_Cube,
	Primitive_Sphere,
	Primitive_Cylinder
};

class Primitive
{
public:

	Primitive();

	void Update();
	virtual void	Render() const;

	void			SetPos(float x, float y, float z);
	void			SetRotation(float angle, const vec3 &u);
	void			Scale(float x, float y, float z);
	PrimitiveTypes	GetType() const;

public:
	
	Color color;
	mat4x4 transform;
	bool axis,wire;
	bool sensor;
	PhysBody3D body;
protected:
	virtual void	InnerRender() const;
	PrimitiveTypes type;
};

// ============================================
class Cube : public Primitive
{
public :
	//Cube();
	Cube(const vec3& size = vec3(1.f, 1.f, 1.f), float mass = 1.f, bool sensor = false, senType stype = senType::OTHER);
	Cube(float sizeX, float sizeY, float sizeZ);
protected:
	void InnerRender() const;
public:
	vec3 size;
	vec3 GetSize() const;
};

// ============================================
class Sphere : public Primitive
{
public:
	//Sphere();
	//Sphere(float radius);
	Sphere(float radius = 1.f, float mass = 1.f, bool sensor = false, senType stype = senType::OTHER);
protected:
	void InnerRender() const;
public:
	float radius;
	float GetRadius() const;
};

// ============================================
class Cylinder : public Primitive
{
public:
	//Cylinder();
	//Cylinder(float radius, float height);
	Cylinder(float radius = 1.f, float height = 2.f, float mass = 1.f, bool sensor = false, senType stype = senType::OTHER);
protected:
	void InnerRender() const;
public:
	float radius;
	float height;
	float GetRadius() const;
	float GetHeight() const;
};

// ============================================
class Line : public Primitive
{
public:
	Line();
	Line(float x, float y, float z);
protected:
	void InnerRender() const;
public:
	vec3 origin;
	vec3 destination;
};

// ============================================
class Plane : public Primitive
{
public:
	Plane();
	Plane(float x, float y, float z, float d);
protected:
	void InnerRender() const;
public:
	vec3 normal;
	float constant;
};