#include <SDL2/SDL.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    srand(time(0));

    int cellSize = 20;
    int cols = 40, rows = 30;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Snake",
        100,
        100,
        cols * cellSize,
        rows * cellSize,
        0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    std::vector<int> snakeX = {10, 9, 8};
    std::vector<int> snakeY = {10, 10, 10};

    int dirX = 1;
    int dirY = 0;

    int foodX = rand() % cols;
    int foodY = rand() % rows;

    int score = 0;

    bool gameOver = false;
    bool running = true;

    while (running) {

        SDL_Event e;

        while (SDL_PollEvent(&e)) {

            if (e.type == SDL_QUIT)
                running = false;

            if (e.type == SDL_KEYDOWN) {

                if (e.key.keysym.sym == SDLK_UP) {
                    dirX = 0;
                    dirY = -1;
                }

                if (e.key.keysym.sym == SDLK_DOWN) {
                    dirX = 0;
                    dirY = 1;
                }

                if (e.key.keysym.sym == SDLK_LEFT) {
                    dirX = -1;
                    dirY = 0;
                }

                if (e.key.keysym.sym == SDLK_RIGHT) {
                    dirX = 1;
                    dirY = 0;
                }
            }
        }

        if (!gameOver) {

            int newX = snakeX[0] + dirX;
            int newY = snakeY[0] + dirY;

            for (size_t i = 0; i < snakeX.size(); i++) {
//detect if snakes cuurect coordinates is new 
                if (snakeX[i] == newX &&
                    snakeY[i] == newY) {

                    gameOver = true;

                    std::cout
                        << "GAME OVER! Final Score: "
                        << score
                        << std::endl;
                }
            }

            snakeX.insert(snakeX.begin(), newX);
            snakeY.insert(snakeY.begin(), newY);

            if (newX == foodX &&
                newY == foodY) {

                foodX = rand() % cols;
                foodY = rand() % rows;

                score += 10;

                std::cout
                    << "Score: "
                    << score
                    << std::endl;
            }
            else {

                snakeX.pop_back();
                snakeY.pop_back();
            }
        }

        if (!gameOver) {

            SDL_SetRenderDrawColor(
                renderer,
                0, 0, 0, 255
            );

            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(
                renderer,
                0, 255, 0, 255
            );

            for (size_t i = 0; i < snakeX.size(); i++) {

                SDL_Rect rect = {
                    snakeX[i] * cellSize,
                    snakeY[i] * cellSize,
                    cellSize,
                    cellSize
                };

                SDL_RenderFillRect(
                    renderer,
                    &rect
                );
            }

            SDL_SetRenderDrawColor(
                renderer,
                255, 0, 0, 255
            );

            SDL_Rect foodRect = {
                foodX * cellSize,
                foodY * cellSize,
                cellSize,
                cellSize
            };

            SDL_RenderFillRect(
                renderer,
                &foodRect
            );
        }
        else {

            SDL_SetRenderDrawColor(
                renderer,
                150, 0, 0, 255
            );

            SDL_RenderClear(renderer);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(150);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}

