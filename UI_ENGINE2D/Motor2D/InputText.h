#ifndef _INPUTTEXT_
#define _INPUTTEXT_

#include "Label.h"
#include "j1Gui.h"
#include "p2SString.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Input.h"

class InputText : public Label {
public:
	InputText(UI* parent,int x, int y, int w, int h) : Label(INPUT_TEXT,parent, x, y, w, h) {}
	~InputText() {}

	void InnerDraw() {
		text_texture = App->font->Print(text.GetString());
		SDL_QueryTexture(text_texture, NULL, NULL, &texture_rect.w, &texture_rect.h);
		App->render->Blit(text_texture, position.x, position.y, &texture_rect, false);
		App->render->DrawQuad({ position.x, position.y, 2, position.h }, 255U, 255U, 255U, 255U);
		//App->render->Blit(App->font->Print(text.GetString()), position.x, position.y, NULL, false);
	}
	bool Update() {
		//text = default_text;
		if (App->gui->on_UIElem == this) {
			//App->render->DrawQuad({ position.x, position.y, 1, 3 }, 0, 0, 0);
			if (!active) {
				active = true;
				text.Clear();
				App->input->StartInputText(&text, &cursor_position);
			}
		}
		else {
			if (text.Length() < 1 && active)
				text = default_text;
			if (active) {
				active = false;
				if (App->input->input_text == &text)
					App->input->EndInputText();
			}

		}
		return true;
	}

	void SetDefaultText(char* text) {
		default_text = text;
	}
private:
	int cursor_position;
	p2SString default_text;
	bool active = true;
};

#endif