#ifndef CLI_H_
#define CLI_H_

/// A command line interface of the editor.
class CLI
{
public:

  /// Parses the command line options and runs the editor.
  void Run (int argc, char ** argv);

private:

  /// Prints the CLI usage.
  void Usage (int status) const;

  /// Prints the editor's version.
  void Version () const;

  /// Prints an ASCII logo to the standard output.
  void ASCII () const;
};

#endif // CLI_H_
