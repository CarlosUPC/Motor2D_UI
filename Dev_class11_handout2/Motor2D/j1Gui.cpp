#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());
	//no_atlas_tex = App->tex->Load("homework/logonscreen.png");
	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");
	for (uint i = 0; i < ui_elements.count(); i++)
	{
		delete ui_elements[i];
		ui_elements[i] = nullptr;
	}

	//App->tex->UnLoad(no_atlas_tex);
	return true;
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

//SDL_Texture* j1Gui::GetNoAtlas()
//{
//	return no_atlas_tex;
//}
// class Gui ---------------------------------------------------

//---------------------------------------------Constructors-----------------------------------------
UI::UI(iPoint position, UI_TYPE type) : position(position), type(type) {}
Passive_UI::Passive_UI(iPoint position, UI_TYPE type) : UI(position, type) {}
Image::Image(iPoint position, UI_TYPE type, SDL_Rect rect) : Passive_UI(position, type), Image_Rect(rect) {}
Text::Text(iPoint position, UI_TYPE type, char* string_text, TTF_Font* text_font) : Passive_UI(position, type), string(string_text), text_font(text_font) {}
Active_UI::Active_UI(iPoint position, UI_TYPE type, SDL_Rect rect) : UI(position, type), rect(rect) {}
Button::Button(iPoint position, UI_TYPE type, SDL_Rect rect) : Active_UI(position, type, rect) {}

//---------------------------------------------Updates--------------------------------------------
bool	UI::Update() { return true; }
bool	Passive_UI::Update() { return true; }
bool	Image::Update(){
	App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), this->position.x, this->position.y, &this->Image_Rect);
	return true;
}
bool	Text::Update(){
	App->render->Blit(App->font->Print(this->string, { 255,0,0,255 }, this->text_font), this->position.x, this->position.y);
	return true;
}

bool	Active_UI::Update() { return true; }
bool	Button::Update(){
	App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), this->position.x, this->position.y, &this->rect);
	CheckMouse(this->rect, this->position);
	return true;
}

//---------------------------------------------Destructors-------------------------------------------
UI::~UI() {}
Passive_UI::~Passive_UI() {}
Image::~Image() {}
Text::~Text() {}
Active_UI::~Active_UI() {}
Button::~Button() {}
//---------------------------------------------UI Elements methods -----------------------------------------//


//bool NoAtlasImage::Update()
//{
//	App->render->Blit(this->texture, this->position.x, this->position.y, &this->rect);
//	return true;
//}
//NoAtlasImage::~NoAtlasImage() {}


//------------------------Create image UI ---------------------------//
UI* j1Gui::CreateImage(iPoint position, UI_TYPE type, SDL_Rect ImageRect)
{
	UI* elemImage = nullptr;

	elemImage = new Image(position, type, ImageRect);

	ui_elements.add(elemImage);
	return elemImage;
}
//----------------------- Create text UI -----------------------------//
UI* j1Gui::CreateText(iPoint position, UI_TYPE type, char* string_text, TTF_Font* text_font)
{
	UI* elemText = nullptr;

	elemText = new Text(position, type, string_text, (text_font) ? text_font : App->font->default);

	ui_elements.add(elemText);
	return elemText;
}
//----------------------Create background UI -----------------------//
//UI* j1Gui::CreateBackground(iPoint position, UI_TYPE type, SDL_Texture* texture, SDL_Rect rect)
//{
//	UI* elemBack = nullptr;
//
//	elemBack = new NoAtlasImage(position, type, texture, rect);
//
//	ui_elements.add(elemBack);
//
//	return elemBack;
//}
//----------------------- Create Button UI -----------------------------//
UI* j1Gui::CreateButton(iPoint position, UI_TYPE type, SDL_Rect ButtonRect)
{
	UI* elemButton = nullptr;

	elemButton = new Button(position, type, ButtonRect);

	ui_elements.add(elemButton);
	return elemButton;
}

//Buttons----------------------------------------------------------------------------------------------
EVENT Active_UI::CheckMouse(const SDL_Rect button_rect, const iPoint position)
{
	EVENT res = MOUSE_LEAVE;

	int m_x, m_y;
	App->input->GetMousePosition(m_x, m_y);

	if (m_x < position.x + button_rect.w && m_x > position.x &&
		m_y < position.y + button_rect.h && m_y > position.y)
	{
		res = MOUSE_ENTER;
		//App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), 0, 0);
		LOG("Mouse on button");
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			LOG("Left Click on button");
			res = MOUSE_LEFT_CLICK;
		}
		else if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_REPEAT)
		{
			LOG("Right Click on button");
			res = MOUSE_RIGHT_CLICK;
			
		}
	}
	else
	{
		res = MOUSE_LEAVE;
	}

	return res;
}
