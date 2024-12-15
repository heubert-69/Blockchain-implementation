#include<iostream>
#include "../include/chain.hpp"
#include "../include/block.hpp"
#include<string>

Blockchain::Blockchain()
{
	chain.push_back(CreateGenesisBlock());
}

Block Blockchain::CreateGenesisBlock()
{
	return Block(0, "Genesis Block", "0");
}

void Blockchain::AddBlock(const std::string& data)
{
	Block NewBlock(chain.size(), data, chain.back().hash);
	chain.push_back(NewBlock);
}

void Blockchain::ShowChain()
{
	for(const auto& block: Blockchain::chain){
		std::cout << "Index: " << block.index << "\n" << "Data: " << block.data << "\n" << "Previous Hash: " << block.prev_hash << "\n" << "Current Hash: " << block.hash << "\n\n";
	}
}
