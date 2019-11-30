#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>

/***********************************************************************
*******
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2
uppercase
  letters and a 2 digit integer. Your personalised data set is included
in the
  code.

  Compile with:
    cc -o CrackAZ99-With-Data CrackAZ99-With-Data.c -lcrypt

  If you want to analyse the results then use the redirection operator
to send
  output to a file that you can view using an editor or the less
utility:

    ./CrackAZ99-With-Data > results.txt

  Dr Kevan Buckley, University of Wolverhampton, 2018
************************************************************************
******/
int n_passwords = 4;

char *encrypted_passwords[] = {

"$6$KB$CC/sLPlM0K44jbGJ7SSR00OTt1j3bO2PXFyRerCmwKu9iZhyipCFz2Lz5d3.8urjwomOVRDq0upjYt4nkfXvA0",

"$6$KB$YEoFUv/3nyduRCvkyCCCCXeRgOBi6x3OBy.xQEVacaCEKtE6VKQ4eBLNj5fhLUGdEazB4Q7317BRLeZbwfKf5.",

"$6$KB$sTgOCutLBcHht0AFGph3on73arcCWDoZn8FwhoD/U3UPWO4Dyui0RgHxqQOzTvoynbW7apMtfjNcyzXhjlLId1",

"$6$KB$hZQbhQC9eiI3SMS3ZpaQ03481788lSefnQOz3O4GotHQu6gM3djF2C08xotJn9g0R2jR3HkjxHWsS6wkaUINE/"
};

/**
 Required by lack of standard function in C.   
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

/**
 This function can crack the kind of password explained above. All
combinations
 that are tried are displayed and when the password is found, #, is put
at the
 start of the line. Note that one of the most time consuming operations
that
 it performs is the output of intermediate results, so performance
experiments
 for this kind of program should not include this. i.e. comment out the
printfs.
*/

void crack(char *salt_and_encrypted){
  int x, y, z, b;     // Loop counters
  char salt[7];    // String used in hahttps://www.youtube.com/watch?v=L8yJjIGleMwshing the password. Need space
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='A'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
	for(b='A'; b<='Z'; b++){
      		for(z=0; z<=99; z++){
        		sprintf(plain, "%c%c%c%02d", x, y, b, z);
        		enc = (char *) crypt(plain, salt);
        		count++;
        		if(strcmp(salt_and_encrypted, enc) == 0){
          			printf("#%-8d%s %s\n", count, plain, enc);
        		} else {
          			printf(" %-8d%s %s\n", count, plain, enc);
       		}
	 }
      }
    }
  }
  printf("%d solutions explored\n", count);
}


//Calculating time

int time_difference(struct timespec *start, struct timespec *finish, long long int *difference)
 {
	  long long int ds =  finish->tv_sec - start->tv_sec; 
	  long long int dn =  finish->tv_nsec - start->tv_nsec; 

	  if(dn < 0 ) {
	    ds--;
	    dn += 1000000000; 
  } 
	  *difference = ds * 1000000000 + dn;
	  return !(*difference > 0);
}
int main(int argc, char *argv[])
{
  	int i;
	struct timespec start, finish;   
  	long long int time_elapsed;

  	clock_gettime(CLOCK_MONOTONIC, &start);

  	for(i=0;i<n_passwords;i<i++) 
	{
    		crack(encrypted_passwords[i]);
  	}
	clock_gettime(CLOCK_MONOTONIC, &finish);
	  time_difference(&start, &finish, &time_elapsed);
	  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
		                                 (time_elapsed/1.0e9)); 
  return 0;
}
