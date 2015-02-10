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
 * @file DES.h
 *
 * Class declaration for DES / 3DES and helper enums
 */

#ifndef DES_h
#define DES_h

#include "DES_config.h"

/* the FIPS 46-3 (1999-10-25) name for triple DES is triple data encryption algorithm so TDEA.
 * Also we only implement the three key mode  */

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
		* \param IVCl int or hex value of iv , ex. 0x0000000000000001
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
		* \param IVCl int or hex value of iv , ex. 0x0000000000000001
		*/
		void set_IV(unsigned long long int IVCl);
		
		/** Getter method for IV
		 * 
		 * This function return the IV
		 * @param *out byte pointer that gets the IV.
		 * @return none, the IV is writed to the out pointer.
		 */
		void get_IV(byte *out);
		
		/** Getter method for IV
		 * 
		 * This function return the IV
		 * @param out byte pointer that gets the IV.
		 * @return none, the IV is writed to the out pointer.
		 */
		unsigned long long int get_IV_int();
		
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
		* @return returns the key
		
		*/
		byte* get_key();
		
		/** \fn get_size()
		* \brief getter method for size
		* 
		* This function return the size
		* @return returns the size
		
		*/
		int get_size();
		
		/** Setter method for size
		 *
		 * This function sets the size of the plaintext+pad
		 * 
		 */
		 void set_size(int sizel);
		
		/** \fn calc_size_n_pad(uint8_t p_size)
		* \brief calculates the size of the plaintext and the padding
		* 
		* calculates the size of theplaintext with the padding
		* and the size of the padding needed. Moreover it stores them in their variables.
		* 
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
		* \param out the string of the padded plaintext in a byte array
		*/
		void padPlaintext(void* in,byte* out);
		
		/** \fn CheckPad(void* in,int size)
		* \brief check the if the padding is correct
		* 
		* This functions checks the padding of the plaintext.
		* 
		* \param *in the string of the plaintext in a byte array
		* \param size the size of the string
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
		* \param out the string of the ciphertext in a byte array
		*/
		void tdesCbcEncipher(byte* in,byte* out);
		
		/** \fn tdesCbcDecipher(byte* in,byte* out)
		* \brief the main decrypt 3DES with IV function
		* 
		* This function if the reverse of the tdesCbcEncipher function.
		* used the IV and then the tripleDecrypt
		* 
		* \param in the string of the ciphertext in a byte array
		* \param out the string of the plaintext in a byte array
		*/
		void tdesCbcDecipher(byte* in,byte* out);
		
		/** \fn tprintArray(byte output[],bool p_pad = true)
		* \brief Prints the array given
		* 
		* This function prints the given array with size equal \var size
		* and pad equal \var pad. It is mainlly used for debugging purpuses or to output the string.
		* 
		* \param output the string of the plaintext in a byte array
		* \param p_pad optional, used to print with out the padding characters
		*/
		void printArray(byte output[],bool p_pad = true);
		
		/** Prints the array given.
		 * 
		 * This function prints the given array in Hexadecimal.
		 * 
		 * @param output[] the string of the text in a byte array
		 * @param sizel the size of the array.
		 */
		void printArray(byte output[],int sizel);
		
		/** User friendly implementation of AES-CBC encryption.
		 * 
	     * @param *plain pointer to the plaintext
		 * @param size_p size of the plaintext
		 * @param *cipher pointer to the ciphertext
		 * @param *key pointer to the key that will be used.
		 * @param inc optional parameter to automaticaly increase IV
		 * @note The key will be stored in class variable.
		 */
		void do_3des_encrypt(byte *plain,int size_p,byte *cipher,const void *key, bool inc = false);
	
		/** User friendly implementation of AES-CBC decryption.
		* 
		* @param *cipher pointer to the ciphertext
		* @param size_c size of the ciphertext
		* @param *plain pointer to the plaintext
		* @param *key pointer to the key that will be used.
		* @param ivl the initialization vector IV that will be used for decryption.
		* @note The key will be stored in class variable.
		*/
	void do_3des_decrypt(byte *cipher,int size_c,byte *plain,const void *key, unsigned long long int ivl);
		#if defined(DES_LINUX)
			/**
			 * used in linux in order to retrieve the time in milliseconds.
			 *
			 * @return returns the milliseconds in a double format.
			 */
			double millis();
		#endif
	private:
		/** Permutation for DES.
		 * @param *ptable the permutaion table to be used.
		 * @param *in the pointer that holds the data before the permutations.
		 * @param *out the pointer that holds the data after the permutation.
		 * @return none, the output is inside the out pointer
		 *
		 */
		void permute(const uint8_t *ptable, const uint8_t *in, uint8_t *out);
		
		/** change endian form.
		 *  @param *a the byte to change endian
		 */
		void changeendian32(uint32_t * a);
		
		/** used to shift the key.
		 * Used the shiftkey_permtab permutation table.
		 * @param *key the key to be shifted.
		 *
		 */
		inline void shiftkey(uint8_t *key);
		
		/** used to shift the key back.
		 * Used the shiftkeyinv_permtab permutation table.
		 * @param *key the key to be shifted.
		 *
		 */
		inline void shiftkey_inv(uint8_t *key);
		
		/** splits in 6 bit words
		 * 
		 *  @param a uint64_t size that will be slitted, permuted and returned.
		 *  @return the permuted a.
		 *
		 */
		inline uint64_t splitin6bitwords(uint64_t a);
		
		/** main function for the substitutions
		 *  @param a array position
		 *  @param *sbp array to read byte from
		 *  @returns the substituted byte.
		 *
		 */
		inline uint8_t substitute(uint8_t a, uint8_t * sbp);
		
		/** Primary function of DES.
		 *  Used in encryption and decryption process.
		 *
		 *  @param r unsigned intefer 32 bit, Data to be permuted.
		 *  @param kr pointer of unsigned integers 8 bit, Data to be XOR with r after permutation
		 *  @return
		 *
		 */
		uint32_t des_f(uint32_t r, uint8_t* kr);
		byte key[24];/**< holds the key for the encryption */
		unsigned long long int IVC;/**< holds the initialization vector counter in numerical format. */
		byte iv[8];/**< holds the initialization vector that will be used in the cipher. */
		int pad;/**< holds the size of the padding. */
		int size;/**< hold the size of the plaintext to be ciphered */
		#if defined(DES_LINUX)
			timeval tv;/**< holds the time value on linux */
		#endif
			
		byte arr_pad[7];/**< holds the hexadecimal padding values, initialisation in the constructor */
};

