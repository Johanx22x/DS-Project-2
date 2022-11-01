#ifndef LOADER_HH
#define LOADER_HH

#include <context.hh>
#include <string>

typedef void(command)(Context *);

class Command {
  std::string name;
  command *cmd;

public:
  Command(std::string name, command *cmd);
};

Command *loadCommand(std::string);

#endif // LOADER_HH
