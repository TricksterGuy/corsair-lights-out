corsair-lights-out
==================

What is it
----------

A simple game to showcase the linux driver from ccMSC/ckb (and a starter project for me),  When the program is ran several keys are lit up and you must turn them all off.  When a key is pressed the state of the led and its 6 neighboring keys is toggled.
You can modify how easy / hard the game is by passing in a number for the number of moves it should take (maximum) by default it should take 5 moves or less to solve.

Building for Linux
------------------

You can either use the provided Makefile, or CodeBlocks to build the program.  The only dependency thats required is ncurses

Usage and Rules
---------------

make sure you have the linux daemon from ccMSC/ckb running.
./corsair-lights-out [max_moves=5]

You then press keys to turn lights on/off.
The keys in the game are the following

1 2 3 4 5 6 7 8 9 0 - =
q w e r t y u i o p [ ]
a s d f g h j k l ; '
z x c v b n m , . /

When a key is pressed the led of it and its neighbors is toggled

For instance if I press 'G' then T, Y, F, G, H, V, B are switched from on/off

You win if all of the leds of the keys are turned off.


