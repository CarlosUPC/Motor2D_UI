#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "UI.h"
#include "p2Stack.h"
#include "p2PQueue.h"

// TODO 1: Create your structure of classes

// ---------------------------------------------------

enum UI_Event {
	MOUSE_ENTER, 
	MOUSE_LEAVE, 
	RIGHT_CLICK, 
	LEFT_CLICK, 
	RIGHT_CLICK_UP, 
	LEFT_CLICK_UP, 
	TAB, 
	LEFT_ARROW, 
	UP_ARROW, 
	RIGHT_ARROW,
	DOWN_ARROW, 
	NONE
};

class UI;

class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Update Elements
	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Application Function UI
	void UI_Events(UI* element, UI_Event action);
	
	// GUI creation functions
	UI* CreateUIElement(UI_type type, int pos_x, int pos_y, int w = 0, int h = 0 , UI* parent = nullptr);
	void DeleteUIElement(UI* element);
	void ClearUIElements();
	SDL_Texture* GetAtlas() const;
	UI* GetNextElem();

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;

	p2List<UI*> UIelements;
	p2PQueue<UI*> draw_queue;
	p2Stack<UI*> react_stack;

	iPoint last_mouse;
	bool elem_changed = false;

public:
	UI* on_UIElem = nullptr;
};

#endif // __j1GUI_H__