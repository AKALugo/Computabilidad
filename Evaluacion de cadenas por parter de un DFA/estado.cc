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


#include "estado.h"

Estado::Estado(const std::string cadena) {

  estado_ = cadena;
}



Estado::~Estado() {}



const std::string
Estado::get_Estado() {

  return estado_;
}



const unsigned
Estado::get_TamanoEstado() {

  return estado_.size();
}



void
Estado::GuardarEstadoAceptacion(const bool aceptacion) {

  estadoaceptacion_ = aceptacion;
}



bool
Estado::RetornarEstadoAceptacion() {

  return estadoaceptacion_;
}



void
Estado::GuardarEstadoInicial(const bool inicial) {

  estadoinicial_ = inicial;
}



bool
Estado::RetornarEstadoInicial() {

  return estadoinicial_;
}