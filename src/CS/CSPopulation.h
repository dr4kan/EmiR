#ifndef EmiR_CSPopulation_h
#define EmiR_CSPopulation_h

#include "Nest.h"
#include "CSConfig.h"
#include "../Base/Algorithm.h"

class CSPopulation {
public:

  CSPopulation(Function);

  void init();

  void setConfig(const CSConfig&);

  void setParRange(const ParametersRange&);

  void setConstraints(List);

  /// Sort the particles according to the best cost
  void sort();

  /// Return the number of particles in the BATPopulation
  size_t size() const;

  /// Access the specified solution
  Nest &operator[](size_t t) { return m_harmonies[t]; };

  /// Return the position of all particles
  std::vector<std::vector<double>> getPopulationPosition();

  void evaluate();

  void evaluate(Nest&);

private:
  CSConfig          m_config;
  std::mt19937      m_mt;
  ParametersRange   m_par_range;
  Function          m_obj_func;
  std::vector<Nest> m_harmonies;
  List              m_constraints;

};

#endif
