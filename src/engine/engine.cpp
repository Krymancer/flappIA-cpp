#include <engine/LTexture.hpp>
#include <engine/engine.hpp>
#include <iostream>

namespace Engine {

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

//The window renderer
SDL_Renderer* gRenderer = nullptr;

//Globally used font
TTF_Font* gFont = nullptr;

//Rendered texture
LTexture gFPSTextTexture;

bool init() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    } else {
        //Create window
        gWindow = SDL_CreateWindow("FlappyBird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow == nullptr) {
            std::cout << "Window cloud not be created! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        } else {
            //Create renderer to window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == nullptr) {
                std::cout << "Renderer cloud not be created! SDL_Error: " << SDL_GetError() << std::endl;
                return false;
            } else {
                //Initiaize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);

                //Initializing PNG load
                if (!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) {
                    std::cout << "SDL_Image cloud not initalize! SDL_Image_Error: " << IMG_GetError() << std::endl;
                    return false;
                } else {
                    //Initialize SDL_ttf
                    if (TTF_Init() == -1) {
                        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
                        return false;
                    } else {
                        //Get screen surface
                        gScreenSurface = SDL_GetWindowSurface(gWindow);
                    }
                }
            }
        }
    }
    return true;
}

bool loadMedia() {
    //Open the font
    gFont = TTF_OpenFont("./assets/font/Roboto-Regular.ttf", 20);
    if (gFont == nullptr) {
        std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

void close() {
    //Free global font
    TTF_CloseFont(gFont);
    gFont = NULL;

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

}  // namespace Engine