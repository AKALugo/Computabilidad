/**
*  Grado:       Grado de ingeniería informática.
*  Asignatura:  Computablilidad y algoritmia.
*  Autor:       Alejandro Lugo Fumero.
*  Correo:      alu0101329185@ull.edu.es
*  Práctica nº: 7
*  Comentario:  Este programa evualua el reconocimiento de una serie de
*               cadenas por parte de un DFA
*  Compilar:    g++ -std=c++14 -g -Wall -o dfa_simulation dfa_simulation_main.cc
*               dfa_simulation.cc estado.cc
*  Ejecución:   ./dfa_simulation input.dfa input.txt outfile.txt
*/

#include "dfa_simulation.h"

#include <iostream>

int main (int argc, char* argv[]) {
  
  std::string archivo_de_salida = "outfile.txt";
  std::string archivo_dfa = "input.dfa";
  std::string archivo_de_entrada = "input.txt";
  std::string ayuda = "--help";

  /// Si el usuario escribe --help.
  if (argc == 2 && argv[1] == ayuda) {
 
    std::cout << "Este programa evalua el reconocimiento de una serie de"
    " cadenas por parte de un DFA" << std::endl;    
    return 0;
  }

  /// Revisamos que todos los datos introducidos sean correctos.
  if (argc != 4 || argv[1] != archivo_dfa || argv[2] != archivo_de_entrada ||
      argv[3] != archivo_de_salida) {
    
    std::cout << "Modo de empleo: ./dfa_simulation input.dfa input.txt"
    " outfile.txt" << std::endl << "Pruebe ’dfa_simulation --help’ para más"
    " información." << std::endl;

    return 0;
  }
  
  /// Creamos e inicializamos los ficheros y los distintos tipos de dato a usar.
  std::ifstream archivo_de_cadenas (archivo_de_entrada);
  std::ofstream archivo_de_escritura (archivo_de_salida);
  std::string cadena_a_leer;
  Dfa dfa(archivo_dfa);
  bool aceptar;
  
  /// Llamamos a ErrorAutomata que en el caso de que en el infile.dfa haya algun
  /// error retorna 0 e imprime un mensaje avisando al usuario.
  if (!dfa.ErrorAutomata()){
    std::cout << "HA OCURRIDO UN ERROR IMPREVISTO, EL DFA ESTA MAL DEFINIDO" <<
    std::endl;
    return 0;
  }

  /// Leemos las distintas cadenas a analizar con el Dfa y las guardamos
  /// en un fichero de salida outfile.txt una vez evaluadas.
  while (getline(archivo_de_cadenas, cadena_a_leer)) {
    
    /// Comprobamos que los caracteres de la cadena pertenezcan al Dfa.
    if (dfa.ErrorCadena(cadena_a_leer))
      archivo_de_escritura << cadena_a_leer << " La cadena a leer contiene"
      " elementos que no pertenecen al alfabeto del Dfa" << std::endl;
    else {
      aceptar = dfa.Evaluar(cadena_a_leer);
      dfa.ImprimirEnFichero(cadena_a_leer, aceptar, archivo_de_escritura);
    }
  }
  archivo_de_cadenas.close();
  archivo_de_escritura.close();
}