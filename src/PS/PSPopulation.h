#ifndef EmiR_PSPopulation_h
#define EmiR_PSPopulation_h

#include "PSParticle.h"
#include "PSConfig.h"
#include "../Base/Population.h"

class PSPopulation : public Population {
public:

  PSPopulation(Function);

  void init();

  void setConfig(const PSConfig&);

  /// Sort the particles according to the best cost
  void sort();

  /// Return the number of particles in the PSPopulation
  size_t size() const;

  /// Access the specified solution
  PSParticle &operator[](size_t t) { return m_particles[t]; };

  /// Return the position of all particles
  std::vector<std::vector<double> > getPopulationPosition();

  void evaluate();

  void evaluate(PSParticle&);

  PSParticle getBestSolution() {return m_best_solution;}

  void setVelocity();

  void moveParticles();

private:
  PSConfig                m_config;
  std::vector<PSParticle> m_particles;
  PSParticle              m_best_solution;
};

#endif
