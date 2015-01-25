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
  byte plaintext[] = "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
  byte ciphertext[des.get_size()];
  byte plaintext_p[des.get_size()];
  do_3des_encrypt(plaintext,sizeof(plaintext),ciphertext,"012345677654321001234567\0")
  printf(" Encryption took %f ms\n",(des.millis() - ms));
  ms = des.millis();
  do_3des_dencrypt(ciphertext,sizeof(ciphertext),plaintext_p,"012345677654321001234567\0", get_IV_int();
  printf(" Decryption took %f ms\n",(des.millis() - ms));
  return 0;
}
