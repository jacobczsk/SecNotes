#ifndef OKCRYPT_H
#define OKCRYPT_H

#include <string>

namespace OKCrypt {
std::string encrypt(std::string data, std::string passphrase, int start);
std::string decrypt(std::string data, std::string passphrase, int start);
}

#endif // OKCRYPT_H
