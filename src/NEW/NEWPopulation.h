#ifndef EmiR_NEWPopulation_h
#define EmiR_NEWPopulation_h

#include "Particle.h"
#include "NEWConfig.h"
#include "../Base/Population.h"

class NEWPopulation : public Population {
public:

  NEWPopulation(Function);

  void init();

  void setConfig(const NEWConfig&);

  /// Sort the particles according to the best cost
  void sort();

  /// Return the number of particles in the BATPopulation
  size_t size() const;

  /// Access the specified solution
  Individual &operator[](size_t t) { return m_charges[t]; };

  /// Return the position of all particles
  std::vector<std::vector<double> > getPopulationPosition();

  void evaluate();

  void evaluate(Individual&);

  void moveParicles();

  Particle getBestSolution() {return m_best_solution;}

private:
  NEWConfig             m_config;
  std::vector<Particle> m_charges;
  Particle              m_best_solution;
};

#endif
