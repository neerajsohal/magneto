#include "OStream.h"

#if !defined ( __OSTREAM_CPP_ )
#define __OSTREAM_CPP_


namespace std
{
 OStream cout;

 OStream& OStream::operator<<(const char *cp)
 {
  writeln(cp) ;
  return *this;
 }

 OStream& OStream::operator<<(const char c)
 {
  putch(c) ;
  return *this;
 }

 OStream& OStream::operator<<(const unsigned char *cq)
 {
  writeln((char *)cq) ;
  return *this;
 }

 OStream& OStream::operator<<(const unsigned char c1)
 {
  putch((char)c1) ;
  return *this;
 }

 OStream& OStream::operator<<(const unsigned int n1)
 {
  writeint(n1) ;
  return *this;
 }

 OStream& OStream::operator<<(const int n1)
 {
  writeint(n1) ;
  return *this;
 }

}

#endif
