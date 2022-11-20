#include <command.hh>
#include <program.hh>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <time.h>

using std::string;

Program::Program() {}
Program::~Program() {}

void Program::run() {
  srand(time(0));
  while (true) {
    printf(">> ");

    string command;
    std::getline(std::cin, command, '\n');

    try {
      Command *cmd = this->commands->at(command);

      if (cmd == nullptr) {
        puts("that command doesn't exist");
        continue;
      }

      cmd->cmd(this);
    } catch (std::out_of_range e) {
      printf("Program::Error: %s\nYou can use the 'help' command to see a list of commands.\n", e.what());
    }
  }
}
