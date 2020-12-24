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
  Bee &operator[](size_t t) { return m_food[t]; };

  /// Return the position of all particles
  std::vector<std::vector<double> > getPopulationPosition();

  void evaluate();

  void evaluate(Bee&);

  void employedBeesEvalutaion();

  void onlookerBeesEvaluation();

  Bee getBestSolution() {return m_best_solution;}

private:
  void generateSolution(Bee&, size_t);

  void computeProbabilities();

  /// Return a random integer in [0, pop_size-1] different from the passed value
  size_t getRandomPopulationIndex(size_t);

  // there is only one artificial employed bee for each food source

  ABCConfig           m_config;
  std::vector<Bee>    m_food; // the size of the entire colony
  std::vector<double> m_prob;
  std::vector<int>    m_trial;
  size_t              m_onlookers;
  size_t              m_scouters;
  double              m_fitness_sum;
  size_t              m_limit_scout; // lmit for scout
  Bee                 m_best_solution;
};

#endif
