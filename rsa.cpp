#include "cryptopp870/rsa.h"
#include "cryptopp870/osrng.h"
#include "cryptopp870/base64.h"
#include "cryptopp870/files.h"
#include "cryptopp870/hex.h"
#include <iostream>
#include <string>

CryptoPP::AutoSeededRandomPool rng;


void generate_keys(){
    
    CryptoPP::RSA::PrivateKey privKey;
    CryptoPP::RSA::PublicKey pubKey;
    privKey.GenerateRandomWithKeySize(rng, 8192);
    pubKey = CryptoPP::RSA::PublicKey(privKey);
    std::cout << "Generation ended." << std::endl;

    std::ofstream privFile("rsa-private.key", std::ios::binary);
    CryptoPP::FileSink privSink(privFile);
    privKey.DEREncode(privSink);
    privFile.close();

    std::ofstream pubFile("rsa-public.key", std::ios::binary);
    CryptoPP::FileSink pubSink(pubFile);
    pubKey.DEREncode(pubSink);
    pubFile.close();
}

std::string rsa_encrypt(std::string to_encrypt){

    CryptoPP::RSA::PublicKey pubKey;
    std::ifstream pubFile("rsa-public.key", std::ios::binary);
    CryptoPP::FileSource pubSource(pubFile, true);
    pubKey.BERDecode(pubSource);
    pubFile.close();


    CryptoPP::RSAES_OAEP_SHA_Encryptor encryptor(pubKey);
    std::string ciphered;
    CryptoPP::StringSource(to_encrypt, true, new CryptoPP::PK_EncryptorFilter(rng, encryptor, new CryptoPP::StringSink(ciphered)));

    std::string encoded_ciphered;
    CryptoPP::StringSource(ciphered, true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(encoded_ciphered)));
    std::cout << "Encoded ciphered : " << encoded_ciphered << std::endl;
    return encoded_ciphered;
}

std::string rsa_decrypt(std::string to_decrypt){

    CryptoPP::RSA::PrivateKey privKey;
    std::ifstream privFile("rsa-private.key", std::ios::binary);
    CryptoPP::FileSource privSource(privFile, true);
    privKey.BERDecode(privSource);
    privFile.close();

    std::string decoded_ciphered;
    CryptoPP::StringSource(to_decrypt, true, new CryptoPP::Base64Decoder(new CryptoPP::StringSink(decoded_ciphered)));
    
    std::string recovered;
    CryptoPP::RSAES_OAEP_SHA_Decryptor decryptor(privKey);
    CryptoPP::StringSource(decoded_ciphered, true, new CryptoPP::PK_DecryptorFilter(rng, decryptor, new CryptoPP::StringSink(recovered)));

    return recovered;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string first_arg(argv[1]);
        std::cout << "Text to encrypt : " << first_arg << std::endl;
    } else {
        std::cout << "Nothing to encrypt." << std::endl;
    }
    generate_keys();
    std::string encrypted = rsa_encrypt(argv[1]);
    std::cout << "Decoded cipher  : " << rsa_decrypt(encrypted) << std::endl;
    return 0;
}