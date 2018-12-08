#ifndef _UISTATICIMAGE_
#define _UISTATICIMAGE_

#include "UI.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1App.h"

class Image : public UI {
public:

	//UIImage() : UIElement(Image, 0, 0, nullptr) {}
	Image(UI* parent,int pos_x, int pos_y, int w, int h) : UI(IMAGE, parent,true, pos_x, pos_y, w, h) {  }

	Image(UI_type type, UI* parent, bool interactable = true, int x= 0, int y = 0, int width = 0, int height = 0) : UI(type,parent, interactable, x, y, width, height) {  }

	void InnerDraw() {
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &image_rect, false);
	}

	void SetRect(SDL_Rect img_rect) {
		image_rect = img_rect;
	}

public:
	SDL_Rect image_rect = { 0,0,0,0 };
private:

private:

};

#endif
