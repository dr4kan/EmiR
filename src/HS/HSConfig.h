#ifndef EmiR_HSConfig_h
#define EmiR_HSConfig_h

#include <vector>
#include <iostream>

class HSConfig {
public:
  /// HSConfig default constructor
  HSConfig();

  /// Set the maximum number of iterations
  void setNMaxIterations(size_t);

  /// Set the maximum number of consecutive iterations with approximately the same cost
  void setNMaxIterationsAtSameCost(size_t);

  /// Set the number of particles in the population
  void setPopulationSize(size_t);

  void setHmcr(double);

  void setPar(double);

  void setBw(double);

  /// Return the maximum number of iterations
  size_t getNMaxIterations() const;

  /// Return the maximum number of consecutive iterations with the same cost
  size_t getNMaxIterationsSameCost() const;

  /// Return the number of particles in the population
  size_t getPopulationSize() const;

  double getHmcr() const;

  double getPar() const;

  double getBw() const;

private:
  int    m_nmax_iter;       /**< Maximum number of iterations */
  int    m_nmax_iter_scost; /**< Maximum number of consecutive iterations with approximately the same cost */
  int    m_nparticles;      /**< Number of particles */
  double m_hmcr;            /**< Harmony memory considering rate */
  double m_par;             /**< Pitch adjusting rate */
  double m_bw;              /**< Distance bandwidth */
};

#endif
