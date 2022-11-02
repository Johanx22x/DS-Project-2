#ifndef COMMAND_HH
#define COMMAND_HH

#include <string>

typedef void(command)(class Program *);

class Command {
  std::string name;
  command *cmd;

public:
  Command(std::string name, command *cmd);
};

#endif // COMMAND_HH
