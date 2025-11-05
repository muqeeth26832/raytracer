#include "CApp.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

// Constructor (default)
CApp::CApp()
{
    isRunning=true;
    pWindow=nullptr;
    pRenderer=nullptr;
}

bool CApp::OnInit()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        return false;
    }

    pWindow=SDL_CreateWindow("Muqeeth's Raytracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

    if(pWindow!=nullptr)
    {
        pRenderer=SDL_CreateRenderer(pWindow, -1, 0);


        // init mqImage instance.
        m_image.Initialize(1280, 720, pRenderer);

        // create some color variations
        for(int x=0;x<1280;x++)
        {
            for(int y=0;y<720;y++)
            {
                double red = (static_cast<double>(x)/1280.0)*255;
                double green = (static_cast<double>(y)/720.0)*255;
                // left to right red increases
                // top to bottom green increases
                m_image.SetPixel(x, y, red, green, 0.0);
            }
        }
    }
    else
    {
        return false;
    }

    return true;
}


int CApp::OnExecute()
{
    SDL_Event event;

    if(OnInit()==false)
    {
        return -1;
    }

    while(isRunning)
    {
        while(SDL_PollEvent(&event)!=0)
        {
            OnEvent(&event);
        }

        // OnLoop();
        OnRender();
    }

    return 0;
}


void CApp::OnEvent(SDL_Event *event)
{
    if(event->type == SDL_QUIT)
    {
        isRunning=false;
    }
}

void CApp::OnLoop()
{

}

void CApp::OnRender()
{
   // set the background color to white
   SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
   SDL_RenderClear(pRenderer);

   // Display Image
   m_image.Display();

   // show the result
   SDL_RenderPresent(pRenderer);
}

void CApp::OnExit()
{
    // Tidy up SDL2 stuff
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow=nullptr;
    SDL_Quit();
}
