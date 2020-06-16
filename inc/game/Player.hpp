#include <cmath>
#include <engine/LTexture.hpp>
#include <engine/engine.hpp>
#include <game/Enemy.hpp>
#include <neural-network/NeuralNetwork.hpp>
#include <neural-network/util.hpp>
#include <vector>

#pragma once

class Player {
   public:
    Player();
    Player(NeuralNetwork brain);
    ~Player();

    /**
    *  Initilizate the texture
    * 
    *  @returns true if the initialization was sucessfully
    */
    bool init();

    /// Update the player
    void update();

    /// Show the player
    void show();

    /// Make the player jump
    void jump();

    /// Reset player position and stats
    void reset();

    /// Think
    void think(Enemy &pipe);

    /// Get the bird score
    int getScore();

    /// Get the bird fitness
    double getFitness();

    /// Set the bird fitness
    void setFitness(double fitness);

    /// Get the bird brain
    NeuralNetwork getBrain();

    /// Set bird->dead to true;
    void kill();

    /// return false if the bird->dead is true
    bool alive();

    /**
     *   Update the player neural network and apply a mutation
     * 
     *  @param brain the old neural network
     */
    void regenerate(NeuralNetwork brain);

    /**
    *  Check if the player collides with a enemy
    * 
    *  @param enemy the enemy to check
    * 
    *  @returns true if collides
    */
    bool collide(Enemy &enemy);

   private:
    LTexture mTexture;
    int x, y;

    double velocityY = -9.0;          // Player's velocity along Y, default same as flapped;
    double maxVelocityY = 10.0;       // Max velocity along Y, max descend speed
    double minVelocityY = -8.0;       // Min velocity along X, max ascend speed
    double acclerationY = 1.0;        // Player's downward accleration
    double rotationAngle = -45.0;     // Player's rotation
    double visibleRotation = 0;       // Player's visible rotation
    double velocityRotation = 6.0;    // Angular Speed
    double rotationThreshold = 20.0;  // Rotation Trheshold
    double flappyAccleration = -9.0;  // Player's speed on flapping
    bool flapped = false;             // True when player flaps

    int frame = 0;
    const int FLY_ANIMATION_FRAMES = 3;
    SDL_Rect spritesClips[3];

    NeuralNetwork brain = NeuralNetwork(5, 8, 2);

    int score = 0;
    double fitness = 0;

    bool dead = false;
};