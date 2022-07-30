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

#include "nfa.h"

Nfa::Nfa (const std::string & fichero_nfa) {

  estados_.InicializarEstados(fichero_nfa);
}



void
Nfa::Evaluacion (const std::string& cadena) {

  std::string auxiliar;
  cadena_actual_ = cadena;
  eval_cadena_actual = false;

  for (unsigned desplazamiento = 0; desplazamiento < cadena.size(); desplazamiento++) {
    Epsilon();
    auxiliar = cadena[desplazamiento];
    estados_.LimpiarAuxEstados ();
    for (unsigned recorrido = 0; recorrido < estados_.get_TamanoDeEstados(); recorrido ++)
      if (estados_.get_EstadosSecond(recorrido) == 1) {

        unsigned contador = 0;
        while (estados_.get_TransicionesFirst(contador) != estados_.get_EstadosFirst(recorrido))
          contador++;
        contador++;

        while (estados_.get_TransicionesSecond(contador) != "-1" && contador < estados_.get_TamanoDeTransciones()) {
          if (estados_.get_TransicionesFirst(contador) == auxiliar)
            for (unsigned recorrido1 = 0; recorrido1 < estados_.get_TamanoDeEstados(); recorrido1 ++) 
              if (estados_.get_TransicionesSecond(contador) == estados_.get_EstadosFirst(recorrido1)) {
                estados_.set_AuxEstadosSecond(recorrido1, 1);
                break;
              }
          contador++;
        }
      }
    estados_.ActualizarEstados ();
  }

  Epsilon();
  Resultado ();

  estados_.Reset();
}



void
Nfa::Epsilon () {

  for (unsigned recorrido = 0; recorrido < estados_.get_TamanoDeEstados(); recorrido ++)
    if (estados_.get_EstadosSecond(recorrido) == 1) {
    
      unsigned contador = 0;
      while (estados_.get_TransicionesFirst(contador) != estados_.get_EstadosFirst(recorrido))
        contador++;
      contador++;
      
      while (estados_.get_TransicionesSecond(contador) != "-1" && contador < estados_.get_TamanoDeTransciones()) {
        if (estados_.get_TransicionesFirst(contador) == "~")
          for (unsigned recorrido1 = 0; recorrido1 < estados_.get_TamanoDeEstados(); recorrido1 ++) 
            if (estados_.get_TransicionesSecond(contador) == estados_.get_EstadosFirst(recorrido1)) {
              estados_.set_AuxEstadosSecond(recorrido1, 1);
              break;
            }
        contador++;
      }
    }
  estados_.ActualizarEstados ();
}



void
Nfa::Resultado () {

  for (unsigned recorrido = 0; recorrido < estados_.get_TamanoDeEstados(); recorrido ++) {
    if (estados_.get_EstadosSecond(recorrido) == 1)
    for (unsigned recorrido1 = 0; recorrido1 < estados_.get_TamanoDeEstadosDeAceptacion(); recorrido1 ++)
      if (estados_.get_EstadosFirst(recorrido) == estados_.get_EstadosDeAceptacion(recorrido1))
        eval_cadena_actual = true;
  }
}



void
Nfa::Escritura(std::ostream& os) {

  if (!eval_cadena_actual)
    os << cadena_actual_ << " -- NO" << std::endl;
  else
    os << cadena_actual_ << " -- SI" << std::endl;
}



void 
Nfa::Lectura(std::istream& is) {
  
  is >> cadena_actual_;
  Evaluacion(cadena_actual_);
}



std::istream&
operator>>(std::istream& is, Nfa& A) {
  
  A.Lectura(is);
  return is;
}



std::ostream&
operator<<(std::ostream& os, Nfa& A) {
  
  A.Escritura(os);
  return os;
}