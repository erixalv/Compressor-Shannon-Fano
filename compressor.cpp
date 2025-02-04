#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <tuple>
#include <bitset>

using namespace std;

// Função para codificar o texto e exibir os bits no terminal
vector<uint8_t> codificarTexto(const string& texto, const unordered_map<char, string>& mapaCodigo, int& totalBits, int& numCaracteresCodificados, string& bitsCodificados) {
    vector<uint8_t> textoCodificado;
    string buffer;
    totalBits = 0;
    numCaracteresCodificados = 0;
    bitsCodificados = "";

    for (char c : texto) {
        if (mapaCodigo.find(c) != mapaCodigo.end()) {
            string codigo = mapaCodigo.at(c);
            bitsCodificados += codigo;  // Acumula a sequência de bits
            buffer += codigo;
            totalBits += codigo.size();
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
        {'a', "010"}, {'b', "1111100"}, {'c', "11011"},
        {'d', "10111"}, {'e', "001"}, {'f', "1111101"},
        {'g', "111100"}, {'h', "1111010"}, {'i', "1010"},
        {'j', "11111110"}, {'k', "1111111110"}, {'l', "11100"},
        {'m', "11000"}, {'n', "10110"}, {'o', "011"},
        {'p', "111010"}, {'q', "1111011"}, {'r', "1001"},
        {'s', "1000"}, {'t', "11010"}, {'u', "11001"},
        {'v', "111011"}, {'w', "11111111110"}, {'x', "111111110"},
        {'y', "11111111111"}, {'z', "1111110"}, {' ', "000"},
        {'A', "010"}, {'B', "1111100"}, {'C', "11011"},
        {'D', "10111"}, {'E', "001"}, {'F', "1111101"},
        {'G', "111100"}, {'H', "1111010"}, {'I', "1010"},
        {'J', "11111110"}, {'K', "1111111110"}, {'L', "11100"},
        {'M', "11000"}, {'N', "10110"}, {'O', "011"},
        {'P', "111010"}, {'Q', "1111011"}, {'R', "1001"},
        {'S', "1000"}, {'T', "11010"}, {'U', "11001"},
        {'V', "111011"}, {'W', "11111111110"}, {'X', "111111110"},
        {'Y', "11111111111"}, {'Z', "1111110"},
    };

    ifstream arquivoEntrada("../input.txt");
    string linha, conteudo;
    while (getline(arquivoEntrada, linha)) {
        conteudo += linha + '\n';
    }
    arquivoEntrada.close();

    int totalBits, numCaracteresCodificados;
    string bitsCodificados;
    vector<uint8_t> textoCodificado = codificarTexto(conteudo, mapaCodigo, totalBits, numCaracteresCodificados, bitsCodificados);

    // Exibir a sequência de bits codificada
    cout << "Texto codificado em bits:\n" << bitsCodificados << endl;

    ofstream arquivoSaida("../texto_codificado.bin", ios::binary);
    arquivoSaida.write(reinterpret_cast<const char*>(textoCodificado.data()), textoCodificado.size());
    arquivoSaida.close();

    if (numCaracteresCodificados > 0) {
        double mediaBitsPorSimbolo = static_cast<double>(totalBits) / numCaracteresCodificados;
        double razaoCompressao = 5.0 / mediaBitsPorSimbolo;

        cout << "Razao de compressao: " << razaoCompressao << endl;
    }
}
