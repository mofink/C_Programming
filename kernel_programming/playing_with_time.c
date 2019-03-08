/* demonstrates that ctime() is the same as asctime(localtime()) */

#include <stdio.h>
#include <time.h>

int main(void)
{
	time_t now = time(NULL); /* now is time_t 
				  				returns time in seconds to time_t now */

	printf("The current time is %s\n",ctime(&now));



	time_t also_now = time(NULL); /* also_now is time_t */
	struct tm *time_struct;
	time_struct = localtime(&also_now);
	printf("The curent time is %s\n",asctime(time_struct));


	return 0;
}
