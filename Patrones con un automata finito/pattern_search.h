/** 
*  Grado:       Grado de ingeniería informática.
*  Asignatura:  Computablilidad y algoritmia.
*  Autor:       Alejandro Lugo Fumero.
*  Correo:      alu0101329185@ull.edu.es
*  Práctica nº: 6
*  Comentario:  Este programa comprueba si un patrón se encuentra en una cadena
*               utilizando un automata finito
*  Compilar:    g++ -std=c++14 -g -Wall -o set_calculator 
*  Ejecución:   ./pattern_search pattern infile.txt outfile.txt
*/

#pragma once

#include "automata.h"

#include <fstream>
#include <iostream>
#include <string>

/// Lee de un fichero y crea un objeto llamado automata
/// con el que imprimos en fichero salida con condiciones
class Pattern_search {

  public:
    Pattern_search(const std::string, const std::string, const std::string);
    ~Pattern_search();

    bool ErrorAlfabeto(const std::string);
    void EscribirFichero();
   
  private: 
    std::pair<unsigned, unsigned> limit;
    std::string nombre_archivo_de_entrada_;
    std::string nombre_archivo_de_salida_;

    Automata automata;
};