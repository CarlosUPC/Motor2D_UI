#ifndef _UILABEL_
#define _UILABEL_

#include "UI.h"
#include "p2SString.h"
#include "j1App.h"
#include "j1Fonts.h"

class Label : public UI{
public:

	//Label() : UI(LABEL, 0, 0, nullptr) {	}
	Label(UI* parent,int pos_x, int pos_y, int w, int h) : UI(LABEL,parent,true, pos_x, pos_y, w, h) {}
	Label(UI_type type, UI* parent,int pos_x, int pos_y, int w, int h) : UI(type,parent,true, pos_x, pos_y, w, h) {}

	void InnerDraw() {
		App->render->Blit(App->font->Print(text.GetString()), position.x, position.y, NULL, false);
	}

	void SetText(char* txt) {
		text = txt;
	}

public:
	p2SString text;
private:
};

#endif