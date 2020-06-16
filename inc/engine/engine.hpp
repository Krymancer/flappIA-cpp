#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <engine/LTexture.hpp>
#include <engine/LTimer.hpp>

namespace Engine {

//Screen dimension constants
const int SCREEN_WIDTH = 288;
const int SCREEN_HEIGHT = 512;

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The surface contained by the window
extern SDL_Surface* gScreenSurface;

//Globally used font
extern TTF_Font *gFont;

//The window renderer
extern SDL_Renderer* gRenderer;

//Start up SDL and creates window
bool init();

/**
*   Load image from specified path
* 
*  @param path Path correspondent to image
* 
*  @returns Return the image as a surface
*/
SDL_Surface* loadSurface(const char* path);

/**
*   Load image from specified path
* 
*  @param path Path correspondent to image
* 
*  @returns Retuns the image as a texture
*/
SDL_Texture* loadTexture(const char* path);

//Load the media
bool loadMedia();

//Free media and shuts down SDL
void close();

//Calculate the run time
double runTime();

}  // namespace Engine