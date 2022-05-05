#ifndef _GAME_H_
#define _GAME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct {
  uint8_t *cells;
  uint16_t width;
  uint16_t height;
} game_data_t;

typedef void (*game_update_func_t)(uint16_t x, uint16_t y, uint8_t cell);

void init_game(game_data_t *game, uint16_t width, uint16_t height);
void update_game(game_data_t *game, game_update_func_t update_func);
void reset_game(game_data_t *game);
void free_game(game_data_t *game);

#ifdef __cplusplus
}
#endif

#endif