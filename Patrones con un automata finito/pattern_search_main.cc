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

int main (int argc, char* argv[]) {

  std::string archivo_de_texto1 = "infile.txt";
  std::string archivo_de_texto2 = "outfile.txt";
  std::string ayuda = "--help";

  if (argc == 2 && argv[1] == ayuda){

    std::cout << "INTRODUZCA UNICAMENTE 3 PARAMETRO, EL PRIMERO DE ELLOS DEBE "
    "SER pattern Y EL SEGUNDO DEBE SER infile.txt YEL TERCERO DEBE SER outfile.txt"
     << std::endl;
 
    std::cout << "BUSCAR PATRON CON LA AYUDA DE UN AUTÓMATA FINITO"
    "DETERMINAR SI EN ELLAS SE ENCUENTRA O NO EL PATRÓN BUSCADO" << std::endl;
    
    return 0;
  }

  std::string cadena = argv[1];

  if (argc != 4 || argv[2] != archivo_de_texto1 || argv[3] != archivo_de_texto2) {
    
    std::cout << "INTRODUZCA UNICAMENTE 3 PARAMETRO, EL PRIMERO DE ELLOS DEBE "
    "SER pattern Y EL SEGUNDO DEBE SER infile.txt YEL TERCERO DEBE SER outfile.txt"
     << std::endl;

    return 0;
  }

  Pattern_search Automata(archivo_de_texto1, archivo_de_texto2, cadena);
  Automata.EscribirFichero();

  return 1;

}