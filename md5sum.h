#include <string.h>
#include <openssl/evp.h>

int compare_digest(unsigned char *digest_1,unsigned char *digest_2,unsigned int len);
void string_to_digest(unsigned char *digest,unsigned int *len,char *buffer);
void print_as_hex (unsigned char *digest, int len);
void calculate_md5_of(const void *content, ssize_t len,unsigned char *md_value,unsigned int *md_len);
