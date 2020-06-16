#include <game/Player.hpp>

Player::Player() {
    this->x = Engine::SCREEN_WIDTH * 0.2;
    this->y = (Engine::SCREEN_HEIGHT - 24) / 2;  // SCREEN HEIGHT - PLAYER HEIGHT / 2

    this->spritesClips[0].x = 0;
    this->spritesClips[0].y = 0;
    this->spritesClips[0].w = 34;
    this->spritesClips[0].h = 24;

    this->spritesClips[1].x = 34;
    this->spritesClips[1].y = 0;
    this->spritesClips[1].w = 34;
    this->spritesClips[1].h = 24;

    this->spritesClips[2].x = 68;
    this->spritesClips[2].y = 0;
    this->spritesClips[2].w = 34;
    this->spritesClips[2].h = 24;
}

Player::Player(NeuralNetwork brain) {
    this->x = Engine::SCREEN_WIDTH * 0.2;
    this->y = (Engine::SCREEN_HEIGHT - 24) / 2;  // SCREEN HEIGHT - PLAYER HEIGHT / 2

    this->spritesClips[0].x = 0;
    this->spritesClips[0].y = 0;
    this->spritesClips[0].w = 34;
    this->spritesClips[0].h = 24;

    this->spritesClips[1].x = 34;
    this->spritesClips[1].y = 0;
    this->spritesClips[1].w = 34;
    this->spritesClips[1].h = 24;

    this->spritesClips[2].x = 68;
    this->spritesClips[2].y = 0;
    this->spritesClips[2].w = 34;
    this->spritesClips[2].h = 24;

    this->brain = brain.copy();
    this->brain.mutate(mutate);
}

Player::~Player() {
    //TODO
}

bool Player::init() {
    /* Can't load in the constructor because needed a global scope
    * When the variable was created SDL_Init has not yet called
    * Causing in not having a renderer to make the texture
    */
    return this->mTexture.loadFromFile("./assets/image/bird.png");
}

void Player::show() {
    this->mTexture.draw(this->x, this->y, this->rotationAngle, &this->spritesClips[this->frame / 6], nullptr, SDL_FLIP_NONE);
}

void Player::update() {
    this->score++;
    //Animation
    ++this->frame;
    if (this->frame / 6 >= this->FLY_ANIMATION_FRAMES) this->frame = 0;

    //Rotate the player
    this->rotationAngle += this->velocityRotation;
    if (this->rotationAngle > 90) this->rotationAngle -= this->velocityRotation;

    //Player moviment
    if ((this->velocityY < this->maxVelocityY) && !this->flapped) {
        this->velocityY += this->acclerationY;
    }
    if (this->flapped) {
        this->flapped = false;
        this->rotationAngle = -45.0;
    }

    this->y += this->velocityY;

    // Player rotation has a threshold
    this->visibleRotation = this->rotationThreshold;
    if (this->rotationAngle <= this->rotationThreshold) this->visibleRotation = this->rotationAngle;
}

void Player::jump() {
    // Bounders
    this->velocityY = this->flappyAccleration;
    this->flapped = true;
    this->rotationAngle = -45.0;
}

bool Player::collide(Enemy &enemy) {
    // Check if player hit the ground
    if ((this->y + this->mTexture.getHeight()) >= (Engine::SCREEN_HEIGHT * 0.79)) {
        return true;
    }

    if(this->y < -this->mTexture.getHeight()) return true;

    SDL_Rect pCollider = {this->x, this->y,
                          34, 24};

    SDL_Rect lCollider = {enemy.getX(), enemy.getY(),
                          enemy.getWidth(), enemy.getHeight()};

    SDL_Rect uCollider = {enemy.getX(), enemy.getUpperY(),
                          enemy.getWidth(), enemy.getHeight()};

    SDL_Rect result;

    if (SDL_IntersectRect(&pCollider, &lCollider, &result)) {
        return true;
    } else if (SDL_IntersectRect(&pCollider, &uCollider, &result)) {
        return true;
    } else {
        return false;
    }
}

void Player::reset() {
    this->y = (Engine::SCREEN_HEIGHT - 24) / 2;  // SCREEN HEIGHT - PLAYER HEIGHT / 2
    this->dead = false;
    this->score = 0;
}

void Player::think(Enemy &pipe) {
    // if (this->y > pipe.getY() - 34) {
    //     this->jump();
    // }

    std::vector<double> inputs;

    inputs.push_back(map(this->x, this->x, 288, 0, 1));
    inputs.push_back(map(pipe.getUpperY() + pipe.getHeight(), 0, 512, 0, 1));
    inputs.push_back(map(pipe.getY(), 0, 512, 0, 1));
    inputs.push_back(map(this->y, 0, 512, 0, 1));
    inputs.push_back(map(pipe.getX(), 0, 288, 0, 1));

    std::vector<double> action = this->brain.predict(inputs);

    if (action[0] > action[1]) {
        this->jump();
    }
}

int Player::getScore() {
    return this->score;
}

NeuralNetwork Player::getBrain() {
    return this->brain;
}

double Player::getFitness() {
    return this->fitness;
}

void Player::setFitness(double fitness) {
    this->fitness = fitness;
}

void Player::kill(){
    this->dead = true;
}

bool Player::alive(){
    return !this->dead;
}

void Player::regenerate(NeuralNetwork brain){
    this->brain = brain.copy();
    this->brain.mutate(mutate);
}