#ifndef _LABEL_
#define _LABEL_

#include "UI.h"
#include "p2SString.h"
#include "j1App.h"
#include "j1Fonts.h"

class Label : public UI {
public:

	Label() : UI(LABEL, 0, 0, nullptr) {	}
	Label(int pos_x, int pos_y, int w, int h, UI* parent) : UI(LABEL, pos_x, pos_y, parent, true, w, h){}
	Label(UI_type type, int pos_x, int pos_y, int w, int h, UI* parent) : UI(type, pos_x, pos_y, parent, true, w, h) {}

	void InnerDraw() {
		if (text_texture != nullptr)
			SDL_DestroyTexture(text_texture);

		text_texture = App->font->Print(text.c_str());
		SDL_QueryTexture(text_texture, NULL, NULL, &texture_rect.w, &texture_rect.h);
		App->render->Blit(text_texture, draw_offset.x, draw_offset.y,&texture_rect,false);

		/*App->render->SetViewPort({ GetPosition().x,GetPosition().y,position.w,position.h });
		App->render->Blit(text_texture, 0, 0, &texture_rect, false);*/

		//App->render->Blit(text_texture, position.x, position.y, &texture_rect, false);
		//App->render->Blit(App->font->Print(text.GetString()), position.x, position.y, NULL, false);


	}

	void SetText(char* txt) {
		text = txt;
	}

	void Scroll(char dir, float percentage) {
		if (dir == 'h') {
			draw_offset.x = -(texture_rect.w-position.w)*percentage;
		}
		if (dir == 'v') {
			draw_offset.y = -(texture_rect.h-position.h)*percentage;
		}
	}

public:
	std::string text = "";
	//p2SString text = "";
	SDL_Texture* text_texture;
	SDL_Rect texture_rect = { 0, 0, 0, 0 };
private:
	
};

#endif