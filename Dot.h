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
        int color; // 0 red 1 green 2 yellow 3 blue
        int type; // 0 1

    public:    
        Dot();
        ~Dot();
        double distance( int x1, int y1, int x2, int y2);
        Dot* check_collision( Circle A, std::vector<Dot*> B );
        void direction(std::vector<Dot*> others);
        Dot* closest(std::vector<Dot*> others);
        void move( Uint32 deltaTicks , std::vector<Dot*> collisions );
        void push();
        void setxVel(float in);
        void setyVel(float in); 
        float getxVel();
        float getyVel();
        float getX();
        float getY();
        void setX(float in);
        void setY(float in);
        int getColor();
        void setColor(int in);
        Circle getC();
        void setC(Circle in);
        int getType();
        void setType(int in);
        Dot* breed();
        

};
#endif
