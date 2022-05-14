#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>

struct estado {
  int fila;
  int columna;
  int orientacion;
};

struct estadoCompleto : public estado {
  private:
  bool bikini, zapatillas;

  void setParams(bool b, bool z) {
    bikini = b;
    zapatillas = z;
  }

  public:
  explicit estadoCompleto(const estado & st) : estado(st) {
    bikini = zapatillas = false;
  }

  bool hasBikini() const {
    return bikini;
  }

  bool hasZapatillas() const {
    return zapatillas;
  }

  void acquireBikini() {
    setParams(true, false);
  }

  void acquireZapatillas() {
    setParams(false, true);
  }
};

class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      // Inicializar Variables de Estado
      hayPlan = false;
      acabar = false;
    }
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      // Inicializar Variables de Estado
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void VisualizaPlan(const estado &st, const list<Action> &plan);
    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}

  private:
    // Declarar Variables de Estado
    estado actual;
    list<estado> objetivos;
    list<Action> plan;
    bool hayPlan;
    bool acabar;

    // Métodos privados de la clase
    bool pathFinding(int level, const estado &origen, const list<estado> &destino, list<Action> &plan);
    bool pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_A_Estrella(const estado &origen, const estado &destino, list<Action> &plan, bool bikiniInicial, bool zapatillasInicial);

    void PintaPlan(list<Action> plan);
    bool HayObstaculoDelante(estado &st);

    int calcularCoste(Action accion, const estado & st, bool bikini, bool zapatillas) const;
    int calcularCoste(Action accion, const estadoCompleto & st) const;

    void resolverItemsEspeciales(estadoCompleto & st);

};

#endif
