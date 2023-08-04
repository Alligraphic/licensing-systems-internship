#include <iostream>
#include "HttpClient.h"
#include <fstream>
#include <string>
#include <vector>

#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>

bool verifySignature(const std::string& message, const std::string& signature, const std::string& publicKeyPath) {
    // Load the public key from file
    std::ifstream publicKeyFile(publicKeyPath, std::ios::binary);
    if (!publicKeyFile) {
        std::cerr << "Failed to open public key file: " << publicKeyPath << std::endl;
        return false;
    }

    std::string publicKeyData((std::istreambuf_iterator<char>(publicKeyFile)),
                              std::istreambuf_iterator<char>());

    // Create an OpenSSL BIO object to hold the public key data
    BIO* bio = BIO_new_mem_buf(publicKeyData.data(), publicKeyData.size());

    // Read the public key
    RSA* rsaPublicKey = PEM_read_bio_RSA_PUBKEY(bio, nullptr, nullptr, nullptr);

    // Calculate the SHA-256 hash of the message
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(message.c_str()), message.length(), digest);

    // Convert the signature from hex string to binary format
    std::vector<unsigned char> signatureBytes;
    for (size_t i = 0; i < signature.length(); i += 2) {
        std::string byteString = signature.substr(i, 2);
        unsigned char byte = static_cast<unsigned char>(std::strtol(byteString.c_str(), nullptr, 16));
        signatureBytes.push_back(byte);
    }

    std::cout << "signatureBytes: " << signatureBytes.data() << std::endl;

    // Verify the signature
    int result = RSA_verify(
            NID_sha256,
            digest,
            SHA256_DIGEST_LENGTH,
            signatureBytes.data(),
            signatureBytes.size(),
            rsaPublicKey
    );

    // Clean up resources
    RSA_free(rsaPublicKey);
    BIO_free(bio);

    // Return the verification result

    std::cout << "result: " << result << std::endl;

    return result == 1;
}

// extract message from json
std::string extract_message(const std::string& json) {
    std::string message = json.substr(json.find("sub_status") + 13);
    message = message.substr(0, message.find("\""));
    return message;
}

// extract signature from json
std::string extract_signature(const std::string& json) {
    std::string signature = json.substr(json.find("signature") + 12);
    signature = signature.substr(0, signature.find("\""));
    return signature;
}

void checkSubscription(const std::string& username, const std::string& password) {
    HttpClient client;
    client.setUrl("http://127.0.0.1:8001/sub-licensing/sign-check/");

    std::string request = R"("{\"username\":\"")" + username + R"("\",\"password\":\")" + password + R"("\"})";
    client.setRequest(request);

    client.post();

    if (client.getResponse().getData().find("true") != std::string::npos) {
        std::cout << "Valid subscription" << std::endl;

        std::string message = extract_message(client.getResponse().getData());
        std::string signature = extract_signature(client.getResponse().getData());

        client.setUrl("http://127.0.0.1:8001/sub-licensing/verify-sign/");
        client.setRequest(R"("{\"message\":\"")" + message + R"("\",\"signature\":\")" + signature + R"("\"})");

        client.post();

        std::cout << client.getResponse().getData() << std::endl;

        if (client.getResponse().getData().find("true") != std::string::npos) {
            std::cout << "Valid signature" << std::endl;
            system("cd ../../application && dragdroprobot.exe");
        } else {
            std::cout << "Invalid signature" << std::endl;
        }
    } else {
        if (client.getResponse().getData().find("expired") != std::string::npos) {
            std::cout << "Subscription expired" << std::endl;
            std::cout << "renew in: http://127.0.0.1:8001/sub-licensing/subscriptions/" << std::endl;
        } else if (client.getResponse().getData().find("no subscription") != std::string::npos) {
            std::cout << "No subscription" << std::endl;
            std::cout << "get a plan in: http://127.0.0.1:8001/sub-licensing/subscriptions/" << std::endl;
        } else {
            std::cout << client.getResponse().getData() << std::endl;
            std::cout << "renew in: http://127.0.0.1:8001/auth/users/" << std::endl;
        }
    }
}

int main() {
    std::string username;
    std::string password;

    std::cout << "Enter username:\n";
    std::cin >> username;

    std::cout << "Enter password:\n";
    std::cin >> password;

    checkSubscription(username, password);

    return 0;
}

//int main() {
//    std::string message = "expired";
//    std::string signature = "73cccdf8f8947fcd86b558f9670bf65e1423396ed516936a2d22de0e9ef6c2aa5e2503f7894c9adef386c98d386da5cb7f30c8752774082085996fb783f9baebceac0cdc59139d87fce07261b73f6bff8732793ed51c0fd354b7b4316c59d5a9e1de31f8de29fbd1da7e40a27c904a507d0f6e430436d155f923f23d5ea3fefff89ea0ab55902023f583fbcb6401c0acec92d54f32a3fa58ab1e1b21960462d8660907a9b6c79f44ab767e1f5d702ecc659ac96c35e37592560f577d2f8398f4f882b9c5820f58c639d46e96d0296c1aa8a2c49b8944f008e68c597e55fd5865bbaebaf2b608773071e5ee34d263f7561b5e86a2f6c1fff3a43748810db3697a";
//    std::string publicKeyPath = "../public_key.pem";
//
//    bool isValid = verifySignature(message, signature, publicKeyPath);
//    std::cout << (isValid ? "Signature is valid" : "Signature is invalid") << std::endl;
//
//    return 0;
//}