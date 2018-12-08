#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "UI.h"
#include "p2Stack.h"
#include "p2PQueue.h"

// TODO 1: Create your structure of classes

// ---------------------------------------------------

enum Events {

	MOUSE_ENTER, 
	MOUSE_LEAVE, 
	RIGHT_CLICK, 
	LEFT_CLICK, 
	RIGHT_CLICK_UP, 
	LEFT_CLICK_UP, 
	TAB, 
	NONE
};

class UIElement;

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

	void UI_Event(UI* element, Events react);

	// TODO 2: Create the factory methods
	// Gui creation functions

	SDL_Texture* GetAtlas() const;

	UI* CreateUIElement(UI_type type, int pos_x, int pos_y, int w, int h, UI* parent = nullptr);

	void DeleteUIElement(UI* element);
	
private:
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