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

#include "Image.h"
#include "Label.h"
#include "Button.h"
#include "InputText.h"
#include "Window.h"

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
	if(App->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if(App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	debug_tex = App->tex->Load("maps/path2.png");

	// Create UI Elemets
	window = (Window*)App->gui->CreateUIElement(WINDOW,nullptr, 30, 30, 421, 453);
	window->SetRect({ 32,542,421,453 });
	window->listeners.add(this);

	banner = (Image*)App->gui->CreateUIElement(IMAGE,window, 50, 50, 318, 103);
	banner->SetRect({ 485, 829, 328, 103 });
	banner->interactable = false;

	button2 = (Button*)App->gui->CreateUIElement(BUTTON, window, 70, 150, 218, 57);
	button2->SetRects({ 648,173,218,57 }, { 6,117,218,57 }, { 417,173,218,57 });
	button2->listeners.add(this);

	text2 = (Label*)App->gui->CreateUIElement(LABEL,button2, 50, 6, 90, 20);
	text2->SetText("_______________");
	text2->listeners.add(this);

	button = (Button*)App->gui->CreateUIElement(BUTTON, window,10, 30, 218, 57);
	button->SetRects({ 648,173,218,57 }, { 6,117,218,57 }, { 417,173,218,57 });
	button->listeners.add(this);

	/*text = (Label*)App->gui->CreateUIElement(LABEL,button, 5, 2, 90, 20);
	text->SetText("Helloudaa :)");
	text->listeners.add(this);
	text->is_static = true;*/

	input_text = (InputText*)App->gui->CreateUIElement(INPUT_TEXT,nullptr, 70, 50, 50, 20);
	input_text->SetDefaultText("Hello World");
	input_text->listeners.add(this);
	input_text->is_static = true;


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

	//// Debug pathfinding ------------------------------
	////int x, y;
	//App->input->GetMousePosition(x, y);
	//iPoint p = App->render->ScreenToWorld(x, y);
	//p = App->map->WorldToMap(p.x, p.y);
	//p = App->map->MapToWorld(p.x, p.y);

	//App->render->Blit(debug_tex, p.x, p.y);

	//const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	//for(uint i = 0; i < path->Count(); ++i)
	//{
	//	iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
	//	App->render->Blit(debug_tex, pos.x, pos.y);
	//}

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


void j1Scene::UIEvent(UI* element, UI_Events react)
{
	

	switch (react)
	{
	case UI_Events::MOUSE_ENTER:
		if (element == text) {
			text->SetText("Mouse Hovering");
		}
		if (element == text2) {
			text2->SetText("Mouse Hovering 2");
		}
		
		break;
	case UI_Events::MOUSE_LEAVE:
		if (element == text) {
			text->SetText("Mouse Leaving");
		}
		
		break;
	case UI_Events::RIGHT_CLICK:
		if (element == text) {
			text->SetText("Right Click");
		}
		
		break;
	case UI_Events::LEFT_CLICK:
		if (element == text) {
			text->SetText("Left Click");
		}
		
		break;
	case UI_Events::LEFT_CLICK_UP:
	
		break;
	case UI_Events::RIGHT_CLICK_UP:
		
		break;
	case UI_Events::DRAG:
		int x_motion, y_motion;
		App->input->GetMouseMotion(x_motion, y_motion);
		if (x_motion != 0 || y_motion != 0)
			element->SetPos(element->GetLocalPosition().x + x_motion, element->GetLocalPosition().y + y_motion);
		break;
	case UI_Events::TAB:
		break;
	default:
		break;
	}
}