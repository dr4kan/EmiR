#ifndef EmiR_SAPopulation_h
#define EmiR_SAPopulation_h

#include "SAConfig.h"
#include "Particle.h"
#include "ParametersRange.h"
#include <random>
#include <functional>
#include <algorithm>

class SAPopulation {
public:
  /// SAPopulation default constructor assigning the configuration Config.
  /// The population is initialized with random starting positions and velocities = 0
  SAPopulation(const SAConfig&, const ParametersRange&);

  /// Sort the particles according to the best cost
  void sort();

  /// Move all the particles into a new position and compute the cost for each particles
  /// using the provided cost function
  void moveParticles(std::function<double (double*)>, int);

  Particle createGuess(size_t);

  /// Return the number of particles in the SAPopulation
  size_t size() const;

  /// Access the specified particle
  Particle &operator[](size_t t) { return m_particles[t]; };

  friend std::ostream &operator<<(std::ostream &t_os, SAPopulation &t_rhs) {
    t_os << "SA population:\n";
    for (size_t i = 0; i < t_rhs.size(); ++i) {
      t_os << "  " << t_rhs[i];
    };
    t_os << "\n";
    return t_os;
  };

  /// Set the velocity for each particle in the population
  void setVelocity();

  /// Return the position of all particles
  std::vector<std::vector<double>> getPopulationPosition();

private:

  SAConfig              m_config;   /**< Configuration */
  std::mt19937          m_mt;
  ParametersRange       m_par_range;
  std::vector<Particle> m_particles; /**< Particles in the population */
};

#endif
