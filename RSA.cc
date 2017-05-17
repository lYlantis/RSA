// ECE4122/6122 RSA Encryption/Decryption assignment
// Jacob Ashmore
// ECE4122 Project 4

#include <iostream>
#include "RSA_Algorithm.h"

using namespace std;

int main()
{
  // Instantiate the one and only RSA_Algorithm object
  RSA_Algorithm RSA;
  
  // Loop from sz = 32 to 1024 inclusive
  // for each size choose 100 different key pairs
  // For each key pair choose 100 differnt plaintext 
  // messages making sure it is smaller than n.
  // If not smaller then n then choose another
  // For eacm message encrypt it using the public key (n,e).
  // After encryption, decrypt the ciphertext using the private
  // key (n,d) and verify it matches the original message.

  mpz_class M, C; 
  
  for(size_t sz = 32; sz <= 1024; sz=sz*2) {
	  
	  //sz=sizeof(p and q) n=p*q
	  
	  for(size_t i=0; i < 10; i++) {
		  
		  //for each size compute 100 different n,d, and e
		  RSA.GenerateRandomKeyPair(sz);
		  RSA.PrintNDE();
		  
		  for(size_t j=0; j<10; j++) {
			  
			  //for each key pair, compute 100 random messages for sz<n (sz*2)
			  
			  //Make sure the size of your message is less than n 
			  M = RSA.rng.get_z_bits(sz);
			  while(M > RSA.n) {
				  M = RSA.rng.get_z_bits(sz);
			  }
			  RSA.PrintM(M);			  
			  
			  //Now compute the ciphertext for each message and print
			  C = RSA.Encrypt(M);
			  RSA.PrintC(C);
			  
			  //Now Decrypt the message and print
			  M = RSA.Decrypt(C);
			  //RSA.PrintM(M);
		  }
	  }
  }
  
}
  
