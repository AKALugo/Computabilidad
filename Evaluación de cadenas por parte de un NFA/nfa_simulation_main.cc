/**
*  Grado:       Grado de ingeniería informática.
*  Asignatura:  Computablilidad y algoritmia.
*  Autor:       Alejandro Lugo Fumero.
*  Correo:      alu0101329185@ull.edu.es
*  Práctica nº: 8
*  Comentario:  Este programa evualua el reconocimiento de una serie de
*               cadenas por parte de un NFA
*  Compilar:    g++ -std=c++14 -g -Wall -o dfa_simulation dfa_simulation_main.cc
*               dfa_simulation.cc estado.cc
*  Ejecución:   ./dfa_simulation input.dfa input.txt outfile.txt
*/

#include "nfa.h"

#include <iostream>

int main (int argc, char* argv[]) {
  
  std::string archivo_de_salida = "outfile.txt";
  std::string archivo_nfa = "input.nfa";
  std::string archivo_de_entrada = "input.txt";
  std::string ayuda = "--help";

  /// Si el usuario escribe --help.
  if (argc == 2 && argv[1] == ayuda) {
 
    std::cout << "Este programa evalua el reconocimiento de una serie de"
    " cadenas por parte de un NFA" << std::endl;    
    return 0;
  }

  /// Revisamos que todos los datos introducidos sean correctos.
  if (argc != 4 || argv[1] != archivo_nfa || argv[2] != archivo_de_entrada ||
      argv[3] != archivo_de_salida) {
    
    std::cout << "Modo de empleo: ./nfa_simulation input.nfa input.txt"
    " outfile.txt" << std::endl << "Pruebe ’dfa_simulation --help’ para más"
    " información." << std::endl;

    return 0;
  }
  
  /// Creamos e inicializamos los ficheros y los distintos tipos de dato a usar.
  std::ifstream archivo_de_cadenas (archivo_de_entrada);
  std::ofstream archivo_de_escritura (archivo_de_salida);
  Nfa nfa(archivo_nfa);

  while (!archivo_de_cadenas.eof()){
    archivo_de_cadenas >> nfa;
    archivo_de_escritura << nfa;
  }

  archivo_de_cadenas.close();
  archivo_de_escritura.close();
}