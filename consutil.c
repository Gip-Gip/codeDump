/* consutil.c, a C file with a bunch of functions to aid console app development
consutil.c is under The Unlicense. See LICENSE.TXT for details
*/

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
