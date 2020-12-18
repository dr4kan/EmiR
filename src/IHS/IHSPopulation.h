#ifndef EmiR_Population_h
#define EmiR_Population_h

#include "../HS/Harmony.h"
#include "IHSConfig.h"
#include "../Base/Algorithm.h"

class IHSPopulation {
public:

  IHSPopulation(Function);

  void init();

  void setConfig(const IHSConfig&);

  void setParRange(const ParametersRange&);

  void setConstraints(List);

  /// Sort the particles according to the best cost
  void sort();

  /// Return the number of particles in the BATPopulation
  size_t size() const;

  /// Access the specified solution
  Harmony &operator[](size_t t) { return m_harmonies[t]; };

  /// Return the position of all particles
  std::vector<std::vector<double>> getPopulationPosition();

  void updateParameters(size_t);

  void generateNewHarmony();

  void evaluate();

  void evaluate(Harmony&);

private:
  IHSConfig             m_config;   /**< Configuration */
  std::mt19937          m_mt;
  ParametersRange       m_par_range;
  Function              m_obj_func;
  std::vector<Harmony>  m_harmonies;
  List                  m_constraints;

  double                m_current_par;
  double                m_current_bw;
};

#endif
