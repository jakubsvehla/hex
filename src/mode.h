#ifndef MODE_H_
#define MODE_H_

// FIXME: change to KEY_ESC
#define ESC 27

class Editor;

/// An abstract class representing a mode in the editor.
/// All modes should inherit from this class
/// and have to implement only one method to be instantiable and runnable.
class Mode
{
public:

  /// Constructs a new mode.
  Mode (Editor * editor);

  virtual ~Mode ();

  /// This method is an entry point to the mode.
  virtual void Run () = 0;

protected:

  /// The pointer to the editor.
  /// Every mode should be a friend class of the editor class to have the access
  /// to all editor's private members and methods.
  Editor * m_Editor;
};

#endif // MODE_H_
