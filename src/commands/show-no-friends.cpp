#include <program.hh>

extern "C" {
void command(Program *ctx) {
  if (!ctx->simulationDone) {
    puts("You must run the simulation before running this command!");
    return;
  }

  puts("\n");
  puts("---------------------------------");
  puts("People who got no friends");
  puts("---------------------------------");
  puts("ID\tName");
  puts("---------------------------------");
  for (Person *person = ctx->people->head; person != nullptr;
       person = person->next) {
    if (person->friends->size() == 0) {
      printf("%d\t%s\n", person->id, person->name.c_str());
    }
  }
  puts("---------------------------------");
}
}
