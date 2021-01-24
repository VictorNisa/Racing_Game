#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Timer.h"

struct PhysVehicle3D;
class vec3;

#define MAX_ACCELERATION 1000.0f			// 1000 default
#define TURN_DEGREES 15.0f * DEGTORAD		// 15	default
#define BRAKE_POWER 1000.0f					// 1000 default



enum VEHICLESTATE
{
	START,
	STOP,
	DEBUG,
	RUN
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	bool cameraLock;
	VEHICLESTATE state;
	Timer chronos;
	bool chroned;

	// Audio files go here

};