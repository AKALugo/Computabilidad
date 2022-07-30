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


#include "pattern_search.h"


/// Constructor que inicializa valores y añade el alfabeto sobre
/// el que vamos a trabajar.
Pattern_search::Pattern_search(const std::string entrada, const std::string salida, 
                              const std::string patron) {
  nombre_archivo_de_entrada_ = entrada;
  nombre_archivo_de_salida_ = salida;
  limit.first = unsigned('a');
  limit.second = unsigned('z');

  automata.Construir(patron);
}


Pattern_search::~Pattern_search() {}



/// Comprueba que las cadenas del fichero de entrada son
/// las esperadas por el alfabeto.
bool
Pattern_search::ErrorAlfabeto(const std::string cadena) {

  for (unsigned recorrido = 0; recorrido < cadena.size(); recorrido++)
    if (unsigned(cadena[recorrido]) < limit.first || unsigned(cadena[recorrido]) > limit.second)
      return true;
  
  return false;
}



/// Escribir error si no pertenece al alfabeto y tambien
/// si o no en fichero de salida.
void
Pattern_search::EscribirFichero() {

  std::ifstream archivo_de_entrada(nombre_archivo_de_entrada_);
  std::ofstream archivo_de_salida(nombre_archivo_de_salida_);
  
  std::string linea;        
  
  while(getline(archivo_de_entrada, linea)) {

    if (ErrorAlfabeto(linea))
      archivo_de_salida << "ERROR" << std::endl;
    else{
      if (automata.Evaluar(linea))
        archivo_de_salida << "si" << std::endl;
      else
        archivo_de_salida << "no" << std::endl;
      std::cout << std::endl;
    }
  }

  archivo_de_entrada.close();
  archivo_de_salida.close();
}