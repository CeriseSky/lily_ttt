#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uti.h"

int main() {
  char *command = nullptr;
  size_t commandLen = 0;

  while(!g_state.hasExited) {
    ssize_t numRead = getline(&command, &commandLen, stdin);
    if(numRead < 0) {
      fprintf(stderr, "Failed to read from stdin\n");
      return EXIT_FAILURE;
    }
    command[--numRead] = '\0'; // getline returns the \n but not the null
                               // which is the opposite of what I want

    if(!strlen(command)) {
      fprintf(stderr, "Empty commands are not supported\n");
      return EXIT_FAILURE;
    }

    char *savePtr;
    char **tokens = nullptr;
    size_t tokensLen = 0;
    for(char *token = strtok_r(command, " \n\r", &savePtr);
        token; token = strtok_r(nullptr, " \n\r", &savePtr)) {
      tokens = realloc(tokens, ++tokensLen);
      tokens[tokensLen - 1] = token;
    }

    bool handled = false;
    for(size_t i = 0; i < numCommands; i++)
      if(!strcmp(tokens[0], commands[i].token)) {
        commands[i].handler(tokensLen, tokens);
        handled = true;
        break;
      }

    if(!handled) {
      printf("uci_no\n");
    }

    free(tokens);
  }

  return EXIT_SUCCESS;
}

