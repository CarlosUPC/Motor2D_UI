#ifndef _CHECKBOX_
#define _CHECKBOX_

#include "Button.h"

class CheckBox :public Button {
public:
	CheckBox(int x, int y, UI* parent, int w, int h) :Button(CHECKBOX, x, y, w, h, parent) {

	}
	~CheckBox(){}

	void InnerDraw()
	{
		if (image_rect.w == 0)
			Standard();
		App->render->Blit(App->gui->GetAtlas(), draw_offset.x, draw_offset.y, &image_rect, false);
		if (clicked) {
			App->render->Blit(App->gui->GetAtlas(), draw_offset.x + (position.w - GetClickedRect().w) / 2, draw_offset.y + (position.h - GetClickedRect().h) / 2, &GetClickedRect());
		}
	}

	void AddOptions(CheckBox* option) {
		if (options.find(option) == -1) {
			options.add(option);
		}
		if (option->options.find(this) == -1) {
			option->options.add(this);
		}
	}

	void Clicked() {
		clicked = !clicked;
		if (is_option) {
			for (p2List_item<CheckBox*>* item = options.start; item; item = item->next) {
				item->data->clicked = false;
			}
		}
	}

	bool GetIsClicked()const {
		return clicked;
	}

public:
	bool is_option = false;

private:
	bool clicked = false;
	p2List<CheckBox*> options;

private:

};

#endif // !_UICHECKBOX_

