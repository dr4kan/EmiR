#ifndef EmiR_HSPopulation_h
#define EmiR_HSPopulation_h

#include "../Base/Individual.h"
#include "HSConfig.h"
#include "../Base/Population.h"

class HSPopulation : public Population {
public:

  HSPopulation(Function);

  void init();

  void setConfig(const HSConfig&);

  /// Sort the particles according to the best cost
  void sort();

  /// Return the number of particles in the BATPopulation
  size_t size() const;

  /// Access the specified solution
  Individual &operator[](size_t t) { return m_harmonies[t]; };

  /// Return the position of all particles
  std::vector<std::vector<double> > getPopulationPosition();

  void generateNewHarmony();

  void evaluate();

  void evaluate(Individual&);

private:
  HSConfig             m_config;
  std::vector<Individual> m_harmonies;

};

#endif
