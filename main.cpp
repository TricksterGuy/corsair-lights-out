#include <features.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <ncurses.h>
#include <map>

#include "keylib.hpp"

class LightsOutKey
{
    public:
        LightsOutKey(int i, int posx, int posy, int w, int h, int key, bool ison = false) :
            index(i), x(posx), y(posy), width(w), height(h), key_id(key), on(ison) {}
        void TurnOn(bool force = false);
        void TurnOff(bool force = false);
        void Toggle(bool neighbors = true);
        bool IsOn() const {return on;}
    private:
        int index;
        int x;
        int y;
        int width;
        int height;
        int key_id;
        bool on;
};

#define NUM_KEYS 45
LightsOutKey keys[NUM_KEYS] =
{
    {0, 0, 0, 4, 1, 34}, {1, 1, 0, 4, 1, 35}, {2, 2, 0, 4, 1, 36}, {3, 3, 0, 4, 1, 37}, {4, 4, 0, 4, 1, 38}, {5, 5, 0, 4, 1, 39}, {6, 6, 0, 4, 1, 40}, {7, 7, 0, 4, 1, 41}, {8, 8, 0, 4, 1, 42}, {9, 9, 0, 4, 1, 43}, {10, 10, 0, 4, 1, 44}, {11, 11, 0, 4, 1, 45},
    {12, 0, 1, 4, 1, 58}, {13, 1, 1, 4, 1, 59}, {14, 2, 1, 4, 1, 60}, {15, 3, 1, 4, 1, 61}, {16, 4, 1, 4, 1, 62}, {17, 5, 1, 4, 1, 63}, {18, 6, 1, 4, 1, 64}, {19, 7, 1, 4, 1, 65}, {20, 8, 1, 4, 1, 66}, {21, 9, 1, 4, 1, 67}, {22, 10, 1, 4, 1, 68}, {23, 11, 1, 4, 1, 69},
    {24, 0, 2, 4, 1, 82}, {25, 1, 2, 4, 1, 83}, {26, 2, 2, 4, 1, 84}, {27, 3, 2, 4, 1, 85}, {28, 4, 2, 4, 1, 86}, {29, 5, 2, 4, 1, 87}, {30, 6, 2, 4, 1, 88}, {31, 7, 2, 4, 1, 89}, {32, 8, 2, 4, 1, 90}, {33, 9, 2, 4, 1, 91}, {34, 10, 2, 4, 1, 92},
    {35, 0, 3, 4, 1, 101}, {36, 1, 3, 4, 1, 102}, {37, 2, 3, 4, 1, 103}, {38, 3, 3, 4, 1, 104}, {39, 4, 3, 4, 1, 105}, {40, 5, 3, 4, 1, 106}, {41, 6, 3, 4, 1, 107}, {42, 7, 3, 4, 1, 108}, {43, 8, 3, 4, 1, 109}, {44, 9, 3, 4, 1, 110},
};

int max_per_row[4] =
{
    12,
    12,
    11,
    10,
};

std::map<char, int> key_id =
{
    {'1', 0}, {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4}, {'6', 5}, {'7', 6}, {'8', 7}, {'9', 8}, {'0', 9}, {'-', 10}, {'=', 11},
    {'q', 12}, {'w', 13}, {'e', 14}, {'r', 15}, {'t', 16}, {'y', 17}, {'u', 18}, {'i', 19}, {'o', 20}, {'p', 21}, {'[', 22}, {']', 23},
    {'a', 24}, {'s', 25}, {'d', 26}, {'f', 27}, {'g', 28}, {'h', 29}, {'j', 30}, {'k', 31}, {'l', 32}, {';', 33}, {'\'', 34},
    {'z', 35}, {'x', 36}, {'c', 37}, {'v', 38}, {'b', 39}, {'n', 40}, {'m', 41}, {',', 42}, {'.', 43}, {'/', 44},
};

void LightsOutKey::TurnOn(bool force)
{
    if (on && !force) return;
    on = true;
    Keyboard::Instance().KeyOn(positions[key_id].name);
}

void LightsOutKey::TurnOff(bool force)
{
    if (!on && !force) return;
    on = false;
    Keyboard::Instance().KeyOff(positions[key_id].name);
}

void LightsOutKey::Toggle(bool neighbors)
{
    on ? TurnOff() : TurnOn();
    if (neighbors)
    {
        // Adjacent keys
        if (x > 0)
            keys[index - 1].Toggle(false);
        if (x + 1 < max_per_row[y])
            keys[index + 1].Toggle(false);
        // Upper 2 keys
        if (y > 0)
        {
            if (x + 1 < max_per_row[y - 1])
                keys[index - max_per_row[y - 1] + 1].Toggle(false);
            if (x < max_per_row[y - 1])
                keys[index - max_per_row[y - 1]].Toggle(false);
        }
        // Lower 2 keys
        if (y < 3)
        {
            if (x < max_per_row[y + 1])
                keys[index + max_per_row[y]].Toggle(false);
            if (x > 0 && x < max_per_row[y])
                keys[index + max_per_row[y] - 1].Toggle(false);
        }
    }
}

int main(int argc, char** argv)
{
    int moves = 5;
    int moves_taken = 0;
    if (argc >= 2)
    {
        moves = strtol(argv[1], NULL, 10);
        if (moves == 0) moves = 5;
    }

    srand(time(NULL));

    Keyboard::Instance().StartBatch();
    for (int i = 0; i < NUM_KEYS; i++)
    {
        keys[i].TurnOff(true);
    }
    Keyboard::Instance().EndBatch();

    Keyboard::Instance().StartBatch();
    for (int i = 0; i < moves; i++)
    {
        int x = rand() % NUM_KEYS;
        keys[x].Toggle();
    }
    Keyboard::Instance().EndBatch();

    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);


    while(1)
    {
        int c = getch();
        if (c == 10)
        {
            endwin();
            Keyboard::Instance().AllOff();
            return 0;
        }
        if (key_id.find(c) == key_id.end()) continue;
        moves_taken++;

        int id = key_id[c];
        LightsOutKey& key = keys[id];

        Keyboard::Instance().StartBatch();
        key.Toggle();
        Keyboard::Instance().EndBatch();

        bool win = true;
        for (int i = 0; i < NUM_KEYS; i++)
        {
            if (keys[i].IsOn())
            {
                win = false;
                break;
            }
        }

        if (win)
        {
            break;
        }
    }

    endwin();
    printf("You win, moves taken: %d\n", moves_taken);
    Keyboard::Instance().AllOff();
    return 0;
}
