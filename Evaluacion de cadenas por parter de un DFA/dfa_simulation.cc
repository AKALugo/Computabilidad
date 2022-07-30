/**
*  Grado:       Grado de ingeniería informática.
*  Asignatura:  Computablilidad y algoritmia.
*  Autor:       Alejandro Lugo Fumero.
*  Correo:      alu0101329185@ull.edu.es
*  Práctica nº: 7
*  Comentario:  Este programa evualua el reconocimiento de una serie de
*               cadenas por parte de un DFA
*  Compilar:    g++ -std=c++14 -g -Wall -o dfa_simulation dfa_simulation_main.cc
*               dfa_simulation.cc estado.cc
*  Ejecución:   ./dfa_simulation input.dfa input.txt outfile.txt
*/

#include "dfa_simulation.h"

/// Leemos los datos del fichero que crea el Dfa y utilizamos distintos metodos
/// para crear las distintas partes que lo forman.
Dfa::Dfa(const std::string& fichero_automata) {
    
  std::ifstream creacion_automata(fichero_automata);
  int partes_dfa = 0;
  int numero;
  int contador = 0;
  int contador_interno = 0;

  std::pair<std::string,std::string> auxiliar_estados;
  std::string lectura;
    
  while(getline(creacion_automata, lectura)) {
    /// Si la línea empieza por "//" la vamos a omitir.
    if (lectura[0] != '/' && lectura[1] != '/') {
      if (partes_dfa == 0) {
        ConstruirAlfabeto (lectura, partes_dfa, contador, contador_interno,
                          numero);
      }

      if (partes_dfa == 2) {
        ConstruirEstados (lectura, partes_dfa, contador, contador_interno,
                         numero);
      }

      if (partes_dfa == 4) {
        ConstruirEstadoInicial(lectura, partes_dfa);
      }

      if (partes_dfa == 6) {
        ConstruirEstadoAceptacion (lectura, partes_dfa, contador,
                                   contador_interno, numero);
      }

      if (partes_dfa == 8) {
        ConstruirTransicion (lectura, auxiliar_estados, partes_dfa, contador,
                             contador_interno, numero);
      }
      if (partes_dfa == 1 || partes_dfa == 3 || partes_dfa == 5 ||
          partes_dfa == 7)
        partes_dfa ++;
    }
  }
  creacion_automata.close();
}



Dfa::~Dfa () {
  
  alfabeto_.clear();
  estados_.clear();
  alfabeto_de_transicion_.clear();
  transicion_.clear();
}



/// Almacenamos los distintos simbolos del alfabeto en "alfabeto_", (este
/// algoritmo se repite para algunas de las otras partes del Dfa).
void
Dfa::ConstruirAlfabeto (std::string& lectura, int& partes_dfa, int& contador,
                        int& contador_interno, int& numero) {
  /// Miramos la cantidad de simbolos a almacenar
  if (contador == 0) {
    numero = stoi(lectura);
    contador ++;
  }
  /// Almacenamos los distintos simbolos
  if (contador <= numero && contador_interno != 0) {
    /// Comprobamos que los simbolos del alfabeto sean imprimibles.
    ErrorAlfabeto(lectura);
    alfabeto_.push_back(lectura);
    contador ++; 
  }
  /// Si hemos acabado ponemos el contador a "0" y sumamos "1" a partes_dfa
  /// para no volver a este metodo.
  if (contador > numero) {
    partes_dfa ++;
    contador = 0;
  }
  /// Este contador sirve para no almacenar el valor que nos dice la cantidad
  /// de simbolos a almacenar sino empezar a alamcenar apartir de ahí.
  contador_interno = 1;
}



/// Almacenamos los distintos estados en "estados_".
void
Dfa::ConstruirEstados (std::string& lectura, int& partes_dfa, int& contador,
                       int& contador_interno, int& numero) {
  Estado auxiliar(lectura);
  if (contador == 0) {
    numero = stoi(lectura);
    contador ++;
    contador_interno = 0;
  }
  if (contador <= numero && contador_interno != 0) {
    estados_.push_back(auxiliar);
    contador ++; 
  }
  if (contador > numero) {
    partes_dfa ++;
    contador = 0;
  }
  contador_interno = 1;
}



