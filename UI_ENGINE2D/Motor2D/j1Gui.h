#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "UI.h"
#include "p2Stack.h"
#include "p2PQueue.h"
#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes

// ---------------------------------------------------

enum UI_Events {
	MOUSE_ENTER, 
	MOUSE_LEAVE, 
	RIGHT_CLICK, 
	LEFT_CLICK, 
	RIGHT_CLICK_UP, 
	LEFT_CLICK_UP, 
	TAB, 
	DRAG, 
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

	// TODO 2: Create the factory methods
	// Gui creation functions

	const SDL_Texture* GetAtlas() const;
	UI* CreateUIElement(UI_type type, UI* parent = nullptr, int pos_x = 0, int pos_y = 0, int w = 0, int h = 0);
	void UIEvent(UI* element, UI_Events react);

	void DeleteUIElement(UI* element);
	void ClearUIElements();

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;

	p2List<UI*> UIelements;
	p2PQueue<UI*> draw_queue;
	p2Stack<UI*> react_stack;

	iPoint last_mouse;
public:
	UI* on_UIElem = nullptr;
};

#endif // __j1GUI_H__