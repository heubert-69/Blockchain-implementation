#ifndef SHA_HPP
#define SHA_HPP

#include<iostream>
#include<cmath>
#include<vector>
#include<string>

class SHA256
{
	public:
		static std::string hash(const std::string& input);

	private:
		static const unsigned int K[64]; //list of sample addresses
		static const unsigned int InitialHash[8]; //addresses

		static void Preprocess(const std::string& input, std::vector<unsigned char>& ProcessedMessage, uint64_t& message_length);
		static void ProcessChunk(const std::vector<unsigned char>& chunk, unsigned int HashValues[8]);
		static unsigned int RightRotate(unsigned int value, unsigned int count);
};

#endif //SHA_HPP
