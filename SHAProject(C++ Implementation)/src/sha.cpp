#include<iostream>
#include<cmath>
#include<vector>
#include<sstream>
#include<iomanip>
#include<cstring>
#include<bitset>
#include "../include/sha.hpp"

const unsigned int SHA256::InitialHash[8] = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };

// SHA-256 constants (k0-k63)
const unsigned int SHA256::K[64] = { 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

unsigned int SHA256:: RightRotate(unsigned int value, unsigned int count)
{
	return (value >> count) | (value << (32 - count)); //32, because we assume that count is a 32 bit integer
}

void SHA256::Preprocess(const std::string& input, std::vector<unsigned char>& ProcessedMessage, uint64_t& message_length)
{

	ProcessedMessage.assign(input.begin(), input.end()); //assigning a vector of values

	message_length = ProcessedMessage.size() * 8;

	ProcessedMessage.push_back(0x80); //pushing 1-bit to an empty vector

	while((ProcessedMessage.size() * 8) % 512 != 448){
		ProcessedMessage.push_back(0x00); //append 0 bits until message bit reaches 448 mod 512
	}

	//put the original message length in the ProcessedMessage vector
	for(int i=7; i >= 0; --i){
		ProcessedMessage.push_back((message_length >> (i * 8)) & 0xFF);
	}
}

//processing a 512 bit chunk
void SHA256::ProcessChunk(const std::vector<unsigned char>& chunk, unsigned int HashValues[8])
{
	unsigned int w[64]; //making a list thats consisting 64 memory spaces
	memset(w, 0, sizeof(w));

	//preparing the message schedule
	for(int i=0; i < 16; ++i){
		w[i] = (chunk[i * 4] << 24) | (chunk[i * 4 + 1] << 16) | (chunk[i * 4 + 2] << 8) | (chunk[i * 4 + 3]);
	}

	//processing message
	for(int i=16; i < 64; ++i){
		unsigned int s0 = RightRotate(w[i - 15], 7) ^ RightRotate(w[i - 15], 18) ^ (w[i - 15] >> 3);
		unsigned int s1 = RightRotate(w[i - 2], 17) ^ RightRotate(w[i - 2], 19) ^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}

	//initializing working variables
	unsigned int a = HashValues[0], b = HashValues[1], c = HashValues[2], d = HashValues[3];
	unsigned int e = HashValues[4], f = HashValues[5], g = HashValues[6], h = HashValues[7];


	for(int i=0; i < 64; i++){
		unsigned int S1 = RightRotate(e, 6) ^ RightRotate(e, 11) ^ RightRotate(e, 25);
		unsigned int ch = (e & f) ^ (~e & g);
		unsigned int temp1 = h + S1 + ch + K[i] + w[i]; // temporary variable to combines samples of addresses
		unsigned int S0 = RightRotate(a, 2) ^ RightRotate(a, 13) ^ RightRotate(a, 22);
		unsigned int maj = (a & b) ^ (a & c) ^ (b & c); //major variable for final result
		unsigned int temp2 = S0 + maj; //temporary variable should there be changes

		h = g;
		g = f;
		f = e;
		e = d + temp1;
		d = c;
		c = b;
		b = a;
		a = temp1 + temp2;
	}
	//adding the compressed chunks to the present hash value
	HashValues[0] += a;
	HashValues[1] += b;
	HashValues[2] += c;
	HashValues[3] += d;
	HashValues[4] += e;
	HashValues[5] += f;
	HashValues[6] += g;
	HashValues[7] += h;
}


//main hash functions
std::string SHA256::hash(const std::string& input)
{
	if(input.empty()){
		throw std::invalid_argument("Input Cannot be an Empty String!\n");
	}
	std::vector<unsigned char> ProcessedMessage;
	uint64_t MsgLength;
	Preprocess(input, ProcessedMessage, MsgLength);

	//initial hash
	const unsigned int InitialHash[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

	//initialize hash values
        unsigned int HashValues[8];
        memcpy(HashValues, InitialHash, sizeof(InitialHash));


	//process each 512-bit chunk
	for(size_t i= 0; i + 64 <= ProcessedMessage.size(); i += 64){
		std::vector<unsigned char> chunk(ProcessedMessage.begin() + i, ProcessedMessage.begin() + i + 64);
		ProcessChunk(chunk, HashValues);
	}

	//converting hash messages or hex values or strings
	std::stringstream ss;
	for(int i=0; i < 8; i++){
		ss << std::hex << std::setw(8) << std::setfill('0') << HashValues[i];
	}
	return ss.str();
}
