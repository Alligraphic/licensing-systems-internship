from Crypto.PublicKey import RSA
from Crypto.Signature import pkcs1_15
from Crypto.Hash import SHA256

message = b'expired'
signature = bytes.fromhex('73cccdf8f8947fcd86b558f9670bf65e1423396ed516936a2d22de0e9ef6c2aa5e2503f7894c9adef386c98d386da5cb7f30c8752774082085996fb783f9baebceac0cdc59139d87fce07261b73f6bff8732793ed51c0fd354b7b4316c59d5a9e1de31f8de29fbd1da7e40a27c904a507d0f6e430436d155f923f23d5ea3fefff89ea0ab55902023f583fbcb6401c0acec92d54f32a3fa58ab1e1b21960462d8660907a9b6c79f44ab767e1f5d702ecc659ac96c35e37592560f577d2f8398f4f882b9c5820f58c639d46e96d0296c1aa8a2c49b8944f008e68c597e55fd5865bbaebaf2b608773071e5ee34d263f7561b5e86a2f6c1fff3a43748810db3697a')
public_key = '''-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAolCvpEY0fe8TxNFeCBDL
xhP36i2C8kUzkC2gNhbuW4yeSy+T1rByo2g52RRXBQDMAfpqv7Fw+0SyPQN35ho3
Bl+WEcA3VnGEMpIl9GkAqnIDVwE9P/ZCkCXGIA5EXPkO2rZQBnsMUMI/9is2LmA2
4zxcMX4Ti3XX7xLnKe7+XJH/CCxFI+/SanhqQJ+WkUuOuXD4Ml9eKEcWeLZTnqzm
O2iel467GaftAbzK/ixDxhhVZlMOp0nxDK4/M5fwX6UCPAqFTXUKUfzdZiMN69rK
7Fv6eV6H49lPdoNypz9aOtE2P2u5uyd9BeuQoR1Hpd7u4EaPKG0ugmFxWbuHFgLi
hwIDAQAB
-----END PUBLIC KEY-----'''

# Load the public key
rsa_public_key = RSA.import_key(public_key)

# Create a SHA-256 hash object for the message
hash_obj = SHA256.new(message)

# Verify the signature
verifier = pkcs1_15.new(rsa_public_key)
try:
    verifier.verify(hash_obj, signature)
    print("Signature is valid.")
except (ValueError, TypeError):
    print("Signature is not valid.")