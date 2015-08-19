/* consutil.c, a C file with a bunch of functions to aid console app development
consutil.c is under The Unlicense. See LICENSE.TXT for details
*/

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif
#ifndef _INC_STDIO
#include <stdio.h>
#endif

#ifndef bool
#define bool char
#endif
#ifndef false
#define false 0
#endif
#ifndef true
#define true 1
#endif

/* getStingLength, a alternative to strlen. It finds the length of a string

VARIABLES:
----------

___st___
the pointer to the string being measured.

___tm___
the terminator that ends the string. Usually NULL.

___cn___
the counter that measures the string.
*/
int getStringLength(const char *___st___, char ___tm___)
{
	int ___cn___ = 0;
	while(*(___st___+___cn___) != ___tm___)
	{
		___cn___ ++;
	}
	return ___cn___;
}

/* checkForChar, a function that checks if there is a specific character in a
string before the terminator.

VARIABLES:
____st____
the string we're searching in.

___lk___
the character we're looking for

____tm____
the terminator. Usually null

____cn____
the counter used to find the character

____tr____
used to keep track of whether the character has been fount or not
*/

int checkForChar(const char *____st____, char ___lk___, char ____tm____)
{
	int ____cn____ = 0;
	int ____tr____ = 0;
	while(*(____st____ + ____cn____) != ____tm____ && \
	*(____st____ + ____cn____) != ___lk___)
	{
		____cn____ ++;
		if(*(____st____ + ____cn____) == ___lk___)
		{
			____tr____ = 1;
		}
	}
	return ____tr____;
}

/* getExtension, a function that returns a pointer to the extension in the given
file name

VARIABLES:
----------
__fn__
The pointer to the file name

__cn__
the counter used to find the extension
*/

const char * getExtension(const char *__fn__)
{
	int __cn__ = getStringLength(__fn__, 0);
	while(*(__fn__+__cn__) != '.' && __cn__)
	{
		__cn__ --;
	}
	__fn__ += __cn__;
	return __fn__;
}

/* setExtension, a function that changes the extension of a filename
___fn___
the filename to change/add the extension of/to

__ex__
the new extention

__ap__
the append flag. If it equals false, setExtension replaces the extension instead of
adding it.

__es__
the length of the new extension

__fs__
the length of the filename without the extension
__nl__
the length of the filename with the new extension

__nf__
the string containing the new extension

__cn__
the primary counter
*/

const char * setExtension(const char *___fn___, const char *__ex__, bool __ap__)
{
	int __es__ = getStringLength(__ex__, 0);
	int __fs__ = getStringLength(___fn___, 0);
	if(checkForChar(___fn___, '.', 0) && !__ap__)
		__fs__ = getStringLength(___fn___, '.');
	int __nl__ = __fs__+__es__;
	char *__nf__ = malloc(__nl__+1);
	int __cn__ = 0;
	while(__cn__ != __fs__)
	{
		*(__nf__+__cn__) = *(___fn___+__cn__);
		__cn__ ++;
	}
	while(__cn__ != __fs__+__es__)
	{
		*(__nf__+__cn__) = *(__ex__+__cn__-__fs__);
		__cn__ ++;
	}
	return __nf__;
}

/* safeFileWrite, a function that if a file exists, will make sure that if a
file exists, it will not destroy it unless the user says otherwise.

VARIABLES:
__fn__

*/

FILE safeFileWrite(const char *__fn__)
{
	fopen(__fn__, "r");
	if(__fn__ != NULL)
	{
		#ifndef OVR_WRITE_MSG
		printf("%s already exists! Overwrite(y/n)?\n", __fn__);
		#else
		printf(OVR_WRITE_MSG, __fn__);
		#endif
		char *__yn__
		scanf("%c", &__yn__);
		if(__yn__ != 'y', __yn__ != 'Y')
		{
			printf("Not overwriting.\n");
			return NULL;
		}
	}
	return fopen(__fn__, "w");
}
