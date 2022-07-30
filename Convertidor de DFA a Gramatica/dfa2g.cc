/**
*  Grado:       Grado de ingeniería informática.
*  Asignatura:  Asignatura de computablilidad y algoritmia.
*  Autor:       Alejandro Lugo Fumero.
*  Correo:      alu0101329185@ull.edu.es
*  Práctica nº: 9
*  Comentario:  Este programa a partir de un Dfa genera su Gramatica, creando
*               un objeto de la clase Gramatica.
*  Compilar:    g++ -std=c++14 -g -Wall -o dfa2g dfa.cc clase.cc gramatica.cc dfa2g.cc
*  Ejecutar:    ./dfa2g input.dfa output.gra
*/

#include "dfa.h"
#include "gramatica.h"

#include <iostream>

int main (int argc, char* argv[]) {
  
  std::string archivo_de_salida = "output.gra";
  std::string archivo_dfa = "input.dfa";
  std::string ayuda = "--help";

  /// Si el usuario escribe --help.
  if (argc == 2 && argv[1] == ayuda) {
 
    std::cout << "Este programa genera una Gramatica partiendo de un Dfa" << 
              std::endl;    
    return 0;
  }

  /// Revisamos que todos los datos introducidos sean correctos.
  if (argc != 3 || argv[1] != archivo_dfa || argv[2] != archivo_de_salida) {
    
    std::cout << "Modo de empleo: ./dfa2g input.dfa output.gra" << std::endl <<
             "Pruebe ’dfa_simulation --help’ para más información." << std::endl;
    return 0;
  }
  
  Dfa dfa(archivo_dfa);

  if (!dfa.ErrorAutomata()){
    std::cout << "HA OCURRIDO UN ERROR IMPREVISTO, EL DFA ESTA MAL DEFINIDO" <<
    std::endl;
    return 0;
  }

  std::ofstream archivo_de_escritura (archivo_de_salida);
  Gramatica gramatica;
  gramatica = dfa.ConvertirAGramatica();

  archivo_de_escritura << gramatica;
}