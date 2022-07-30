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

#include "gramatica.h"

/**
 * @brief Construct a new Gramatica:: Gramatica object
 */
Gramatica::Gramatica () {

  simbolos_terminales_.resize(0);
  simbolos_no_terminales_.resize(0);
  union_no_simbolo_estado_.resize(0);
  producciones_.resize(0);
}



/**
 * @brief Destroy the Gramatica:: Gramatica object
 */
Gramatica::~Gramatica () {

  simbolos_terminales_.clear();
  simbolos_no_terminales_.clear();
  union_no_simbolo_estado_.clear();
  producciones_.clear();
  simbolo_arranque_.clear();
}



/**
 * @brief para ahorrarnos codigo vamos a copiar el vector que contiene el
 * alfabeto al vector que va a almacenar los simbolos terminales
 * @param alfabeto vector de la clase Dfa que contiene al alfabeto
 */
void
Gramatica::SimbolosTerminales (const std::vector<std::string> alfabeto) {

  simbolos_terminales_ = alfabeto;
}



/**
 * @brief por cada estado de la clase Dfa va a generar un simbolo no terminal,
 * al estado inicial siempre se la a asociar una S.
 * @param estados vector de Estado de la clase Dfa que contiene los diferentes
 * estados.
 */
void
Gramatica::SimbolosNoTerminales (std::vector<Estado>& estados) {

  char auxiliar = 'A';
  std::string convertir;
  simbolos_no_terminales_.push_back("S");
  simbolo_arranque_ = "S";

  for (unsigned recorrido = 0; recorrido < estados.size() - 1; recorrido++) {
    convertir = auxiliar;
    simbolos_no_terminales_.push_back(convertir);
    auxiliar = auxiliar + 1;
  }
  SimbolosNoTerminalesEstados(estados);
}



/**
 * @brief vamos a asociar a cada simbolo no terminal un estado de la clase Dfa,
 * al estado inicial le asociamos siempre una S
 * @param estados vector de Estado de la clase Dfa que contiene los diferentes
 * estados.
 */
void
Gramatica::SimbolosNoTerminalesEstados (std::vector<Estado>& estados) {

  std::pair<std::string,std::string> auxiliar;
  unsigned ayuda = 1;
  for (unsigned recorrido = 0; recorrido < estados.size(); recorrido++) {
    if (estados[recorrido].RetornarEstadoInicial() == true) {
      
      auxiliar.first = simbolo_arranque_;
      auxiliar.second = estados[recorrido].get_Estado();
      union_no_simbolo_estado_.push_back(auxiliar);
    }
  }

  for (unsigned recorrido = 0; recorrido < estados.size(); recorrido++) {
    if (estados[recorrido].RetornarEstadoInicial() != true) {
      
      auxiliar.first = simbolos_no_terminales_[ayuda];
      auxiliar.second = estados[recorrido].get_Estado();
      union_no_simbolo_estado_.push_back(auxiliar);
      ayuda ++;
    }
  }
}



/**
 * @brief vamos generar las distintas producciones de cada simbolo no termninal
 * para ello previamente hemos asociado un estado a cada simbolo no terminal,
 * @param estados vector de Estado de la clase Dfa que contiene los diferentes
 * estados.
 * @param alfabeto_de_transiciones vector de strings de la clase Dfa que contiene
 * el alfabeto que necesita cada estado para pasar al siguiente.
 * @param transicion vector de pares de strings de la clase Dfa que contiene los
 * distintos estados y que otro estado pueden transitar.
 */
