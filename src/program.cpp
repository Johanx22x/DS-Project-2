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
    string command;
    std::getline(std::cin, command);

    try {
      Command *cmd = this->commands->at(command);
      cmd->cmd(this);
    } catch (std::out_of_range e) {
      printf("%s\n", e.what());
    }
  }
}
