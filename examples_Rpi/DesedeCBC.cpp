#include <DES.h>

#define MESSAGE_LENGTH 16

void tdesCbcEncipherTest();
void tdesCbcDecipherTest();
void printArray(byte output[]);
double millis();

DES des;
byte key[] =  { 
                0xDE, 0x4F, 0x86, 0xB8, 0x38, 0x94, 0x74, 0x75, // key A
                0x90, 0x13, 0x39, 0xE5, 0x96, 0x36, 0x94, 0x43, // key B
                0xDE, 0x4F, 0x86, 0xB8, 0x38, 0x94, 0x74, 0x75  // key C (in this case A)
              };
timeval tv;

int main(int argc, char** argv) 
{
	printf("Hello!");
	tdesCbcEncipherTest();
  	tdesCbcDecipherTest();
	usleep(2000);
	return 0;
}

void tdesCbcEncipherTest()
{
  byte out[MESSAGE_LENGTH];
  byte in[] = { 0xA3, 0xA7, 0x2C, 0x1F, 0xEC, 0x9F, 0x1E, 0x8B, 0xBC, 0x56, 0xC3, 0xA8, 0xF9, 0x47, 0x3C, 0xD6 };
  byte iv[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  
  printf("\n");
  printf("====== Triple-DES CBC encipher test ======\n");
  
  printf("Encrypt...");
  double time = millis();
  
  for (int i = 0; i < MESSAGE_LENGTH; i += 8)
  {
    //CBC algorithm
    //IMPORTANT: THIS WILL MODIFY THE INPUT ARRAY!!!
    for (byte xorIdx = 0; xorIdx < 8; xorIdx++)
    {
      // 0 -> use IV; >0 -> use ciphertext
      if (i == 0)
      {
        in[i + xorIdx] = in[i + xorIdx] ^ iv[xorIdx];
      }
      else
      {
        in[i + xorIdx] = in[i + xorIdx] ^ out[(i - 8) + xorIdx];
      }
    }
    
    des.tripleEncrypt((byte*)out + i, (byte*)in + i, key);
  }
  
  time = millis() - time;
  printf("done. (");
  printf("%f",time);
  printf(" ms)\n");
  
  for (int i = 0; i < MESSAGE_LENGTH; i += 8)
  {
    printArray((byte*)out + i);
  }
}

void tdesCbcDecipherTest()
{
  byte out[MESSAGE_LENGTH];
  byte in[] = { 0x68, 0x6C, 0x6B, 0x02, 0x21, 0x49, 0x0D, 0xB0, 0x0A, 0x5C, 0x53, 0x15, 0x42, 0x90, 0x84, 0xF4 };
  byte iv[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  
  printf("\n");
  printf("====== Triple-DES CBC decipher test ======\n");
  
  printf("Decrypt...");
  double time = millis();
  
  for (int i = 0; i < MESSAGE_LENGTH; i += 8)
  {
    des.tripleDecrypt((byte*)out + i, (byte*)in + i, key);
    
    //CBC algorithm
    for (byte xorIdx = 0; xorIdx < 8; xorIdx++)
    {
      // 0 -> use IV; >0 -> use ciphertext
      if (i == 0)
      {
        out[i + xorIdx] = out[i + xorIdx] ^ iv[xorIdx];
      }
      else
      {
        out[i + xorIdx] = out[i + xorIdx] ^ in[(i - 8) + xorIdx];
      }
    }
  }
  
  time = millis() - time;
  printf("done. (");
  printf("%f",time);
  printf(" ms)\n");
  
  for (int i = 0; i < MESSAGE_LENGTH; i += 8)
  {
    printArray((byte*)out + i);
  }
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