void
Gramatica::Producciones(std::vector<Estado>& estados, std::vector<std::string>&
                        alfabeto_de_transiciones, 
                        std::vector<std::pair<std::string,std::string>>& 
                        transicion) {

  std::pair<std::string,std::string> auxiliar;
  std::string concatenacion;
  std::string mismo_movimiento;

  /// Recorremos el vector que asocia a cada estado un simbolo no terminal.
  for (unsigned recorrido = 0; recorrido < union_no_simbolo_estado_.size();
       recorrido++) {
    
    /// Guardamos el simbolo no terminal ya que vamos a generar su produccion.
    auxiliar.first = union_no_simbolo_estado_[recorrido].first;
    /// Recorremos todas las transiciones para poder crear las produciones de 
    /// cada estado.
    for (unsigned movimiento = 0; movimiento < transicion.size(); movimiento++) {
      
      /// Solo vamos a realizar el algoritmo si el estado de donde se transita 
      /// coincide con el estado asociado al simbolo no terminal que estamos 
      /// tratando.
      if (transicion[movimiento].first == 
          union_no_simbolo_estado_[recorrido].second) {
        /// Como con distinto simbolos de transicion podemos transitar al mismo
        /// estado primero guardaremos los datos de la transicion hasta comprobar
        /// que en la siguiente transicion del estado a tratar no transitemos a
        /// otro distinto.
          concatenacion = alfabeto_de_transiciones[movimiento];
          mismo_movimiento = transicion[movimiento].second;
          FormarProducciones (auxiliar, concatenacion, mismo_movimiento);
          concatenacion.clear();
      }
    }

    /// Si el estado a tratar es terminal en su produccion añadiremos una "~"
    FormarProduccionesEpsilon(auxiliar, recorrido, estados);
  }
}



/**
 * @brief creamos la produccion
 * @param auxiliar vector de pares de strings donde vamos almacenado el simbolo
 * no terminal y su produccion
 * @param concatenacion string donde concatenaremos los simbolos de transicion
 * y el simbolo no terminal
 * @param mismo_movimiento string donde esta el estado de que vamos que estamos
 * tratando.
 */
void
Gramatica::FormarProducciones (std::pair<std::string,std::string>& auxiliar, 
                               std::string& concatenacion, std::string& 
                               mismo_movimiento) {

  for (unsigned desplazamiento = 0; desplazamiento < 
       union_no_simbolo_estado_.size(); desplazamiento++) {
    if (mismo_movimiento == union_no_simbolo_estado_[desplazamiento].second) {
      concatenacion = concatenacion + union_no_simbolo_estado_[desplazamiento].first;
      auxiliar.second = concatenacion;
      producciones_.push_back(auxiliar);
    }
  }
}



/**
 * @brief creamos una produccion especial, llamada epsilon en el caso de que 
 * el simbolo no terminal este asociado a un estado de aceptacion.
 * @param auxiliar vector de pares de strings donde vamos almacenado el simbolo
 * no terminal y su produccion 
 * @param recorrido posicion del vector que asocia un simbolo no terminal con
 * un estado
 * @param estados vector de la clase Dfa que usaremos para mirar si un estado
 * es terminal
 */
void
Gramatica::FormarProduccionesEpsilon (std::pair<std::string,std::string>& auxiliar,
                                      const unsigned recorrido, std::vector<Estado>&
                                      estados) {

    for (unsigned desplazamiento = 0; desplazamiento < estados.size();
         desplazamiento++) {
      if (estados[desplazamiento].RetornarEstadoAceptacion() == true && 
          estados[desplazamiento].get_Estado() == 
          union_no_simbolo_estado_[recorrido].second) {
        auxiliar.second = "~";
        producciones_.push_back(auxiliar);
      }
    }
}



/**
 * @brief escribimos nuestra gramatica
 */
void
Gramatica::Escritura(std::ostream& os) {

  os << simbolos_terminales_.size() << std::endl;
  for (unsigned recorrido = 0; recorrido < simbolos_terminales_.size();
       recorrido++)
    os << simbolos_terminales_[recorrido] << std::endl;

  os << simbolos_no_terminales_.size() << std::endl;
  for (unsigned recorrido = 0; recorrido < simbolos_no_terminales_.size();
       recorrido++)
    os << simbolos_no_terminales_[recorrido] << std::endl;

  os << simbolo_arranque_ << std::endl;

  os << producciones_.size() << std::endl;
  for (unsigned recorrido = 0; recorrido < producciones_.size(); recorrido++)
  os << producciones_[recorrido].first << " --> " << 
     producciones_[recorrido].second << std::endl;
}



std::ostream&
operator<<(std::ostream& os, Gramatica& A) {

  A.Escritura(os);
  return os;
}