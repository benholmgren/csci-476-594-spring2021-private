// bn_sample.c
//
// To compile this example program, run:
//    $ gcc bn_sample.c -lcrypto

#include <stdio.h>
#include <openssl/bn.h>
#define NBITS 256

void printBN(char *msg, BIGNUM * a)
{
  // Use BN_bn2hex(a) for hex string
  // Use BN_bn2dec(a) for decimal string
  char * number_str = BN_bn2hex(a);
  printf("%s %s\n", msg, number_str);
  OPENSSL_free(number_str);
}

int main ()
{
  BN_CTX *ctx = BN_CTX_new();
  BIGNUM *p = BN_new();
  BIGNUM *q = BN_new();
  BIGNUM *e = BN_new();
  BIGNUM *n = BN_new();
  BIGNUM *o = BN_new();
  BIGNUM *totp = BN_new();
  BIGNUM *totq = BN_new();
  BIGNUM *totn = BN_new();
  BIGNUM *d = BN_new();
  BIGNUM *msg = BN_new();
  BIGNUM *enc = BN_new();
  BIGNUM *dec = BN_new();

  // Initialize p, q, n, and one
  BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
  BN_hex2bn(&e, "010001");
  BN_dec2bn(&o, "1");
  BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");

  // create message in hex
  BN_hex2bn(&msg, "4120746f702073656372657421");

  BN_hex2bn(&enc, "8C0F971DF2F3672B28811407E2DABBE1DA0FEBBBDFC7DCB67396567EA1E2493F");
  printBN("Encrypted version:", enc);

  BN_mod_exp(dec, enc, d, n, ctx);
  printBN("Decrypted hex:", dec);


  return 0;
}
