#include "mqImage.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <cstdint>
#include <vector>

// constructor
mqImage::mqImage()
{
    m_xSize=0;
    m_ySize=0;
    m_pTexture=nullptr;
}

// destructor
mqImage::~mqImage()
{
    if(m_pTexture!=nullptr)
        SDL_DestroyTexture(m_pTexture);
}

// init
void mqImage::Initialize(const int xSize,const int ySize,SDL_Renderer *pRenderer)
{
    // resize to store image data
    m_rChannel.resize(xSize,std::vector<double>(ySize,0.0));
    m_gChannel.resize(xSize,std::vector<double>(ySize,0.0));
    m_bChannel.resize(xSize,std::vector<double>(ySize,0.0));

    // store dimesions
    m_xSize=xSize;
    m_ySize=ySize;

    // store pointer to the renderer
    m_pRenderer=pRenderer;

    // texture init
    InitTexture();
}


void mqImage::SetPixel(const int x,const int y, const double red,const double green,const double blue)
{
    // check validity of x,y
    if(!(x>=0 && x<m_xSize && y>=0 && y<m_ySize))
        return;

    // set
    m_rChannel[x][y]=red;
    m_gChannel[x][y]=green;
    m_bChannel[x][y]=blue;
}

// display
void mqImage::Display()
{
    // allocate memory for a pixel buffer
    Uint32 *tempPixels = new Uint32[m_xSize*m_ySize];

    // set all 0
    memset(tempPixels,0,m_xSize*m_ySize*sizeof(Uint32));

    for(int y=0;y<m_ySize;y++)
    {
        for(int x=0;x<m_xSize;x++)
        {
            // here x changes more so better for spacialy locality
            tempPixels[(y*m_xSize)+x] = ConvertColor(m_rChannel[x][y], m_gChannel[x][y],m_bChannel[x][y]);
        }
    }

    // update texture
    SDL_UpdateTexture(m_pTexture, nullptr, tempPixels, m_xSize*sizeof(Uint32));

    // dealloac pixel buffer
    delete[] tempPixels;


    // copy texture to the renderer
    SDL_Rect scrRect,bounds;
    scrRect.x = 0;
    scrRect.y = 0;
    scrRect.w = m_xSize;
    scrRect.h = m_ySize;

    bounds = scrRect;

    SDL_RenderCopy(m_pRenderer, m_pTexture, &scrRect, &bounds);
}

// init texture
void mqImage::InitTexture()
{
    Uint32 rmask,gmask,bmask,amask;

    // check if we are using big endian or not
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask=0xff000000;
        gmask=0x00ff0000;
        bmask=0x0000ff00;
        amask=0x000000ff;
    #else
        rmask=0x000000ff;
        gmask=0x0000ff00;
        bmask=0x00ff0000;
        amask=0xff000000;
    #endif

    // Delete previous textures
    if(m_pTexture!=nullptr)
        SDL_DestroyTexture(m_pTexture);

    // create texture that will store the image
    SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

// convert color to Uint32
Uint32 mqImage::ConvertColor(const double red,const double green,const double blue)
{
    uint8_t r = static_cast<uint8_t>(red);
    uint8_t g = static_cast<uint8_t>(green);
    uint8_t b = static_cast<uint8_t>(blue);

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        Uint32 pixelColor = (r<<24)+(g<<16)+(b<<8)+255;
    #else
        Uint32 pixelColor = (255<<24)+(b<<16)+(g<<8)+r;
    #endif

    return pixelColor;
}
