#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;

class Image;
class Label;
class Button;
class Window;
class InputText;
class ScrollBar;
enum Events;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void UI_Event(UI* element, Events react);

private:
	SDL_Texture* debug_tex;

	Image* banner;
	Label* text;
	Label* text2;
	Button* button;
	Button* button2;
	Window* window;
	InputText* input_text;
	ScrollBar* horizontal;
	ScrollBar* vertical;
};

#endif // __j1SCENE_H__