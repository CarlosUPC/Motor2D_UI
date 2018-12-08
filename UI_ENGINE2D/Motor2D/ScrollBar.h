#ifndef _UISCROLLBAR_
#define _UISCROLLBAR_
#include "UI.h"
#include "Image.h"
#include "j1App.h"
#include "j1Gui.h"

class ScrollBar :public UI {

public:

	ScrollBar(UI* parent,int x, int y, int w, int h) : UI(SCROLLBAR,parent,true,x, y, w, h) {	}
	~ScrollBar() {}

	void SetBar(int rect_x, int rect_y, int w, int h)
	{
		bar = (Image*)App->gui->CreateUIElement(IMAGE, this,position.x + (position.w - w) / 2, position.y + (position.h - h) / 2, w, h);
		bar->SetRect({ rect_x,rect_y,w,h });
		bar->interactable = false;
	}

	void SetScroll(int rect_x, int rect_y, int w, int h)
	{
		scroll = (Image*)App->gui->CreateUIElement(IMAGE, this, 0, 0, w, h);
		scroll->SetRect({ rect_x,rect_y,w,h });
	}

	bool Update()
	{
		if (position.w > position.h) {
			//scroll->position.y = 0;
			if (pos_diff != scroll->GetLocalPosition().x - bar->GetLocalPosition().x) {
				pos_diff = scroll->GetLocalPosition().x - bar->GetLocalPosition().x;
				target->Scroll('h', (float)pos_diff / (float)(bar->position.w - 2 * scroll->position.w)); //horizontal scrollbar
			}
		}
		else if (position.h > position.w) {
			//scroll->position.x = 0;
			if (pos_diff != scroll->GetLocalPosition().y - bar->GetLocalPosition().y) {
				pos_diff = scroll->GetLocalPosition().y - bar->GetLocalPosition().y;
				target->Scroll('v', (float)pos_diff / (float)(bar->position.h - 2 * scroll->position.h)); //verticall scrollbar
			}
		}
		return true;
	}

private:
	Image* bar;
	Image* scroll;
	int pos_diff = 0;
public:
	UI* target;
};
#endif // !_UISCROLLBAR_