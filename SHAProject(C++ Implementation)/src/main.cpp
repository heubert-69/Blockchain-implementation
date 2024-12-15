#include "../include/chain.hpp"
#include "../include/block.hpp"
#include "../include/sha.hpp"
#include<iostream>

int main()
{

	Blockchain blockchain;

	blockchain.AddBlock("manny likes diddy");
	blockchain.AddBlock("Im gonna cum");

	blockchain.ShowChain();

	return 0;
}
