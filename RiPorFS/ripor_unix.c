/* RiPorFS Utilities!

ripor_unix.c is under The Unlicense. See LICENSE.TXT for details
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAINTYPE int

#define START_MSG "\nRiPorFS Utilities!\n\n"
#define USE "USE:\nripor a/e/r/x in (out)\na=add\ne=extract\nv=veiw\nr=rid\n\n"

#define ERROR_NOFILE "Error: file does not exist!\n\n"
#define ERROR_SIGFAIL "Error: signature does not match \"RiPorFS\"!\n\n"
#define ERROR_AB_FREAD "Error: fread did not return the magic number!\n\n"
#define ERROR_AB_FWRITE "Error: fwrite did not return the magic number!\n\n"
#define ERROR_AB_FREAD_2 "Error: fread did not return file size!\n\n"
#define ERROR_AB_FWRITE_2 "Error: fwrite did not return file size!\n\n"

#define INFO_CREATE "Info: Creating %s from %s!\n"
#define INFO_ADD "Info: Adding %s to %s!\n"
#define INFO_DONE "Info: Done!\n"

#define MAGIC_NUM 253

#define MAX_FILENAME_LENGTH 255

enum returnCodes {
	noError,
	noFile,
	sigFail,
	abFread,
	abFwrite
};

unsigned char fileData[MAGIC_NUM];
unsigned char fileName[MAX_FILENAME_LENGTH];

FILE *in = 0;
FILE *out = 0;
size_t fileSize = 0;
int passes = 0;
unsigned char consCheckSig[] = "RiPorFS";
unsigned char fileNameMark = 255;
unsigned char endOfFS = 254;
unsigned char ridge = MAGIC_NUM;

int freadTillNull(FILE *__in__, unsigned char *__out__)
{
	char __ch__ = '0';
	size_t __sc__ = 0;
	while(__ch__)
	{
		if(fread(&__ch__, 1, 1, __in__) != 1)
		{
			return 1;
		}
		*(__out__+__sc__) = __ch__;
		__sc__ ++;
	}
	return 0;
}

MAINTYPE main(int argc, char *argv[])
{
	printf(START_MSG);
	if(argc == 4 && *(argv[1]) == 'a')
	{
		in = fopen(argv[2], "r");
		if(in == NULL)
		{
			printf(ERROR_NOFILE);
			return noFile;
		}
		out = fopen(argv[3], "r+");
		if(out == NULL)
		{
			out = fopen(argv[3], "w+");
			fseek(out, 0, SEEK_SET);
			fwrite("RiPorFS", 1, 7, out);
			fseek(out, 0, SEEK_SET);
			fread(consCheckSig, 1, 7, out);
			if(strncmp(consCheckSig, "RiPorFS", 7))
			{
				printf(ERROR_SIGFAIL);
				fclose(in);
				fclose(out);
				return sigFail;
			}
			printf(INFO_CREATE, argv[3], argv[2]);
			fseek(out, 0, SEEK_END);
		}
		else
		{
			fseek(out, 0, SEEK_SET);
			fread(consCheckSig, 1, 7, out);
			if(strncmp(consCheckSig, "RiPorFS", 7))
			{
				printf(ERROR_SIGFAIL);
				fclose(in);
				fclose(out);
				return sigFail;
			}
			printf(INFO_ADD, argv[2], argv[3]);
			fseek(out, -1, SEEK_END);
		}
		fseek(in, 0, SEEK_END);
		fileSize = ftell(in);
		fseek(in, 0, SEEK_SET);
		fwrite(&fileNameMark, 1, 1, out);
		fwrite(argv[2], 1, strlen(argv[2])+1, out);
		while(fileSize >= MAGIC_NUM)
		{
			if(fread(&fileData, 1, MAGIC_NUM, in) != MAGIC_NUM)
			{
				printf(ERROR_AB_FREAD);
				fclose(in);
				fclose(out);
				return abFread;
			}
			fwrite(&ridge, 1, 1, out);
			if(fwrite(&fileData, 1, MAGIC_NUM, out) != MAGIC_NUM)
			{
				printf(ERROR_AB_FWRITE);
				fclose(in);
				fclose(out);
				return abFwrite;
			}
			fileSize -= MAGIC_NUM;
		}
		if(fileSize)
		{
			ridge = fileSize;
			fwrite(&ridge, 1, 1, out);
			if(fread(&fileData, 1, fileSize, in) != fileSize)
			{
				printf(ERROR_AB_FREAD_2);
				fclose(in);
				fclose(out);
				return abFread;
			}
			if(fwrite(&fileData, 1, fileSize, out) != fileSize)
			{
				printf(ERROR_AB_FWRITE_2);
				fclose(in);
				fclose(out);
				return abFwrite;
			}
		}
		fwrite(&endOfFS, 1, 1, out);
		fclose(in);
		fclose(out);
		printf(INFO_DONE);
	}
	else if(argc == 3 && *(argv[1]) == 'v')
	{
		in = fopen(argv[2], "r");
		if(in == NULL)
		{
			printf(ERROR_NOFILE);
			return noFile;
		}
		fseek(in, 0, SEEK_SET);
		fread(consCheckSig, 1, 7, in);
		if(strncmp(consCheckSig, "RiPorFS", 7))
		{
			printf(ERROR_SIGFAIL);
			fclose(in);
			return sigFail;
		}
		while(ridge != endOfFS)
		{
			if(fread(&ridge, 1, 1, in) != 1)
			{
				printf(ERROR_AB_FREAD);
				fclose(in);
				return abFread;
			}
			if(ridge == fileNameMark)
			{
				if(freadTillNull(in, fileName))
				{
					printf(ERROR_AB_FREAD);
					return abFread;
				}
				printf("%s\n",  fileName);
			}
			else if(ridge != endOfFS)
			{
				fseek(in, ridge, SEEK_CUR);
			}
		}
		printf(INFO_DONE);
		fclose(in);
	}
	else printf(USE);
	return 0;
}
