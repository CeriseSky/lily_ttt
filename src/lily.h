#ifndef _LILY_H_
#define _LILY_H_

#include <stdint.h>
#include <stddef.h>

// returns number of available moves
size_t lily_getMoves(uint16_t noughts, uint16_t crosses,
                     char *output);

// returns the score of the position from crosses' perspective (higher is better)
int8_t lily_evaluate(uint16_t noughts, uint16_t crosses, char *bestmove);

bool lily_hasWon(uint16_t attacker);

#endif

