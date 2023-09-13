#ifndef COMPARADOR_HPP
#define COMPARADOR_HPP
#include "arvore.hpp"

struct CompararOcorrencias{
   bool operator()(itemHuffman * a, itemHuffman * b){
        return a->ocorrencia > b->ocorrencia;
   }
};

#endif