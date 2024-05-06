#include<cmath>
#include <cstdio>
#include<cstdint>
#include<SDL.h>
#include<SDL_image.h>

#define main vex_emu_main
#include"Test.cpp"
#undef main

int brain_thread(void* data)
{
    return vex_emu_main();
}

int main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Thread* thread = nullptr;

    while (Brain.Screen.m_running)
    {
        Brain.Screen.update();
        Brain.Screen.render();

        if (thread == nullptr)
        {
            thread = SDL_CreateThread(brain_thread, "vex_emu", nullptr);
            if (thread == NULL) {
                // Thread creation failed
                printf("SDL_CreateThread failed: %s\n", SDL_GetError());
            }
        }
        while(vex::brain::is_waiting);
        SDL_Delay(1);
    }

    SDL_Quit();

    return 0;
}