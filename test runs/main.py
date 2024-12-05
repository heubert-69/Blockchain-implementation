from chain import Block, Blockchain
import hashlib


if __name__ == "__main__":
	blockchain = Blockchain()

	#implementation
	blockchain.AddBlock("First Genesis Block")
	blockchain.AddBlock("Second Genesis Block")
	blockchain.AddBlock("Third Genesis Block")

	blockchain.ShowChain()
	print(f"The Blockchain's Validity: {blockchain.IsChainValid()}")





