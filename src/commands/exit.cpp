#include <iostream>
#include <program.hh>

extern "C" {
void command(Program *) {
    std::cout << "See you later!\n\n";
    std::cout <<
"\u001b[0;32m    .---.     \n"
"\u001b[0;32m   /     \\    \n"
"\u001b[0;32m   \\.@-@./     \u001b[0mDeveloped by:\n"
"\u001b[0;32m   /`\\_/`\\     \u001b[0m- @Johanx22x\n"
"\u001b[0;32m  //  _  \\\\    \u001b[0m- @zSnails\n"
"\u001b[0;32m | \\     )|_   \u001b[0m- @DavidArguedas\n"
"\u001b[0;32m/`\\_`>  <_/ \\  \u001b[0m© 2022\n"
"\u001b[0;32m\\__/'---'\\__/ \n";

    exit(0);
}
}
