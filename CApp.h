#ifndef CAPP_H
#define CAPP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "./mqRayTrace/mqImage.hpp"

class CApp
{
    public:
        CApp();

        int OnExecute();
        bool OnInit();
        void OnEvent(SDL_Event *event);
        void OnLoop();
        void OnRender();
        void OnExit();

    private:
        // mqImage class to store image
        mqImage m_image;


        // SDL2 stuff
        bool isRunning;
        SDL_Window *pWindow;
        SDL_Renderer *pRenderer;

};

#endif
