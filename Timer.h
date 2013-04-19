//SDL-Dots Daniel Piet Apr 2013
#ifndef _TIMER_H
#define _TIMER_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>

class Timer {
    private:
        int startTicks;
        int pausedTicks;
        bool paused;
        bool started;

    public:
        Timer();
        void start();
        void stop();
        void pause();
        void unpause();
        int get_ticks();
        bool is_started();
        bool is_paused();
};

#endif
