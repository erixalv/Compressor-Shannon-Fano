#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

// Função para decodificar o texto
string decodificarTexto(const unordered_map<string, char>& mapaDecodificador, const vector<uint8_t>& textoCodificado) {
    string textoDecodificado;
    string buffer;

    for (uint8_t byte : textoCodificado) {
        bitset<8> bits(byte);
        string bitString = bits.to_string();
        for (char c : bitString) {
            buffer += c;
            if (mapaDecodificador.find(buffer) != mapaDecodificador.end()) {
                textoDecodificado += mapaDecodificador.at(buffer);
                buffer.clear();
            }
        }
    }

    return textoDecodificado;
}

int main() {
    unordered_map<string, char> mapaDecodificador = {
        {"010", 'a'}, {"1111101", 'b'}, {"11100", 'c'},
        {"10111", 'd'}, {"001", 'e'}, {"1111110", 'f'},
        {"1111010", 'g'}, {"1111011", 'h'}, {"1010", 'i'},
        {"111111110", 'j'}, {"11111111110", 'k'}, {"111010", 'l'},
        {"1100", 'm'}, {"10110", 'n'}, {"011", 'o'},
        {"111011", 'p'}, {"1111100", 'q'}, {"1001", 'r'},
        {"1000", 's'}, {"11011", 't'}, {"11010", 'u'},
        {"1111000", 'v'}, {"111111111110", 'w'}, {"1111111110", 'x'},
        {"111111111111", 'y'}, {"11111110", 'z'}, {"000", ' '}
    };

    ifstream arquivoEntrada("../texto_codificado.bin", ios::binary);
    vector<uint8_t> textoCodificado((istreambuf_iterator<char>(arquivoEntrada)), istreambuf_iterator<char>());
    arquivoEntrada.close();

    string textoDecodificado = decodificarTexto(mapaDecodificador, textoCodificado);

    ofstream arquivoSaida("../texto_decodificado.txt");
    arquivoSaida << textoDecodificado;
    arquivoSaida.close();

}
