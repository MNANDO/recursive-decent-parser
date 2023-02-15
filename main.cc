#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

/* A -> I = E */
/* E -> P O P | P */
/* O -> + | - | * | / | ** */
/* P -> I | L | UI | UL | (E) */
/* U -> + | - | ! */
/* I -> C | CI */
/* C -> a | b | ... | y | z */
/* L -> D | DL */
/* D -> 0 | 1 | ... | 8 | 9 */

using std::cout;
using std::cerr;
using std::ifstream;
using std::getline;
using std::endl;
using std::string;

bool A(string& line, int& i);
bool E(string& line, int& i);
bool O(string& line, int& i);
bool P(string& line, int& i);
bool U(string& line, int& i);
bool I(string& line, int& i);
bool C(string& line, int& i);
bool L(string& line, int& i);
bool D(string& line, int& i);

int main(int argc, char* argv[]) {
    ifstream file;

    if (argc <= 1) {
        cerr << "No file name given" << endl;
        return 0;
    }

    string path = argv[1];
    file.open(path.c_str());

    if ( !file.is_open() ) {
        cerr << "File cannot be opened: " << path << endl;
        return 0;
    } 

    string line; 

    while (getline(file, line, '\n')) {
        int i = -1;
        if (A(line, i)) {
            cout << "The string \"" << line << "\" is in the language" << endl;
        } else {
            cout << "The string \"" << line << "\" is not in the language" << endl;
        }
    }

    return 0;
}

void getNextChar(string& line, int& i) {
    int max = line.length();
    if (i < max) {
        i++;        
    }
}

void putBackChar(int& i) {
    if (!(i < 0)) {
        i--;
    }
}

/* O -> + | - | * | / | ** */
bool O(string& line, int& i) {
    getNextChar(line, i);
    char c = line[i];
    if (c == '+' || c == '-' || c == '*' || c == '/') {
        if (c == '*') {
            getNextChar(line, i);
            c = line[i];
            if (c == '*') {
                return true;
            }
            putBackChar(i);
            return true;            
        }
        return true;
    }
    putBackChar(i);
    return false;
}

/* U -> + | - | ! */
bool U(string& line, int& i) {
    string unary = "+-!";
    getNextChar(line, i);
    char c = line[i];
    if (unary.find(c) != string::npos) {
        return true;
    }
    putBackChar(i);
    return false;
}

/* D -> 0 | 1 | ... | 8 | 9 */
bool D(string& line, int& i) {
    string digits = "0123456789";
    getNextChar(line, i);
    char c = line[i];
    if (digits.find(c) != string::npos) {
        return true;
    }
    putBackChar(i);
    return false;
}

/* L -> D | DL */
bool L(string& line, int& i) {
    if (D(line, i)) {
        if (L(line, i)) {
            return true;
        }
        return true;
    }
    return false;
}

bool C(string& line, int& i) {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    getNextChar(line, i);
    char c = line[i];
    if (alphabet.find(c) != string::npos) {
        return true; 
    }
    putBackChar(i);
    return false;
}

/* I -> C | CI */
bool I(string& line, int& i) {
    if (C(line, i)) {
        if (I(line, i)) {
            return true;
        }
        return true; 
    }
    return false;
}

/* E -> P O P | P */
bool E(string& line, int& i) {
    if (P(line, i)) {
        if (O(line, i)) {
            if (P(line, i)) {
                return true;
            } else {
                return false;
            }
        } 
        return true;
    }
    return false;
}

/* P -> I | L | UI | UL | E | (E) */
bool P(string& line, int& i) {
    if (I(line, i)) {
        return true; 
    }
    if (L(line, i)) {
        return true; 
    } 
    if (U(line, i)) {
        if (I(line, i)) {
            return true;
        } else if (L(line, i)) {
            return true; 
        }
    }     
    getNextChar(line, i);
    char c = line[i];
    if (c == '(') {
        if (E(line, i)) {
            getNextChar(line, i);
            c = line[i];
            if (c == ')') {
                return true;
            }
            putBackChar(i);
        } 
    }
    putBackChar(i);
    return false;
}

/* A -> I = E */
bool A(string& line, int& i) {
    if (I(line, i)) {
        getNextChar(line, i);
        char c = line[i];
        if (c == '=') {
            if (E(line, i)) {
                return true;
            }
        }
        putBackChar(i);
    }
    return false; 
}



