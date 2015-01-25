#include "DES.h"

const uint8_t sbox[256] PROGMEM = {
  /* S-box 1 */
  0xE4, 0xD1, 0x2F, 0xB8, 0x3A, 0x6C, 0x59, 0x07,
  0x0F, 0x74, 0xE2, 0xD1, 0xA6, 0xCB, 0x95, 0x38,
  0x41, 0xE8, 0xD6, 0x2B, 0xFC, 0x97, 0x3A, 0x50,
  0xFC, 0x82, 0x49, 0x17, 0x5B, 0x3E, 0xA0, 0x6D,
  /* S-box 2 */
  0xF1, 0x8E, 0x6B, 0x34, 0x97, 0x2D, 0xC0, 0x5A,
  0x3D, 0x47, 0xF2, 0x8E, 0xC0, 0x1A, 0x69, 0xB5,
  0x0E, 0x7B, 0xA4, 0xD1, 0x58, 0xC6, 0x93, 0x2F,
  0xD8, 0xA1, 0x3F, 0x42, 0xB6, 0x7C, 0x05, 0xE9,
  /* S-box 3 */
  0xA0, 0x9E, 0x63, 0xF5, 0x1D, 0xC7, 0xB4, 0x28,
  0xD7, 0x09, 0x34, 0x6A, 0x28, 0x5E, 0xCB, 0xF1,
  0xD6, 0x49, 0x8F, 0x30, 0xB1, 0x2C, 0x5A, 0xE7,
  0x1A, 0xD0, 0x69, 0x87, 0x4F, 0xE3, 0xB5, 0x2C,
  /* S-box 4 */
  0x7D, 0xE3, 0x06, 0x9A, 0x12, 0x85, 0xBC, 0x4F,
  0xD8, 0xB5, 0x6F, 0x03, 0x47, 0x2C, 0x1A, 0xE9,
  0xA6, 0x90, 0xCB, 0x7D, 0xF1, 0x3E, 0x52, 0x84,
  0x3F, 0x06, 0xA1, 0xD8, 0x94, 0x5B, 0xC7, 0x2E,
  /* S-box 5 */
  0x2C, 0x41, 0x7A, 0xB6, 0x85, 0x3F, 0xD0, 0xE9,
  0xEB, 0x2C, 0x47, 0xD1, 0x50, 0xFA, 0x39, 0x86,
  0x42, 0x1B, 0xAD, 0x78, 0xF9, 0xC5, 0x63, 0x0E,
  0xB8, 0xC7, 0x1E, 0x2D, 0x6F, 0x09, 0xA4, 0x53,
  /* S-box 6 */
  0xC1, 0xAF, 0x92, 0x68, 0x0D, 0x34, 0xE7, 0x5B,
  0xAF, 0x42, 0x7C, 0x95, 0x61, 0xDE, 0x0B, 0x38,
  0x9E, 0xF5, 0x28, 0xC3, 0x70, 0x4A, 0x1D, 0xB6,
  0x43, 0x2C, 0x95, 0xFA, 0xBE, 0x17, 0x60, 0x8D,
  /* S-box 7 */
  0x4B, 0x2E, 0xF0, 0x8D, 0x3C, 0x97, 0x5A, 0x61,
  0xD0, 0xB7, 0x49, 0x1A, 0xE3, 0x5C, 0x2F, 0x86,
  0x14, 0xBD, 0xC3, 0x7E, 0xAF, 0x68, 0x05, 0x92,
  0x6B, 0xD8, 0x14, 0xA7, 0x95, 0x0F, 0xE2, 0x3C,
  /* S-box 8 */
  0xD2, 0x84, 0x6F, 0xB1, 0xA9, 0x3E, 0x50, 0xC7,
  0x1F, 0xD8, 0xA3, 0x74, 0xC5, 0x6B, 0x0E, 0x92,
  0x7B, 0x41, 0x9C, 0xE2, 0x06, 0xAD, 0xF3, 0x58,
  0x21, 0xE7, 0x4A, 0x8D, 0xFC, 0x90, 0x35, 0x6B
};
	
const uint8_t e_permtab[] PROGMEM = {
         4,  6,                                         /* 4 bytes in 6 bytes out*/
        32,  1,  2,  3,  4,  5,
         4,  5,  6,  7,  8,  9,
         8,  9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32,  1
};
	
const uint8_t p_permtab[] PROGMEM = {
         4,  4,                                         /* 32 bit -> 32 bit */
        16,  7, 20, 21,
        29, 12, 28, 17,
         1, 15, 23, 26,
         5, 18, 31, 10,
         2,  8, 24, 14,
        32, 27,  3,  9,
        19, 13, 30,  6,
        22, 11,  4, 25
};
	
const uint8_t ip_permtab[] PROGMEM = {
         8,  8,                                         /* 64 bit -> 64 bit */
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17,  9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
};
	
