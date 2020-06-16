#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <engine/engine.hpp>
#include <iostream>

class LTexture {
   public:
    LTexture();   //Constructor
    ~LTexture();  //Destructor

    /**
    *   Load image from specified path
    * 
    *  @param path Path correspondent to image
    * 
    *  @returns Return true if the image load sucessfully
    */
    bool loadFromFile(const char* path);

    /**
    *   Load image from specified path
    * 
    *  @param textureText The text to render
    *  @param textColor Color of the rendered text
    * 
    *  @returns Return true if the text texture as rendered sucessfully
    */
    bool loadFromRenderedText(const char* textureText, SDL_Color textColor);

    /// Dealocate the texture
    void free();

    /**
    * Render texture at the given point
    * 
    * @param x The x-axis cordinate to place the top-left corner of the texure
    * @param y The y-axis cordinate to place the top-left corner of the texure
    */
    void draw(int x, int y);

    /**
    * Render part of the texture at the given point
    * 
    * @param x  The x-axis cordinate to place the top-left corner of the texure
    * @param y  The y-axis cordinate to place the top-left corner of the texure
    * @param dx The x-axis cordinates to clip the texture
    * @param dy The y-axis cordinates to clip the texture
    * @param w  The width of the clip
    * @param h  The height of the clip
    */
    void draw(int x, int y, int dx, int dy, int w, int h);

    /**
    * Render a clip of the texture at the given point
    * 
    * @param x The x-axis cordinate to place the top-left corner of the texure
    * @param y The y-axis cordinate to place the top-left corner of the texure
    * @param clip The rect represset the cliped part of the texture
    */
    void draw(int x, int y, SDL_Rect* clip);

    /**
    * Render a clip of the texture at the given point
    * 
    * @param x The x-axis cordinate to place the top-left corner of the texure
    * @param y The y-axis cordinate to place the top-left corner of the texure
    * @param clip The rect represset the cliped part of the texture
    * @param center The center point to rotate the texture
    * @param flip Determine the flipping of the texture
    */
    void draw(int x, int y, double angle, SDL_Rect* clip, SDL_Point* center, SDL_RendererFlip flip);

    /**
    * Tint the texture to determinade color
    * 
    * @param r Red
    * @param g Green
    * @param b Blue
    */
    void tint(Uint8 r, Uint8 g, Uint8 b);

    /**
    * Tint the texture to determinade color and alpha
    * 
    * @param r Red
    * @param g Green
    * @param b Blue
    * @param a Alpha
    */
    void tint(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    /**
    * Set the alpha of a texture
    * 
    * @param a Alpha
    */
    void setAlpha(Uint8 a);

    /**
    * Set the blend mode of the texture
    * 
    * @param mode The specified mode to blend the texture
    */
    void setBlending(SDL_BlendMode mode);

    /// Get the width of the texture
    int getWidth();

    /// Get the height of the texture
    int getHeight();

   private:
    /// The actual hardware texture
    SDL_Texture* mTexture;

    /// Image width
    int mWidth;

    /// Image height
    int mHeight;
};