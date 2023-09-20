/*
    Bruteforce Bootloader Unlocker for HUAWEI Related smartphones
    This is intended to be the fastest ever created bootloader unlocker
*/
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define LEN 37

unsigned long long base_start = 1000000000000000;

time_t start_time;

void resumer(int r){
    printf("\n\nLast used code was: %lld", base_start);
	FILE * fp = fopen("lastcode","w");
	fprintf(fp,"%llu",base_start);
	fclose(fp);
  FILE * fr = fopen("record","a");
  fprintf(fr,"END %llu %ld BLAH\n", base_start, time(NULL));
  fclose(fr);
  if (r) {
    return;
  }
    exit(1);
}

long long numr(long long x) {
  // printf("%llu\n",x);
  if (x%5000) {
    return x;
  }
  printf(" ### ### COUNTING NOW: %llu\n", x);
  resumer(1);
  return x;
}

int main( int argc, char **argv) {
	if ( argc > 1 ) {
	        char *base = argv[1];
	        base_start = atoll( base );
	} else {
		FILE * fp;
		if(fp= fopen("lastcode","w")) {
		fscanf(fp,"%llu",&base_start);
		fclose(fp);
		}
	}
  start_time = time(NULL);
  FILE * fr = fopen("record","a");
  fprintf(fr,"START %llu %ld BLOOP\n", base_start, start_time);
  fclose(fr);
    signal(SIGINT, resumer);
	signal(SIGTERM, resumer);
    char fou[LEN] = "fastboot oem unlock ";
    char TOTAL[LEN];

    while (sprintf( TOTAL, "%s%llu", fou, numr(base_start++)) && system( TOTAL ));

    printf("Your unlock code is: %llu", base_start);

    return 1;
}
