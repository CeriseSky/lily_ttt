#include "lily.h"
#include "uti.h"
#include <stdio.h>

size_t lily_getMoves(uint16_t noughts, uint16_t crosses,
                     char *output) {
  uint16_t allPieces = noughts | crosses;
  size_t count = 0;
  for(char i = 'A'; i <= 'I'; i++) {
    uint16_t square = 1 << (i - 'A');
    if(!(square & allPieces)) {
      output[count] = i;
      count++;
    }
  }
  return count;
}

// remove the turn parameter because noughts and crosses can just switch
// and assume crosses is the player
int8_t lily_evaluate(uint16_t noughts, uint16_t crosses, char *bestmove) {
  char legalmoves[9] = {0};
  size_t numMoves = lily_getMoves(noughts, crosses, legalmoves);
  int8_t bestscore = -100;
  if(bestmove)
    *bestmove = UTI_NULL;

  if(lily_hasWon(crosses)) return 100;
  if(lily_hasWon(noughts)) return -100;
  if(!numMoves) return 0;

  for(size_t i = 0; i < numMoves; i++) {
    uint16_t alteredCrosses = crosses | 1 << (legalmoves[i] - 'A');
    int8_t score;

    if(lily_hasWon(alteredCrosses)) {
      score = 100;
    } else
      score = -lily_evaluate(alteredCrosses, noughts, nullptr);

    if(score >= bestscore) {
      bestscore = score;
      if(bestmove) *bestmove = legalmoves[i];
    }
  }

  return bestscore;
}

bool lily_hasWon(uint16_t attacker) {
  uint16_t horizontal[3] = { 0b111000000, 0b000111000, 0b000000111 };
  uint16_t vertical[3] = { 0b001001001, 0b010010010, 0b100100100 };
  uint16_t diagonal[2] = { 0b100010001, 0b001010100 };

  for(int i = 0; i < 2; i++) {
    if((attacker & horizontal[i]) == horizontal[i] ||
       (attacker & vertical[i]) == vertical[i] ||
       (attacker & diagonal[i]) == diagonal[i])
      return true;
  }

  if((attacker & horizontal[2]) == horizontal[2] ||
     (attacker & vertical[2]) == vertical[2])
    return true;

  return false;
}

