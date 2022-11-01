#include <command_loader.hh>
#include <context.hh>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <map>

#include <string>

#if defined(_WIN32)
#define DL ".dll"
#else
#define DL ".so"
#endif

using std::string;

int main() {

  /* Context ctx; */
  std::map<string, Command *> commands = std::map<string, Command *>();

  for (const std::filesystem::directory_entry &entry :
       std::filesystem::directory_iterator("./")) {

    string fileName = entry.path();

    int position = fileName.find_last_of(".");

    string ft = fileName.substr(position);

    printf("%s %s\n", fileName.c_str(), ft.c_str());

    if (ft.compare(DL) == 0) {
      Command *cmd = loadCommand(entry.path());
      /* commands.emplace(entry.path(), cmd); */
    }
  }

  return 0;
}
