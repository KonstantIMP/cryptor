#ifndef CRYPT_HPP
#define CRYPT_HPP

#include <iostream>

#include <cstddef>
#include <string>

class cryptor {
public:
    static std::string crypt(const std::string &, const bool & = false);
    std::string operator()(const std::string & msg) {return this->crypt(msg);}
};

#endif // CRYPT_HPP
