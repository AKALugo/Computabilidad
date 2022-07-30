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

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Estados {

  public:
    void Clean();

    void InicializarEstados(const std::string &);
    void ConstruirEstados(std::string&);
    void ActualizarEstados ();
    void LimpiarAuxEstados ();
    void Reset ();
    
    const std::string get_EstadosFirst(const unsigned);
    const int get_EstadosSecond(const unsigned);
    const unsigned get_TamanoDeEstados();

    const std::string get_EstadosDeAceptacion(const unsigned);
    const unsigned get_TamanoDeEstadosDeAceptacion();

    const std::string get_TransicionesFirst(const unsigned);
    const std::string get_TransicionesSecond(const unsigned);
    const unsigned get_TamanoDeTransciones();

    void set_AuxEstadosSecond (const unsigned, int);
    void set_EstadosSecond (const unsigned, int);

  private:
    std::string estado_inicial_;
    std::vector<std::pair<std::string, int>> estados_;
    std::vector<std::pair<std::string, int>> aux_estados_;
    std::vector<std::string> estados_aceptacion_;
    std::vector<std::pair<std::string, std::string>> transiciones_;
};