#ifndef EmiR_Config_h
#define EmiR_Config_h

#include <vector>

class Config {
public:
  /// Config default constructor
  Config();

  /// Set the maximum number of iterations
  void setNMaxIterations(size_t);

  /// Set the maximum number of consecutive iterations with approximately the same cost
  void setNMaxIterationsAtSameCost(size_t);

  /// Set the number of particles in the population
  void setPopulationSize(size_t);

  /// Return the maximum number of iterations
  size_t getNMaxIterations() const;

  /// Return the maximum number of consecutive iterations with the same cost
  size_t getNMaxIterationsSameCost() const;

  /// Return the number of particles in the population
  size_t getPopulationSize() const;

protected:
  int    m_nmax_iter;       /**< Maximum number of iterations */
  int    m_nmax_iter_scost; /**< Maximum number of consecutive iterations with approximately the same cost */
  int    m_nparticles;      /**< Number of individuals in the population */

};

#endif
