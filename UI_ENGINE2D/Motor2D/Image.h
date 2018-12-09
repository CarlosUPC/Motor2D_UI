#ifndef _UISTATICIMAGE_
#define _UISTATICIMAGE_

#include "UI.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1App.h"

class Image : public UI {
public:

	Image() : UI(IMAGE, 0, 0,nullptr) {}
	Image(int pos_x, int pos_y, int w, int h, UI* parent) : UI(IMAGE, pos_x, pos_y, parent, true, w, h) {  }

	Image(UI_type type, int x, int y, UI* parent, bool interactable = true, int width = 0, int height = 0) : UI(type, x, y, parent, interactable, width, height) {  }

	void InnerDraw() {
		App->render->Blit(App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &image_rect,false);
	}

	void SetRect(SDL_Rect img_rect) {
		image_rect = img_rect;
		if (position.w == 0 && position.h == 0) {
			position.w = img_rect.w;
			position.h = img_rect.h;
		}
	}

	void Scroll(char dir, float percentage) {
		if (dir == 'h') {
			draw_offset.x = -(image_rect.w-position.w)*percentage;
		}
		if (dir == 'v') {
			draw_offset.y = -(image_rect.h-position.h)*percentage;
		}
	}

public:
	SDL_Rect image_rect = { 0,0,0,0 };
private:
	
private:

};

#endif