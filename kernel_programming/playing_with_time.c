/* demonstrates that ctime() is the same as asctime(localtime()) */
/* also this is a neat article about time_t and the year 2038 problem:
http://www.rogermwilcox.com/Y2038.html */


#include <stdio.h>
#include <time.h>

int main(void)
{
	time_t now = time(NULL); /* now is time_t 
				  time(NULL) returns time in seconds to time_t now */

	printf("The current time is %s\n",ctime(&now));

	
	
	time_t also_now = time(NULL); /* also_now is time_t */
	struct tm *time_struct;
	time_struct = localtime(&also_now);
	printf("The curent time is %s\n",asctime(time_struct));


	return 0;
}
