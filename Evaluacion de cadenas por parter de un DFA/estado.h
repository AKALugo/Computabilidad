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

#pragma once

#include <iostream>
#include <string>

class Estado {

  public:
    Estado (const std::string);
    ~Estado ();

    const std::string get_Estado();
    const unsigned get_TamanoEstado();
    void GuardarEstadoAceptacion(const bool estado = false);
    bool RetornarEstadoAceptacion();
    void GuardarEstadoInicial(const bool estado = false);
    bool RetornarEstadoInicial();

  private:
    std::string estado_;
    bool estadoaceptacion_;
    bool estadoinicial_;
};