#include <iostream>
#include <sstream>
#include <vector>

#include "engine/engine.hpp"
#include "game/Enemy.hpp"
#include "game/Player.hpp"
#include "neural-network/auxiliar.hpp"

bool loadMedia();
void render();
void close();
void update();
void restart();
void nextGeneration();

bool gameOver = false;
bool pause = false;

LTexture gFPSTextTexture;
LTexture generationTexture;
LTexture bestScoreTexture;

LTexture bg;
LTexture fg;

const int BASEY = Engine::SCREEN_HEIGHT * 0.79;
// BASE_SHIFT = base.png width and background.png width
const int BASE_SHIFT = 336 - 288;

const int ENEMIESAMMOUT = 2;
int baseX = 0;

//Player player;
std::vector<Enemy *> enemies;

const int TOTALPOPULATION = 500;
std::vector<Player *> allBirds;
std::vector<Player *> activeBirds;
int generation = 0;
int bestScore = 0;
int deads = 0;

int main(int argc, char **argv) {
    if (!Engine::init()) {
        std::cout << "Initialization failed!" << std::endl;
    } else {
        // load();
        if (!loadMedia()) {
            std::cout << "Failed to load media!" << std::endl;
        } else {
            //Quit flag
            bool quit = false;
            //Event handler
            SDL_Event e;

            //Set text color as black
            SDL_Color textColor = {255, 255, 255, 255};

            //The frames per second timer
            LTimer fpsTimer;

            //In memory text stream
            std::stringstream timeText;
            std::stringstream generationText;
            std::stringstream bestScoreText;

            //Start counting frames per second
            int countedFrames = 0;
            fpsTimer.start();

            while (!quit) {
                //Handle events on qeue
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {  //User request quit
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {  //User press a key
                        switch (e.key.keysym.sym) {
                            case SDLK_UP:
                                // player.jump();
                                break;
                            case SDLK_r:
                                restart();
                                break;
                            case SDLK_p:
                                pause = !pause;
                                break;
                            default:
                                break;
                        }
                    }
                }

                //Calculate and correct fps
                float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
                if (avgFPS > 2000000) {
                    avgFPS = 0;
                }

                //Set text to be rendered
                timeText.str("");
                timeText << "FPS: " << avgFPS;

                generationText.str("");
                generationText << "Generation: " << generation;

                bestScoreText.str("");
                bestScoreText << "Best Score: " << bestScore;

                //Render text
                if (!gFPSTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor)) {
                    std::cout << "Unable to render FPS texture!" << std::endl;
                }

                if (!generationTexture.loadFromRenderedText(generationText.str().c_str(), textColor)) {
                    std::cout << "Unable to render generation texture!" << std::endl;
                }

                if (!bestScoreTexture.loadFromRenderedText(bestScoreText.str().c_str(), textColor)) {
                    std::cout << "Unable to render bestScoreTexture texture!" << std::endl;
                }

                if (!gameOver && !pause) {
                    // Update everything
                    update();
                }

                // Clear screen
                SDL_SetRenderDrawColor(Engine::gRenderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderClear(Engine::gRenderer);

                // Render everything
                render();

                //Update screen
                SDL_RenderPresent(Engine::gRenderer);

                ++countedFrames;
            }
        }
    }

    close();
    Engine::close();

    std::cout << "[PASS]" << std::endl;
    return 0;
}

bool loadMedia() {
    bool assetsStatus = true;

    assetsStatus &= Engine::loadMedia();

    assetsStatus &= bg.loadFromFile("./assets/image/background-day.png");
    assetsStatus &= fg.loadFromFile("./assets/image/base.png");

    for (int i = 0; i < ENEMIESAMMOUT; i++) {
        enemies.push_back(new Enemy(i * 200));
        assetsStatus &= enemies[i]->init();
    }

    for (int i = 0; i < TOTALPOPULATION; i++) {
        allBirds.push_back(new Player());
        assetsStatus &= allBirds[i]->init();
    }

    return assetsStatus;
}

void render() {
    bg.draw(0, 0);

    for (auto &enemy : enemies) {
        enemy->show();
    }

    for (auto &bird : allBirds) {
        if (bird->alive()) {
            bird->show();
        }
    }

    fg.draw(baseX, BASEY);
    gFPSTextTexture.draw(10, 20);
    generationTexture.draw(10, 40);
    bestScoreTexture.draw(10, 60);
}

void update() {
    baseX = -((-baseX + 4) % BASE_SHIFT);

    for (auto &enemy : enemies) {
        enemy->update();
        for (auto &bird : allBirds) {
            if (bird->alive()) {
                bird->update();
                if (bird->getScore() > bestScore) bestScore = bird->getScore();
                if (bird->collide(*enemy)) {
                    bird->kill();
                    deads++;
                }
            }

            if ((enemies[0]->getX() < enemies[1]->getX())) {
                bird->think(*enemies[0]);
            } else {
                bird->think(*enemies[1]);
            }
        }
    }

    if (deads == TOTALPOPULATION) {
        gameOver = true;
        nextGeneration();
        restart();
    }
}

void close() {
    bg.free();
    fg.free();
}

void restart() {
    // player.reset();
    for (auto &enemy : enemies) {
        enemy->reset();
    }
    for (auto &bird : allBirds) {
        bird->reset();
    }
    gameOver = false;
    deads=0;
}

void nextGeneration() {
    generation++;
    normalizeFitness(allBirds);
    generate(allBirds);
    restart();
}