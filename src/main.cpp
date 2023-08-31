#include "palavra.hpp"
#include "arvore.hpp"
#include "functions.hpp"
#include <sstream> 
#include <vector>
#include <time.h>
#define NUMERO_ARQUIVOS 6

int main() {
    clock_t startTime, endTime;
    startTime = clock();
    itemArvore * raiz = nullptr;
    string vetorArquivos[NUMERO_ARQUIVOS] = {"dataset/filosofia.txt", "dataset/filosofia2.txt", "dataset/globalizacao.txt", "dataset/politica.txt", "dataset/ti.txt", "dataset/ti2.txt"}, linha;
    string palavraAtual;
    ifstream arquivo, arquivoStopWords, arquivoInput;
    ofstream output;
    vector<string> tokens, vetorInput;
    vector<Palavra> vetorPalavras, copiaHeap;
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
    output.open("dataset/output.data", ios::out);
    if (!arquivoInput.is_open()) {
        cout << "Não foi possível abrir o arquivo de input." << endl;
        return 1;
    }
    if(!output.is_open()){
        cout << "Não foi possível abrir o arquivo de output." << endl;
        return 1;
    }
    while(!arquivoInput.eof()){
        arquivoInput >> palavraAtual;
        vetorInput.push_back(palavraAtual);
    }    
    arquivoInput.close();

    for(int i = 0; i < NUMERO_ARQUIVOS; i++){
        cout << "\nTexto " << i+1 << endl;
        criarHeapK(vetorMaps[i], vetorPalavras);
        check(vetorMaps[i], vetorPalavras);
        copiaHeap = vetorPalavras;
        for(int j = 0; j < (int)vetorInput.size(); j++){
            for(int x = 0; x < NUMERO_ARQUIVOS; x++){
                vetorOcorrencias.push_back(make_pair((x+1),vetorMaps[x][vetorInput[j]].ocorrencias));
            }
            for(int k = 0; k < (int)vetorPalavras.size(); k++){
                if(vetorPalavras[k].texto == vetorInput[j]){
                    vetorPalavras.erase(vetorPalavras.begin() + k);
                    controle = 1;
                    break;
                }
            }
            if(controle == 0){
                //A palavra digitada não está nos top elementos, então preciso remover o último para ter o top K
                vetorPalavras.pop_back();
            }
            for(int k = 0; k < (int)vetorPalavras.size(); k++){
                if(vetorOcorrencias[i].second > 0){
                    arvoreBinaria(&raiz, vetorPalavras[k]);
                }
            }
            BubbleSort(vetorOcorrencias);
            outputFile(output, palavraAtual, vetorOcorrencias);
            vetorOcorrencias.clear();
            vetorPalavras = copiaHeap;
        }
    }

    output.close();

    endTime = clock();
    clock_t elapsedTime = endTime - startTime;
    double elapsedTimeMs = ((double)elapsedTime/CLOCKS_PER_SEC)*1000;
    cout << "TEMPO DE EXECUÇÃO: " << elapsedTimeMs << " ms " << endl;
    
    return 0;
}

//MUDAR O VETOR PALAVRA PARA UM VETOR DE VETORES E FAZER OS HEAPS ANTES DA LEITURA DO ARQUIVO DE INPUT