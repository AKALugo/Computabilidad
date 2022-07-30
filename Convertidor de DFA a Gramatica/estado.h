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

#pragma once

#include <iostream>
#include <string>

/**
 * @class Estado
 * @brief esta clase es usada en la clase Dfa para formar los distintos estados.
 */

class Estado {

  public:
    Estado (const std::string);
    ~Estado ();

    const std::string get_Estado();
    const unsigned get_TamanoEstado();
    void GuardarEstadoAceptacion(const bool);
    bool RetornarEstadoAceptacion();
    void GuardarEstadoInicial(const bool);
    bool RetornarEstadoInicial();

  private:
    /// String donde alamacenaremos el estado
    std::string estado_;
    /// Bool que es true si el estado en cuestion es de aceptacion.
    bool estadoaceptacion_;
    /// Bool que es true si el estado en cuestion es un estado inicial.
    bool estadoinicial_;
};