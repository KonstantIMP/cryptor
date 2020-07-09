#include "../include/crypt.hpp"

std::string crypt(const std::string & str, const bool & debug_out) {
    std::string result = "";
	
    if(debug_out) std::clog << "[DEBUG] Crypt start\n\n";

    if(debug_out) std::clog << "[DEBUG] Encrypting string has " << str.length() << " symbol(s)\n\n";

    if(debug_out) std::clog << "[DEBUG] Symbols analisys\n";

    unsigned char a = 0, b = 0;

    for(std::size_t i{0}; i < str.length(); i++) {
        if(debug_out) std::clog << '\t' << i + 1 << "th symbol - " << str.at(i) << '\n';

        a = b = str.at(i);
        a = a << 4; b = b >> 4;

        a = b = ~(a | b) + 1;

        a = a << 4; b = b >> 4;

        result += a | b;

        if(debug_out) std::clog << "\t\t Encrypted to " << (char)(a | b) << '\n';
    }

    if(debug_out) std::clog << "\n[DEBUG] Result string is " << result << "\n\n";
	
	return result;
}
