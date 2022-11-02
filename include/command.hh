#ifndef COMMAND_HH
#define COMMAND_HH

#include <context.hh>
#include <string>

typedef void(command)(Context *);

class Command {
  std::string name;
  command *cmd;

public:
  Command(std::string name, command *cmd);
};

#endif // COMMAND_HH
