#ifndef EmiR_ABCPopulation_h
#define EmiR_ABCPopulation_h

#include "Bee.h"
#include "ABCConfig.h"
#include "../Base/Population.h"

class ABCPopulation : public Population {
public:

  ABCPopulation(Function);

  void init();

  void setConfig(const ABCConfig&);

  /// Sort the particles according to the best cost
  void sort();

  /// Return the number of particles in the BATPopulation
  size_t size() const;

  /// Access the specified solution
  Bee &operator[](size_t t) { return m_bees[t]; };

  /// Return the position of all particles
  std::vector<std::vector<double>> getPopulationPosition();

  void evaluate();

  void evaluate(Bee&);

  void newEmployedBeesSolutions();

private:
  double fitness(Bee&);

  /// Return a random integer in [0, pop_size-1] different from the passed value
  size_t getRandomPopulationIndex(size_t);

  // there is only one artificial employed bee for each food source

  ABCConfig          m_config;
  std::vector<Bee>   m_bees;
  size_t             m_unemployed_bees;

};

#endif
