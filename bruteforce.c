/* bruteforce.c - implements a brute force attack against the
 * cryptosystem with a given hint
 *
 * Frank Recker, 2011
 */

#include "md5sum.h"

char *try_buffer;
ssize_t try_len;

void increment_try_buffer(void) {
  int i=0;

  for(;;) {
    if(i==try_len) {
      try_buffer[try_len]=32;
      try_buffer[++try_len]=0;
      break;
    }
    if(++try_buffer[i]<=126)
      break;
    try_buffer[i++]=32;
  }
}

int main(int argc,char *argv[]) {
  char *md_str_1;
  unsigned char md_value_1[EVP_MAX_MD_SIZE];
  unsigned char md_value_2[EVP_MAX_MD_SIZE];
  unsigned int md_len_1,md_len_2;
  int j;
  int hint_len;

  if(argc!=3) {
    fprintf(stderr,"usage: bruteforce <hint> <md5sum of the password>\n");
    exit(1);
  }

  hint_len=strlen(argv[1]);
  md_str_1=argv[2];

  if(strlen(md_str_1)!=32) {
    fprintf(stderr,"md5sum has wrong length\n");
    exit(1);
  }
  string_to_digest(md_value_1,&md_len_1,md_str_1);
  if(md_len_1!=16) {
    fprintf(stderr,"digest has wrong length\n");
    exit(1);
  }

  try_buffer=malloc(strlen(argv[1])+50);
  try_buffer[0]=0;
  try_len=0;

  for(;;) {
    for(j=0;j<=hint_len;++j) {
      strcpy(try_buffer+try_len,argv[1]+j);
      calculate_md5_of(try_buffer,try_len+hint_len-j,md_value_2,&md_len_2);
      if(compare_digest(md_value_1,md_value_2,16)==0) {
	printf("The password is %s\n",try_buffer);
	return 0;
      }
    }
    increment_try_buffer();
  }
}
