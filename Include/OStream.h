#include "Drivers\Video\Console\Console.h"

#if !defined ( __OSTREAM_H_ )
#define __OSTREAM_H_

namespace std
{
 const char endl = '\n';

 class OStream : private Console
 {
  private:

  public:
     OStream& operator<<(const char *cp);
     OStream& operator<<(const char c);
     OStream& operator<<(const unsigned char *cq);
     OStream& operator<<(const unsigned char c1);
     OStream& operator<<(const unsigned int n1);
     OStream& operator<<(const int n1);
 };

 extern OStream cout;
}


#endif
