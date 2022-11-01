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
  void *libcmd = dlopen(name.c_str(), RTLD_NOW);

  command *cmd = (command *)dlsym(libcmd, "command");

  return new Command(name, cmd);
}

Command::Command(std::string name, command *cmd) : name(name), cmd(cmd) {}