/// Guardamos el estado inicial en nuestro vector de la clase Estados poniendo
/// a true un bool correspondiente al estado inicial.
void 
Dfa::ConstruirEstadoInicial (std::string& lectura, int& partes_dfa) {

  for (unsigned recorrido = 0; recorrido < estados_.size(); recorrido++) {
    if (estados_[recorrido].get_Estado() == lectura) 
      estados_[recorrido].GuardarEstadoInicial(true);   
  }
  partes_dfa ++;
}



/// Guardamos el estado de aceptacion en nuestro vector de la clase Estados poniendo
/// a true un bool correspondiente al estado de aceptacion.
void 
Dfa::ConstruirEstadoAceptacion (std::string& lectura, int& partes_dfa, int&
                                contador, int& contador_interno, int& numero) {
  if (contador == 0) {
    numero = stoi(lectura);
    contador ++;
    contador_interno = 0;
  }
  if (contador <= numero && contador_interno != 0) {
    for (unsigned recorrido = 0; recorrido < estados_.size(); recorrido++) {
      if (estados_[recorrido].get_Estado() == lectura) 
        estados_[recorrido].GuardarEstadoAceptacion(true);   
  }
    contador ++; 
  }
  if (contador > numero) {
    partes_dfa ++;
    contador = 0;
  }
  contador_interno = 1;
}



/// Almacenamos los distintos estados de transicion en "transicion_" y los
/// simbolos de alfabeto necesarios para cambiar de un estado a otro los
/// guardaremos en la misma posicion que las transiciones per en un vector
/// llamado "alfabeto_transicion_".
void 
Dfa::ConstruirTransicion(std::string& lectura, std::pair<std::string,std::string>&
                         auxiliar_estados, int& partes_dfa, int& contador, int&
                         contador_interno, int& numero) {
  if (contador == 0) {
    numero = stoi(lectura);
    contador ++;
    contador_interno = 0;
  }
  if (contador <= numero && contador_interno != 0) {
    contador ++;
    /// Int que cuenta los espacios que hay para así separar las distintas partes.
    int espacios = 0;
    /// String que vamos a usar para formar las distintas partes.
    std::string cadena;
    /// Recorremos los distintos simbolos del string ya que de el vamos a sacar
    /// tres datos distintos, 2 estados y el simbolo necesario para cambiar
    /// del primero al segundo.
    for (unsigned recorrido = 0; recorrido < lectura.size(); recorrido ++) {
      if (lectura[recorrido] != ' ')
        cadena.push_back(lectura[recorrido]);
      if (lectura[recorrido] == ' ')
        espacios ++;
      /// El primer simbolo (hasta el primer espacio).
      if (espacios == 1){
        auxiliar_estados.first = cadena;
        espacios ++;
        cadena.clear();
      }
      /// El segundo simbolo (del primer espacio al segundo).
      if (espacios == 3){
        alfabeto_de_transicion_.push_back(cadena);
        espacios ++;
        cadena.clear();
      }
      /// El ultimo simbolo (del ultimo espacio hasta el final).
      if (recorrido == lectura.size() -1)
        auxiliar_estados.second = cadena;
    }
    transicion_.push_back(auxiliar_estados);
  }
  contador_interno = 1;
}



/// Este metodo es el algoritmo del Dfa, comienza en una posicion inicial y según
/// reciba un simbolo del alfabeto se moverá hacia un estado u otro, en el caso
/// de que reciba un simbolo del alfabeto y no disponga de un nodo para 
/// moverse lo que hará será ir a un estado de muerte y acabar el algoritmo
/// cuando recorra toda la cadena mirará el estado donde se encuentra, si este
/// es de aceptación retornará true y si no lo es retornará false (cabe destacar
/// que si llega a un estado de muerte retornará false)
bool
Dfa::Evaluar(std::string cadena){

  std::string movimiento;
  std::string simbolo;
  bool anadir = false;
  bool no_muerte = false;

  for (unsigned recorrido = 0; recorrido < estados_.size(); recorrido++) {
    if (estados_[recorrido].RetornarEstadoInicial() == true) 
      movimiento = estados_[recorrido].get_Estado();   
  }

  /// Recorremos los distintos simbolos de la cadena.
  for (unsigned recorrido = 0; recorrido < cadena.size(); recorrido++) {
    simbolo = cadena[recorrido];
    /// Recorremos las distintas transiciones.
    for (unsigned desplazamiento = 0; desplazamiento < transicion_.size();
         desplazamiento++) {
      if (anadir == false){
        /// Si nos encontramos en un estado que acepta el simbolo de la cadena
        /// nos desplazamos a el.
        if (transicion_[desplazamiento].first == movimiento && simbolo == 
            alfabeto_de_transicion_[desplazamiento]) {
          movimiento = transicion_[desplazamiento].second;
          no_muerte = true;
          anadir = true;
        }
      }
    }
    /// Si no hemos encontrado ningun estado al que movernos nos vamos al estado
    /// de muerte. 
    if (no_muerte == false){
      return false;
    }
    no_muerte = false;
    anadir = false;
  }
  /// Miramos si nos encontramos en un estado de aceptación.
  for (unsigned recorrido = 0; recorrido < estados_.size();
       recorrido++) {
    if (estados_[recorrido].get_Estado() == movimiento && 
        estados_[recorrido].RetornarEstadoAceptacion() == true)
      return true;
  }
  return false;
}



