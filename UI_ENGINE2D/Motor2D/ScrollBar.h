#ifndef _UISCROLLBAR_
#define _UISCROLLBAR_
#include "UI.h"
#include "StaticImage.h"
#include "j1App.h"
#include "j1Gui.h"

class UIScrollBar :public UI {

public:

	UIScrollBar(int x, int y, int w, int h, UI* parent) : UI(SCROLLBAR,parent,true,x, y, w, h) {	}
	~UIScrollBar() {}

	void SetBar(int rect_x, int rect_y, int w, int h)
	{
		bar = (StaticImage*)App->gui->CreateUIElement(IMAGE, this,position.x + (position.w - w) / 2, position.y + (position.h - h) / 2, w, h);
		bar->SetRect({ rect_x,rect_y,w,h });
		bar->interactable = false;
	}

	void SetScroll(int rect_x, int rect_y, int w, int h)
	{
		scroll = (StaticImage*)App->gui->CreateUIElement(IMAGE, bar, bar->GetLocalPosition().x, bar->GetLocalPosition().y, w, h);
		scroll->SetRect({ rect_x,rect_y,w,h });
	}
private:
	StaticImage* bar;
	StaticImage* scroll;
public:
	UI* target;
};
#endif // !_UISCROLLBAR_