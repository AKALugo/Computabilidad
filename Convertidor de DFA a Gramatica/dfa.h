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

#include "estado.h"
#include "gramatica.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector> 

/**
 * @class Dfa
 * @brief apartir de un input.dfa crea un automata y lee las cadenas de un
 * input.txt donde las evaluará y escribirá en un outfile.txt, escribiendo
 * la cadena seguido de su evaluacion
 */

class Dfa {

  public:
    Dfa (const std::string&);
    ~Dfa ();

    bool Evaluar(std::string);
    void ImprimirEnFichero (std::string&, const bool, std::ofstream&);
    bool ErrorAutomata();
    bool ErrorCadena(std::string&);
    Gramatica ConvertirAGramatica ();

  private:
    void ConstruirAlfabeto (std::string&, int&, int&, int&, int&);
    void ConstruirEstados (std::string&, int&, int&, int&, int&);
    void ConstruirEstadoInicial (std::string&, int&);
    void ConstruirEstadoAceptacion(std::string&, int&, int&, int&, int&);
    void ConstruirTransicion(std::string&, std::pair<std::string,std::string>&, 
                             int&, int&, int&, int&);
    bool ErrorAlfabeto(std::string&);
    
    /// Vector de string donde almacenamos el alfabeto.
    std::vector<std::string> alfabeto_; 
    /// Vector de la clase Estado donde almacenamos los distintos estados, si
    /// es un estado de aceptacion y si es un estado de inicializacion.
    std::vector<Estado> estados_;
    /// Vector de string donde almacenamos el alfabeto necesario para pasar de
    /// un estado a otro.
    std::vector<std::string> alfabeto_de_transicion_;
    /// Vector de pares donde almacenamos los distintos estados de transcion,
    /// pero no el elemento del alfabeto necesario para cambiar de uno a otro.
    std::vector<std::pair<std::string,std::string>> transicion_;
    /// Numero ascii del primer y ultimo caracter imprimible, el resto de
    /// caracteres imprimibles se encuentra entre estos dos valores.
    int kPrimerCaracterImprimible_{20};
    int kSegundoCaracterImprimible_{127};
};