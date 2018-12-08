#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

#include "Label.h"
#include "Image.h"
#include "Button.h"
#include "Window.h"
#include "InputText.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	bool ret = true;
	
	ClearUIElements();

	for (p2List_item<UI*>* item = UIelements.start; item != nullptr; item = item->next) {
		if (item->data->active) {
			ret = item->data->Update();
			draw_queue.Push(item->data, item->data->GetPriority());
		}
	}

	for (int i = 0; i < draw_queue.Count(); i++) {
		UI* tmp = *draw_queue.Peek(i);
		if (tmp->interactable) {
			react_stack.push(tmp);
		}
	}

	return ret;
	
}
bool j1Gui::Update(float dt)
{
	iPoint mouse;
	App->input->GetMousePosition(mouse.x, mouse.y);
	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN || App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {
		if (on_UIElem != nullptr) {
			if (!(mouse.x > on_UIElem->GetPosition().x && mouse.x<(on_UIElem->GetPosition().x + on_UIElem->position.w) && mouse.y > on_UIElem->GetPosition().y && mouse.y < (on_UIElem->GetPosition().y + on_UIElem->position.h))) {
				on_UIElem = nullptr;
			}
		}
	}

	UI* item;
	while (react_stack.pop(item)) {
		UI_Events event = NONE;

		if (mouse.x > item->GetPosition().x && mouse.x<(item->GetPosition().x + item->position.w) && mouse.y > item->GetPosition().y && mouse.y < (item->GetPosition().y + item->position.h)) {
			
			if (item->mouse_off) {
				item->mouse_on = true;
				item->mouse_off = false;
				event = MOUSE_ENTER;
			}
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {
				event = LEFT_CLICK;
				on_UIElem = item;
			}
			if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN) {
				event = RIGHT_CLICK;
				on_UIElem = item;
			}
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP) {

				event = LEFT_CLICK_UP;
			}
			if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP) {
				event = RIGHT_CLICK_UP;
			}
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT && (mouse.x != last_mouse.x || mouse.y != last_mouse.y)) {
				event = DRAG;
			}
		}
		else {
			if (item->mouse_on) {
				item->mouse_on = false;
				item->mouse_off = true;
				event = MOUSE_LEAVE;
			}
		}
		if (event != NONE) {
			for (p2List_item<j1Module*>* module = item->listeners.start; module; module = module->next) {
				module->data->UIEvent(item, event);
			}
			break;
		}
	}
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT && (mouse.x != last_mouse.x || mouse.y != last_mouse.y)) {
		if (on_UIElem != nullptr && !on_UIElem->GetParent() && on_UIElem->can_move) {
			int x_motion = mouse.x - last_mouse.x;
			int y_motion = mouse.y - last_mouse.y;
			on_UIElem->SetPos(on_UIElem->GetLocalPosition().x + x_motion, on_UIElem->GetLocalPosition().y + y_motion);
		}
	}

	last_mouse = mouse;
	react_stack.clear();

	return true;
}
// Called after all Updates
bool j1Gui::PostUpdate()
{
	UI* tmp;
	while (draw_queue.Pop(tmp))
		tmp->Draw();
	
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");
	for (p2List_item<UI*>* item = UIelements.start; item != nullptr; item = item->next) {
		RELEASE(item->data);
	}
	return true;
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

UI* j1Gui::CreateUIElement(UI_type type, UI* parent, int pos_x, int pos_y, int w, int h)
{
	UI* element = nullptr;

	switch (type)
	{
	case CHECKBOX:
		break;
	case INPUT_TEXT:
		element = new InputText(parent,pos_x, pos_y, w, h);
		break;
	case OUTPUT_FIELD:
		break;
	case BUTTON:
		element = new Button(parent,pos_x, pos_y, w, h);
		break;
	case LABEL:
		element = new Label(parent,pos_x, pos_y, w, h);
		break;
	case IMAGE:
		element = new Image(parent,pos_x, pos_y);
		break;
	case WINDOW:
		element = new Window(parent,pos_x, pos_y, w, h);
	case UNKNOW:
		break;
	default:
		break;
	}

	if (element != nullptr) {
		element->listeners.add(this);
		UIelements.add(element);
	}

	return element;
}


void j1Gui::DeleteUIElement(UI* element)
{
	element->to_delete = true;
}
void j1Gui::ClearUIElements()
{
	for (p2List_item<UI*>* item = UIelements.start; item != nullptr; item = item->next) {
		if (item->data->to_delete == true) {
			RELEASE(item->data);
			UIelements.del(item);
			if (item->data == on_UIElem)
				on_UIElem = nullptr;
		}
	}
}

// class Gui ---------------------------------------------------

void j1Gui::UIEvent(UI* element, UI_Events react)
{


	switch (react)
	{
	case UI_Events::MOUSE_ENTER:
		if (element->GetType() == BUTTON) {
			Button* button = (Button*)element;
			button->OnHover();
		}
		break;
	case UI_Events::MOUSE_LEAVE:
		if (element->GetType() == BUTTON) {
			Button* button = (Button*)element;
			button->Standard();
		}
		break;
	case UI_Events::RIGHT_CLICK:
		if (element->GetType() == BUTTON) {
			Button* button = (Button*)element;
			button->OnClick();
		}
		break;
	case UI_Events::LEFT_CLICK:
		if (element->GetType() == BUTTON) {
			Button* button = (Button*)element;
			button->OnClick();
		}
		break;
	case UI_Events::LEFT_CLICK_UP:
		if (element->GetType() == BUTTON) {
			Button* button = (Button*)element;
			button->OnHover();
		}
		break;
	case UI_Events::RIGHT_CLICK_UP:
		if (element->GetType() == BUTTON) {
			Button* button = (Button*)element;
			button->OnHover();
		}
		break;
	case UI_Events::DRAG:
		
		break;
	case UI_Events::TAB:

		break;
	default:

		break;
	}
}