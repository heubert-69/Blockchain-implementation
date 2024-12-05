import hashlib

class Block:

	def __init__(self, index, data, prev_hash):
		self.index = index
		self.data = data
		self.prev_hash = prev_hash
		self.hash = self.CalculateHash()
	def CalculateHash(self):
		to_hash = str(self.index) + self.data + self.prev_hash
		return hashlib.sha256(to_hash.encode()).hexdigest()



class Blockchain:

	def __init__(self):
		self.chain = [self.CreateGenesisBlock()]

	def CreateGenesisBlock(self):
		return Block(0, "Genesis Block", "0")

	def GetLatestBlock(self):
		return self.chain[-1]

	def AddBlock(self, new_data):
		latest_block = self.GetLatestBlock()
		new_block = Block(len(self.chain), new_data, latest_block.hash)
		self.chain.append(latest_block)

	def IsChainValid(self):
		for i in range(1, len(self.chain)):
			curr = self.chain[i]
			prev = self.chain[i - 1]

			if curr.hash != curr.CalculateHash():
				print(f"Block {i} is Invalid!!")
				return False
			if curr.prev_hash != prev.hash:
				print(f"Block {i}'s Previous Hash is Invalid!!")
				return False

		return True

	def ShowChain(self):
		for block in self.chain:
			print("----------------------------")
			print(f"Block {block.index}:")
			print(f"Data: {block.data}")
			print(f"Hash: {block.hash}")
			print(f"Previous Hash: {block.prev_hash}")
			print("----------------------------")
