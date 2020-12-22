#ifndef EmiR_SAPopulation_h
#define EmiR_SAPopulation_h

#include "SAParticle.h"
#include "SAConfig.h"
#include "../Base/Population.h"

class SAPopulation : public Population {
public:

  SAPopulation(Function);

  void init();

  void setConfig(const SAConfig&);

  /// Sort the particles according to the best cost
  void sort();

  /// Return the number of particles in the BATPopulation
  size_t size() const;

  /// Access the specified solution
  Individual &operator[](size_t t) { return m_particles[t]; };

  /// Return the position of all particles
  std::vector<std::vector<double>> getPopulationPosition();

  void evaluate();

  void evaluate(Individual&);

  SAParticle getBestSolution() {return m_best_solution;}

  /// Update the temperature
  void updateTemperature(size_t);

  void randomWalk();

private:
  SAConfig                m_config;
  std::vector<SAParticle> m_particles;
  std::vector<double>     m_step_sizes;
  SAParticle              m_best_solution;
  double                  m_temperature; /**< Annealing temperature */
  double                  m_beta;        /**< Cooling rate for linear schedule */
};

#endif
