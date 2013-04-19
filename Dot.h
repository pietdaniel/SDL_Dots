//SDL-Dots Daniel Piet Apr 2013
#ifndef _DOT_H
#define _DOT_H
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Global.h"
#include <vector>

struct Circle {
    int x, y;
    int r;
};

class Dot {
    private:
        float x, y;
        Circle c;
        float xVel, yVel;

    public:    
        Dot();
        ~Dot();
        double distance( int x1, int y1, int x2, int y2);
        Dot* check_collision( Circle A, std::vector<Dot*> B );
        void move( Uint32 deltaTicks , std::vector<Dot*> collisions );
        void push();
        void setxVel(float x);
        void setyVel(float y); 
        float getxVel();
        float getyVel();
        float getX();
        float getY();
        Circle getC();

};
#endif
