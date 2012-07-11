#ifndef EDITOR_H_
#define EDITOR_H_

#define VERSION "0.0.1"

#include "file.h"
#include "file_view.h"
#include "cmd_line_view.h"
#include "config.h"

class Mode;
class NormalMode;
class CmdMode;
class InsertMode;

/// The main class wrapping up the whole logic of the editor.
/// It serves as a container for opened files, views and modes.
class Editor
{
public:

  /// Constructs the editor.
  Editor ();

  /// Destructs the editor, exits curses and deallocates all allocated memory.
  ~Editor ();

  /// A convenience initalization method which opens the file, iniatializes curses, all views and all modes.
  void Init ();

  /// Opens a file with a given |name|.
  /// If it doesn't exist it creates an empty file.
  void OpenFile (char * name);

  /// Runs the editor.
  void Run ();

  /// Exits the editor.
  void Exit ();

  /// All modes are friend classes in order to have full access to the editor's private members and methods.
  friend class NormalMode;
  friend class CmdMode;
  friend class InsertMode;

private:

  bool m_Run;

  Config * m_Config;

  /// Pointer to an opened file.
  File * m_File;

  /// Pointer to the file view.
  FileView * m_FileView;

  /// Pointer to the command line view.
  CmdLineView * m_CmdLineView;

  /// Currently used mode.
  Mode * m_Mode;

  /// Pointers to all modes available in the editor.
  Mode * m_NormalMode;
  Mode * m_CmdMode;
  Mode * m_InsertMode;
};

#endif // EDITOR_H_
