#include <command_loader.hh>
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
  void *libcmd = dlopen(name.c_str(), RTLD_LAZY);
  if (libcmd == nullptr)
    printf("warning: libcmd is null\nError: %s\n", dlerror());

  command *cmd = (command *)dlsym(libcmd, "command");
  if (cmd == nullptr)
    printf("warning: cmd is null\nError: %s\n", dlerror());

  return new Command(name, cmd);
}
