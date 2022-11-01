#include <command_loader.hh>
#include <context.hh>
#include <filesystem>
#include <iostream>
#include <map>

#include <string>

using std::string;

int main() {

  Context ctx;
  std::map<string, Command> commands = std::map<string, Command>();

  for (const std::filesystem::directory_entry &dir :
       std::filesystem::directory_iterator("./")) {

    Command *cmd = loadCommand(dir.path());

    commands.emplace(dir.path(), cmd);
  }

  return 0;
}
