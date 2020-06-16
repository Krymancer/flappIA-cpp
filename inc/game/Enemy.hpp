#include <engine/LTexture.hpp>
#include <engine/engine.hpp>
#include <random>

#pragma once

class Enemy {
   public:
    Enemy(int offset);
    ~Enemy();

    /**
    *  Initilizate the texture
    * 
    *  @returns if the initialization was sucessfully
    */
    bool init();

    /// Update method
    void update();

    /// Show the car texture
    void show();

    /// Set the start position of the enemy
    void setStartPosition();

    /// Get the x position of the enemy
    int getX();

    /// Get the y position of the enemy
    int getY();

    /// Get the y position of the enemy
    int getUpperY();

    /// Get the width position of the enemy
    int getWidth();

    /// Get the height position of the enemy
    int getHeight();

    /// Restart
    void reset();

   private:
    LTexture mTexture;
    int x, y;

    int velocity = 4;
    bool alive = true;

    int gap = 100;
    const int gapSize = 100;
    int offset = 0;
};