const uint8_t inv_ip_permtab[] PROGMEM = {
         8, 8,                                          /* 64 bit -> 64 bit */
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41,  9, 49, 17, 57, 25
};

const uint8_t pc1_permtab[] PROGMEM = {
         8,  7,                                         /* 64 bit -> 56 bit*/
        57, 49, 41, 33, 25, 17,  9,
         1, 58, 50, 42, 34, 26, 18,
        10,  2, 59, 51, 43, 35, 27,
        19, 11,  3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
         7, 62, 54, 46, 38, 30, 22,
        14,  6, 61, 53, 45, 37, 29,
        21, 13,  5, 28, 20, 12,  4
};

const uint8_t pc2_permtab[] PROGMEM = {
         7,      6,                                     /* 56 bit -> 48 bit */
        14, 17, 11, 24,  1,  5,
         3, 28, 15,  6, 21, 10,
        23, 19, 12,  4, 26,  8,
        16,  7, 27, 20, 13,  2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
};

const uint8_t splitin6bitword_permtab[] PROGMEM = {
         8,  8,                                         /* 64 bit -> 64 bit */
        64, 64,  1,  6,  2,  3,  4,  5, 
        64, 64,  7, 12,  8,  9, 10, 11, 
        64, 64, 13, 18, 14, 15, 16, 17, 
        64, 64, 19, 24, 20, 21, 22, 23, 
        64, 64, 25, 30, 26, 27, 28, 29, 
        64, 64, 31, 36, 32, 33, 34, 35, 
        64, 64, 37, 42, 38, 39, 40, 41, 
        64, 64, 43, 48, 44, 45, 46, 47 
};

const uint8_t shiftkey_permtab[] PROGMEM = {
         7,  7,                                         /* 56 bit -> 56 bit */
         2,  3,  4,  5,  6,  7,  8,  9,
        10, 11, 12, 13, 14, 15, 16, 17,
        18, 19, 20, 21, 22, 23, 24, 25, 
        26, 27, 28,  1, 
        30, 31, 32, 33, 34, 35, 36, 37, 
        38, 39, 40, 41, 42, 43, 44, 45, 
        46, 47, 48, 49, 50, 51, 52, 53, 
        54, 55, 56, 29
};

const uint8_t shiftkeyinv_permtab[] PROGMEM = {
         7,  7,
        28,  1,  2,  3,  4,  5,  6,  7,
         8,  9, 10, 11, 12, 13, 14, 15,
        16, 17, 18, 19, 20, 21, 22, 23,
        24, 25, 26, 27,
        56, 29, 30, 31, 32, 33, 34, 35, 
        36, 37, 38, 39, 40, 41, 42, 43, 
        44, 45, 46, 47, 48, 49, 50, 51, 
        52, 53, 54, 55
};

/*
1 0
1 0
2 1
2 1
2 1
2 1
2 1
2 1
----
1 0
2 1
2 1
2 1
2 1
2 1
2 1
1 0
*/
#define ROTTABLE      0x7EFC 
#define ROTTABLE_INV  0x3F7E
/******************************************************************************/
DES::DES(){
	sprintf((char *)key,"000000000000000000000000\0");
	byte ar_iv[8] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
	memcpy(iv,ar_iv,8);
	memcpy(&IVC,ar_iv,8);
 	arr_pad[0] = 0x01;
	arr_pad[1] = 0x02;
	arr_pad[2] = 0x03;
	arr_pad[3] = 0x04;
	arr_pad[4] = 0x05;
	arr_pad[5] = 0x06;
	arr_pad[6] = 0x07;
}

/*****************************************************************************/

void DES::init(const void* m_key,unsigned long long int IVCl){
	sprintf((char *)key,"%s",m_key);
	memcpy(iv,&IVCl,8);
	IVC = IVCl;
}

/*****************************************************************************/

void DES::init(const void* m_key){
	sprintf((char *)key,"%s",m_key);
}

/*****************************************************************************/

void DES::change_key(const void* m_key){
	sprintf((char *)key,"000000000000000000000000\0");
	sprintf((char *)key,"%s",m_key);
}

/*****************************************************************************/

void DES::set_IV(unsigned long long int IVCl){
	memcpy(iv,&IVCl,8);
	IVC = IVCl;
}

/******************************************************************************/

void DES::get_IV(byte *out){
	memcpy(out,&IVC,8);
}

/******************************************************************************/

unsigned long long int get_IV_int(){
	return IVC;
}

/*****************************************************************************/

