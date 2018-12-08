#ifndef _INPUTTEXT_
#define _INPUTTEXT_

#include "Label.h"
#include "j1Gui.h"
#include "p2SString.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Fonts.h"

class InputText : public Label {
public:
	InputText(UI* parent,int x, int y, int w, int h) : Label(INPUT_TEXT,parent, x, y, w, h) {}
	~InputText() {}

	void InnerDraw() {
		App->render->Blit(App->font->Print(text.GetString()), position.x, position.y, NULL, false);
	}
	bool Update() {
		text = default_text;
		if (App->gui->on_UIElem == this) {
			App->render->DrawQuad({ position.x, position.y, 1, 3 }, 0, 0, 0);
		}
		return true;
	}

	void SetDefaultText(char* text) {
		default_text = text;
	}
private:
	uint cursor_position;
	p2SString default_text;
};

#endif