/*
	DES.h - Library for DES and 3DES encryption and decryption
	Ported to the Arduino platform 2013 by Tim Riemann
   
	Original version taken from the AVR-Crypto-Lib
	(http://www.das-labor.org/wiki/AVR-Crypto-Lib)
	Copyright (C) 2006-2010  Daniel Otte (daniel.otte@rub.de)

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * \file     des.c
 * \author   Daniel Otte
 * \email    daniel.otte@rub.de
 * \date     2007-06-16
 * \brief    DES and EDE-DES implementation
 * \license      GPLv3 or later
 */

#ifndef DES_h
#define DES_h

#include "DES_config.h"

/* the FIPS 46-3 (1999-10-25) name for triple DES is triple data encryption algorithm so TDEA.
 * Also we only implement the three key mode  */

/** \def tdea_enc
 * \brief defining an alias for void tdes_enc(void* out, const void* in, const void* key)
 */

/** \def tdea_dec
 * \brief defining an alias for void tdes_dec(void* out, const void* in, const void* key)
 */
#define tdea_enc tdes_enc
#define tdea_dec tdes_dec

class DES
{
	public:
		/** \fn void decrypt(void* out, const void* in, const void* key)
		* \brief encrypt a block with DES
		* 
		* This function encrypts a block of 64 bits (8 bytes) with the DES algorithm.
		* Key expansion is done automatically. The key is 64 bits long, but note that
		* only 56 bits are used (the LSB of each byte is dropped). The input and output
		* blocks may overlap.
		* 
		* \param out pointer to the block (64 bit = 8 byte) where the ciphertext is written to
		* \param in  pointer to the block (64 bit = 8 byte) where the plaintext is read from
		* \param key pointer to the key (64 bit = 8 byte)
		*/
		void encrypt(void* out, const void* in, const void* key);
		
		/** \fn void encrypt(void* out, const void* in, const void* key)
		* \brief decrypt a block with DES
		* 
		* This function decrypts a block of 64 bits (8 bytes) with the DES algorithm.
		* Key expansion is done automatically. The key is 64 bits long, but note that
		* only 56 bits are used (the LSB of each byte is dropped). The input and output
		* blocks may overlap.
		* 
		* \param out pointer to the block (64 bit = 8 byte) where the plaintext is written to
		* \param in  pointer to the block (64 bit = 8 byte) where the ciphertext is read from
		* \param key pointer to the key (64 bit = 8 byte)
		*/
		void decrypt(void* out, const void* in, const uint8_t* key);
		
		/** \fn void tripleEncrypt(void* out, const void* in, const void* key)
		* \brief encrypt a block with Tripple-DES
		* 
		* This function encrypts a block of 64 bits (8 bytes) with the Tripple-DES (EDE)
		* algorithm. Key expansion is done automatically. The key is 192 bits long, but
		* note that only 178 bits are used (the LSB of each byte is dropped). The input
		* and output blocks may overlap.
		* 
		* \param out pointer to the block (64 bit = 8 byte) where the ciphertext is written to
		* \param in  pointer to the block (64 bit = 8 byte) where the plaintext is read from
		* \param key pointer to the key (192 bit = 24 byte)
		*/
		void tripleEncrypt(void* out, void* in, const void* key);

		/** \fn void tripleDecrypt(void* out, const void* in, const void* key)
		* \brief decrypt a block with Tripple-DES
		* 
		* This function decrypts a block of 64 bits (8 bytes) with the Tripple-DES (EDE)
		* algorithm. Key expansion is done automatically. The key is 192 bits long, but
		* note that only 178 bits are used (the LSB of each byte is dropped). The input
		* and output blocks may overlap.
		* 
		* \param out pointer to the block (64 bit = 8 byte) where the plaintext is written to
		* \param in  pointer to the block (64 bit = 8 byte) where the ciphertext is read from
		* \param key pointer to the key (192 bit = 24 byte)
		*/
		void tripleDecrypt(void* out, void* in, const uint8_t* key);
		
		/** \fn DES()
		* \brief DES constructor
		* 
		* This function initialized an instance of DES
		*/
		DES();
		
		/** \fn void init(const void* m_key,unsigned long long int IVCl)
		* \brief initiallize the key and IVC and IV array
		* 
		* This function initialized the basic variables needed for 3DES
		* 
		* \param m_key (64 bit = 8 byte)
		* \param IVC int or hex value of iv , ex. 0x0000000000000001
		*/
		void init(const void* m_key,unsigned long long int IVCl);
		
