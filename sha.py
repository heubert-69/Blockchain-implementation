import hashlib


#separate implementation
def GenerateSHA256(data):
	to_hash = hashlib.sha256(data.encode())
	return to_hash.hexdigest()
