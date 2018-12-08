#ifndef _UISTATICIMAGE_
#define _UISTATICIMAGE_

#include "UI.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1App.h"

class StaticImage : public UI {
public:

	//StaticImage() : UI(STATIC_IMAGE, 0, 0) {}
	//StaticImage(int pos_x, int pos_y) : UIElement(StaticImage, pos_x, pos_y) {}
	StaticImage(SDL_Rect image_rect, int pos_x, int pos_y) : UI(IMAGE,nullptr,false,pos_x, pos_y), image_rect(image_rect) {}

	void Draw() const {
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), -App->render->camera.x + position.x, -App->render->camera.y + position.y, &image_rect);
	}

	void SetRect(SDL_Rect img_rect) {
		image_rect = img_rect;
	}

public:
private:
	SDL_Rect image_rect = { 0,0,0,0 };
private:

};

#endif
