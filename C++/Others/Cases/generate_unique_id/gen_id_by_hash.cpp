#include <iomanip>
#include <iostream>
#include <openssl/evp.h>
#include <sstream>

std::string generateHashId(const std::string &input)
{
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digest_len = 0;

    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_md5();

    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, input.c_str(), input.length());
    EVP_DigestFinal_ex(mdctx, digest, &digest_len);

    EVP_MD_CTX_free(mdctx);

    std::stringstream ss;
    for (unsigned int i = 0; i < digest_len; i++) {
        ss << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(digest[i]);
    }
    return ss.str();
}

int main()
{
    std::string input = "unique_input_data";
    std::cout << "Generated Hash ID: " << generateHashId(input) << std::endl;
    return 0;
}

// g++ gen_id_by_hash.cpp -lcrypto