/// Metodo que imprimirá en outfile.txt la cadena seguida de su evaluacion.
void
Dfa::ImprimirEnFichero(std::string& cadena, const bool evaluacion, std::ofstream&
                       salida) {

  if (!evaluacion)
    salida << cadena << " -- NO" << std::endl;
  if (evaluacion)
    salida << cadena << " -- SI" << std::endl;
}



/// En este metodo vamos a comprobar que todos los datos que forman el Dfa son
/// coherentes.
bool
Dfa::ErrorAutomata() {
  unsigned error = 0;
  /// Comprobamos que los simbolos para cambiar de un estado a otro pertenecen
  /// al alfabeto.
  for (unsigned recorrido = 0; recorrido < alfabeto_.size(); recorrido++) {
    for (unsigned desplazamiento = 0; desplazamiento < 
         alfabeto_de_transicion_.size(); desplazamiento++) {
      if (alfabeto_[recorrido] == alfabeto_de_transicion_[desplazamiento])
        error ++;
    }
  }
  if (error != alfabeto_de_transicion_.size())
    return false;

  error = 0;
  /// Comprobamos que los estados de aceptacion pertenezcan a los estados del 
  /// DFA.
  for (unsigned recorrido = 0; recorrido < estados_.size(); recorrido++) { 
    if (estados_[recorrido].RetornarEstadoAceptacion() == true)
      error ++;
    }
  if (error == 0)
    return false;

  error = 0;
  /// Comprobamos que el estado inicial pertenece a los estados del DFA.
  for (unsigned recorrido = 0; recorrido < estados_.size(); recorrido++) {
    if (estados_[recorrido].RetornarEstadoInicial() == true)
      error ++;
  }
  if (error != 1)
    return false;

  error = 0;
  /// Comprobamos que los estados de transicion pertenezcan a los estados del
  /// Dfa.
  for (unsigned recorrido = 0; recorrido < estados_.size(); recorrido++) {
    for (unsigned desplazamiento = 0; desplazamiento < transicion_.size();
         desplazamiento++) {
      if (estados_[recorrido].get_Estado() == transicion_[desplazamiento].first)
        error ++;
      if (estados_[recorrido].get_Estado() == transicion_[desplazamiento].second)
        error ++;
    }
  }
  if (error != (transicion_.size() * 2))
    return false;

  return true;
}



/// Metodo que comprueba que todos los simbolos de la cadena a analizar
/// pertenezcan al alfabeto del Dfa.
bool
Dfa::ErrorCadena(std::string& cadena){
  unsigned error = 0;
  std::string simbolo;
  
  for (unsigned recorrido = 0; recorrido < alfabeto_.size(); recorrido++) {
    for (unsigned desplazamiento = 0; desplazamiento < cadena.size();
         desplazamiento++) {
      simbolo = cadena[desplazamiento];
      if (alfabeto_[recorrido] == simbolo)
        error ++;
    }
  }
  if (error != cadena.size())
    return true;
  return false;
}



/// Metodo que comprueba que todos los simbolos del alfabeto sean caracteres
/// imprimibles.
bool
Dfa::ErrorAlfabeto(std::string& cadena){
  if (cadena.size() == 1 && int(cadena[0]) >= kPrimerCaracterImprimible_ &&
      kSegundoCaracterImprimible_ >= int(cadena[0]))
    return 1;
  else {
    std::cout << "HA OCURRIDO UN ERROR INESPERADO, EN EL ALFABETO DEL DFA"
    " SE HAN ENCONTRADO CARACTERES NO IMPRIMIBLES" << std::endl;
    exit(0);
  }
}