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

  // Initialize p, q, n, and one
  BN_hex2bn(&p, "F7E75FDC469067FFDC4E847C51F452DF");
  BN_hex2bn(&q, "E85CED54AF57E53E092113E62F436F4F");
  BN_hex2bn(&e, "0D88C3");
  BN_dec2bn(&o, "1");

  // Init p-1, q-1 (totients acting on p and q)
  BN_sub(totp, p, o);
  BN_sub(totq, q, o);
  // Init totient(n) by totp*totq
  BN_mul(totn, totp, totq, ctx);

  // compute n = p*q... we don't actually need it but sanity check
  BN_mul(n, p, q, ctx);

  // find mod inverse of e mod n
  BN_mod_inverse(d, e, totn, ctx);
  printBN("Solution to task 1: d=", d);

  // create message in hex
  BN_hex2bn(&msg, "5468697320697320736f6d652073656e73697469766520696e666f2c20796f2e");

  BN_mod_exp(enc, msg, e, n, ctx);
  printBN("Solution to task 2: a^e mod n =", enc);

  return 0;
}
