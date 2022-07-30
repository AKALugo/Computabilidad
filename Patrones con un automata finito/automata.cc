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


#include "automata.h"

Automata::Automata (const std::string cadena) {

  Construir (cadena);
}



bool 
Automata::Evaluar (const std::string cadena) {

  unsigned contador = 0;
  for (unsigned recorrido = 0; recorrido < cadena.size(); recorrido++) {

    if (contador >= Kcadena_.size()) return true;
    MostrarProceso (cadena[recorrido], Kcadena_[contador], contador);

    if (cadena[recorrido] == Kcadena_[contador]) contador ++;
    else contador = 0;
  }

  if (contador >= Kcadena_.size()) return true;
  return false;
}



void
Automata::Construir (const std::string cadena) {

  Kcadena_ = cadena;
}



void
Automata::MostrarProceso(char analizar, char patron, unsigned posicion){

  std::cout<<"posicion->" << posicion << " " << "Cadena comprobar->" 
  << analizar << " " <<"Patron de busqueda->" << patron <<std::endl;
}