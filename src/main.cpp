#include "cli.h"

/// @mainpage View and edit files in hexadecimal and ASCII.
/// @author Jakub Svehla
/// @version 0.0.1

int main (int argc, char ** argv)
{
  CLI cli;

  cli.Run(argc, argv);

  return 0;
}
