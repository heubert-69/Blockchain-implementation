#ifndef BLOCK_HPP
#define BLOCK_HPP


#include<iostream>
#include<vector>
#include<string>


class Block
{
	public:
		Block(int idx, const std::string& data, const std::string& prev_hash);
		std::string CalculateHash();

		int index;
		std::string data;
		std::string prev_hash;
		std::string hash;

	private:
		int nonce;
};

#endif //BLOCK_HPP

