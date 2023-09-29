#include <SDL.h>
#include <iostream>
#include <vector>

// Tamaño de la cuadrícula
const int WIDTH = 800;
const int HEIGHT = 600;
const int CELL_SIZE = 10;

// Función para inicializar la cuadrícula con células vivas y muertas al azar
void initGrid(std::vector<std::vector<bool>>& grid) {
    for (int i = 0; i < HEIGHT / CELL_SIZE; ++i) {
        std::vector<bool> row;
        for (int j = 0; j < WIDTH / CELL_SIZE; ++j) {
            row.push_back(rand() % 2 == 0);
        }
        grid.push_back(row);
    }
}

// Función para actualizar la cuadrícula en función de las reglas del Juego de la Vida
void updateGrid(std::vector<std::vector<bool>>& grid) {
    std::vector<std::vector<bool>> newGrid = grid;

    for (int i = 0; i < HEIGHT / CELL_SIZE; ++i) {
        for (int j = 0; j < WIDTH / CELL_SIZE; ++j) {
            int neighbors = 0;

            // Calcular el número de vecinos vivos
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx == 0 && dy == 0) continue; // No contar la célula actual
                    int x = i + dx;
                    int y = j + dy;
                    if (x >= 0 && x < HEIGHT / CELL_SIZE && y >= 0 && y < WIDTH / CELL_SIZE && grid[x][y]) {
                        neighbors++;
                    }
                }
            }

            // Aplicar las reglas del Juego de la Vida
            if (grid[i][j]) {
                if (neighbors < 2 || neighbors > 3) {
                    newGrid[i][j] = false;
                }
            } else {
                if (neighbors == 3) {
                    newGrid[i][j] = true;
                }
            }
        }
    }

    grid = newGrid;
}

int SDL_main(int argc, char* argv[]) {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Crear una ventana
    SDL_Window* window = SDL_CreateWindow("Juego de la Vida", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Crear un renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Inicializar la cuadrícula
    std::vector<std::vector<bool>> grid;
    initGrid(grid);

    // Bucle principal
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Actualizar la cuadrícula
        updateGrid(grid);

        // Limpiar el renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dibujar las células vivas
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < HEIGHT / CELL_SIZE; ++i) {
            for (int j = 0; j < WIDTH / CELL_SIZE; ++j) {
                if (grid[i][j]) {
                    SDL_Rect cellRect = { j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE };
                    SDL_RenderFillRect(renderer, &cellRect);
                }
            }
        }

        // Actualizar la ventana
        SDL_RenderPresent(renderer);

        // Pequeña pausa para controlar la velocidad de la simulación
        SDL_Delay(100);
    }

    // Liberar recursos y salir
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
