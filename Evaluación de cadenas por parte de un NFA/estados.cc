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

#include "estados.h"

void
Estados::InicializarEstados(const std::string& fichero_automata) {
  
  std::ifstream creacion_automata(fichero_automata);
  int cantidad_estados;
  int partes_nfa = 0;
  std::string lectura;

  while(getline(creacion_automata, lectura)) {
    if (lectura[0] != '/' && lectura[1] != '/' && lectura[0] != '*' && lectura[1] != '*') {

      if (partes_nfa == 2 && cantidad_estados >= 0){
        ConstruirEstados(lectura);
        cantidad_estados --;
      }

      else if (partes_nfa == 1) {
        estado_inicial_ = lectura;
        partes_nfa ++;
      }

      else if (partes_nfa == 0) {
        cantidad_estados = stoi(lectura);
        partes_nfa ++;
      }
    }
  }
  aux_estados_ = estados_;
}
  


void
Estados::ConstruirEstados(std::string& lectura) {
    
  std::pair<std::string, std::string> auxiliar_transiciones;
  std::pair<std::string, int> auxiliar_estados;
  std::string cadena;
  int espacios = 0;


  for (unsigned recorrido = 0; recorrido < lectura.size(); recorrido ++) {
    if (espacios <= 5) {
      if (lectura[recorrido] != ' ')
        cadena.push_back(lectura[recorrido]);
    
      if (lectura[recorrido] == ' ' && espacios < 5)
        espacios ++;
    
      if (espacios == 1) { 
        auxiliar_estados.first = cadena;
        if (cadena == estado_inicial_) auxiliar_estados.second = 1;
        else auxiliar_estados.second = 0;
        estados_.push_back(auxiliar_estados);

        auxiliar_transiciones.first = cadena;
        auxiliar_transiciones.second = "-1";
        transiciones_.push_back(auxiliar_transiciones);

        espacios ++;
        cadena.clear();  
      }
    
      if (espacios == 3) {
        if (cadena == "1") estados_aceptacion_.push_back(auxiliar_estados.first);
        espacios ++;
        cadena.clear();
      }

      if (espacios == 5) {
        espacios ++;
        cadena.clear();
      }
    }
    else {
      if (lectura[recorrido] != ' ')
        cadena.push_back(lectura[recorrido]);
      else {
        if (espacios == 6) {
          auxiliar_transiciones.first = cadena;
          cadena.clear();
          espacios ++;
        }
        else if (espacios == 7) {
          auxiliar_transiciones.second = cadena;
          cadena.clear();
          espacios ++;
        }
        if (espacios == 8) {
          transiciones_.push_back(auxiliar_transiciones);
          espacios = espacios -2;
        }
      }
    }
  }
  if (espacios > 5) {
    auxiliar_transiciones.second = cadena;
    transiciones_.push_back(auxiliar_transiciones);
  }
}



void
Estados::Reset () {

  for (unsigned recorrido = 0; recorrido < aux_estados_.size(); recorrido++) {
    if (aux_estados_[recorrido].first == estado_inicial_)
      aux_estados_[recorrido].second = 1;
    else
      aux_estados_[recorrido].second = 0;
  }
  ActualizarEstados();
}



void
Estados::ActualizarEstados () {
  
  estados_ = aux_estados_;
}


void 
Estados::LimpiarAuxEstados () {

  for (unsigned recorrido = 0; recorrido < aux_estados_.size(); recorrido++)
    aux_estados_[recorrido].second = 0;
}



void
Estados::set_AuxEstadosSecond (const unsigned posicion, int valor) {

  aux_estados_[posicion].second = valor;
}



void
Estados::set_EstadosSecond (const unsigned posicion, int valor) {

  estados_[posicion].second = valor;
}



const std::string
Estados::get_EstadosFirst(const unsigned posicion) {

  return estados_[posicion].first;
}



const int
Estados::get_EstadosSecond(const unsigned posicion) {

  return estados_[posicion].second;
}



const std::string 
Estados::get_EstadosDeAceptacion(const unsigned posicion) {

  return estados_aceptacion_[posicion];
}



const std::string 
Estados::get_TransicionesFirst(const unsigned posicion) {

  return transiciones_[posicion].first;
}



const std::string
Estados::get_TransicionesSecond(const unsigned posicion) {

  return transiciones_[posicion].second;
}



const unsigned 
Estados::get_TamanoDeEstados() {

  return estados_.size();
}



const unsigned
Estados::get_TamanoDeEstadosDeAceptacion() {

  return estados_aceptacion_.size();
}



const unsigned
Estados::get_TamanoDeTransciones(){

  return transiciones_.size();
}