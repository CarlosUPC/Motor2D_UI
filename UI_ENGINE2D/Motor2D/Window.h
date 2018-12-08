#ifndef _WINDOW_
#define _WINDOW_

#include "Image.h"
#include "p2SString.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1App.h"
#include "j1Gui.h"

class Window : public Image {
public:
	//Constructor
	Window(UI* parent,int x, int y, int w, int h) : Image(WINDOW,parent,true,x, y, w, h)
	{
	}
	// Destructor
	~Window() {}

	// Draw
	void InnerDraw()
	{
		if (visible) {
			App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), position.x, position.y, &image_rect, false);
		}
	}

public:
	bool visible = true;
private:

private:
};
#endif // !_UIBUTTON_
