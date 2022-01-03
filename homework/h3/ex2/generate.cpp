//
// Created by lanwang on 10/18/21.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <ctime>

#define MAX 170773

using namespace std;

int main(int argc, char **argv) {
    char *type = argv[1];
    if (type == nullptr) {
        return -1;
    }
    srand( (unsigned)time(0) );
    ofstream outfile;
    char fileName[100]={""};
    strcat(fileName, "rand_");
    strcat(fileName, type);
    strcat(fileName, ".txt");
    outfile.open(fileName, ios::out | ios::trunc);
    srand(1743);
    int range = 'z' - 'a' + 1;

    for (int n = 0; n < 10; ++n) {
        if (strcmp(type, "char*") == 0) {
            ostringstream str("", std::ios_base::ate);
            ostringstream data("", std::ios_base::ate);
            for (int i = 0; i < 5; ++i) {
                str << char('a' + rand() % range);
            }
            for (int i = 0; i < 5; ++i) {
                data << char('a' + rand() % range);
            }
            outfile << str.str() << "=" << data.str() << endl;
            str.clear();
            data.clear();
        } else if (strcmp(type, "int") == 0) {
            ostringstream str("", std::ios_base::ate);
            for (int i = 0; i < 5; ++i) {
                str << char('a' + rand() % range);
            }
            outfile << str.str() << "=" << ((rand() % (MAX - 0)) + 0 + 1) << endl; // generate numbers
            str.clear();
        } else {
            ostringstream str("", std::ios_base::ate);
            for (int i = 0; i < 5; ++i) {
                str << char('a' + rand() % range);
            }
            double data = (double) rand() / RAND_MAX * 1000;
            outfile << str.str() << "=" << data << endl; // generate numbers
            str.clear();
        }
    }
    outfile << endl;
}
