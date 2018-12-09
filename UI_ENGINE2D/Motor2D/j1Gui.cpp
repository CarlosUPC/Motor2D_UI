#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "UI.h"
#include "Label.h"
#include "Image.h"
#include "Button.h"
#include "Window.h"
#include "InputText.h"
#include "ScrollBar.h"
#include "CheckBox.h"


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

	elem_changed = false;

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
		if (on_UIElem != nullptr){
			if (!(mouse.x > on_UIElem->GetPosition().x && mouse.x<(on_UIElem->GetPosition().x + on_UIElem->position.w) && mouse.y > on_UIElem->GetPosition().y && mouse.y < (on_UIElem->GetPosition().y + on_UIElem->position.h))) {
				on_UIElem = nullptr;
			}
		}
	}

	UI* item;
	while (react_stack.pop(item)) {
		UI_Event react = NONE;
		if (mouse.x > item->GetPosition().x && mouse.x<(item->GetPosition().x + item->position.w) && mouse.y > item->GetPosition().y && mouse.y < (item->GetPosition().y + item->position.h)) {
			if (item->mouse_off) {
				item->mouse_on = true;
				item->mouse_off = false;
				react = MOUSE_ENTER;
			}
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {
				react = LEFT_CLICK;
				on_UIElem = item;
			}
			if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN) {
				react = RIGHT_CLICK;
				on_UIElem = item;
			}
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP) {
				react = LEFT_CLICK_UP;
			}
			if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP) {
				react = RIGHT_CLICK_UP;
			}
		}
		else {
			if (item->mouse_on) {
				item->mouse_on = false;
				item->mouse_off = true;
				react = MOUSE_LEAVE;
			}
		}
		if (on_UIElem == item) {
			if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {
				react = LEFT_ARROW;
			}
			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {
				react = RIGHT_ARROW;
			}
			if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
				react = UP_ARROW;
			}
			if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
				react = DOWN_ARROW;
			}
			if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN) {
				if(!elem_changed)
					on_UIElem = GetNextFocus();
			}
		}
		if (react != NONE) {
			for (p2List_item<j1Module*>* module = item->GetFirstListener(); module; module = module->next) {
				module->data->UI_Events(item, react);
			}
			break;
		}
	}
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT && (mouse.x != last_mouse.x || mouse.y != last_mouse.y)) {
		if (on_UIElem != nullptr && on_UIElem->draggable) {
			int x_motion = mouse.x - last_mouse.x, y_motion = mouse.y - last_mouse.y;
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

void j1Gui::UI_Events(UI* element, UI_Event react)
{
	
	switch (react)
	{
	case MOUSE_ENTER:
		if (element->GetType() == BUTTON) {
			Button* button = (Button*)element;
			button->OnHover();
		}
		if (element->GetType() == CHECKBOX) {
			CheckBox* box = (CheckBox*)element;
			box->OnHover();
		}
		break;
	case MOUSE_LEAVE:
		if (element->GetType() == BUTTON) {
			Button* button = (Button*)element;
			button->Standard();
		}
		if (element->GetType() == CHECKBOX) {
			CheckBox* box = (CheckBox*)element;
			box->Standard();
		}
		break;
	case RIGHT_CLICK:
		if (element->GetType() == BUTTON) {
			Button* button = (Button*)element;
			button->OnClick();
		}
		if (element->GetType() == CHECKBOX) {
			CheckBox* box = (CheckBox*)element;
			box->Clicked();
		}
		break;
	case LEFT_CLICK:
		if (element->GetType() == BUTTON) {
			Button* button = (Button*)element;
			button->OnClick();
		}
		if (element->GetType() == CHECKBOX) {
			CheckBox* box = (CheckBox*)element;
			box->Clicked();
		}
		break;
	case RIGHT_CLICK_UP:
		if (element->GetType() == BUTTON) {
			Button* button = (Button*)element;
			button->OnHover();
		}
		if (element->GetType() == CHECKBOX) {
			CheckBox* box = (CheckBox*)element;
			box->OnHover();
		}
		break;
	case LEFT_CLICK_UP:
		if (element->GetType() == BUTTON) {
			Button* button = (Button*)element;
			button->OnHover();
		}
		if (element->GetType() == CHECKBOX) {
			CheckBox* box = (CheckBox*)element;
			box->OnHover();
		}
		break;
	case TAB:
		break;
	case NONE:
		break;
	default:
		break;
	}
}

// getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

UI * j1Gui::CreateUIElement(UI_type type, int pos_x, int pos_y,int w, int h, UI* parent)
{
	UI* element = nullptr;

	switch (type)
	{
	case CHECKBOX:
		element = new CheckBox(pos_x, pos_y, parent, w, h);
		break;
	case INPUT_TEXT:
		element = new InputText(pos_x, pos_y,w,h,parent);
		break;
	case BUTTON:
		element = new Button(pos_x, pos_y, w, h, parent);
		break;
	case LABEL:
		element = new Label(pos_x, pos_y, w, h, parent);
		break;
	case IMAGE:
		element = new Image(pos_x, pos_y, w, h, parent);
		break;
	case WINDOW:
		element = new Window(pos_x, pos_y, w, h, parent);
		break;
	case SCROLLBAR:
		element = new ScrollBar(pos_x, pos_y, w, h, parent);
		break;
	case UNKNOW:
		break;
	default:
		break;
	}

	if (element != nullptr) {
		element->AddListener(this);
		UIelements.add(element);
	}

	return element;
}

void j1Gui::DeleteUIElement(UI * element)
{
	element->to_delete = true;
}

void j1Gui::ClearUIElements()
{
	for (p2List_item<UI*>* item = UIelements.start; item != nullptr; item = item->next) {
		if (item->data->to_delete == true) {
			item->data->CleanUp();
			RELEASE(item->data);
			UIelements.del(item);
			if (item->data == on_UIElem)
				on_UIElem = nullptr;
		}

	}
}

UI * j1Gui::GetNextFocus()
{
	UI* new_focus = nullptr;

	for (p2List_item<UI*>* item = UIelements.end; item; item = item->prev) {
		if (on_UIElem->GetPriority() == item->data->GetPriority() && item->data != on_UIElem && item->data->interactable) {
			new_focus = item->data;
		}
		else if (item->data == on_UIElem && new_focus != nullptr) break;

	}
	elem_changed = true;
	return new_focus;
}

// class Gui ---------------------------------------------------

