#ifndef _UI_
#define _UI_

#include "SDL\include\SDL.h"
#include "j1App.h"
#include "j1Render.h"

class j1Module;

enum UI_type {

	CHECKBOX, 
	INPUT_TEXT, 
	OUTPUT_FIELD, 
	BUTTON, 
	LABEL, 
	IMAGE,
	WINDOW, 
	UNKNOW
};

class UI {
public:
	UI() : type(UNKNOW) {}

	UI(UI_type type, UI* parent, bool interactable = true, int pos_x = 0, int pos_y = 0, int width = 0, int height = 0) : type(type),parent(parent), interactable(interactable), position({ pos_x, pos_y, width, height }){
		
		/*if (parent != nullptr) {
			priority = parent->priority + 1;
			SetPos(pos_x, pos_y);
		}*/
		
	}

	
	virtual bool Update(){
		return true;
	}

	virtual void Draw()
	{
		SDL_Rect viewport;
		if (parent != nullptr)
			viewport = { parent->GetPosition().x, parent->GetPosition().y, parent->position.w, parent->position.h };
		else
			viewport = App->render->viewport;
		App->render->SetViewPort(viewport);
		
		InnerDraw();
		DebugDraw();
		App->render->ResetViewPort();
		
	}

	virtual void InnerDraw() {}

	UI_type GetType()const { return type; }

	void SetPos(int x, int y) {
		if (!is_static) {
			position.x = x;
			position.y = y;
		}
	}

	int GetPriority()const {
		return priority;
	}

	iPoint GetPosition()const {
		if (parent != nullptr) {
			return{ position.x + parent->GetPosition().x,position.y + parent->GetPosition().y };
		}
		else return{ position.x,position.y };
	}

	iPoint GetLocalPosition()const {
		return{ position.x,position.y };
	}

	UI* GetParent()const {
		return parent;
	}

	void DebugDraw() {
		App->render->DrawQuad(position, 255U, 0U, 0U, 255U, false, false);
	}

public:
	bool interactable = true;
	SDL_Rect position;
	
	bool mouse_on = false;
	bool mouse_off = true;

	p2List<j1Module*> listeners;

	bool is_static = false;
	bool can_move = true;
	//iPoint last_position;

private:
	UI_type type;
	UI* parent = nullptr;
	int priority = 0;

private:

};

#endif
