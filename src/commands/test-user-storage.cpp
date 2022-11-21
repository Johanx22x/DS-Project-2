#include <encoding.hh>
#include <program.hh>

extern "C" {
void command(Program *ctx) {
  char buf[65000];

  for (Person *person = ctx->people->head; person != nullptr;
       person = person->next) {
    if (person->from == nullptr) {
      person->from = ctx->nodes->head;
    }
  }

  encodePeople(ctx->people, buf);

  FILE *out = fopen("people.spp", "w");

  fprintf(out, "%s", buf);

  fflush(out);
  fclose(out);
  return;
}
}
