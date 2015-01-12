#include <DES.h>
#include "printf.h"

DES des;
double ms;

int main(int argc, char** argv) {
  printf("\n============================================\n");
  printf(" Triple DES sample for Arduino/Raspberry pi\n");
  printf("============================================\n");
  des.init("012345677654321001234567\0",(unsigned long long int)0);
  
  ms = des.millis();
  des.iv_inc();
  byte plaintext[] = "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
  des.calc_size_n_pad(sizeof(plaintext));
  byte plaintext_p[des.get_size()];
  des.padPlaintext(plaintext,plaintext_p);
  byte cyphertext[des.get_size()];
  des.tdesCbcEncipher(plaintext_p,cyphertext);
  printf(" Encryption took %f ms\n",(des.millis() - ms));
  ms = des.millis();
  des.calc_size_n_pad(sizeof(cyphertext));
  des.tdesCbcDecipher(cyphertext,plaintext_p);
  bool ok = des.CheckPad(plaintext_p,sizeof(plaintext_p));
  if (ok)
    printf("padding ok!");
  else
    printf("padding corrupted!"); 
  printf(" Decryption took %f ms",(des.millis() - ms));
  return 0;
}
