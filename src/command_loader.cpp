#include <command_loader.hh>
#include <context.hh>
#include <string>

#if defined(_WIN32)
#define DL ".dll"
#define dlopen LoadLibrary
#define dlsym GetProcAddress
#else
#define DL ".so"
#include <dlfcn.h>
#endif

using std::string;

Command *loadCommand(string name) {
  void *symb = dlopen(name.c_str(), RTLD_LAZY);

  command *cmd = (command *)dlsym(symb, "command");

  dlclose(symb);

  return new Command(name, cmd);
}

Command::Command(std::string name, command *cmd) : name(name), cmd(cmd) {}
