#ifndef CMD_MODE_H_
#define CMD_MODE_H_

#include "editor.h"
#include "mode.h"

/// In command-line mode you can enter a line of text
/// at the bottom of the window which will be interpreted
/// as a command.
///
/// You can use commands listed below:
/// - :w or :write to save the file
/// - :q or :quit to exit the editor (this command will warn you if you have changed the file since the last save)
/// - :q! to exit the editor even if you have unsaved changes in the file
///
/// You can exit the command-line mode with ESC key.
class CmdMode : public Mode
{
public:

  /// A constructor.
  /// @param [in] editor Pointer to the editor which will be controlled by this mode.
  CmdMode (Editor * editor);

  /// A destructor.
  virtual ~CmdMode ();

  /// An entry point to the mode.
  /// Executes a command and exits.
  virtual void Run ();

  /// Exits this mode.
  void Exit ();

};

#endif // CMD_MODE_H_
