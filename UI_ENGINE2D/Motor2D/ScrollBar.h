#ifndef _SCROLLBAR_
#define _SCROLLBAR_

#include "UI.h"
#include "Image.h"
#include "j1App.h"
#include "j1Gui.h"

class ScrollBar :public UI {

public:

	//------------------------------Constructor & Destructor Function--------------------------------//
	ScrollBar(int x, int y, int w, int h, UI* parent) : UI(SCROLLBAR, x, y, parent, true, w, h)	{	}
	~ScrollBar(){}
	//------------------------------Constructor & Destructor Function--------------------------------//



	//-------------Virtual Functions--------------//
	bool Update()
	{
		if (position.w > position.h) {

			if (pos_diff != pivot->GetLocalPosition().x - bar->GetLocalPosition().x) {
				pos_diff = pivot->GetLocalPosition().x - bar->GetLocalPosition().x;

				//-----------------------Scroll Function---------------------------//
				target->Scroll('h', (float)pos_diff / (float)(bar->position.w - pivot->position.w));
			}
		}
		else if (position.h > position.w) {

			if (pos_diff != pivot->GetLocalPosition().y - bar->GetLocalPosition().y) {
				pos_diff = pivot->GetLocalPosition().y - bar->GetLocalPosition().y;

				//------------------------Scroll Function---------------------------//
				target->Scroll('v', (float)pos_diff / (float)(bar->position.h - pivot->position.h));
			}
		}
		return true;
	}

	void CleanUp() {
		App->gui->DeleteUIElement(bar);
		App->gui->DeleteUIElement(pivot);
	}
	//-------------Virtual Functions--------------//



	//-------------Factory Functions--------------//
	void SetBar(int rect_x, int rect_y, int w, int h) 
	{
		bar = (Image*)App->gui->CreateUIElement(IMAGE, (position.w - w) / 2, (position.h - h) / 2, w, h,this);
		bar->SetRect({ rect_x,rect_y,w,h });
		bar->interactable = false;
	}

	void SetScroll(int rect_x, int rect_y, int w, int h)
	{
		pivot = (Image*)App->gui->CreateUIElement(IMAGE, 0, 0, w, h,this);
		pivot->SetRect({ rect_x,rect_y,w,h });
	}
	//-------------Factory Functions--------------//



private:
	Image* bar;
	Image* pivot;
	int pos_diff = 0;

public:
	UI* target;
};

#endif // !_UISCROLLBAR_

