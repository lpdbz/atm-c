#include <stdio.h>
#include <time.h>

void currentTime(char* time1){
    time_t timep;
    struct tm *p;
    time(&timep);
    p=gmtime(&timep);
    sprintf(time1,"%dÄê%dÔÂ%dÈÕ-%d:%d:%d",1900+p->tm_year,1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min,p->tm_sec);
}


/*int main(){
	char time2[30];
	currentTime(time2);
	return 0;
}*/
