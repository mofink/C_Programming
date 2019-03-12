/* This is an ongoing project to implement <stdio.h> for a UNIX system without relying on external libraries */


/* I've based the architecture on the C89 (ANSI) standard: http://port70.net/~nsz/c/c89/c89-draft.html#4.9 
Much of the code is based on sources found online, comments are my own */




/*declare types 

size_t

FILE
has EOF, error indicator, pointer to file position, buffer, state information 

fpost_t
macros are NULL

used in setvbuf to assign buffering to a stream
_IOFBF
_IOLBF
_IONBF

BUFSIZ  size of buffer used by setbuf 
EOF indicates no more input from stream 
FOPEN_MAX  system guarantees this number of streams can be open simultaneously 

FILENAME_MAX  to do with tmpnam function 

 use these in fseek 
SEEK_CUR
SEEK_END
SEEK_SET

TMP_MAX /* to do with tmpname function 


 type "pointer-to-FILE" for their respective streams, opened at program startup *
stderr
stdin 
stdout

when you open a file you are essentially connecting it to a stream 
fptr = fopem(fname, fmode);
DO NOT PEEK INSIDE *fptr    
*/


#include <yvals.h>
/* UNIX examples for relevant parameters from <yvals.h> which is implementation dependent
#define _NULL (void *)0 //Value for NULL
#define _FNAMAX 64 //value for FILENAME_MAX
#define _FOPMAX 32 //value for FOPEN_MAX 
#define _TNAMAX 16 //value for L_tmpnam
*/


//Random macros, adding as needed
#define NULL _NULL
#define _IOFBF 0
#define _IOLBF 1
#define _IONBF 2
#define BUFSIZ 512
#define EOF -1
#define FILENAME_MAX _FNAMAX
#define FOPEN_MAX _FOPMAX
#define L_tmpnam _TNAMAX
#define TMP_MAX 32
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#define stdin _Files[0]
#define stdout _Files[1]
#define stderr _Files[2]



//bits for _Mode members in FILE, correspond to bit set. Convention based on Standard C Library book
#define _OPENR 0x1 //set if file is open for reading
#define _OPENW 0x2 //set if file is open for writing
#define _NBUF 0x800//set if no buffering should occur
#define _ALFIL 0x80//set if FILE object must be freed on close 


//type definitions

/* Type definition of FILE 
members are:
_Mode - status bits for the stream
_Handle - file descriptor returned by the OS
_Buf - pointer to start of stream buffer, NULL if buffer not allocated
_Bend - pointer to first character beyond end of buffer. NULL if _Buf is null
_Next - pointer to next character to read or write. Never NULL
_Rend - pointer to first character beyond data to be read. Never NULL
_Rsave - hold _Rend if characters have been held back
_Wend - like _Rend but for writing
_Back - stack of push back characters
_Cbuf - one character buffer to use when no other buffers are avail
_Nback - number of pushed back characters
_Tmpnam - pointer to the name of a temp file to be removed when file is closed, else NULL
*/

typedef struct 
{
	//choice for types are based on what I found online ¯\_(ツ)_/¯
	unsigned short _Mode;
	short _Handle;
	unsigned char *_Buf, *_Bend, *_Next, *_Rend, *_Rsave, *_Wend, *_Back[2], _Cbuf, _Nback;
	char *_Tmpnam;
} FILE;

//_Files[] data object. tracks open streams, first three are stdin, stdout, stderr, the rest are initilized to NULL. 
// up to FOPEN_MAX streams open at a time

//stderr buffer
static unsigned char errbuf[100];

//stdin
static FILE stream_in = { _OPENR, 0, NULL, NULL, &stream_in._Cbuf, &stream_in._Cbuf, NULL, &stream_in._Cbuf};

//stdout
static FILE stream_out { _OPENW, 1, NULL, &stream_out._Cbuf, &stream_out._Cbuf, NULL, &stream_out._Cbuf};

//stderr
static FILE stream_err { _OPENW | _NBUF, 2, errbuf, errbuf + sizeof(errbuf), errbuf, errbuf, NULL, errbuf};

//array of pointers to open streams
FILE * _Files[FOPEN_MAX] = {&stream_in, &stream_out, &stream_err};



//declerations 

FILE * fopen(const char *name,cont char *modes);





FILE * fopen(const char *name,cont char *modes)
{
	FILE *str;
	int i; //need to implement size_t and change this
	for (i = 0; i < FOPEN_MAX; ++i)
	{
		if (_Files[i] == NULL) //create FILE object at _Files[i] where none existed previously
		{
			str = (FILE *) malloc(sizeof(FILE)); //allocate memory for FILE object
			_Files[i] = str; //point _Files[i] at allocated memory in previous step
			_Files[i]->_Mode = _ALFIL; //free this memory location when closing stream
			break; //done
		}

		else if (_Files[i]->_Mode == 0) //FILE object exists at this address but its stream has been closed (not freed).
		//We can reuse it without creating new FILE. This happens when closing a standard stream
		{
			str = _Files[i];
			break;
		}
	}
	if (i > FOPEN_MAX)
		return NULL; //no more space to open file


	// need to set values in FILE and return pointer to its location
}






