#ifndef SPRITECOMPONENT_H_INCLUDED
#define SPRITECOMPONENT_H_INCLUDED

#pragma once

#endif // SPRITECOMPONENT_H_INCLUDED


#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

public:
    SpriteComponent() = default;
    SpriteComponent(const char* path){
        setTex(path);
    }

    void setTex(const char* path){
        texture = TextureManager::LoadTexture(path);
    }
    void init() override{
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.h = srcRect.w = 32;
        destRect.h = destRect.w = 64;
    }
    void update() override{
        destRect.x = (int)transform->position.x;
        destRect.y = (int)transform->position.y;
    }
    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect);
    }
};
