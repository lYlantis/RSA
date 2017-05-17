// RSA Assignment for ECE4122/6122 Fall 2015

#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "RSA_Algorithm.h"

using namespace std;

// Implement the RSA_Algorithm methods here

// Constructor
RSA_Algorithm::RSA_Algorithm()
  : rng(gmp_randinit_default)
{
  // get a random seed for the random number generator
  int dr = open("/dev/random", O_RDONLY);
  if (dr < 0)
    {
      cout << "Can't open /dev/random, exiting" << endl;
      exit(0);
    }
  unsigned long drValue;
  read(dr, (char*)&drValue, sizeof(drValue));
  //cout << "drValue " << drValue << endl;
  rng.seed(drValue);
// No need to init n, d, or e.
}

// Fill in the remainder of the RSA_Algorithm methods
void RSA_Algorithm::GenerateRandomKeyPair(size_t sz)
{
	mpz_class p,q,phi,gcd, e1, d1;
	
	//generate prime p and q
	//p = rng.get_z_bits(sz);
	while(!mpz_probab_prime_p(p.get_mpz_t(),100)) 
	{
		p = rng.get_z_bits(sz);
	}
	
	//q = rng.get_z_bits(sz);
	while(!mpz_probab_prime_p(q.get_mpz_t(),100)) 
	{
		q = rng.get_z_bits(sz);
	}
	
	//calculate n=p*q
	n=p*q;
	
	//calculate phi
	phi=(p-1)*(q-1);
	
	//Get a random value for d=sz*2 and make sure d<phi and that the gcd of d and phi is 1
	while(!(e1<phi && gcd==1)) {
		e1=rng.get_z_bits(sz*2);
		mpz_gcd(gcd.get_mpz_t(), e1.get_mpz_t(), phi.get_mpz_t());
	}
	
	//calculate e as the inverse of d mod phi
	mpz_invert(d1.get_mpz_t(), e1.get_mpz_t(), phi.get_mpz_t());
	
	e=e1;
	d=d1;
}

mpz_class RSA_Algorithm::Encrypt(mpz_class M)
{
	//Encrypt a text C as C=M^d(mod n)
	mpz_class C;
	mpz_powm(C.get_mpz_t(), M.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());
	return C;
}

mpz_class RSA_Algorithm::Decrypt(mpz_class C)
{
	//Decrypt a text M as M=C^e(mod n)
	mpz_class M;
	mpz_powm(M.get_mpz_t(), C.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());
	return M;
}

void RSA_Algorithm::PrintND()
{ // Do not change this, right format for the grading script
  cout << "n " << n << " d " << d << endl;
}

void RSA_Algorithm::PrintNE()
{ // Do not change this, right format for the grading script
  cout << "n " << n << " e " << e << endl;
}

void RSA_Algorithm::PrintNDE()
{ // Do not change this, right format for the grading script
  cout << "n " << n << " d " << d << " e " << e << endl;
}

void RSA_Algorithm::PrintM(mpz_class M)
{ // Do not change this, right format for the grading script
  cout << "M " << M << endl;
}

void RSA_Algorithm::PrintC(mpz_class C)
{ // Do not change this, right format for the grading script
  cout << "C " << C << endl;
}




