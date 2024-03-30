#include "draw.h"
#include <stdlib.h>

static const tile_height = 3;
static const tile_width = 5;

void init_colors();

screen_t *init_screen(game_t *game) {
    screen_t *screen = (screen_t *)malloc(sizeof(screen_t));
    screen->tiles = (WINDOW **)malloc(game->board_size * sizeof(WINDOW *));
    screen->main_window = initscr();
    screen->game = game;

    int width = game->width;
    int i;
    for(i = 0; i < game->board_size; i++) {
        int y = i%width;
        int x = i/width;

        /* Create subwidow for each board tile */
        WINDOW *tile = subwin(screen->main_window, tile_height, tile_width, x*tile_height, y*tile_width);

        /* Set text of the tile */
        screen->tiles[i] = tile;
    }

    /* init_colors(); */

    return screen;
}
void draw_state(screen_t *screen) {
    int i;

    /* If terminal supports colors */
    if(has_colors()) {
        /* Start color mode */
        start_color();
    }

    /* init_colors(); */
    for(i = 0; i < screen->game->board_size; i++) {

        char c[1];
        c[0] = screen->game->board[i];

        if(c[0] == screen->game->mine_char) {
            wattron(screen->tiles[i], COLOR_PAIR(2));
        } else if(c[0] == screen->game->empy_char) {
            /* TODO */
        } else {
            int color_pair_index = ((c[0]-'0')%4)+3;
            printf("\rcolor pair index %c %d\n", c[0], color_pair_index);
            wattron(screen->tiles[i], COLOR_PAIR(color_pair_index));
        }
        /* set tile text */
        mvwaddstr(screen->tiles[i], 1, 2, c);
        
        /* Create box to draw the tile */
        box(screen->tiles[i], 0, 0);
    }
}

void init_colors() {
    init_pair(2, COLOR_RED, COLOR_BLACK);

    init_pair(3, COLOR_RED+1, COLOR_BLACK);
    init_pair(4, COLOR_RED+2, COLOR_BLACK);
    init_pair(5, COLOR_RED+3, COLOR_BLACK);
    init_pair(6, COLOR_RED+4, COLOR_BLACK);
    init_pair(7, COLOR_RED+5, COLOR_BLACK);
}

void terminate_screen(screen_t *screen) {
    int i;

    delwin(screen->main_window);

    for(i = 0; i < screen->game->board_size; i++) {
        delwin(screen->tiles[i]);
    }
    free(screen->tiles);
    free(screen);
}