void DES::permute(const uint8_t *ptable, const uint8_t *in, uint8_t *out){
        uint8_t ob; /* in-bytes and out-bytes */
        uint8_t byte, bit; /* counter for bit and byte */
        ob = pgm_read_byte(&ptable[1]);
        ptable = &(ptable[2]);
        for(byte=0; byte<ob; ++byte){
                uint8_t x,t=0;
                for(bit=0; bit<8; ++bit){
                        x = pgm_read_byte(ptable++) -1 ;
                                t <<= 1;
                        if((in[x/8]) & (0x80>>(x%8)) ){
                                t|=0x01;
                        }
                }
                out[byte]=t;
        }
}

/******************************************************************************/

void DES::changeendian32(uint32_t * a){
        *a = (*a & 0x000000FF) << 24 |
                 (*a & 0x0000FF00) <<  8 |
                 (*a & 0x00FF0000) >>  8 |
                 (*a & 0xFF000000) >> 24;
}

/******************************************************************************/
//static inline
void DES::shiftkey(uint8_t *key){
        uint8_t k[7];
        memcpy(k, key, 7);
        permute((uint8_t*)shiftkey_permtab, k, key);    
}

/******************************************************************************/
//static inline
void DES::shiftkey_inv(uint8_t *key){
        uint8_t k[7];
        memcpy(k, key, 7);
        permute((uint8_t*)shiftkeyinv_permtab, k, key);
        
}

/******************************************************************************/
//static inline
uint64_t DES::splitin6bitwords(uint64_t a){
        uint64_t ret=0;
        a &= 0x0000ffffffffffffLL;
        permute((uint8_t*)splitin6bitword_permtab, (uint8_t*)&a, (uint8_t*)&ret);       
        return ret;
}

/******************************************************************************/

//static inline
uint8_t DES::substitute(uint8_t a, uint8_t * sbp){
        uint8_t x;      
        x = pgm_read_byte(&sbp[a>>1]);
        x = (a&1)?x&0x0F:x>>4;
        return x;
        
}

/******************************************************************************/

uint32_t DES::des_f(uint32_t r, uint8_t* kr){
        uint8_t i;
        uint32_t t=0,ret;
        uint64_t data;
        uint8_t *sbp; /* sboxpointer */ 
        permute((uint8_t*)e_permtab, (uint8_t*)&r, (uint8_t*)&data);
        for(i=0; i<7; ++i)
                ((uint8_t*)&data)[i] ^= kr[i];
        
        /* Sbox substitution */
        data = splitin6bitwords(data);
        sbp=(uint8_t*)sbox;
        for(i=0; i<8; ++i){
                uint8_t x;
                x = substitute(((uint8_t*)&data)[i], sbp);
                t <<= 4;
                t |= x;
                sbp += 32;
        }
        changeendian32(&t);
                
        permute((uint8_t*)p_permtab,(uint8_t*)&t, (uint8_t*)&ret);

        return ret;
}

/******************************************************************************/

void DES::encrypt(void* out, const void* in, const void* key){
#define R (data.v32[1])
#define L (data.v32[0])

        uint8_t kr[6],k[7];
        uint8_t i;
        union {
                uint8_t v8[8];
                uint32_t v32[2];
        } data;
        
        permute((uint8_t*)ip_permtab, (uint8_t*)in, data.v8);
        permute((uint8_t*)pc1_permtab, (const uint8_t*)key, k);
        for(i=0; i<8; ++i){
                shiftkey(k);
                if(ROTTABLE&((1<<((i<<1)+0))) )
                        shiftkey(k);
                permute((uint8_t*)pc2_permtab, k, kr);
                L ^= des_f(R, kr);
                
                shiftkey(k);
                if(ROTTABLE&((1<<((i<<1)+1))) )
                        shiftkey(k);
                permute((uint8_t*)pc2_permtab, k, kr);
                R ^= des_f(L, kr);

        }
        /* L <-> R*/
        R ^= L;
        L ^= R;
        R ^= L;
        permute((uint8_t*)inv_ip_permtab, data.v8, (uint8_t*)out);
}

/******************************************************************************/

void DES::decrypt(void* out, const void* in, const uint8_t* key){
        uint8_t kr[6],k[7];
        union {
                uint8_t v8[8];
                uint32_t v32[2];
        } data;
        int8_t i;
        permute((uint8_t*)ip_permtab, (uint8_t*)in, data.v8);
        permute((uint8_t*)pc1_permtab, (const uint8_t*)key, k);
        for(i=7; i>=0; --i){
                
                permute((uint8_t*)pc2_permtab, k, kr);
                L ^= des_f(R, kr);
                shiftkey_inv(k);
                if(ROTTABLE&((1<<((i<<1)+1))) ){
                        shiftkey_inv(k);
                }

                permute((uint8_t*)pc2_permtab, k, kr);
                R ^= des_f(L, kr);
                shiftkey_inv(k);
                if(ROTTABLE&((1<<((i<<1)+0))) ){
                        shiftkey_inv(k);
                }

        }
        /* L <-> R*/
        R ^= L;
        L ^= R;
        R ^= L;
        permute((uint8_t*)inv_ip_permtab, data.v8, (uint8_t*)out);
}

