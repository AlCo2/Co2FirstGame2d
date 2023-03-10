#include "Game.h"
#include "../TextureManager.h"
#include "../Map.h"
#include "ECS/Components.h"
#include "../Vector2D.h"

Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& player(manager.addEntity());
SDL_Event Game::event;

Game::Game()
{

}

Game::~Game()
{
    //dtor
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){

    int flags = 0;

    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING)==0){

        cout << "SubSystems Initialised!..." << endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window){
            cout << "window created" << endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "renderer created" << endl;
        }
        isRunning = true;
    }else{
        isRunning = false;
    }
    map = new Map();

    // ECS:

    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>("assets/try.png");
    player.addComponent<KeyboardController>();

}

void Game::handleEvent(){
    SDL_PollEvent(&event);
    switch(event.type){
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}


void Game::update(){
    manager.refresh();
    manager.update();
}
void Game::render(){
    SDL_RenderClear(renderer);
    map->DrawMap();
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game Cleaned" << endl;

}

