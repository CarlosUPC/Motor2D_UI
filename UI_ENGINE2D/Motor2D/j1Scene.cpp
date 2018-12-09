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
#include "Image.h"
#include "Label.h"
#include "Button.h"
#include "InputText.h"
#include "j1Scene.h"
#include "Window.h"
#include "ScrollBar.h"
#include "CheckBox.h"

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
	// UIElements Creation

	window = (Window*)App->gui->CreateUIElement(WINDOW, 30, 30,421, 453, nullptr);
	window->SetRect({ 32,542,421,453 });
	window->AddListener(this);

	banner = (Image*)App->gui->CreateUIElement(IMAGE, 50, 50,50,50,window);
	banner->SetRect({ 485, 829, 328, 103 });
	banner->interactable = false;
	banner->active = false;

	vertical = (ScrollBar*)App->gui->CreateUIElement(SCROLLBAR, 40, 50, 15, 154, window);
	vertical->can_move = false;
	vertical->SetBar(974, 788, 8, 154);
	vertical->SetScroll(843, 330, 15, 10);
	vertical->target = banner;

	horizontal = (ScrollBar*)App->gui->CreateUIElement(SCROLLBAR, 60, 80,154, 15, window);
	horizontal->can_move = false;
	horizontal->SetBar(974, 788, 154, 8);
	horizontal->SetScroll(843, 330, 10, 15);
	horizontal->target = banner;

	button2 = (Button*)App->gui->CreateUIElement(BUTTON, 70, 150, 0,0,window);
	button2->SetRects({ 648,173,218,57 }, { 6,117,218,57 }, { 417,173,218,57 });
	button2->AddListener(this);

	text2 = (Label*)App->gui->CreateUIElement(LABEL, 50, 6,90, 20, button2);
	text2->SetText("_______________");
	text2->AddListener(this);

	button = (Button*)App->gui->CreateUIElement(BUTTON, 10, 250, 0,0,window);
	button->SetRects({ 648,173,218,57 }, { 6,117,218,57 }, { 417,173,218,57 });
	button->AddListener(this);

	text = (Label*)App->gui->CreateUIElement(LABEL, 5, 2, 90, 20, button);
	text->SetText("HOLA RIC :)");
	text->AddListener(this);
	text->can_move = false;

	input_text = (InputText*)App->gui->CreateUIElement(INPUT_TEXT, 10, 20, 70, 20,window);
	input_text->SetDefaultText("Hello World");
	input_text->AddListener(this);
	input_text->can_move = false;

	option1 = (CheckBox*)App->gui->CreateUIElement(CHECKBOX, 400, 10);
	option1->SetRects({ 977,432,20,21 }, { 858,89,20,21 }, { 391,168,12,11 });
	option1->is_option = true;
	option1->can_move = false;

	option2 = (CheckBox*)App->gui->CreateUIElement(CHECKBOX, 400, 33);
	option2->SetRects({ 977,432,20,21 }, { 858,89,20,21 }, { 391,168,12,11 });
	option2->is_option = true;
	option2->can_move = false;
	option2->AddOptions(option1);

	multi_option1 = (CheckBox*)App->gui->CreateUIElement(CHECKBOX, 450, 10);
	multi_option1->SetRects({ 992,847,20,20 }, { 992,814,20,20 }, { 391,168,12,11 });
	multi_option1->can_move = false;

	multi_option2 = (CheckBox*)App->gui->CreateUIElement(CHECKBOX, 450, 33);
	multi_option2->SetRects({ 992,847,20,20 }, { 992,814,20,20 }, { 391,168,12,11 });
	multi_option2->can_move = false;
	multi_option2->AddOptions(multi_option1);

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	

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

void j1Scene::UIReaction(UI * element, UI_Event react)
{
	

	switch (react)
	{
	case MOUSE_ENTER:
		if (element == text) {
			text->SetText("Mouse Over");
		}
		if (element == text2) {
			text2->SetText("SIMON NOOB");
		}
		break;
	case MOUSE_LEAVE:
		if (element == text) {
			text->SetText("Hola Ric :)");
		}
		break;
	case RIGHT_CLICK:
		if (element == text) {
			text->SetText("Right Click");
		}
		break;
	case LEFT_CLICK:
		if (element == text) {
			text->SetText("Left Click");
		}
		if (element == button2) {
			banner->active = true;
		}
		break;
	case LEFT_CLICK_UP:
		break;
	case RIGHT_CLICK_UP:
		break;
	case TAB:
		break;
	case RIGHT_ARROW:
		break;
	case LEFT_ARROW:
		break;
	case UP_ARROW:
		break;
	case DOWN_ARROW:
		break;
	default:
		break;
	}
}