#endif
/**
 * @example DESexample.ino
 * <b>For Arduino</b><br>
 * <b>Updated: spaniakos 2015 </b><br>
 *
 * A simple example demonstrating the DES encyption decruption use using Hexadecimal values.
 */
 
 /**
 * @example DESexample.cpp
 * <b>For Rasberry pi</b><br>
 * <b>Updated: spaniakos 2015 </b><br>
 *
 * A simple example demonstrating the DES encyption decruption use using Hexadecimal values.
 */
 
 /**
 * @example DesedeCBCexample.ino
 * <b>For Arduino</b><br>
 * <b>Updated: spaniakos 2015 </b><br>
 *
 * This example dempnstrates how to implement: <br />
 * <ul>
 * <li>3des Encryption</li>
 * <li>3des Decyption</li>
 * <li>Padding check</li>
 * </ul><br />
 * Using all functions manually.
 */
 
 /**
 * @example DesedeCBCexample.cpp
 * <b>For Rasberry pi</b><br>
 * <b>Updated: spaniakos 2015 </b><br>
 *
 * This example dempnstrates how to implement: <br />
 * <ul>
 * <li>3des Encryption</li>
 * <li>3des Decyption</li>
 * <li>Padding check</li>
 * </ul><br />
 * Using all function manually
 */
 
 /**
 * @example DesedeCBC-easy.ino
 * <b>For Arduino</b><br>
 * <b>Updated: spaniakos 2015 </b><br>
 *
 * This Demonstrates the user friendly implementation.
 * <b>NOTE:</b><br />
 * calc_size Function calculates the size for the ciphertext.
 */
 
 /**
 * @example DesedeCBC-easy.cpp
 * <b>For Rasberry pi</b><br>
 * <b>Updated: spaniakos 2015 </b><br>
 *
 * This Demonstrates the user friendly implementation.
 * <b>NOTE:</b><br />
 * calc_size Function calculates the size for the ciphertext.
 */


/**
 * @mainpage DES library for Arduino and Raspberry pi.
 *
 * @section Goals Design Goals
 *
 * This library is designed to be...
 * @li Fast and efficient.
 * @li Able to effectively encrypt and decrypt any size of string.
 * @li Able to encrypt and decrypt using DES and 3DES.
 * @li Easy for the user to use in his programs.
 *
 * @section Acknowledgements Acknowledgements
 * This is an DES library for the Arduino, based on tzikis's DES library, which you can find <a href= "https://github.com/tzikis/arduino">here:</a>.<br />
 * Tzikis library was based on scottmac`s library, which you can find <a href="https://github.com/scottmac/arduino">here:</a><br /> 
 * 
 * @section Installation Installation
 * <h3>Arduino</h3>
 * Create a folder named _DES_ in the _libraries_ folder inside your Arduino sketch folder. If the 
 * libraries folder doesn't exist, create it. Then copy everything inside. (re)launch the Arduino IDE.<br />
 * You're done. Time for a mojito
 * 
 * <h3>Raspberry  pi</h3>
 * <b>install</b><br /><br />
 * 
 * sudo make install<br />
 * cd examples_Rpi<br />
 * make<br /><br />
 * 
 * <b>What to do after changes to the library</b><br /><br />
 * sudo make clean<br />
 * sudo make install<br />
 * cd examples_Rpi<br />
 * make clean<br />
 * make<br /><br />
 * <b>What to do after changes to a sketch</b><br /><br />
 * cd examples_Rpi<br />
 * make <sketch><br /><br />
 * or <br />
 * make clean<br />
 * make<br /><br /><br />
 * <b>How to start a sketch</b><br /><br />
 * cd examples_Rpi<br />
 * sudo ./<sketch><br /><br />
 * 
 * @section News News
 *
 * If issues are discovered with the documentation, please report them <a href="https://github.com/spaniakos/spaniakos.github.io/issues"> here</a>
 * @section Useful Useful References
 *
 * Please refer to:
 *
 * @li <a href="http://spaniakos.github.io/ArduinoDES/classDES.html"><b>DES</b> Class Documentation</a>
 * @li <a href="https://github.com/spaniakos/ArduinoDES/archive/master.zip"><b>Download</b></a>
 * @li <a href="https://github.com/spaniakos/ArduinoDES/"><b>Source Code</b></a>
 * @li <a href="http://spaniakos.github.io/">All spaniakos Documentation Main Page</a>
 *
 * @section Board_Support Board Support
 *
 * Most standard Arduino based boards are supported:
 * - Arduino
 * - Intel Galileo support
 * - Raspberry Pi Support
 * 
 * - The library has not been tested to other boards, but it should suppport ATMega 328 based boards,Mega Boards,Arduino Due,ATTiny board
 */

