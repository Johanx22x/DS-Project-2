#ifndef COMMAND_HH
#define COMMAND_HH

#include <exception>
#include <string>

// command type definition, describes a command function pointer
typedef void(command)(class Program *);

/**
 * Command class
 * This class is used to store a command function pointer and its name
 *
 * @author Aaron Gonzalez
 * @version 1.0
 */
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
