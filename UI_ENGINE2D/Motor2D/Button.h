#ifndef _BUTTON_
#define _BUTTON_

#include "Image.h"
#include "p2SString.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Gui.h"

class Button : public Image {
public:
	//Constructor
	Button(int x, int y, int w, int h,UI* parent) : Image(BUTTON,x,y,parent,true,w,h)
	{
	}
	// Destructor
	~Button(){}

	// Draw
	void InnerDraw() 
	{
		if (image_rect.w == 0)
			Standard();
		App->render->Blit(App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &image_rect,false);
	}

	//Set Draw Rect
	void SetRects(SDL_Rect std_rect,SDL_Rect hl_rect, SDL_Rect click_rect) {
		standard_rect = std_rect;
		highlight_rect = hl_rect;
		clicked_rect = click_rect;
	}
	void Standard() {
		image_rect = standard_rect;
	}
	void OnHover() {
		image_rect = highlight_rect;
	}
	void OnClick() {
		image_rect = clicked_rect;
	}

public:
	
private:
	
private:
	SDL_Rect standard_rect = { 0,0,0,0 };
	SDL_Rect highlight_rect = { 0,0,0,0 };
	SDL_Rect clicked_rect = { 0,0,0,0 };
};
#endif // !_UIBUTTON_