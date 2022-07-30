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

#include "estado.h"

/**
 * @brief Construct a new Estado:: Estado object
 * @param cadena string que contiene el estado.
 */

Estado::Estado(const std::string cadena) {

  estado_ = cadena;
  estadoaceptacion_ = false;
  estadoinicial_ = false;
}



/**
 * @brief Destroy the Estado:: Estado object
 */
Estado::~Estado() {

  estado_.clear();
}



/**
 * @brief retornamos el estado
 */
const std::string
Estado::get_Estado() {

  return estado_;
}



/**
 * @brief retornamos el tamaño del string que contiene al estado.
 */
const unsigned
Estado::get_TamanoEstado() {

  return estado_.size();
}



/**
 * @brief guardamos si el estado es de aceptacion.
 */
void
Estado::GuardarEstadoAceptacion(const bool aceptacion) {

  estadoaceptacion_ = aceptacion;
}



/**
 * @brief retornamos true si el estado es de aceptacion y false si el estado no
 * es de aceptacion.
 */
bool
Estado::RetornarEstadoAceptacion() {

  return estadoaceptacion_;
}



/**
 * @brief guardamos si el estado es de aceptacion.
 */
void
Estado::GuardarEstadoInicial(const bool inicial) {

  estadoinicial_ = inicial;
}



/**
 * @brief retornamos true si el estado es de inicializacion y false si el estado
 *  no es de aceptacion.
 */
bool
Estado::RetornarEstadoInicial() {

  return estadoinicial_;
}