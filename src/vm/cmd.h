#pragma once

typedef enum Cmd {
  CMD_NOOP = 0,
  CMD_END,
  CMD_PUSH_INT,
  CMD_PUSH_FLOAT,
  CMD_PUSH_POINTER,
  CMD_PLUS
} Cmd;
