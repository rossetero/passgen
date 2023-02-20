#include <iostream>
#include <ctime>
#include <fstream>
#include<string>
using namespace std;


void str_subtraction(char* a, char* b) {
    char c[100];
    int len_c = 0;
    for (unsigned i = 0; i < strlen(a); i++) {    
        bool t = true;                           
        for (unsigned j = 0; j < strlen(b); j++) {
            if (a[i] == b[j]) t = false;
        }
        if (t) { c[len_c] = a[i]; ++len_c; }
    }

    c[len_c] = '\0';
    for (int i = 0; i <= len_c; i++) {
        a[i] = c[i];
    }

}

bool compare(char* a, const char* b) {
    if (strlen(a) != strlen(b)) return false;
    for (unsigned i = 0; i < strlen(a); i++) {
        if (a[i] != b[i]) return false;
    }
    return true;

}

bool isnum(char* x) {
    bool t = true;
    for (int i = 0; i < strlen(x) && t; ++i) {
        if (!(isdigit(x[i]))) t = false;
    }
    return t;
}


void gen(int len=8) { //generation without parametrs
    srand(time(0));
    char all[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
    char password[100] = { '0' };
    int index = 0;
    for (int i = 0; i < len; i++) {
        int randomNumber = rand() % strlen(all);
        password[index] = all[randomNumber];
        ++index;
    }
    password[len] = '\0';
    for (int i = 0; i < strlen(password); i++) {
        cout << password[i];
    }
}


void gen(int len, int c, char** v) { //generation with parametrs
    srand(time(0));
    char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //0-25
    char lowercase[] = "abcdefghijklmnopqrstuvwxyz"; //26-51
    char numbers[] = "0123456789";//52-61
    char symbols[] = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";//62-93
    char all[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
    char password[100] = "";
    int uflag = 0, lflag = 0, nflag = 0, sflag = 0;
    for (int i = 2; i < c; ++i) {
        if (compare(v[i], "-u")) { str_subtraction(all, uppercase); ++uflag; }
        else {
            if (compare(v[i], "-l")) { str_subtraction(all, lowercase); ++lflag; }
            else {
                if (compare(v[i], "-n")) { str_subtraction(all, numbers); ++nflag; }
                else {
                    if (compare(v[i], "-s")) { str_subtraction(all, symbols); ++sflag; }
                    else {
                        cout << "Improper argument!";
                        exit(-1);
                    }
                }
            }
        }
    }
    if (uflag > 1 || lflag > 1 || nflag > 1 || sflag > 1) {
        cout << "Duplicated arguments!";
        exit(-1);
    }
    int index = 0;
    for (int i = 0; i < len; i++) {
        int randomNumber = rand() % strlen(all);
        password[index] = all[randomNumber];
        ++index;
    }
    password[len] = '\0';
    for (int i = 0; i < strlen(password); i++) {
        cout << password[i];
    }
}

void help_printer(ifstream& f) {
    string out;
    if (!f) {
        cout << "problems with help.txt";
        exit(-1);
    }
    while (!f.eof()) {
        out = "";
        getline(f, out);
        cout << out << endl;
    }

}

int main(int argc, char** argv)
{

    ifstream fin("help.txt");

    if (argc > 6) { cout << "Too many argsuments. Type \"help\" command, if you need"; return 0; }
    if (argc < 2) { gen();}
    else {
        if (!strcmp(argv[1], "save")) {
            cout << "saved";
            
        }
        else {
            if (!strcmp(argv[1], "search")) {
                cout << "search";
            }
            else {
                if (!strcmp(argv[1], "show")) {
                    cout << "show";
                }
                else {
                    if (!strcmp(argv[1], "help")) { 
                        help_printer(fin);
                    }
                    else {

                        if (isnum(argv[1])) {
                            int len = atoi(argv[1]);
                            if (argc == 2) gen(len);
                            else gen(len,argc,argv);
                          
                        }
                        else {
                            clog << "Incorrect input! Type \"help\" for information";
                        }
                    }

                }
            }

        }
    }
    
    return 0;
}



