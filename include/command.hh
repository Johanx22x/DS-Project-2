#ifndef COMMAND_HH
#define COMMAND_HH

#include <exception>
#include <string>

typedef void(command)(class Program *);

class Command {
public:
  std::string name;
  command *cmd = nullptr;
  Command(std::string name, command *cmd) : name(name), cmd(cmd) {}
};

class CommandNotFoundException : std::exception {
  char *reason;

public:
  CommandNotFoundException(char *reason) : reason(reason) {}

  char *what() { return reason; }
};

#endif // COMMAND_HH
