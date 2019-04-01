# Portfolio-Project

To compile the game, cd into the Portfolio-Project directory and run "make"

First you must install the SDL libraries, on ubuntu do so by following this guide as I have it set to standard installs
Only SDL2 and SDL2-image are required

Installation Guide: https://wiki.libsdl.org/Installation

Edit the defined parameter inside of boardSize.h to change the board size.
Board sizes above around 51 will have your tile selection be almost completely off the screen
and after around 101 it becomes pretty hard to read.

Launch the game with "./scrabble" followed by a single character to choose gamemode
Enter s for singleplayer, or m for multiplayer

The datafile is called "words_alpha.txt" and is located inside resources. I did not upload it, but you can download it here: https://github.com/jonathanerskine24/words_alpha.txt

Code Citing:

I modified this maxheap to store my move Values: https://gist.github.com/aatishnn/8265656
I followed this guide for how to set up a basic SDL program: http://lazyfoo.net/tutorials/SDL/


Known bugs:
Multiplayer player 2 tiles do not highlight when selected. They still do select though and function normally, you just cannot tell what you selected
