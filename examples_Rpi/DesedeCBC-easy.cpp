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
  byte ciphertext[calc_size(sizeof(plaintext))];
  byte plaintext_p[sizeof(ciphertext)];
  des.do_3des_encrypt(plaintext,sizeof(plaintext),ciphertext,"012345677654321001234567\0");
  printf(" Encryption took %f ms\n",(des.millis() - ms));
  ms = des.millis();
  des.do_3des_decrypt(ciphertext,sizeof(ciphertext),plaintext_p,"012345677654321001234567\0", des.get_IV_int());
  printf(" Decryption took %f ms\n",(des.millis() - ms));
  return 0;
}

int calc_size(int size){
	size = size + (8 - (size % 8)) - 1;
	return size;
}