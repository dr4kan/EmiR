#ifndef EmiR_GSAPopulation_h
#define EmiR_GSAPopulation_h

#include "GSAPlanets.h"
#include "GSAConfig.h"
#include "../Base/Population.h"

class GSAPopulation : public Population {
public:

  GSAPopulation(Function);

  void init();

  void setConfig(const GSAConfig&);

  /// Sort the planets according to the best cost and select the best solution
  /// of the population
  void firstSort();

  /// Sort the planets according to the best cost and select the best solution
  /// of the population if it is better than before
  void sort();

  /// Return the number of planets in the BATPopulation
  size_t size() const;

  /// Access the specified solution
  Individual &operator[](size_t t) { return m_planets[t]; };

  /// Return the position of all planets
  std::vector<std::vector<double> > getPopulationPosition();

  void evaluate();

  void evaluate(Individual&);

  GSAPlanets getBestSolution() {return m_best_solution;}

  void setVelocity(size_t);

  void setMass();

  void movePlanets(size_t);

private:
  GSAConfig                m_config;
  std::vector<GSAPlanets> m_planets;
  std::vector<double>     m_step_sizes;
  GSAPlanets              m_best_solution;
};

#endif
