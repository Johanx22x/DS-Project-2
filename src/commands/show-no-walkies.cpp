#include "person.hh"
#include <program.hh>

extern "C" {
void command(Program *ctx) {
  if (!ctx->simulationDone) {
    puts("You must run the simulation before running this command!");
    return;
  }

  puts("\n");
  puts("---------------------------------");
  puts("People who couldn't move do to being trapped");
  puts("---------------------------------");
  for (Person *person = ctx->people->head; person != nullptr;
       person = person->next) {
    if (!person->hasPath && (person->mode == MovementType::DIRECT ||
                             person->mode == MovementType::THROUGH_ALL)) {
      printf("%d\t%s\n", person->id, person->name.c_str());
    }
  }
  puts("---------------------------------");
}
}
