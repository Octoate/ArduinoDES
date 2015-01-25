#include <DES.h>
#include "./printf.h"

DES des;
unsigned long ms;

void setup() {
  Serial.begin(9600);
  delay(100);
  printf_begin();  
  delay(100);  

  printf("\n============================================\n");
  printf(" Triple DES sample for Arduino/Raspberry pi\n");
  printf("============================================\n");
  des.init("012345677654321001234567\0",(unsigned long long int)0);
}

void loop() {
  ms = micros();
  byte plaintext[] = "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
  byte ciphertext[calc_size(sizeof(plaintext))];
  byte plaintext_p[sizeof(ciphertext)];
  des.do_3des_encrypt(plaintext,sizeof(plaintext),ciphertext,"012345677654321001234567\0");
  printf(" Encryption took %lu micros\n",(micros()  - ms));
  ms = micros();
  des.calc_size_n_pad(sizeof(cyphertext));
  des.do_3des_decrypt(ciphertext,sizeof(ciphertext),plaintext_p,"012345677654321001234567\0", des.get_IV_int());
  printf(" Decryption took %lu micros",(micros() - ms));
  delay(2000);
}

int calc_size(int size){
	size = size + (8 - (size % 8)) - 1;
	return size;
}