		/** \fn void init(const void* m_key)
		* \brief initiallize the key
		* 
		* This function initialized the basic variables needed for DES
		* 
		* \param m_key (64 bit = 8 byte)
		*/
		void init(const void* m_key);
		
		/** \fn void change_key(const char* m_key);
		* \brief change the key for DEs and 3DES
		* 
		* This function changes the key variable needed for DES
		* 
		* \param m_key (64 bit = 8 byte)
		*/
		void change_key(const void* m_key);
		
		/** \fn void change_IV(unsigned long long int IVCl);
		* \brief Change IVC and iv
		* 
		* This function changes the ivc and iv variables needed for 3DES
		* 
		* \param IVC int or hex value of iv , ex. 0x0000000000000001
		*/
		void change_IV(unsigned long long int IVCl);
		
		/** \fn voiv_inc()
		* \brief inrease the IVC and iv but 1
		* 
		* This function increased the VI by one step in order to have a different IV each time
		* 
		*/
		void iv_inc();
		
		/** \fn get_key()
		* \brief getter method for key
		* 
		* This function return the key
		* 
		*/
		byte* get_key();
		
		/** \fn get_size()
		* \brief getter method for size
		* 
		* This function return the size
		* 
		*/
		int get_size();
		
		/** \fn calc_size_n_pad(uint8_t p_size)
		* \brief calculates the size of the plaintext and the padding
		* 
		* calculates the size of theplaintext with the padding
		* and the size of the padding needed. Moreover it stores them in their variables.
		* 
		* \param m_plaintext the string of the plaintext in a byte array
		* \param p_size the size of the byte array ex sizeof(plaintext)
		*/
		void calc_size_n_pad(int p_size);
		
		/** \fn padPlaintext(void* in,byte* out)
		* \brief pads the plaintext
		* 
		* This function pads the plaintext and returns an char array with the 
		* plaintext and the padding in order for the plaintext to be compatible with 
		* 8bit size blocks required by 3DES
		* 
		* \param in the string of the plaintext in a byte array
		*/
		void padPlaintext(void* in,byte* out);
		
		/** \fn CheckPad(void* in,int size)
		* \brief check the if the padding is correct
		* 
		* This functions checks the padding of the plaintext.
		* 
		* \param in the string of the plaintext in a byte array
		* \param the size of the string
		* \return true if correct / false if not
		*/
		bool CheckPad(byte* in,int size);
		
		/** \fn tdesCbcEncipher(byte* in,byte* out)
		* \brief the main encrypt 3DES with IV function
		* 
		* This function uses the IV to xor (^) the first block of the string
		* and encrypts it using tripleEncrypt function 
		* 
		* \param in the string of the plaintext in a byte array
		*/
		void tdesCbcEncipher(byte* in,byte* out);
		
		/** \fn tdesCbcDecipher(byte* in,byte* out)
		* \brief the main decrypt 3DES with IV function
		* 
		* This function if the reverse of the tdesCbcEncipher function.
		* used the IV and then the tripleDecrypt
		* 
		* \param in the string of the plaintext in a byte array
		*/
		void tdesCbcDecipher(byte* in,byte* out);
		
		/** \fn tprintArray(byte output[],bool p_pad = false)
		* \brief Prints the array given
		* 
		* This function prints the given array with size equal \var size
		* and pad equal \var pad. It is mainlly used for debugging purpuses or to output the string.
		* 
		* \param output the string of the plaintext in a byte array
		* \param p_pad optional, used to print with out the padding characters
		*/
		void printArray(byte output[],bool p_pad = false);
		void printArray(byte output[],int sizel);
		#if defined(DES_LINUX)
			unsigned long millis();
		#endif
	private:
		void permute(const uint8_t *ptable, const uint8_t *in, uint8_t *out);
		void changeendian32(uint32_t * a);
		inline void shiftkey(uint8_t *key);
		inline void shiftkey_inv(uint8_t *key);
		inline uint64_t splitin6bitwords(uint64_t a);
		inline uint8_t substitute(uint8_t a, uint8_t * sbp);
		uint32_t des_f(uint32_t r, uint8_t* kr);
		byte key[24];
		unsigned long long int IVC;
		byte iv[8];
		int pad;
		int size;
		#if defined(DES_LINUX)
			timeval tv;
			byte arr_pad[7];
		#else
			byte arr_pad[7] = { 0x01,0x02,0x03,0x04,0x05,0x06,0x07 };
		#endif
};

#endif
