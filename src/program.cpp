#include <command.hh>
#include <program.hh>
#include <stdexcept>
#include <string>
#include <sys/types.h>

using std::string;

Program::Program() {}
Program::~Program() {}

void Program::run() {
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
      printf("Program::Error: %s\n", e.what());
    }
  }
}
