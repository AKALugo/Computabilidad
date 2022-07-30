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

#include <fstream>
#include <iostream>
#include <string>
#include <vector> 

/**
 * @class Gramatica
 * @brief apartir de un Dfa generamos la Gramatica que compone al Dfa.
 */
class Gramatica {

  public:
    Gramatica ();
    ~Gramatica ();

    void SimbolosTerminales (const std::vector<std::string>);
    void SimbolosNoTerminales (std::vector<Estado>&);
    void Producciones (std::vector<Estado>&, std::vector<std::string>&,
                       std::vector<std::pair<std::string,std::string>>&);
    void Escritura (std::ostream& os = std::cout);

  private:
    /// Metodo que asocia a cada estado un simbolo no terminal.
    void SimbolosNoTerminalesEstados (std::vector<Estado>&);
    /// Metodo que almacena las distintas producciones.
    void FormarProducciones (std::pair<std::string,std::string>&, std::string&,
                             std::string&);
    void FormarProduccionesEpsilon (std::pair<std::string,std::string>&, 
                                    const unsigned, std::vector<Estado>&);

    /// Vector de Strings donde vamos a almacenar los simbolos terminales
    std::vector<std::string> simbolos_terminales_;
    /// Vector de string donde vamos a almacenar los simbolos no terminales.
    std::vector<std::string> simbolos_no_terminales_;
    /// String donde almacenamos el simbolo de arranque (por normal general S)
    std::string simbolo_arranque_;
    /// Vector de pares de strings donde vamos a asociar cada estado del Dfa
    /// a un simbolo no terminal.
    std::vector<std::pair<std::string,std::string>> union_no_simbolo_estado_;
    /// Vector de pares de strings donde guardamos primero el simbolo no 
    /// terminal y luego sus distintas transaciones.
    std::vector<std::pair<std::string,std::string>> producciones_;
};

std::ostream& operator<<(std::ostream&, Gramatica&);