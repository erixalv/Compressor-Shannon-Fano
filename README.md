# Compressor Shannon-Fano

Projeto de um compressor e descompressor Shannon-Fano estático não-contextual em C++. O código consiste em:

## Compressor:
- Realiza a leitura de um arquivo .txt e pré-processa o texto.
- Comprime em um arquivo .bin numa codificação de Shannon-Fano baseado nas frequências de digitação dos caracteres na língua portuguesa.
- Exibe no terminal a razão de compressão no texto e o texto codificado.

## Descompressor:
- Realiza a leitura do arquivo .bin e o decodifica em um arquivo .txt com os caracteres comprimidos anteriormente.
