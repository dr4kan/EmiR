#ifndef EmiR_GAPopulation_h
#define EmiR_GAPopulation_h

#include "GAChromosome.h"
#include "GAConfig.h"
#include "../Base/Population.h"

class GAPopulation : public Population {
public:

  GAPopulation(Function);

  void init();

  void setConfig(const GAConfig&);

  /// Sort the particles according to the  cost
  void sort();

  /// Return the number of particles in the GAPopulation
  size_t size() const;

  /// Access the specified solution
  Individual &operator[](size_t t) { return m_chromosomes[t]; };

  /// Return the position of all particles
  std::vector<std::vector<double> > getPopulationPosition();

  void evaluate();

  void evaluate(GAChromosome&);

  GAChromosome getBestSolution() {return m_best_solution;}

  // Mating, crossover, evaluate and sort
  void crossover();

  // Mutation evaluate and sort
  void mutation();

private:
  GAConfig                  m_config;
  std::vector<GAChromosome> m_chromosomes;
  GAChromosome              m_best_solution;
};

#endif
