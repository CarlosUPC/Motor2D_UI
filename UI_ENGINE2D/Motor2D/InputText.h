#ifndef _INPUTTEXT_
#define _INPUTTEXT_

#include "Label.h"
#include "j1Gui.h"
#include "p2SString.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Input.h"

#define CURSOR_W 2

class InputText : public Label {

public:

	//------------------------------Constructor & Destructor Function--------------------------------//
	InputText(int x, int y, int w, int h, UI* parent) : Label(INPUT_TEXT, x, y, w, h, parent){}
	~InputText(){}
	//------------------------------Constructor & Destructor Function--------------------------------//



	//--------------------Draw Function--------------------//
	void InnerDraw() {
		if (label_tex != nullptr)
			SDL_DestroyTexture(label_tex);
		label_tex = App->font->Print(text.c_str());
		SDL_QueryTexture(label_tex, NULL, NULL, &label_rect.w, &label_rect.h);

		if (App->gui->on_UIElem == this) {
			int w, h;
			App->font->CalcSize(text.substr(0, cursor_position).c_str(), w, h);
			if (w + draw_offset.x > position.w - CURSOR_W) {
				int last_leter_w;
				App->font->CalcSize(text.substr(cursor_position - 1, cursor_position).c_str(), last_leter_w, h);
				draw_offset.x -= last_leter_w;
			}
			if (w + draw_offset.x < 0) {
				int last_leter_w;
				if(App->font->CalcSize(text.substr(cursor_position, cursor_position + 1).c_str(), last_leter_w, h))
					draw_offset.x += last_leter_w;
			}

			App->render->DrawQuad({ w + draw_offset.x, 0, CURSOR_W, position.h }, 255U, 255U, 255U, 255U, true, false);
		}

		App->render->Blit(label_tex, draw_offset.x, draw_offset.y, &label_rect, false);

		/*App->render->SetViewPort({ GetPosition().x,GetPosition().y,position.w,position.h });
		App->render->Blit(text_texture, 0, 0, &texture_rect, false);

		if (App->gui->on_UIElem == this)
			App->render->DrawQuad({ cursor_position, 0, 2, position.h }, 255U, 255U, 255U, 255U);*/

			//App->render->DrawQuad({ position.x, position.y, 2, position.h }, 255U, 255U, 255U, 255U);
			//App->render->Blit(App->font->Print(text.GetString()), position.x, position.y, NULL, false);
		
	}
	//--------------------Draw Function--------------------//



	//-------------Virtual Functions--------------//
	bool Update() {
		if (App->gui->on_UIElem == this) {
			App->input->StartInputText(&text, &cursor_position);

			if (!active) {
				active = true;
				text.clear();
			}
			else {
				if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {
					if(cursor_position>0) cursor_position--;
				}
				if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {
					if (cursor_position<text.length()) cursor_position++;
				}
				if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN) {
					if (cursor_position > 0) {
						int w, h;
						App->font->CalcSize(text.substr(cursor_position - 1, 1).c_str(), w, h);
						text.erase(cursor_position - 1, 1);
						cursor_position--;
						if (draw_offset.x < 0)
							draw_offset.x += w;
					}
				}
				if (App->input->GetKey(SDL_SCANCODE_DELETE) == KEY_DOWN) {
					text.erase(cursor_position, 1);
				}
				if (App->input->GetKey(SDL_SCANCODE_HOME) == KEY_DOWN) {
					cursor_position = 0;
				}
				if (App->input->GetKey(SDL_SCANCODE_END) == KEY_DOWN) {
					cursor_position = text.length();
				}

			}

		}
		else {
			if (active) {
				if(App->input->input_text == &text)
					App->input->EndInputText();
				if (text.length() < 1) {
					text = default_text;
					active = false;
				}
			}
		}
		return true;
	}
	//-------------Virtual Functions--------------//



	//-------------Factory Functions--------------//
	void SetDefaultText(char* text) {
		default_text = text;
	}
	//-------------Factory Functions--------------//


private:
	int cursor_position;
	std::string default_text;
	bool active = true;
};

#endif