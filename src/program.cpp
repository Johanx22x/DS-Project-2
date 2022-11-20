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
  std::cout << "\033[2J\033[1;1H\n\u001b[0;31m"
"██████╗  █████╗ ███╗   ██╗ █████╗     ██████╗  ██████╗  █████╗ ██████╗ \n" 
"██╔══██╗██╔══██╗████╗  ██║██╔══██╗    ██╔══██╗██╔═══██╗██╔══██╗██╔══██╗\n"
"██████╔╝███████║██╔██╗ ██║███████║    ██████╔╝██║   ██║███████║██║  ██║\n"
"██╔═══╝ ██╔══██║██║╚██╗██║██╔══██║    ██╔══██╗██║   ██║██╔══██║██║  ██║\n"
"██║     ██║  ██║██║ ╚████║██║  ██║    ██║  ██║╚██████╔╝██║  ██║██████╔╝\n"
"╚═╝     ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝    ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚═════╝ \n"
"\u001b[0m";

  std::cout << 
"╔═════════════════════════════════════════════════════════════════════╗\n"
"║                        Welcome to Pana Road                         ║\n"
"║                                                                     ║\n"
"║    This game consists of meeting friends through graphs, which      ║\n"
"║    have nodes and arcs through which people must pass.              ║\n"
"║                                                                     ║\n"
"║    To get help on how to use the program you can use the 'help'     ║\n"
"║    command at the prompt below.                                     ║\n"
"╚═════════════════════════════════════════════════════════════════════╝\n";
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
