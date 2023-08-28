#include "palavra.hpp"
#include "functions.hpp"
#include <sstream> 
#include <vector>
#include <time.h>
#define NUMERO_ARQUIVOS 6

int main() {
    clock_t startTime, endTime;
    startTime = clock();

    string vetorArquivos[NUMERO_ARQUIVOS] = {"dataset/filosofia.txt", "dataset/filosofia2.txt", "dataset/globalizacao.txt", "dataset/politica.txt", "dataset/ti.txt", "dataset/ti2.txt"}, linha;
    string palavraAtual;
    ifstream arquivo, arquivoStopWords, arquivoInput;
    ofstream output;
    vector<string> tokens;
    vector<Palavra> vetorPalavras;
    vector<pair<int,int>> vetorOcorrencias;
    string token, stopword; 
    unordered_map<string, Palavra> vetorMaps[NUMERO_ARQUIVOS];
    unordered_map<string, string> stopWordMap;

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
                    transform(token.begin(), token.end(), token.begin(), ::tolower);
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
    while(!arquivoInput.eof()){
        arquivoInput >> palavraAtual;
        for(int i = 0; i < NUMERO_ARQUIVOS; i++){
            vetorOcorrencias.push_back(make_pair((i+1),vetorMaps[i][palavraAtual].ocorrencias));
        }
        BubbleSort(vetorOcorrencias);
        outputFile(output, palavraAtual, vetorOcorrencias);
        vetorOcorrencias.clear();
    }
    
    arquivoInput.close();
    output.close();

    endTime = clock();
    clock_t elapsedTime = endTime - startTime;
    double elapsedTimeMs = ((double)elapsedTime/CLOCKS_PER_SEC)*1000;
    cout << "TEMPO DE EXECUÇÃO: " << elapsedTimeMs << " ms " << endl;
    
    return 0;
}