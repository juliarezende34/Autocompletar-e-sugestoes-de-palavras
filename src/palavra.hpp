#ifndef PALAVRA_HPP
#define PALAVRA_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
#include <sstream>
#include <vector>
#include <unordered_map>

#define K 21

using namespace std;

class Palavra{
    public:
        string texto;
        int ocorrencias;
        Palavra();
        Palavra(string t);
};

#endif