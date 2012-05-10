#ifndef ASSERT_H_INCLUDED
#define ASSERT_H_INCLUDED

#include <stdio.h>  // for perror

#define ASSERT(assertion, description)        \
	if(!(assertion))                            \
	{									                          \
		puts(description ": failure");            \
		return EXIT_FAILURE;                      \
  }                                           \
  else                                        \
    puts(description ": success")

#endif // ASSERT_H_INCLUDED
