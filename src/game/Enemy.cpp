#include <game/Enemy.hpp>
#include <random>

Enemy::Enemy(int offset) {
    this->offset = offset;
    this->setStartPosition();
    this->x = Engine::SCREEN_WIDTH + this->mTexture.getWidth() + this->offset;
}

Enemy::~Enemy() {
}

int Enemy::getX() {
    return this->x;
}

int Enemy::getY() {
    return this->y;
}

int Enemy::getUpperY() {
    return this->gap - this->mTexture.getHeight();
}

int Enemy::getWidth() {
    return this->mTexture.getWidth();
}

int Enemy::getHeight() {
    return this->mTexture.getHeight();
}

bool Enemy::init() {
    //this->mTexture.setBlending(SDL_BLENDMODE_BLEND);
    return this->mTexture.loadFromFile("./assets/image/pipe.png");
}

void Enemy::update() {
    this->x -= this->velocity;

    if (this->x < -this->mTexture.getWidth()) {  // Offscreen
        this->setStartPosition();                // "Generates again"
    }

    //TODO
}

void Enemy::show() {
    this->mTexture.draw(this->x, this->gap - this->mTexture.getHeight(), 0, nullptr, nullptr, SDL_FLIP_VERTICAL);
    this->mTexture.draw(this->x, this->y, 0, nullptr, nullptr, SDL_FLIP_NONE);
}

void Enemy::setStartPosition() {
    int BASEY = (Engine::SCREEN_HEIGHT * 0.79);
    this->x = Engine::SCREEN_WIDTH + this->mTexture.getWidth();
    std::random_device dev;
    std::mt19937 rng(dev());
    int upperLimit = BASEY * 0.6 - this->gapSize;
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, upperLimit);
    this->gap = dist(rng) + BASEY * 0.2;
    this->y = this->gap + this->gapSize;
}

void Enemy::reset() {
    this->setStartPosition();
    this->x = Engine::SCREEN_WIDTH + this->mTexture.getWidth() + this->offset;
}