#include "OStream.h"
#include "Drivers\Keyboard\Keyboard.h"

#if !defined ( __ISTREAM_H_ )
#define __ISTREAM_H_

namespace std
{
//---------------IStream:------------------------

	const int BUFFSIZE = 1024;

	class IStream : public Keyboard
	{
		public:
			IStream& operator >> (char *cp);
			IStream& operator >> (char &c);
			IStream& operator >> (unsigned char *ucp);
			IStream& operator >> (unsigned char &uc);

		private:
			char buffer[BUFFSIZE];

			unsigned int getString();
			void getWord(char *str1, char *p1);
	};

	extern IStream cin;
}

#endif

