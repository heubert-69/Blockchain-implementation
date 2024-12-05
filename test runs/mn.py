from chain import Block, Blockchain
import hashlib



blockchain = Blockchain()

#implementation
blockchain.AddBlock("Luke Redeems 60ETH")
blockchain.AddBlock("Kenji Pays 0.5BTC to Luke")

blockchain.ShowChain()
print(f"The Blockchain's Validity: {blockchain.IsChainValid()}")
