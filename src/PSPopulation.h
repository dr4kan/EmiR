#ifndef EmiR_PSPopulation_h
#define EmiR_PSPopulation_h

#include "PSConfig.h"
#include "Particle.h"
#include "ParametersRange.h"
#include <random>
#include <functional>
#include <algorithm>

class PSPopulation {
public:
  /// PSPopulation default constructor assigning the configuration Config.
  /// The population is initialized with random starting positions and velocities
  PSPopulation(const PSConfig&, const ParametersRange&);

  /// Sort the particles according to the best cost
  void sort();

  /// Move all the particles into a new position
  void moveParticles();

  /// Return the number of particles in the PSPopulation
  size_t size() const;

  /// Compute the cost for the population using the provided cost function
  void ComputeCost(std::function<double (double*)>);

  /// Access the specified particle
  Particle &operator[](size_t t) { return m_particles[t]; };

  friend std::ostream &operator<<(std::ostream &t_os, PSPopulation &t_rhs) {
    t_os << "PS population:\n";
    for (size_t i = 0; i < t_rhs.size(); ++i) {
      t_os << "  " << t_rhs[i];
    };
    t_os << "\n";
    return t_os;
  };

  /// Return the position of all particles
  std::vector<std::vector<double>> getPopulationPosition();

private:
  /// Set the velocity for each particle in the population
  void setVelocity();

  PSConfig              m_config;   /**< Configuration */
  std::mt19937          m_mt;
  ParametersRange       m_par_range;
  std::vector<Particle> m_particles; /**< Particles in the population */
};

#endif
