#include "../include/crypt.hpp"

std::string cryptor::crypt(const std::string & str, const bool & debug_out) {
    std::string result = "";

    if(debug_out) std::clog << "[DEBUG] Crypt start\n\n";

    if(debug_out) std::clog << "[DEBUG] Encrypting string has " << str.length() << " symbol(s)\n\n";

    if(debug_out) std::clog << "[DEBUG] Symbols analisys\n";

    char a = 0; char b = 0;

    for(std::size_t i{0}; i < str.length(); i++) {
        if(debug_out) std::clog << '\t' << i + 1 << "th symbol - " << str.at(i) << '\n';

        a = b = str.at(i);
        a = static_cast<char>(static_cast<char>(a) << static_cast<char>(4));
        b = static_cast<char>(static_cast<char>(b) >> static_cast<char>(4));

        a = b = ~(a | b) + 1;

        a = static_cast<char>(static_cast<char>(a) << static_cast<char>(4));
        b = static_cast<char>(static_cast<char>(b) >> static_cast<char>(4));

        result += a | b;

        if(debug_out) std::clog << "\t\t Encrypted to " << static_cast<char>(a | b) << '\n';
    }

    if(debug_out) std::clog << "\n[DEBUG] Result string is " << result << "\n\n";

    return result;
}
