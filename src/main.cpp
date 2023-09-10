#include "palavra.hpp"
#include "arvore.hpp"
#include "functions.hpp"
#include <sstream> 
#include <vector>
#include <chrono>
#define NUMERO_ARQUIVOS 6

int main() {    
    string vetorArquivos[NUMERO_ARQUIVOS] = {"dataset/filosofia.txt", "dataset/filosofia2.txt", "dataset/globalizacao.txt", "dataset/politica.txt", "dataset/ti.txt", "dataset/ti2.txt"}, linha;
    string palavraAtual;
    ifstream arquivo, arquivoStopWords, arquivoInput;
    ofstream output;
    vector<string> tokens, vetorInput;
    vector<Palavra> vetorPalavras, copiaHeap;
    vector<itemArvore*> vetorArvore;
    vector<itemArvoreAVL*> vetorArvoreAVL;
    vector<pair<int,int>> vetorOcorrencias;
    string token, stopword; 
    unordered_map<string, Palavra> vetorMaps[NUMERO_ARQUIVOS];
    unordered_map<string, string> stopWordMap;
    int controle = 0;

    arquivoStopWords.open("dataset/stopwords.txt", ios::in);
    if (!arquivoStopWords.is_open()) {
        cout << "Não foi possível abrir o arquivo de stop words." << endl;
        return 1;
    }
    while(!arquivoStopWords.eof()){
        arquivoStopWords >> stopword;
        stopWordMap[stopword] = stopword;
    }
    arquivoStopWords.close();

    for(int i = 0; i < NUMERO_ARQUIVOS; i++){

        arquivo.open(vetorArquivos[i], ios::in);

        if (!arquivo.is_open()) {
            cout << "Não foi possível abrir o arquivo." << endl;
            return 1;
        }

        while (getline(arquivo, linha)) {
            linha.erase(remove(linha.begin(), linha.end(), ','), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), '.'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), '?'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), '!'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), '"'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), ';'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), '/'), linha.end());
            linha.erase(remove(linha.begin(), linha.end(), ':'), linha.end());

            istringstream iss(linha); 
            while (iss >> token) {
                if ((token != "--") && (token != "—") && (token != "“") && (token != "”")) { 
                    if (token.size() > 2 && token.substr(0, 2) == "--") {
                        token = token.substr(2); // Remove os primeiros dois caracteres "--", para quando não há espaço
                    }
                    for (char& c : token) {
                        c = std::tolower(c);
                    }
                    if(!isStopWord(stopWordMap, token)){
                        addMap(vetorMaps[i], token);
                    }
                }
            }
        }
        arquivo.close();
    }

    arquivoInput.open("dataset/input.data", ios::in);
    if (!arquivoInput.is_open()) {
        cout << "Não foi possível abrir o arquivo de input." << endl;
        return 1;
    }
    while(!arquivoInput.eof()){
        arquivoInput >> palavraAtual;
        vetorInput.push_back(palavraAtual);
    }    
    arquivoInput.close();

    output.open("dataset/output.data", ios::out);
    if (!output.is_open()) {
        cout << "Não foi possível abrir o arquivo de output." << endl;
        return 1;
    }
    for(int i = 0; i < NUMERO_ARQUIVOS; i++){
        //itemArvore * raiz = new itemArvore();
        outputFileIntro(output, i);
        criarHeapK(vetorMaps[i], vetorPalavras);
        check(vetorMaps[i], vetorPalavras);
        copiaHeap = vetorPalavras;
        for(int j = 0; j < (int)vetorInput.size(); j++){ 
            for(int k = 0; k < (int)vetorPalavras.size(); k++){
                if(vetorPalavras[k].texto == vetorInput[j]){
                    controle = 1;
                    break;
                }
            }
            if(controle == 1){
                //A palavra do input está no heap
                for(int k = 0; k < (int)vetorPalavras.size(); k++){
                    if(vetorPalavras[k].texto == vetorInput[j]){
                        vetorPalavras.erase(vetorPalavras.begin() + k);
                        break;
                    }
                }
            }
            else{
                vetorPalavras.pop_back();
            } 

            if(vetorMaps[i][vetorInput[j]].ocorrencias != 0){
                itemArvore * raiz = new itemArvore();
                itemArvoreAVL * raizAVL = new itemArvoreAVL();
                auto start = std::chrono::high_resolution_clock::now();
                for(int k = 0; k < (int)vetorPalavras.size(); k++){
                    arvoreBinaria(&raiz, vetorPalavras[k]);
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                std::cout << "Tempo de execução - Árvore binária - Texto " << i+1 << " - "<< vetorInput[j] << ": " << duration.count() << " nanossegundos" << std::endl;
                
                start = std::chrono::high_resolution_clock::now();
                for(int k = 0; k < (int)vetorPalavras.size(); k++){
                    arvoreAVL(&raizAVL, vetorPalavras[k]);
                }
                end = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                std::cout << "Tempo de execução - Árvore AVL - Texto " << i+1 << " - "<< vetorInput[j] << ": " << duration.count() << " nanossegundos" << std::endl << endl;
                
                central(raiz, vetorArvore);
                centralAVL(raizAVL, vetorArvoreAVL);
                outputFile(output, vetorMaps[i][vetorInput[j]].texto, vetorMaps[i][vetorInput[j]].ocorrencias, vetorArvore, vetorArvoreAVL);
                deleteTree(raiz);
                deleteTreeAVL(raizAVL);
                controle = 0;
                vetorArvore.clear();
                vetorArvoreAVL.clear();
            }
            vetorPalavras = copiaHeap;  
        }
        vetorPalavras.clear();
    }
    output.close();
    return 0;
}