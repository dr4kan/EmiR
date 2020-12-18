#ifndef EmiR_IHSConfig_h
#define EmiR_IHSConfig_h

#include <vector>
#include <iostream>

class IHSConfig {
public:
  /// IHSConfig default constructor
  IHSConfig();

  /// Set the maximum number of iterations
  void setNMaxIterations(size_t);

  /// Set the maximum number of consecutive iterations with approximately the same cost
  void setNMaxIterationsAtSameCost(size_t);

  /// Set the number of particles in the population
  void setPopulationSize(size_t);

  void setHmcr(double);

  void setParMin(double);

  void setParMax(double);

  void setBwMin(double);

  void setBwMax(double);

  /// Return the maximum number of iterations
  size_t getNMaxIterations() const;

  /// Return the maximum number of consecutive iterations with the same cost
  size_t getNMaxIterationsSameCost() const;

  /// Return the number of particles in the population
  size_t getPopulationSize() const;

  double getHmcr() const;

  double getParMin() const;

  double getParMax() const;

  double getBwMin() const;

  double getBwMax() const;

private:
  int    m_nmax_iter;       /**< Maximum number of iterations */
  int    m_nmax_iter_scost; /**< Maximum number of consecutive iterations with approximately the same cost */
  int    m_nparticles;      /**< Number of particles */
  double m_hmcr;            /**< Harmony memory considering rate */
  double m_par_min;         /**< Minimum pitch adjusting rate */
  double m_par_max;         /**< Maximum pitch adjusting rate */
  double m_bw_min;          /**< Minumum distance bandwidth */
  double m_bw_max;          /**< Maximum distance bandwidth */
};

#endif
