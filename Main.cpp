//SDL-Dots Daniel Piet Apr 2013
#include "Dot.h"
#include "Timer.h"
#include "Global.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <vector>
#include <iostream>

#pragma comment(lib,"SDL.lib")
#pragma comment(lib,"SDLmain.lib")
#pragma comment(lib,"SDL_image.lib")

SDL_Surface *dot = NULL;
SDL_Surface *screen = NULL;
std::vector<Dot*> vdots;

SDL_Event event;

SDL_Surface *load_image( std::string filename ) {

    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL ) {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_FreeSurface( loadedImage );
        if( optimizedImage != NULL ) {
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL ) {
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init() {

    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
        return false;
    }

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL ) {
        return false;
    }

    SDL_WM_SetCaption( "SDL Dots", NULL );

    for (int i = 0;i<DOT_NUM;++i) {
        vdots.push_back(new Dot());
    }

    return true;
}

bool load_files() {

    dot = load_image( "dot.bmp" );

    if( dot == NULL ) {
        return false;
    }

    return true;
}

void clean_up() {
    SDL_FreeSurface( dot );
    SDL_Quit();
}

void draw() {
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

    for (int q=0;q<vdots.size();++q) {
        apply_surface( (int)vdots[q]->getX(), (int)vdots[q]->getY(), dot, screen );
    }
}

void mechanics(Timer* delta) {
    for (int z = 0;z<vdots.size();++z) {
        vdots[z]->push();
        std::vector<Dot*> collisions;
        collisions = vdots;
        collisions.erase(collisions.begin()+z);
        vdots[z]->move(delta->get_ticks(), collisions);
    }

    
}


int mainloop() {
    bool quit = false;
    Timer* delta = new Timer();
    
    delta->start();

    while( quit == false ) {
        while( SDL_PollEvent( &event ) ) {
            if( event.type == SDL_QUIT ) {
                quit = true;
            }
        }

        mechanics(delta);
        delta->start();
        
        draw();

        if( SDL_Flip( screen ) == -1 ) {
            return 3; // ERROR 3 flip failed
        }
    }
    return 0;
}


int main( int argc, char* args[] ) {

    if( init() == false ) {
        return 1; // ERROR 1 init failed
    }

    if( load_files() == false ) {
        return 2; // ERROR 2 file load failed
    }

    if (mainloop() != 0) {
        return 3;
    }

    clean_up();

    return 0;
}
