#ifndef _UTI_H_
#define _UTI_H_

#include <stddef.h>
#include <stdint.h>

typedef struct {
  const char *token;
  void (*handler)(int argc, char **argv);
} UTI_Command;

typedef struct {
  bool initialised;
  bool turn; // 0 for X, 1 for O

  // bitfields for each side where
  // 1 << (square - 'A') is the field with square set
  uint16_t noughts;
  uint16_t crosses;

  bool hasExited;
} UTI_State;
extern UTI_State g_state;

void UTI_uti(int argc, char **argv);
void UTI_position(int argc, char **argv);
void UTI_go(int argc, char **argv);
void UTI_quit(int argc, char **argv);

static UTI_Command commands[] = {
  { .token = "uti", .handler = UTI_uti },
  { .token = "position", .handler = UTI_position },
  { .token = "quit", .handler = UTI_quit },
  { .token = "go", .handler = UTI_go },
};
constexpr size_t numCommands = sizeof(commands)/sizeof(UTI_Command);

#define UTI_NULL 'X'

#endif

