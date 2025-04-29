#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>



#include "game.c"

int main(void) {


    Game game;
    init_game(&game);

    char line[64];
    while (1) {
        draw_game(&game);
        printf("Enter move (e.g. T1 0 T4 or T3 0 F2), or Q to quit:\n> ");

        if (!fgets(line, sizeof(line), stdin))
            break;

        // strip newline
        line[strcspn(line, "\r\n")] = '\0';
        if (line[0] == '\0')
            continue;

        // split into three tokens
        char *tok1 = strtok(line, " \t");
        char *tok2 = strtok(NULL, " \t");
        char *tok3 = strtok(NULL, " \t");

        if (!tok1) continue;
        // Quit?
        if (toupper(tok1[0]) == 'Q')
            break;

        if (!tok2 || !tok3) {
            printf("Bad input format.   →  Use e.g.  T2 0 T4\n\n");
            continue;
        }

        // strip any trailing ':' on the first/third token (in case you typed "T2:")
        size_t L1 = strlen(tok1);
        if (tok1[L1-1] == ':') tok1[L1-1] = '\0';
        size_t L3 = strlen(tok3);
        if (tok3[L3-1] == ':') tok3[L3-1] = '\0';

        // parse them
        char srcType = toupper(tok1[0]);
        int fc = atoi(tok1+1);
        int fp = atoi(tok2);
        char dstType = toupper(tok3[0]);
        int tc = atoi(tok3+1);

        // sanity‐check
        if (srcType != 'T' || (dstType!='T' && dstType!='F')) {
            printf("Bad input format.   →  Use T# pos T# or F#\n\n");
            continue;
        }

        // compute our “to_col” encodingT2
        int dest = (dstType=='T' ? tc : 100 + tc);

        // DEBUG: echo what we parsed
        printf("DEBUG: moving from %c%d at pos %d to %c%d  (internal dest=%d)\n",
               srcType, fc, fp, dstType, tc, dest);

        if (!perform_move(&game, fc, fp, dest)) {
            printf("Illegal move!  That move didn\'t satisfy the Yukon rules.\n\n");
        }
    }

    return 0;
}
