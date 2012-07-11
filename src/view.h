#ifndef VIEW_H_
#define VIEW_H_

#include "window.h"
#include "observer.h"
#include "file.h"

/// An abstract class representing a view in the editor.
/// It serves as an interface for more specific views.
class View : public Window, public Observer
{
public:

  /// Constructs the view.
  /// It delegates its construction to the window constructor.
  View (int lines = 0,
        int cols  = 0,
        int y0    = 0,
        int x0    = 0);

  virtual ~View ();

  /// An abstract method which has to be implemented in classes
  /// which inherits from this class.
  virtual void Render () = 0;

  virtual void Notify (Subject * s) = 0;

};

#endif // VIEW_H_
