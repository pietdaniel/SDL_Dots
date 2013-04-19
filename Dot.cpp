//SDL-Dots Daniel Piet Apr 2013
#include "Dot.h"
#include "Global.h"
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <vector>

Dot::Dot() {
    y = rand() % (SCREEN_HEIGHT-40) + 20;
    x = rand() % (SCREEN_WIDTH-40) + 20;
    c.x = x - DOT_WIDTH/2;
    c.y = y - DOT_WIDTH/2;
    c.r = DOT_WIDTH /2;
    xVel = 0;
    yVel = 0;
}

double Dot::distance( int x1, int y1, int x2, int y2 ) {
    return sqrt( pow( x2 - x1, 2 ) + pow( y2 - y1, 2 ) );
}

Dot* Dot::check_collision( Circle A, std::vector<Dot*> B ) {
    while(!B.empty()) {
        Circle q = B.back()->getC(); // get vector Circle struct as q
        if( distance( A.x, A.y, q.x, q.y ) < ( A.r + q.r ) ) {
            if(A.x!=q.x && A.y != q.y) {
                return B.back();
            }
        }
        B.pop_back();
    }
    return NULL;
}

void Dot::move( Uint32 deltaTicks, std::vector<Dot*> collisions ) {

    Dot* q = check_collision(c, collisions);

    x += xVel * ( deltaTicks / 1000.f );

    if (q) {
        xVel += (x - q->getX())/(DOT_WIDTH/2);
    }

    if( ( x < 0 ) || ( x +DOT_WIDTH > SCREEN_WIDTH ) ) {   
        //Move back
        x -= xVel * ( deltaTicks / 1000.f );
        xVel=xVel*-.9;
    }

    y += yVel * ( deltaTicks / 1000.f );

    if(q) {
        yVel += (y - q->getY())/(DOT_WIDTH/2);
    }    
    
    if( ( y < 0 ) || ( y+DOT_HEIGHT > SCREEN_HEIGHT ) ) {
        y -= yVel * ( deltaTicks / 1000.f );
        yVel = yVel*-.9;
    }

    c.x = x + DOT_WIDTH/2;
    c.y = y + DOT_WIDTH/2;

}

void Dot::push() {
    yVel += rand()%3-1;
    xVel += rand()%3-1;
    if ((xVel>.0000001) || (xVel<-.0000001)) {
        xVel = xVel*.999;
    }else {
        xVel=0;
    }
    if ((yVel>.0000001) || (yVel<-.0000001)) {
        yVel = yVel*.999;
    }else {
        yVel=0;
    }
}

void Dot::setxVel(float x) {
    xVel = x;
}

void Dot::setyVel(float y) {
    yVel = y;
}

float Dot::getxVel() {
    return xVel;
}

float Dot::getyVel() {
    return yVel;
}

float Dot::getX() {
	return x;
}

float Dot::getY() {
	return y;
}
Circle Dot::getC() {
    return c;
}