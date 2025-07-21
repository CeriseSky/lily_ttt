#include "uti.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "lily.h"

UTI_State g_state = {0};

void UTI_uti(int argc, char **argv) {
  printf("id name Lily\n"
         "id author CeriseSky\n"
         "utiok\n");

  g_state.initialised = true;
}

void UTI_position(int argc, char **argv) {
  if(!g_state.initialised || argc > 2) {
    printf("uti_no\n");
    return;
  }

  g_state.crosses = 0;
  g_state.noughts = 0;
  g_state.turn = 0;

  if(argc == 1)
    return;

  char *position = argv[1];
  for(size_t i = 0; i < strlen(position); i++) {
    uint16_t *board = g_state.turn ? &g_state.noughts : &g_state.crosses;
    uint16_t oldBoard = g_state.crosses | g_state.noughts;
    g_state.turn = !g_state.turn;

    if(position[i] == UTI_NULL)
      continue;

    if(position[i] < 'A' || position[i] > 'I') {
      printf("uti_no\n");
      return;
    }

    uint16_t move = 1 << (position[i] - 'A');
    if(oldBoard & move) {
      printf("uti_no\n");
      return;
    }

    *board |= move;
  }
}

void UTI_quit(int argc, char **argv) {
  g_state.hasExited = true;
}

void UTI_go(int argc, char **argv) {
  uint16_t attacker = g_state.turn ? g_state.noughts : g_state.crosses;
  uint16_t defender = !g_state.turn ? g_state.noughts : g_state.crosses;
  char bestmove;
  lily_evaluate(defender, attacker, &bestmove);
  printf("bestmove %c\n", bestmove);
}

