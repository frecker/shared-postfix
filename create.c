/* create.c - creates the md5sum for a password
 *
 * Frank Recker, 2011
 */

#include "md5sum.h"

int main(int argc,char *argv[]) {
  unsigned char md_value[EVP_MAX_MD_SIZE];
  unsigned int md_len;

  if(argc!=2) {
    fprintf(stderr,"usage: create <password>\n");
    exit(1);
  }

  calculate_md5_of(argv[1],strlen(argv[1]),md_value,&md_len);
  print_as_hex(md_value,md_len);
  printf("\n");
  return 0;
}
