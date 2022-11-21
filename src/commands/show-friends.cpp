#include "uio.hh"
#include <cstdio>
#include <program.hh>

extern "C" {
void command(Program *ctx) {
  if (!ctx->simulationDone) {
    puts("You must run the simulation before running this command!");
    return;
  }

  puts("\n");
  puts("---------------------------------");
  puts("ID\tName");
  puts("---------------------------------");

  for (Person *person = ctx->people->head; person != nullptr;
       person = person->next) {
    printf("%d\t%s\n", person->id, person->name.c_str());
  }

  puts("---------------------------------");

  printf("Enter the person's id: ");

  int id = getInt();
  Person *found = ctx->people->find(id);

  puts("\n");
  printf("%s's friends\n", found->name.c_str());
  puts("---------------------------------");
  puts("ID\tName");
  puts("---------------------------------");

  for (const Person *_friend : *found->friends) {
    printf("%d\t%s\n", _friend->id, _friend->name.c_str());
  }

  puts("---------------------------------");

}
}