/******************************************************************************/

void DES::tripleEncrypt(void* out, void* in, const void* key){
        encrypt(out,  in, (uint8_t*)key + 0);
        decrypt(out, out, (uint8_t*)key + 8);
        encrypt(out, out, (uint8_t*)key +16);
}

/******************************************************************************/

void DES::tripleDecrypt(void* out, void* in, const uint8_t* key){
        decrypt(out,  in, (uint8_t*)key +16);
        encrypt(out, out, (uint8_t*)key + 8);
        decrypt(out, out, (uint8_t*)key + 0);
}

/******************************************************************************/

void DES::iv_inc(){
	IVC += 1;
	memcpy(iv,&IVC,8);
}
/******************************************************************************/

byte* DES::get_key(){
	return key;
}

/******************************************************************************/

int DES::get_size(){
	return size;
}

/******************************************************************************/

void DES::set_size(int sizel){
	size = sizel;
}


/******************************************************************************/

void DES::calc_size_n_pad(int p_size){
	int s_of_p = p_size - 1;
	if ( s_of_p % 8 == 0){
      size = s_of_p;
	}else{
		size = s_of_p +  (8-(s_of_p % 8));
	}
	pad = size - s_of_p;
}		

/******************************************************************************/

void DES::padPlaintext(void* in,byte* out)
{
	memcpy(out,in,size);
	for (int i = size-pad; i < size; i++){;
		out[i] = arr_pad[pad - 1];
	}
}

/******************************************************************************/

bool DES::CheckPad(byte* in,int lsize){
	if (in[lsize-1] <= 0x08){	
		int lpad = (int)in[lsize-1];
		for (int i = lsize - 1; i >= lsize-lpad; i--){
			if (arr_pad[lpad - 1] != in[i]){
				return false;
			}
		}
	}else{
		return true;
	}
return true;
}
/******************************************************************************/

void DES::tdesCbcEncipher(byte* in,byte* out)
{
  #if defined(DES_PRINT)
	printf_P(PSTR("\n"));
	printf_P(PSTR("====== Triple-DES CBC encipher test ======\n"));
	printf_P(PSTR("Encrypt..."));
  #endif
  for (int i = 0; i < size; i += 8)
  {
    //CBC algorithm
    //IMPORTANT: THIS WILL MODIFY THE INPUT ARRAY!!!
    for (uint8_t xorIdx = 0; xorIdx < 8; xorIdx++)
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
    
    tripleEncrypt(out + i, in + i, key);
  }
  #if defined(DES_PRINT)
	printArray(out);
  #endif
}

/******************************************************************************/

void DES::tdesCbcDecipher(byte* in,byte* out)
{
  #if defined(DES_PRINT)
	printf_P(PSTR("\n"));
	printf_P(PSTR("====== Triple-DES CBC decipher test ======\n"));
	printf_P(PSTR("Decrypt..."));
  #endif
  for (int i = 0; i < size; i += 8)
  {
    tripleDecrypt(out + i, in + i, key);
    
    //CBC algorithm
    for (uint8_t xorIdx = 0; xorIdx < 8; xorIdx++)
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
  #if defined(DES_PRINT)
	printArray((byte*)out,(bool)true);
  #endif
}

/******************************************************************************/

void DES::printArray(byte output[],bool p_pad)
{
uint8_t i,j;
uint8_t loops = size/8;
uint8_t outp = 8;
for (j = 0; j < loops; j += 1){
  if (p_pad && (j == (loops  - 1)) ) { outp = 8 - pad; }
  for (i = 0; i < outp; i++)
  {
    printf_P(PSTR("%c"),output[j*8 + i]);
  }
}
  printf_P(PSTR("\n"));
}

/******************************************************************************/

void DES::printArray(byte output[],int sizel)
{
  for (int i = 0; i < sizel; i++)
  {
    printf_P(PSTR("%x"),output[i]);
  }
  printf_P(PSTR("\n"));
}

/******************************************************************************/

void DES::do_3des_encrypt(byte *plain,int size_p,byte *cipher,const void *key){
	iv_inc();
	calc_size_n_pad(size_p);
	byte plain_p[get_size()];
	padPlaintext(plain,plain_p);
	change_key (key);
	tdesCbcEncipher(plain_p,cipher);
}

/******************************************************************************/

void DES::do_3des_dencrypt(byte *cipher,int size_c,byte *plain,const void *key, unsigned long long int ivl){
	size = size_c;
	change_key (key);
	set_IV(ivl);
	tdesCbcDecipher(cipher,plain);
}


/******************************************************************************/
#if defined(DES_LINUX)
double DES::millis(){
	gettimeofday(&tv, NULL);
	return (tv.tv_sec + 0.000001 * tv.tv_usec);
}
#endif
