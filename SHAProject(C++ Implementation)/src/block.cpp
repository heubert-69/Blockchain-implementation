#include<iostream>
#include<vector>
#include<ctime>
#include<string>
#include "../include/block.hpp"
#include "../include/sha.hpp"

Block::Block(int idx, const std::string& data, const std::string& prev_hash) : index(idx), data(data), prev_hash(prev_hash), nonce(0)
{
	hash = CalculateHash();
}

std::string Block::CalculateHash()
{
	return SHA256::hash(std::to_string(index) + prev_hash + data + std::to_string(nonce));
}
