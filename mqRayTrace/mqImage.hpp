#ifndef MQIMAGE_H
#define MQIMAGE_H

#include <SDL2/SDL_render.h>
#include <pthread.h>
#include <string>
#include <vector>
#include <SDL2/SDL.h>

class mqImage
{
public:
    // constructor
    mqImage();
    // destructor
    ~mqImage();

    // init
    void Initialize(const int xSize,const int ySize,SDL_Renderer *pRenderer);

    // set color of a pixel
    void SetPixel(const int x,const int y, const double red,const double green,const double blue);

    // display image
    void Display();
private:
    Uint32 ConvertColor(const double red,const double green,const double blue);
    void InitTexture();

    // arrays to store image data
    std::vector<std::vector<double>> m_rChannel;
    std::vector<std::vector<double>> m_gChannel;
    std::vector<std::vector<double>> m_bChannel;

    // dimesions of image
    int m_xSize,m_ySize;

    SDL_Renderer *m_pRenderer;
    SDL_Texture *m_pTexture;


};

#endif
