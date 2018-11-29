#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "j1Fonts.h"
#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes
enum UI_TYPE
{
	NO_TYPE,
	TEXT,
	IMAGE,
	BACKGROUND_IMAGE
};

class UI
{
public:
	iPoint position;
	UI_TYPE type;
public:
	UI(iPoint position, UI_TYPE type);
	virtual bool Update();
	virtual ~UI();
};

class Passive_UI :public UI
{
public:
	Passive_UI(iPoint position, UI_TYPE type);
	virtual bool Update();
	virtual ~Passive_UI();
};

class Image :public Passive_UI
{
public:
	SDL_Rect Image_Rect;
public:
	Image(iPoint position, UI_TYPE type, SDL_Rect rect);
	virtual bool Update();
	virtual ~Image();
};

class Text :public Passive_UI
{
public:
	TTF_Font* text_font = nullptr;
	char* string = nullptr;
public:
	Text(iPoint position, UI_TYPE type, char* string_text, TTF_Font* text_font);
	virtual bool Update();
	virtual ~Text();
};

//class NoAtlasImage :public Passive_UI
//{
//public:
//	SDL_Texture* texture = nullptr;
//	SDL_Rect rect;
//public:
//	NoAtlasImage(iPoint position, UI_TYPE type, SDL_Texture* texture, SDL_Rect rect);
//	virtual bool Update();
//	virtual ~NoAtlasImage();
//};

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions

	UI* CreateImage(iPoint position, UI_TYPE type, SDL_Rect ImageRect);
	UI* CreateText(iPoint position, UI_TYPE type, char* string_text, TTF_Font* text_font);
	//UI* CreateBackground(iPoint position, UI_TYPE type, SDL_Texture* texture, SDL_Rect rect);

	const SDL_Texture* GetAtlas() const;
	//SDL_Texture* GetNoAtlas();

private:

	SDL_Texture* atlas = nullptr;
	//SDL_Texture* no_atlas_tex = nullptr;
	p2SString atlas_file_name;
	p2List<UI*> ui_elements;
};

#endif // __j1GUI_H__