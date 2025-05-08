#include <iostream>
#include <PkFramework.hpp>
#include <argh.h>

int
main (int, char *argv[])
{
    printHello();

    argh::parser cmdl(argv);

    if (cmdl[{ "-v", "--verbose" }])
        std::cout << "Verbose, I am.\n";

    return 0;
}
