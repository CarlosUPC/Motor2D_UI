#ifndef _UI_
#define _UI_

#include "SDL\include\SDL.h"
#include "j1App.h"
#include "j1Render.h"

class j1Module;

enum UI_type {
	CHECKBOX, 
	INPUT_TEXT, 
	SCROLLBAR, 
	BUTTON, 
	LABEL, 
	IMAGE, 
	WINDOW, 
	UNKNOW
};

class UI {

public:

	//------------------------------Constructor Function--------------------------------//
	UI(): type(UNKNOW){}
	UI(UI_type type, int pos_x, int pos_y, UI* parent, bool interactable = true, int width = 0, int height = 0): type(type),parent(parent),interactable(interactable), position({pos_x, pos_y, width, height}){
		/*if (parent != nullptr) {
			priority = parent->priority + 1;
			SetPos(pos_x, pos_y);
		}*/
	}
	//------------------------------Constructor Functions--------------------------------//

	
	//------------------------------Draw Function--------------------------------//
	 void Draw() 
	{
		SDL_Rect viewport;
		if (parent != nullptr)
			viewport = { parent->GetPosition().x, parent->GetPosition().y, parent->position.w, parent->position.h };
		else
			viewport = App->render->viewport;
		App->render->SetViewPort(viewport);
		
		//check element is inside parent boundaries
		if (position.x < 0) position.x = 0;
		if (position.y < 0)position.y = 0;
		if (GetPosition().x + position.w > viewport.x + viewport.w) position.x = viewport.w - position.w;
		if (GetPosition().y + position.h > viewport.y + viewport.h) position.y = viewport.h - position.h;
		
		//DebugDraw();
		App->render->SetViewPort({ GetPosition().x,GetPosition().y,position.w,position.h });
		InnerDraw();
		App->render->ResetViewPort();
	}
	 //------------------------------Draw Function--------------------------------//
	 


	 //-------------Virtual Functions--------------//
	 
	 virtual void InnerDraw() {}

	 virtual bool Update() { return true; }
	 
	 virtual void CleanUp(){}

	 virtual void Scroll(char dir, float percentage) {
		if (dir == 'h') {
			draw_offset.x = -position.w*percentage;
		}
		if (dir == 'v') {
			draw_offset.y = -position.h*percentage;
		}
	 }
	//-------------Virtual Functions--------------//



	//-------------Factory Functions--------------//
	UI_type GetType()const { return type; }
	
	void SetPos(int x, int y) {
		position.x = x; 
		position.y = y;
		
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
	//-------------Factory Functions--------------//



	//-------------Debug Functions--------------//
	void DebugDraw(){
		App->render->DrawQuad(position, 255U, 0U, 0U, 255U, false, false);
	}
	//-------------Debug Functions--------------//
	


	//-------------Application Functions--------------//
	void AddListener(j1Module* module) {
		if (listeners.find(module) == -1) {
			listeners.add(module);
		}
	}

	p2List_item<j1Module*>* GetFirstListener() {
		return listeners.start;
	}

	p2List_item<j1Module*>* GetLastListener() {
		return listeners.end;
	}
	//-------------Application Functions--------------//



public:
	SDL_Rect position;

	bool interactable = true;
	bool draggable = true;
	bool active = true;


	bool mouse_on = false;
	bool mouse_off = true;
	
	bool to_delete = false;

	iPoint draw_offset = { 0,0 };

private:

	UI_type type;
	UI* parent = nullptr;
	int priority = 0;

	p2List<j1Module*> listeners;

};

#endif