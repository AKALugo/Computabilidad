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

#include <iostream>
#include <string>

class Automata {

  public:
    Automata (const std::string = "");
    ~Automata () {}

    bool Evaluar (const std::string);

    void Construir (const std::string);

    void MostrarProceso(char analizar, char patron, unsigned posicion);

  private:
    std::string Kcadena_;
};