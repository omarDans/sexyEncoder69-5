#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>

extern const char b64chars[];
extern int b64invs[];

size_t b64_encoded_size(size_t inLen);
char *b64_encode(const unsigned char *in, size_t len);
size_t b64_decoded_size(const char *in);
int b64_isvalidchar(char c);
size_t b64_decode(const char *in, unsigned char *out, size_t number);

#endif