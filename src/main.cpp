#include <command_loader.hh>
#include <cstdio>
#include <filesystem>
#include <graph.hh>
#include <iostream>
#include <linked_list.hh>
#include <map>
#include <program.hh>
#include <string>
#include <uio.hh>

#if defined(_WIN32)
#define DL ".dll"
#else
#define DL ".so"
#endif

using std::string;

int main() {

  Program *p = new Program();
  /* std::map<string, Command *> commands = std::map<string, Command *>(); */

  for (const std::filesystem::directory_entry &entry :
       std::filesystem::directory_iterator("./bin")) {

    string fileName = entry.path();

    int position = fileName.find_last_of(".");

    string ft = fileName.substr(position);

    if (ft.compare(DL) == 0) {

      puts(fileName.c_str());
      fileName = fileName.erase(position);
      puts(fileName.c_str());

      position = fileName.find_last_of("/");

      string cmdName = fileName.substr(position);

      puts(cmdName.c_str());

      printf("loading: %s %s\n", fileName.c_str(), ft.c_str());
      Command *cmd = loadCommand(entry.path());
      printf("loaded: %s %s\n", fileName.c_str(), ft.c_str());
      p->commands->emplace(cmdName, cmd);
    }
  }

  p->run();

  return 0;
}
