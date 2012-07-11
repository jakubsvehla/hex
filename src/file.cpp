#include <cstddef>
#include <cstdlib>

#include "file.h"

using namespace std;

Byte::Byte ()
{
  m_Next = NULL;
  m_Prev = NULL;
}

Byte::Byte (const unsigned char c)
{
  m_Next = NULL;
  m_Prev = NULL;
  m_Val  = c;
}

File::File ()
{
  Init();
}

File::~File ()
{
  Byte * tmp;

  while (m_Head) {
    tmp = m_Head;
    m_Head = m_Head -> m_Next;
    delete tmp;
  }
}

void File::Init ()
{
  m_Head = m_Tail = m_Mark = new Byte();
  m_Version = 1;
  m_Saved = true;
}

bool File::Open (const char * name)
{
  FILE * f;
  int c;

  // TODO handle errors and throw exceptions

  m_FileName = name;

  f = fopen(name, "ab+");
  fseek(f, 0, SEEK_SET);

  while ((c = fgetc(f)) != EOF)
    Ins(c);

  fclose(f);

  Seek(0);

  m_Saved = true;
  NotifyObservers();

  return true;
}

bool File::Save ()
{
  FILE * f;
  unsigned char c;
  int pos;

  pos = Tell();

  // TODO handle errors and throw exceptions

  if (m_FileName.empty()) return false;

  f = fopen(m_FileName.c_str(), "wb");

  Seek(0);
  while (!Eof()) {
    Get(c);
    fputc(c, f);
  }

  fclose(f);

  m_Saved = true;

  Seek(pos, SEEK_SET);

  return true;
}

void File::Ins (const unsigned char c)
{
  Byte * byte = new Byte(c);

  if (m_Mark == m_Head) {
    byte -> m_Next = m_Mark;

    m_Mark -> m_Prev = byte;
    m_Head = byte;
  }
  else {
    byte -> m_Next = m_Mark;
    byte -> m_Prev = m_Mark -> m_Prev;

    byte -> m_Next -> m_Prev = byte;
    byte -> m_Prev -> m_Next = byte;
  }

  m_Version ++;
  m_Saved = false;
  NotifyObservers();
}

void File::Del (void)
{
  Byte * tmp;

  if (Eof()) {
    return;
  }

  tmp = m_Mark;
  m_Mark = m_Mark -> m_Next;

  if (tmp == m_Head) {
    m_Head = m_Head -> m_Next;
    m_Head -> m_Prev = NULL;
    delete tmp;
  }
  else {
    tmp -> m_Prev -> m_Next = tmp -> m_Next;
    tmp -> m_Next -> m_Prev = tmp -> m_Prev;
    delete tmp;
  }

  m_Version ++;
  m_Saved = false;
  NotifyObservers();
}

bool File::Get (unsigned char & c)
{
  if (Eof()) return false;

  c = m_Mark -> m_Val;
  m_Mark = m_Mark -> m_Next;

  NotifyObservers();

  return true;
}

int File::Read (int offset, int n, unsigned char * buffer) const
{
  Byte  * tmp;
  int     i;

  tmp = m_Head;

  for (i = 0; i < offset; i ++) {
    if (tmp == m_Tail) return 0;
    tmp = tmp -> m_Next;
  }

  for (i = 0; i < n; i ++) {
    if (tmp == m_Tail) break;
    buffer[i] = tmp -> m_Val;
    tmp = tmp -> m_Next;
  }

  return i;
}

bool File::Put (const unsigned char c)
{
  if (Eof()) return false;
  m_Mark -> m_Val = c;
  m_Mark = m_Mark -> m_Next;

  m_Version ++;
  m_Saved = false;
  NotifyObservers();

  return true;
}

bool File::Seek (int offset, int whence)
{
  int    i;
  Byte * tmp;

  tmp = m_Mark;

  if (whence == SEEK_SET) {
    m_Mark = m_Head;
  }

  for (i = 0; i < abs(offset); i ++) {

    if (offset < 0) {
      m_Mark = m_Mark -> m_Prev;
    }
    else {
      m_Mark = m_Mark -> m_Next;
    }

    if (m_Mark == NULL) {
      m_Mark = tmp;
      return false;
    }
  }

  NotifyObservers();

  return true;
}

int File::Tell () const
{
  int i;
  Byte * tmp = m_Head;

  for (i = 0; tmp != m_Mark; i ++) {
    tmp = tmp -> m_Next;
  }

  return i;
}

bool File::Eof (void) const
{
  if (m_Mark == m_Tail) {
    return true;
  } else {
    return false;
  }
}

const char * File::Name () const
{
  return m_FileName.c_str();
}

int File::Version () const
{
  return m_Version;
}

bool File::IsSaved () const
{
  return m_Saved;
}
