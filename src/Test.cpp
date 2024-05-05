#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.




// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
    printf("VEXPlaySound:%s\n", soundName);
    wait(5, msec);
}

#pragma endregion VEXcode Generated Robot Configuration
// Include the V5 Library
#include "vex.h"

const char* getOsName()
{
#ifdef _WIN32
    return "Windows 32-bit";
#elif _WIN64
    return "Windows 64-bit";
    #elif __APPLE__ || __MACH__
    return "Mac OSX";
    #elif __linux__
    return "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #elif __unix || __unix__
    return "Unix";
    #else
    return "Other";
#endif
}
// Allows for easier use of the VEX Library
using namespace vex;

int main()
{
    printf("Ran emu\n");
    printf("OS: %s\n",getOsName());
    float t = 0;

    while (1)
    {
        Brain.Screen.clearScreen({0,0,0});
        Brain.Screen.setPenColor({ 255,255,255 });
        Brain.Screen.setPenWidth(4);
        Brain.Screen.drawPixel(sinf(t)*64+240, cosf(t) * 64 + 136);
        Brain.Screen.setFillColor({ 0,255,0 });
        Brain.Screen.drawRectangle(0, 0, 64, 64);

        Brain.Screen.setCursor(1,1);
        Brain.Screen.setFillColor({0,0,0});
        Brain.Screen.print("The quick brown jumped over the lazy dog! %d", 9);
        Brain.Screen.newLine();
        Brain.Screen.newLine();
        Brain.Screen.newLine();
        Brain.Screen.print("Vex V5 Simulator");

        t += 0.016f;
        wait(16, msec);
    }
    return 0;
}
