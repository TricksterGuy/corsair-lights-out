#include <features.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "keylib.hpp"

FILE* output = NULL;

int main(void)
{
    output = fopen("/dev/input/ckb1/cmd", "w");
    if (!output)
    {
        printf("Unable to open input device\n");
        exit(-1);
    }

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 92; j++)
        {
            const Key& key = get_key(j, i, 0);
            if (key.name.empty()) continue;
            fprintf(output, "rgb on %s:%02x%02x%02x\n", key.name.c_str(), 0, 0, 0xFF);
            fflush(output);
            usleep(50000);
        }
    }

    return 0;
}
