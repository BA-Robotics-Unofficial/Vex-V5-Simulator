# Vex V5 Simulator

Vex V5 Simulator, is just that, a simulator for the Vex V5 Brain. It (will) support running both blocks and c++ code, 
and possibly python code. It is written in C++ and uses the [SDL2](https://www.libsdl.org/) library for rendering. 
Things that will be simulated include the brain and the controller. There are plans to add support for the rest of the 
V5 components.

## Features

- [x] Basic rendering of some drawing primitives
- [x] Multithreaded rendering

## Building

You should just be able to run `cmake .` at least on windows. I left the libraries in the git repo even though i've been
told not to do that. You're welcome! 🥰

## Running

If you want to mess around with it in its current state you can just edit the Test.cpp file.