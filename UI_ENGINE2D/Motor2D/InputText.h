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
		if (text_texture != nullptr)
			SDL_DestroyTexture(text_texture);

		text_texture = App->font->Print(text.GetString());
		SDL_QueryTexture(text_texture, NULL, NULL, &texture_rect.w, &texture_rect.h);
		
		App->render->SetViewPort({ GetPosition().x,GetPosition().y,position.w,position.h });
		App->render->Blit(text_texture, 0, 0, &texture_rect, false);

		if (App->gui->on_UIElem == this)
			App->render->DrawQuad({ cursor_position, 0, 2, position.h }, 255U, 255U, 255U, 255U);

		//App->render->DrawQuad({ position.x, position.y, 2, position.h }, 255U, 255U, 255U, 255U);
		//App->render->Blit(App->font->Print(text.GetString()), position.x, position.y, NULL, false);
	}
	bool Update() {
		//text = default_text;
		if (App->gui->on_UIElem == this) {

			App->input->StartInputText(&text, &cursor_position);

			if (!active) {
				active = true;
				text.Clear();
			}

		}
		else {

				if (active) {
					
					if (App->input->input_text == &text)
						App->input->EndInputText();

					if (text.Length() < 1) {
						text = default_text;
						active = false;
					}
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