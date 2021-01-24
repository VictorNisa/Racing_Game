#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModuleAudio.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	winfx = App->audio->LoadFx("Music/youwin.wav");

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//SENSOR
	Cube sensor(20, 20, 20);
	sensor.SetPos(120, 25, 140);
	PhysBody3D* sensorbody = App->physics->AddBody(sensor, this, 0, true);

	//PLATEAU1
	Cube plat1(50, 10, 100);
	plat1.SetPos(100, 1, 15);
	App->physics->AddBody(plat1, 0.0f);
	plat1.color = Gold;

	//PLATEAU2
	Cube plat2(50, 20, 100);
	plat2.SetPos(150, 1, 15);
	App->physics->AddBody(plat2, 0.0f);
	plat2.color = Gold;

	//PLATEAU3
	Cube plat3(50, 30, 100);
	plat3.SetPos(150, 1, 115);
	App->physics->AddBody(plat3, 0.0f);
	plat3.color = Gold;

	//PLATEAU4
	Cube plat4(50, 40, 100);
	plat4.SetPos(100, 1, 115);
	App->physics->AddBody(plat4, 0.0f);
	plat4.color = Gold;

	//WINCUBE
	Cube winc(7, 7, 7);
	winc.SetPos(120, 25, 140);
	App->physics->AddBody(winc, 0.0f);
	winc.color = Blue;

	//RAMP1
	Cube ramp1(50, 15, 30);
	ramp1.SetPos(100, -5, -60);
	ramp1.SetRotation(30, vec3(-1, 0, 0));
	App->physics->AddBody(ramp1, 0.0f);

	//RAMP2
	Cube ramp2(5, 15, 10);
	ramp2.SetPos(115, 7, 50);
	ramp2.SetRotation(60, vec3(0, 0, -1));
	App->physics->AddBody(ramp2, 0.0f);

	//RAMP3
	Cube ramp3(10, 5, 20);
	ramp3.SetPos(160, 12, 60);
	ramp3.SetRotation(30, vec3(-1, 0, 0));
	App->physics->AddBody(ramp3, 0.0f);

	//RAMP4
	Cube ramp4(15, 5, 10);
	ramp4.SetPos(135, 15, 100);
	ramp4.SetRotation(30, vec3(0, 0, -1));
	App->physics->AddBody(ramp4, 0.0f);

	//Cube track1(200, 10, 10);
	//track1.SetPos(0, -0.5, 200);
	//App->physics->AddBody(track1, 0.0f);
	//track1.color = Green;

	Cube track2(1000, 1, 1000);
	track2.SetPos(0, -0.5, 0);
	App->physics->AddBody(track2, 0.0f);
	track2.color = Green;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	App->physics->CleanUp();
	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.color = Gold;
	p.axis = false;
	p.Render();


	//PLATEAU1
	Cube plat1(50, 10, 100);
	plat1.SetPos(100, 1, 15);
	plat1.color = Gold;
	plat1.Render();

	//PLATEAU2
	Cube plat2(50, 20, 100);
	plat2.SetPos(150, 1, 15);
	plat2.color = Gold;
	plat2.Render();

	//PLATEAU3
	Cube plat3(50, 30, 100);
	plat3.SetPos(150, 1, 115);
	plat3.color = Gold;
	plat3.Render();

	//PLATEAU4
	Cube plat4(50, 40, 100);
	plat4.SetPos(100, 1, 115);
	plat4.color = Gold;
	plat4.Render();

	//WINCUBE
	Cube winc(7, 7, 7);
	winc.SetPos(120, 25, 140);
	winc.color = Blue;
	winc.Render();

	//RAMP1
	Cube ramp1(50, 15, 30);
	ramp1.SetPos(100, -5, -60);
	ramp1.SetRotation(30, vec3(-1, 0, 0));
	ramp1.color = Gold;
	ramp1.Render();

	//RAMP2
	Cube ramp2(5, 15, 10);
	ramp2.SetPos(115, 7, 50);
	ramp2.SetRotation(60, vec3(0, 0, -1));
	ramp2.color = Gold;
	ramp2.Render();

	//RAMP3
	Cube ramp3(10, 5, 20);
	ramp3.SetPos(160, 12, 60);
	ramp3.SetRotation(30, vec3(-1, 0, 0));
	ramp3.color = Gold;
	ramp3.Render();

	// RAMP4
	Cube ramp4(15, 5, 10);
	ramp4.SetPos(135, 15, 100);
	ramp4.SetRotation(30, vec3(0, 0, -1));
	ramp4.color = Gold;
	ramp4.Render();

	//Cube track1(200, 10, 10);
	//track1.SetPos(0, -0.5, 200);
	//track1.color = Green;
	//track1.Render();

	Cube track2(1000, 1, 1000);
	track2.SetPos(0, -0.5, 0);
	track2.color = Green;
	track2.Render();

	return UPDATE_CONTINUE;
}

Cube* ModuleSceneIntro::CreateWall(vec3 dimensions, vec3 pos, vec3 rotation, float angle) {
	Cube* wall = new Cube(dimensions, 0.0f);
	wall->SetPos(pos.x, pos.y, pos.z);
	wall->SetRotation(angle, rotation);
	wall->color = Gold;
	prim.PushBack(wall);

	return wall;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1->is_sensor == true)
	{
		body1->is_sensor = false;
		App->audio->stopMusic();
		App->audio->PlayFx(winfx);
	}
}

