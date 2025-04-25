#include <stdio.h>
#include <string.h>
#include "game.h"

int main(void) {
    Game game;
    init_game(&game);

    char line[64];
    while (1) {
        draw_game(&game);
        printf("Enter move (e.g. T1 0 T4 or T3 0 F2), or Q to quit:\n> ");
        if (!fgets(line, sizeof(line), stdin)) break;
        if (line[0]=='Q' || line[0]=='q') break;

        char srcType, dstType;
        int fc, fp, tc;
        if (sscanf(line, "%c%d %d %c%d",
                   &srcType, &fc, &fp, &dstType, &tc) == 5
            && srcType=='T'
            && (dstType=='T' || dstType=='F')) {
            int dest = (dstType=='T' ? tc : 100 + tc);
            if (!perform_move(&game, fc, fp, dest)) {
                printf("Illegal move!\n");
            }
            } else {
                printf("Bad input format.\n");
            }
    }

    return 0;
}
