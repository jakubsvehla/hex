#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

#include "cli.h"
#include "editor.h"

void CLI::Run (int argc, char ** argv)
{
  Editor editor;

  if (argc < 2) Usage(EXIT_FAILURE);

  // Handle special options --help and --version
  if (strcmp(argv[1], "-h") == 0 ||
      strcmp(argv[1], "--help") == 0) Usage(EXIT_SUCCESS);

  if (strcmp(argv[1], "-v") == 0 ||
      strcmp(argv[1], "--version") == 0) Version();

  // Initialize editor
  editor.Init();

  editor.OpenFile(argv[1]);

  // Start editor
  editor.Run();

}

void CLI::Version () const
{
  ASCII();
  cout << "hex " << VERSION << endl;
  exit(EXIT_SUCCESS);
}

void CLI::Usage (int status) const
{
  ASCII();
  cout << "Usage: hex [OPTIONS] FILE\n"
          "  --help     Output this help and exit\n"
          "  --version  Output version and exit\n";
  exit(status);
}

void CLI::ASCII () const
{

  cout << " __  __                              \n"
          "/\\ \\/\\ \\                         \n"
          "\\ \\ \\_\\ \\     __   __  _        \n"
          " \\ \\  _  \\  /'__`\\/\\ \\/'\\     \n"
          "  \\ \\ \\ \\ \\/\\  __/\\/>  </     \n"
          "   \\ \\_\\ \\_\\ \\____\\/\\_/\\_\\ \n"
          "    \\/_/\\/_/\\/____/\\//\\/_/      \n";
  cout << endl;
}
