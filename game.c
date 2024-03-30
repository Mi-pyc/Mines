#include "game.h"
#include <stdlib.h>

void set_board_to(game_t *game, char c);
void set_mines(game_t *game, int mine_count);
void set_numbers_around(game_t *game, int position);

game_t *init_game(int width, int height, int mine_count) {
    game_t *game = (game_t *)malloc(sizeof(game_t));
    
    game->board_size = width*height;
    game->width = width;
    game->height = height;
    game->mine_count = mine_count;
    
    game->board = (char *)malloc(game->board_size * sizeof(char));

    game->mine_char = 'x';
    game->empy_char = ' ';

    set_board_to(game, game->empy_char);
    set_mines(game, mine_count);

    return game;
}

void set_board_to(game_t *game, char c) {
    int i;
    for(i = 0; i < game->board_size; i++) {
        game->board[i] = c;
    }
}

void set_mines(game_t *game, int mine_count) {
    srand(time(NULL));

    int counter = 0;
    while (counter < mine_count) {
        /* random position for mine */
        int pos = rand() % (game->board_size);
        if(game->board[pos] != game->mine_char) {
            game->board[pos] = game->mine_char;
            /* increment numbers around new mine */
            set_numbers_around(game, pos);
            /* counter is initialized only if new mine was placed */
            counter++;
        }
    }
}

void set_numbers_around(game_t *game, int position) {
    int k, i;
    int width = game->width;
    int board_size = game->board_size;

    for(k = position-width; k <= position+width; k += width) {
        /* check bounds */
        if(k < 0 || k >= board_size) continue;

        for(i = k-1; i <= k + 1; i++) {
            /* check if line didn't overflow/underflow */
            if(k/width != i/width) continue;

            /* check bounds */
            if(i >= 0 && i != position) {
                
                if(game->board[i] != game->mine_char) {
                    if(game->board[i] == game->empy_char) {
                        /* if tile is empty set it to one */
                        game->board[i] = '1';
                    } else {
                        /* otherwise incremet it */
                        game->board[i]++;
                    }
                }
            }
        }
    }
}

void play_position(game_t *game, int arg_pos) {}
void terminate_game(game_t *game) {
    free(game->board);
    free(game);
}