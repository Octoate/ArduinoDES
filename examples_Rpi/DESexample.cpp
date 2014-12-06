#include <DES.h>


void desTest();
void tdesTest();
void printArray(byte output[]);
double millis();

DES des;
timeval tv;

int main(int argc, char** argv) 
{
	printf("Hello!");
	desTest();
  	tdesTest();
	usleep(2000);
	return 0;
}

void desTest()
{
  byte out[8];
  byte in[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
  byte key[] = { 0x3b, 0x38, 0x98, 0x37, 0x15, 0x20, 0xf7, 0x5e };
  
  printf("\n");
  printf("========= DES test ==========\n");
  
  //encrypt
  printf("Encrypt...");
  double time = millis();
  des.encrypt(out, in, key);
  time = millis() - time;
  printf("done. (");
  printf("%f",time);
  printf(" ms)\n");
  printArray(out);
  
  //decrypt
  for (int i = 0; i < 8; i++)
  {
    in[i] = out[i];
  }
  printf("Decrypt...");
  time = millis();
  des.decrypt(out, in, key);
  time = millis() - time;
  printf("done. (");
  printf("%f",time);
  printf(" ms)\n");
  printArray(out);
}

void tdesTest()
{
  byte out[8];
  byte in[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
  byte key[] = { 
                  0x3b, 0x38, 0x98, 0x37, 0x15, 0x20, 0xf7, 0x5e, // key A
                  0x92, 0x2f, 0xb5, 0x10, 0xc7, 0x1f, 0x43, 0x6e, // key B
                  0x3b, 0x38, 0x98, 0x37, 0x15, 0x20, 0xf7, 0x5e, // key C (in this case A)
                };
  
  printf("\n");
  printf("====== Triple-DES test ======\n");
  
  //encrypt
  printf("Encrypt...");
  double time = millis();
  des.tripleEncrypt(out, in, key);
  time = millis() - time;
  printf("done. (");
  printf("%f",time);
  printf(" ms)\n");
  printArray(out);
  
  //decrypt
  for (int i = 0; i < 8; i++)
  {
    in[i] = out[i];
  }
  printf("Decrypt...");
  time = millis();
  des.tripleDecrypt(out, in, key);
  time = millis() - time;
  printf("done. (");
  printf("%f",time);
  printf(" ms)\n");
  printArray(out);
}

void printArray(byte output[])
{
  for (int i = 0; i < 8; i++)
  {
    if (output[i] < 0x10)
    {
      printf("0");
    }
    printf("%02X",output[i]);
    printf(" ");
  }
  printf("\n");
}

double millis(){
	gettimeofday(&tv, NULL);
	return (tv.tv_sec + 0.000001 * tv.tv_usec);
}
