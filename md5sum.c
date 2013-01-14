/* md5sum.c - functions for calcluating the md5sum
 *
 * Frank Recker, 2011
 *
 * The functions "calculate_md5_of" and "print_as_hex" in this module
 * are from http://en.literateprograms.org/ and have there own
 * copyright notice (cf. code below).
 */

#include "md5sum.h"

char hex(int x) {
  if(x>=0 && x<10)
    return x+'0';
  if(x>=10 && x<16)
    return x-10+'a';
  fprintf(stderr,"hex: %d\n",x);
  exit(1);
}

int decimal(char x) {
  if(x>='0' && x<='9')
    return x-'0';
  if(x>='a' && x<='f')
    return x-'a'+10;
  fprintf(stderr,"decimal: %d\n",x);
  exit(1);
}

int compare_digest(unsigned char *digest_1,unsigned char *digest_2,unsigned int len) {
  int i,c;

  for(i=0;i<len;++i) {
    c=digest_1[i]-digest_2[i];
    if(c) return c;
  }
  return 0;
}

void string_to_digest(unsigned char *digest,unsigned int *len,char *buffer) {
  *len=0;
  for(;;){
    int a,r;

    a=buffer[2*(*len)];
    if(a==0)
      break;
    r=buffer[2*(*len)+1];
    digest[*len]=16*decimal(a)+decimal(r);
    ++*len;
  }
}

void digest_to_string(char *buffer,unsigned char *digest,int len) {
  int i;

  for(i=0;i<len;i++){
    int c,a,r;

    c=digest[i];
    a=c/16;
    r=c%16;
    buffer[2*i]=hex(a);
    buffer[2*i+1]=hex(r);
  }
  buffer[2*i]=0;
}

/* Copyright (c) 2011 the authors listed at the following URL, and/or
the authors of referenced articles or incorporated external code:
http://en.literateprograms.org/MD5_sum_(C,_OpenSSL)?action=history&offset=20090615063756

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/MD5_sum_(C,_OpenSSL)?oldid=16463
*/
void print_as_hex(unsigned char *digest,int len) {
  char *bu;

  bu=malloc(2*len+1);
  digest_to_string(bu,digest,len);
  printf("%s",bu);
}

void calculate_md5_of(const void *content, ssize_t len,unsigned char *md_value,unsigned int *md_len) {
  EVP_MD_CTX mdctx;

  EVP_DigestInit(&mdctx,EVP_md5());
  EVP_DigestUpdate(&mdctx,content,(size_t)len);
  EVP_DigestFinal_ex(&mdctx,md_value,md_len);
  EVP_MD_CTX_cleanup(&mdctx);
}
