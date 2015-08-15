/* consutil.c, a C file with a bunch of funtions to aid console app development
 * under The Unlicense. See LICENSE.TXT for details
 */

/* getExtension: Get the filename's extension and return the pointer to it.
 * VARIABLES:
 * __fn__ = the filename
 * __cl__ = the counter used to find the filename's length
 * __ex__ = the array that at the end, holds the filename's extension
 * __co__ = the counter that helps get the characters into the array __ex__
 */

char * getExtension(char *__fn__)
{
	int __cl__ = 0;
	while(*(__fn__-__cl__) != '.')
	{
		__cl__ ++;
	}
	char __ex__[__cl__+1]; /* We have to make it 1 byte bigger so we can
	* place the null terminator at the end */
	int __co__ = 0;
	while(__cl__)
	{
		__ex__[__co__] = *(__fn__-__cl__);
		__cl__ --;
		__co__ ++;
	}
	__ex__[__co__] = 0;
	return __ex__;
}
