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
    
    type = rand()%2;
    color = type;
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

    // if collision 
    if (q) {
        xVel += (x - q->getX())/(DOT_WIDTH/2);
    }

    // if wall
    if( ( x < 0 ) || ( x +DOT_WIDTH > SCREEN_WIDTH ) ) {   
        x -= xVel * ( deltaTicks / 1000.f );
        xVel*=-1;
    }

    y += yVel * ( deltaTicks / 1000.f );

    if(q) {
        yVel += (y - q->getY())/(DOT_WIDTH/2);
    }    
    
    if( ( y < 0 ) || ( y+DOT_HEIGHT > SCREEN_HEIGHT ) ) {
        y -= yVel * ( deltaTicks / 1000.f );
        yVel*=-1;
    }

    c.x = x + DOT_WIDTH/2;
    c.y = y + DOT_WIDTH/2;

}

void Dot::push() {
    
    if (xVel > MAX_VEL || xVel < -MAX_VEL) {
        xVel=MAX_VEL*xVel/abs(xVel);
    }
    if (yVel > MAX_VEL || yVel < -MAX_VEL) {
        yVel=MAX_VEL*yVel/abs(yVel);
    }

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

Dot* Dot::closest(std::vector<Dot*> others) {
    Dot* out = others.back();
    others.pop_back();
    float x2 = out->getX();
    float y2 = out->getY();
    float d1 = distance(x,y,x2,y2);
    float d2;

    while(!others.empty()) {
        x2 = others.back()->getX();
        y2 = others.back()->getY();
        d2 = distance(x,y,x2,y2);
        if (d2 < d1) {
            out = others.back();
        }
        others.pop_back();
    }
    return out;
}

void Dot::direction(std::vector<Dot*> others) {
    Dot* c = closest(others);
    if (type==c->getType()) {
        xVel += ((x-c->getX())*10)/pow((x-c->getX()), 2);
        yVel += ((y-c->getY())*10)/pow((y-c->getY()), 2);
    }else {
        xVel -= ((x-c->getX())*10)/pow((x-c->getX()), 2);
        yVel -= ((y-c->getY())*10)/pow((y-c->getY()), 2);
    }
}

void Dot::setxVel(float in) {
    xVel = in;
}

void Dot::setyVel(float in) {
    yVel = in;
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
void Dot::setX(float in) {
    x = in;
}
void Dot::setY(float in) {
    y = in;
}
Circle Dot::getC() {
    return c;
}
void Dot::setC(Circle in) {
    c = in;
}
int Dot::getColor() {
    return color;
}
void Dot::setColor(int in) {
    color = in;
}
int Dot::getType() {
    return type;
}
void Dot::setType(int in) {
    type = in;
}

Dot* Dot::breed() {
    Dot* out = new Dot();
    out->setC(c);
    out->setX(x);
    out->setY(y);
    out->setType(type);
    out->setColor(color);
    return out;
}