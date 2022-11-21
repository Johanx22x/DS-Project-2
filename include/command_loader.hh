#ifndef LOADER_HH
#define LOADER_HH

#include <command.hh>
#include <string>

/**
 * Loads a command by a given name
 *
 * @param name The name of the command to load
 * @return Pointer to a loaded command
 */
Command *loadCommand(std::string name);

#endif // LOADER_HH
