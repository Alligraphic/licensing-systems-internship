import hashlib
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography import exceptions

def sign_string(message, private_key_path):
    # Load the private key from file
    with open(private_key_path, 'rb') as f:
        private_key_data = f.read()

    private_key = serialization.load_pem_private_key(
        private_key_data,
        password=None,
        backend=default_backend()
    )

    # Calculate the SHA-256 hash of the message
    hash_func = hashlib.sha256()
    hash_func.update(message.encode('utf-8'))
    digest = hash_func.digest()

    # Sign the digest using the private key
    signature = private_key.sign(
        digest,
        padding.PSS(
            mgf=padding.MGF1(hashes.SHA256()),
            salt_length=padding.PSS.MAX_LENGTH
        ),
        hashes.SHA256()
    )

    # Return the signature as bytes
    return signature


def verify_signature(message, signature, public_key_path):
    # Load the public key from file
    with open(public_key_path, 'rb') as f:
        public_key_data = f.read()

    public_key = serialization.load_pem_public_key(
        public_key_data,
        backend=default_backend()
    )

    # Calculate the SHA-256 hash of the message
    hash_func = hashlib.sha256()
    hash_func.update(message.encode('utf-8'))
    digest = hash_func.digest()

    try:
        # Verify the signature
        public_key.verify(
            signature,
            digest,
            padding.PSS(
                mgf=padding.MGF1(hashes.SHA256()),
                salt_length=padding.PSS.MAX_LENGTH
            ),
            hashes.SHA256()
        )
        # Signature is valid
        return True
    except exceptions.InvalidSignature:
        # Signature is invalid
        return False


private_key_path = "private_key.pem"
public_key_path = "public_key.pem"
