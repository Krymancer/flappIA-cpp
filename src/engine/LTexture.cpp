#include <engine/LTexture.hpp>

LTexture::LTexture() {
    this->mTexture = nullptr;
    this->mWidth = 0;
    this->mHeight = 0;
}

LTexture::~LTexture() {
    this->free();
}

bool LTexture::loadFromFile(const char* path) {
    //Get rid of the preexisting texutre
    this->free();

    //The final texture
    SDL_Texture* newTexture = nullptr;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);

    if (loadedSurface == nullptr) {
        std::cout << "Unable to load image "
                  << path
                  << " SDL_Image_Error: " << IMG_GetError() << std::endl;
    } else {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGBA(loadedSurface->format, 0x0, 0x0, 0x0,0xff));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(Engine::gRenderer, loadedSurface);

        if (newTexture == nullptr) {
            std::cout << "Unable to create texture from "
                      << path
                      << " SDL_Error: " << SDL_GetError() << std::endl;
        } else {
            //Get image dimensions
            this->mWidth = loadedSurface->w;
            this->mHeight = loadedSurface->h;
        }

        //Get rid of the old surface
        SDL_FreeSurface(loadedSurface);
    }

    this->mTexture = newTexture;
    return mTexture != nullptr;
}

bool LTexture::loadFromRenderedText(const char* textureText, SDL_Color textColor) {
    //Get rid of preexisting texture
    this->free();
    
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(Engine::gFont, textureText, textColor);

    if (textSurface == nullptr) {
        std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
    } else {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(Engine::gRenderer, textSurface);
        if (mTexture == nullptr) {
            std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
        } else {
            //Get image dimensions
            this->mWidth = textSurface->w;
            this->mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    //Return success
    return mTexture != nullptr;
}

void LTexture::free() {
    //Free image if exists
    if (this->mTexture != nullptr) {
        SDL_DestroyTexture(this->mTexture);
        this->mTexture = nullptr;
        this->mWidth = 0;
        this->mHeight = 0;
    }
}

void LTexture::draw(int x, int y) {
    //Set rendering space
    SDL_Rect renderQuad = {x, y, this->mWidth, this->mHeight};

    //Render to screen
    SDL_RenderCopy(Engine::gRenderer, this->mTexture, nullptr, &renderQuad);
}

void LTexture::draw(int x, int y, int dx, int dy, int w, int h) {
    //Set clip space
    SDL_Rect clip = {dx, dy, w, h};

    //Set rendering space
    SDL_Rect renderQuad = {x, y, w, h};

    //Render to screen
    SDL_RenderCopy(Engine::gRenderer, this->mTexture, &clip, &renderQuad);
}

void LTexture::draw(int x, int y, SDL_Rect* clip) {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, this->mWidth, this->mHeight};

    //Set clip render dimensions
    if (clip != nullptr) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopy(Engine::gRenderer, this->mTexture, clip, &renderQuad);
}

void LTexture::draw(int x, int y, double angle, SDL_Rect* clip, SDL_Point* center, SDL_RendererFlip flip) {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    //Set clip rendering dimensions
    if (clip != nullptr) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(Engine::gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void LTexture::tint(Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetTextureColorMod(this->mTexture, r, g, b);
}

void LTexture::tint(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetTextureColorMod(this->mTexture, r, g, b);
    SDL_SetTextureAlphaMod(this->mTexture, a);
}

void LTexture::setAlpha(Uint8 a) {
    SDL_SetTextureAlphaMod(this->mTexture, a);
}

void LTexture::setBlending(SDL_BlendMode mode) {
    SDL_SetTextureBlendMode(this->mTexture, mode);
}

int LTexture::getWidth() {
    return this->mWidth;
}

int LTexture::getHeight() {
    return this->mHeight;
}