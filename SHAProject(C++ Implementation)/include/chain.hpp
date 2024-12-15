#ifndef CHAIN_HPP
#define CHAIN_HPP


#include<iostream>
#include<vector>
#include "block.hpp"

class Blockchain
{
	public:
		Blockchain(); //instance to create a chain of blocks
		void AddBlock(const std::string& data);//adding a list of hash nodes to the chain 
		void ShowChain(); //printing all of the chain

	private:
		std::vector<Block> chain;
		Block CreateGenesisBlock();
};

#endif //CHAIN_HPP
