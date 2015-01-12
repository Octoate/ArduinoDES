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
  des.iv_inc();
  byte plaintext[] = "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
  des.calc_size_n_pad(sizeof(plaintext));
  byte plaintext_p[des.get_size()];
  des.padPlaintext(plaintext,plaintext_p);
  byte cyphertext[des.get_size()];
  des.tdesCbcEncipher(plaintext_p,cyphertext);
  printf(" Encryption took %lu micros\n",(micros()  - ms));
  ms = micros();
  des.calc_size_n_pad(sizeof(cyphertext));
  des.tdesCbcDecipher(cyphertext,plaintext_p);
  bool ok = des.CheckPad(plaintext_p,sizeof(plaintext_p));
  if (ok)
    printf("padding ok!");
  else
    printf("padding corrupted!");
  printf(" Decryption took %lu micros",(micros() - ms));
  delay(2000);
}
