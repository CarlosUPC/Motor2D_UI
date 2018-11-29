#ifndef __j1FONTS_H__
#define __j1FONTS_H__

#include "j1Module.h"
#include "SDL_TTF\include\SDL_ttf.h"
#include "SDL\include\SDL_pixels.h"

#define DEFAULT_FONT "fonts/open_sans/OpenSans-Regular.ttf"
#define DEFAULT_FONT_SIZE 12

struct SDL_Texture;


class j1Fonts : public j1Module
{
public:

	j1Fonts();

	// Destructor
	virtual ~j1Fonts();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Load Font
	TTF_Font* const Load(const char* path, int size = 12);

	// Create a surface from text
	SDL_Texture* Print(const char* text, SDL_Color color = {255, 255, 255, 255}, TTF_Font* font = NULL);

	bool CalcSize(const char* text, int& width, int& height, TTF_Font* font = NULL) const;

public:

	p2List<TTF_Font*>	fonts;
	TTF_Font*			default;
	TTF_Font*			yellow_font = nullptr;
};


#endif // __j1FONTS_H__