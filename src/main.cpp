#include "../include/defines.hpp"
#include "../include/crypt.hpp"

#include <iostream>
#include <fstream>

#include <cstring>

#include <list>

#ifndef __linux
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>

    int _getch() {
        int ch; termios oldt, newt;

        tcgetattr( STDIN_FILENO, &oldt );
        newt = oldt;

        newt.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newt );

        ch = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldt );

        return ch;
    }
#endif

int main(int argc, char * argv[]) {
    std::cout << "                                    _             \tVersion : " << str_ver << "\n";
    std::cout << "   ||  ||      ___ _ __ _   _ _ __ | |_ ___  _ __ \n";
    std::cout << "   \\\\()//    / __| '__| | | | '_ \\| __/ _ \\| '__|\tDeveloper : KonstantIMP\n";
    std::cout << "  //(__)\\\\  | (__| |  | |_| | |_) | || (_) | |   \tFeedback email : mihedovkos@gmail.com\n";
    std::cout << "  ||    ||   \\___|_|   \\__, | .__/ \\__\\___/|_|   \n";
    std::cout << "                       |___/|_|                  \tUse \"cryptor -h\" to view help message\n\n";

    if(argc == 1) {
        return 0;
    }

    bool mode = 0;
    bool debug = 0;
    bool f_out = 0;
    bool ask_name = true;

    std::ofstream fout;

    std::list<std::string> c_word;
    std::list<std::string> s_name;

    for(int i{1}; i < argc; i++) {
        if(strcmp(argv[i], "-h") == 0) {
            std::cout << "CRYPTOR : version " << str_ver << "\n\n";

            std::cout << "Cryptor is a simple programm, to encrypt & decrypt text messages\n\n";

            std::cout << "HELP MANUAL :\n";
            std::cout << "\t[USAGE] encryptor [OPTIONS] [WORDS]\n\n";

            std::cout << "[OPTIONS]\n";
            std::cout << "\t-d\tView debug output\n";
            std::cout << "\t-v\tView version and exit\n";
            std::cout << "\t-h\tView help message and exit\n";
            std::cout << "\t-a\tView (en/de)crypt algorithm and exit\n";
            std::cout << "\t-t\tDon't ask about stings names\n";

            std::cout << "\t-o [F]\tSet output file\n\n";

            std::cout << "\t-m [M]\tSet output strings style\n";

            std::cout << "\t[STRING STYLE MODES]\n";
            std::cout << "\t\tC\tUse c-style strings\n";
            std::cout << "\t\tCPP\tUse cpp STL strings\n";

            return 0;
        }
        if(strcmp(argv[i], "-v") == 0) {
            std::cout << "Version is : " << str_ver << '\n';
            return 0;
        }
        if(strcmp(argv[i], "-d") == 0) {
            debug = true; continue;
        }
        if(strcmp(argv[i], "-a") == 0) {
            std::cout << "Encrytion & Decryption algorithm :\n\n";

            std::cout << "[DESCRIPTION] As an argument we get a text message in the form of a string :\n";
            std::cout << "\t\tstring text_msg = \"Hello, World!\"\n\n";

            std::cout << "[DESCRIPTION] By definition string is a characters array\n";
            std::cout << "\t\t[ 0] = 'H'\t [ 7] = 'W'\n";
            std::cout << "\t\t[ 1] = 'e'\t [ 8] = 'o'\n";
            std::cout << "\t\t[ 2] = 'l'\t [ 9] = 'r'\n";
            std::cout << "\t\t[ 3] = 'l'\t [10] = 'l'\n";
            std::cout << "\t\t[ 4] = 'o'\t [11] = 'd'\n";
            std::cout << "\t\t[ 5] = ','\t [12] = '!'\n";
            std::cout << "\t\t[ 6] = ' '\n\n";

            std::cout << "[DESCRIPTION] Encryption & Decryption is performed one character at a time\n\n";

            std::cout << "[DESCRIPTION] Two auxiliary unsigned character variables were created for Encryption & Decryption\n";
            std::cout << "\t\tunsigned char a, b;\n\n";

            std::cout << "[DESCRIPTION] The following actions are performed for each character\n";
            std::cout << "\t\ta = b = text_msg[n]\n";
            std::cout << "\t\ta = a << 4\n";
            std::cout << "\t\tb = b >> 4\n";
            std::cout << "\t\ta = b = ~(a | b) - 1\n";
            std::cout << "\t\ta = a << 4\n";
            std::cout << "\t\tb = b >> 4\n";
            std::cout << "\t\tresult = a | b\n\n";

            std::cout << "[DESCRIPTION] The Encryption or Decryption results for each character form the source string\n";

            return 0;
        }
        if(strcmp(argv[i], "-t") == 0) {
            ask_name = false; continue;
        }
        if(strcmp(argv[i], "-m") == 0) {
            i++;

            if(strcmp(argv[i], "C") == 0) mode = 0;
            else if(strcmp(argv[i], "CPP") == 0) mode = 1;
            else {
                std::cout << "[ERROR] Incorrect string style mode\n";
                return 1;
            }

            continue;
        }
        if(strcmp(argv[i], "-o") == 0) {
            if(f_out) {
                std::cout << "You can use only one output file\n";
                return 2;
            }

            f_out = true; i++;

            fout.open(argv[i], std::ios_base::app);

            if(!fout.is_open()) {
                std::cout << "Can't create or open output file\n";
            }

            continue;
        }

        c_word.push_back(argv[i]);
    }

    if(debug) std::clog << "[DEBUG] Debug output is ON\n\n";

    if(debug) std::clog << "[DEBUG] String mode : " << (mode ? "CPP\n\n" : "C\n\n");

    if(debug) std::clog << "[DEBUG] Output to file is " << (f_out ? "ON\n\n" : "OFF\n\n");

    if(debug) {
        std::clog << "[DEBUG] Words analisys\n";

        for(auto iter : c_word) std::clog << '\t' << iter << '\n';
    }

    if(ask_name) {
        bool set = false; char ans = 0;

        do {
            std::cout << "\nDo you want to set names for strings[y/n] : ";
            ans = _getch();

            if(ans == 'n') {
                ask_name = false;
                set = true;
            }
            else if(ans == 'y' || ans == ' ') set = true;
            else std::cout << "Incorrect Answer! Try again!\n\n";
        } while(set == false);
    }

    if(ask_name) {
        auto iter = c_word.begin();

        std::string tmp = "";

        for(std::size_t i{0}; i < c_word.size(); i++) {
            std::cout << "\nEnter name for " << *iter << " : ";
            std::cin >> tmp;

            s_name.push_back(tmp);

            iter++;
        }
    }
    else {
        for(std::size_t i{0}; i < c_word.size(); i++) s_name.push_back("str" + std::to_string(i));

        std::cout << "\n";
    }

    if(debug) std::clog << "[DEBUG] Starting crypt\n\n";

    for(auto & iter : c_word) iter = cryptor::crypt(iter, debug);

    if(debug) std::clog << "[DEBUG] Crypt result\n";

    std::string tmp = ""; auto iter = c_word.begin();
    auto name_iter = s_name.begin();

    for(std::size_t i{0}; i < c_word.size(); i++) {
        std::clog << '\t' << i + 1 << "th - ";

        if(mode) {
            tmp = "std::string " + *name_iter + " = \"" + *iter + "\";";
        }
        else {
            tmp = "char " + *name_iter + "[] = {";

            for(std::size_t j{0}; j < (*iter).length(); j++) {
                if(j != ((*iter).length() - 1)) tmp += std::to_string((int)(*iter).at(j)) + ", ";
                else tmp += std::to_string((int)(*iter).at(j)) + ", 0 };";
            }
        }

        std::clog << tmp << '\n';

        if(f_out) fout << tmp << '\n';

        iter++; name_iter++;
    }

    if(f_out) fout.close();

	return 0;
}
