#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <tuple>
#include <bitset>

using namespace std;

// Função para codificar o texto
vector<uint8_t> codificarTexto(const string& texto, const unordered_map<char, string>& mapaCodigo, int& totalBits, int& numCaracteresCodificados) {
    vector<uint8_t> textoCodificado;
    string buffer;
    totalBits = 0;
    numCaracteresCodificados = 0;

    for (char c : texto) {
        if (mapaCodigo.find(c) != mapaCodigo.end()) {
            buffer += mapaCodigo.at(c);
            totalBits += mapaCodigo.at(c).size();
            numCaracteresCodificados++;

            while (buffer.size() >= 8) {
                bitset<8> byte(buffer.substr(0, 8));
                textoCodificado.push_back(static_cast<uint8_t>(byte.to_ulong()));
                buffer.erase(0, 8);
            }
        }
    }

    // Se houver bits restantes, preenche com zeros
    if (!buffer.empty()) {
        while (buffer.size() < 8) {
            buffer += "0";
        }
        bitset<8> byte(buffer);
        textoCodificado.push_back(static_cast<uint8_t>(byte.to_ulong()));
    }

    return textoCodificado;
}

int main() {
    unordered_map<char, string> mapaCodigo = {
        {'a', "010"}, {'b', "1111101"}, {'c', "11100"},
        {'d', "10111"}, {'e', "001"}, {'f', "1111110"},
        {'g', "1111010"}, {'h', "1111011"}, {'i', "1010"},
        {'j', "111111110"}, {'k', "11111111110"}, {'l', "111010"},
        {'m', "1100"}, {'n', "10110"}, {'o', "011"},
        {'p', "111011"}, {'q', "1111100"}, {'r', "1001"},
        {'s', "1000"}, {'t', "11011"}, {'u', "11010"},
        {'v', "1111000"}, {'w', "111111111110"}, {'y', "111111111111"}, {'z', "11111110"}, {' ', "000"},
        {'A', "010"}, {'B', "1111101"}, {'C', "11100"},
        {'D', "10111"}, {'E', "001"}, {'F', "1111110"},
        {'G', "1111010"}, {'H', "1111011"}, {'I', "1010"},
        {'J', "111111110"}, {'K', "11111111110"}, {'L', "111010"},
        {'M', "1100"}, {'N', "10110"}, {'O', "011"},
        {'P', "111011"}, {'Q', "1111100"}, {'R', "1001"},
        {'S', "1000"}, {'T', "11011"}, {'U', "11010"},
        {'V', "1111000"}, {'W', "111111111110"}, {'X', "1111111110"},
        {'Y', "111111111111"}, {'Z', "11111110"},
    };

    ifstream arquivoEntrada("../input.txt");
    string linha, conteudo;
    while (getline(arquivoEntrada, linha)) {
        conteudo += linha + '\n';
    }
    arquivoEntrada.close();

    int totalBits, numCaracteresCodificados;
    vector<uint8_t> textoCodificado = codificarTexto(conteudo, mapaCodigo, totalBits, numCaracteresCodificados);

    ofstream arquivoSaida("../texto_codificado.bin", ios::binary);
    arquivoSaida.write(reinterpret_cast<const char*>(textoCodificado.data()), textoCodificado.size());
    arquivoSaida.close();

    if (numCaracteresCodificados > 0) {
        double mediaBitsPorSimbolo = static_cast<double>(totalBits) / numCaracteresCodificados;
        double razaoCompressao = 5.0 / mediaBitsPorSimbolo;

        cout << "Razao de compressao: " << razaoCompressao << endl;
    }
}
