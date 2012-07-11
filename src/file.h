#ifndef FILE_H_
#define FILE_H_

#include <string>
#include <cstdio>

#include "subject.h"

/// A class representing a byte.
/// It's used to implement the file buffer as a double-linked list.
struct Byte
{
  /// Constructs an empty byte.
  Byte ();

  /// Constructs a byte with the given |c| value.
  Byte (const unsigned char c);

  /// Actual value of the byte.
  unsigned char m_Val;

  /// Pointer to the next byte in the buffer.
  /// Is NULL when it's the last byte in the buffer.
  Byte * m_Next;

  /// Pointer to the previous byte in the buffer.
  /// Is NULL when it's the first byte in the buffer.
  Byte * m_Prev;
};

/// A class representing a file.
/// It implements its own buffer to be able to insert and delete in O(1) time.
/// It also inherits from the Subject class in order to be observable. It notifies its observers
/// whenever its state is changed. This is useful, for example, if you need to rerender your file view everytime the file is changed.
class File : public Subject
{
public:
  /// Constructs an empty file.
  File ();

  /// Empties the buffer, closes the file and deallocates the buffer.
  ~File ();

  /// Opens a file with a given |name|.
  bool Open (const char * name);

  /// Empties the buffer and saves the file.
  bool Save ();

  /// Inserts a character |c| into the buffer before the current position.
  void Ins (const unsigned char c);

  /// Deletes a character at the current position.
  void Del ();

  /// Reades next character from the file buffer and stores it into |c|.
  /// Returns false if end-of-file has been reached or some error occured.
  bool Get (unsigned char & c);

  /// Reades a block of data of |n| bytes from a given |offset| and stores them in the buffer
  /// specified by |buffer|.
  /// Returns a number of successfully read bytes.
  int Read (int offset,
            int n,
            unsigned char * buffer) const;

  bool Put (const unsigned char c);

  /// Seeks to a given |offset| in the buffer according to the value of |whence|.
  /// Returns false if some error occured.
  bool Seek (int offset, int whence = SEEK_SET);

  /// Returns the current offset in the buffer.
  int Tell () const;

  /// Returns whether the end-of-file has been reached.
  bool Eof () const;

  /// Returns the file name.
  const char * Name () const;

  int Version () const;

  bool IsSaved () const;

private:

  /// Initializes an empty buffer.
  void Init ();

  /// Pointer to the start of the buffer.
  Byte * m_Head;

  /// Pointer to the end of the buffer.
  Byte * m_Tail;

  /// Pointer to the current position in the buffer.
  Byte * m_Mark;

  /// Name of the opened file.
  std::string m_FileName;

  /// Track file versions.
  /// Initial value after opening a file is 1. When a change occurs, the value is incremented.
  int m_Version;

  bool m_Saved;

};

#endif // FILE_H_
