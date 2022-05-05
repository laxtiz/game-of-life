#include <esp_random.h>
#include <game.h>
#include <stddef.h>
#include <stdlib.h>

#define minium(a, b) ((a) < (b) ? (a) : (b))
#define maxium(a, b) ((a) > (b) ? (a) : (b))

void init_game(game_data_t *game, uint16_t width, uint16_t height) {
  free_game(game);
  game->width = width;
  game->height = height;
  game->cells = (uint8_t *)malloc(width * height);
  reset_game(game);
}

uint8_t nearby_cells(game_data_t *game, uint16_t x, uint16_t y) {
  uint8_t count = 0;
  uint16_t i, j;
  for (j = maxium(0, y - 1); j <= minium(game->height - 1, y + 1); j++) {
    for (i = maxium(0, x - 1); i <= minium(game->width - 1, x + 1); i++) {
      count += game->cells[j * game->width + i] != 0;
    }
  }
  return count - game->cells[y * game->width + x];
}

void update_game(game_data_t *game, game_update_func_t update_func) {
  uint8_t *cells = game->cells;
  uint8_t *next = (uint8_t *)malloc(game->width * game->height);

  uint16_t y, x, count, pos;
  for (y = 0; y < game->height; y++) {
    for (x = 0; x < game->width; x++) {
      pos = y * game->width + x;
      count = nearby_cells(game, x, y);
      next[pos] = count == 3 || (count == 2 && cells[pos]);
      if (next[pos] != cells[pos]) {
        update_func(x, y, next[pos]);
      }
    }
  }
  game->cells = next;
  free(cells);
}

void reset_game(game_data_t *game) {
  uint16_t y, x;
  for (y = 0; y < game->height; y++) {
    for (x = 0; x < game->width; x++) {
      game->cells[y * game->width + x] = esp_random() % 3 == 0;
    }
  }
}

void free_game(game_data_t *game) {
  if (game->cells)
    free(game->cells);
  game->cells = NULL;
}