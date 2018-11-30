#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Scene.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	/*if(App->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if(App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	debug_tex = App->tex->Load("maps/path2.png");*/
	
	App->font->yellow_font = App->font->Load("fonts/open_sans/OpenSans-LightItalic.ttf", 12);

	// TODO 3: Create the banner (rect {485, 829, 328, 103}) and the text "Hello World"

	//banner = (Image*)App->gui->CreateImage({ 0,0 }, IMAGE, { 485, 829, 328, 103 });
	//text = (Text*)App->gui->CreateText({ 0,-25 }, TEXT, "Hola mundo!", nullptr);

	text = (Text*)App->gui->CreateText({ 0,-25 }, TEXT, "Hola mundo!", App->font->yellow_font);
	back = (Image*)App->gui->CreateImage({ 0,0 }, BACKGROUND_IMAGE,{ 0,0,1032,774 });

	manage_account_button = (Image*)App->gui->CreateImage({ 16,575 }, IMAGE, { 1049, 147, 138, 40 });
	community_site_button = (Image*)App->gui->CreateImage({ 16,612 }, IMAGE, { 1049, 147, 138, 40 });
	remember_account_name_checkbox = (Image*)App->gui->CreateImage({ 16,656 }, IMAGE, { 1217, 151, 16, 16 });
	esrbNotice = (Image*)App->gui->CreateImage({ 20,683 }, IMAGE, { 1052, 384, 128, 40 });
	account_name_input_box = (Image*)App->gui->CreateImage({ 445,388 }, IMAGE, { 1057, 220, 128, 20 });
	account_pasword_input_box = (Image*)App->gui->CreateImage({ 445,464 }, IMAGE, { 1057, 220, 128, 20 });
	
	blizzard_logo = (Image*)App->gui->CreateImage({ 440,680 }, IMAGE, { 1055, 279, 128, 78 });
	cinematics_button = (Image*)App->gui->CreateImage({ 876,515 }, IMAGE, { 1049, 147, 138, 40 });
	credits_button = (Image*)App->gui->CreateImage({ 876,552 }, IMAGE, { 1049, 147, 138, 40 });
	terms_of_use_button = (Image*)App->gui->CreateImage({ 876,587 }, IMAGE, { 1049, 147, 138, 40 });
	quit_button = (Image*)App->gui->CreateImage({ 876,706 }, IMAGE, { 1049, 147, 138, 40 });
	wow_logo = (Image*)App->gui->CreateImage({ 13,19 }, IMAGE, { 1039, 22, 232, 96 });

	login_button = (Button*)App->gui->CreateButton({ 440,525 }, BUTTON, { 1049, 147, 138, 40 });
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	// debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if(origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	// Gui ---
	//banner->Update();
	back->Update();
	text->Update();

	manage_account_button->Update();
	community_site_button->Update();
	remember_account_name_checkbox->Update();
	esrbNotice->Update();
	account_name_input_box->Update();
	account_pasword_input_box->Update();
	
	blizzard_logo->Update();
	cinematics_button->Update();
	credits_button->Update();
	terms_of_use_button->Update();
	quit_button->Update();
	wow_logo->Update();

	login_button->Update();
	// -------
	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= floor(200.0f * dt);

	App->map->Draw();

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),
					map_coordinates.x, map_coordinates.y);

	//App->win->SetTitle(title.GetString());

	// Debug pathfinding ------------------------------
	//int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	App->render->Blit(debug_tex, p.x, p.y);

	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for(uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		App->render->Blit(debug_tex, pos.x, pos.y);
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
