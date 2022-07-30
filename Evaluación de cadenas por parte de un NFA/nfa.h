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

#pragma once

#include "estados.h"

#include <string>

class Nfa {

  public:
    Nfa (const std::string &);
    ~Nfa () {}

    void Evaluacion (const std::string& cadena);
    void Epsilon ();
    void Resultado ();

    void Escritura(std::ostream& = std::cout);
    void Lectura(std::istream& = std::cin);

  private:
    Estados estados_;
    bool eval_cadena_actual = false;
    std::string cadena_actual_;
};

std::istream& operator>>(std::istream&, Nfa&);
std::ostream& operator<<(std::ostream&, Nfa&);