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
void playVexcodeSound(const char* soundName) {
    printf("VEXPlaySound:%s\n", soundName);
    wait(5, msec);
}

#pragma endregion VEXcode Generated Robot Configuration

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       {author}                                                  */
/*    Created:      {date}                                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"

// Allows for easier use of the VEX Library
using namespace vex;

int main() 
{
    printf("Ran emu\n");
    float t = 0;

    while (1)
    {
        Brain.Screen.clearScreen({0,0,0});
        Brain.Screen.setPenColor({ 255,255,255 });
        Brain.Screen.setPenWidth(4);
        Brain.Screen.drawPixel(sinf(t)*64+240, cosf(t) * 64 + 136);
        Brain.Screen.setFillColor({ 0,255,0 });
        Brain.Screen.drawRectangle(0, 0, 64, 64);

        Brain.Screen.drawLine(64, 64, 128, 128);

        t += 0.016f;
        wait(0.016, seconds);
    }
    return 0;
}
