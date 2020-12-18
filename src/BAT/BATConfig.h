#ifndef EmiR_BATConfig_h
#define EmiR_BATConfig_h

#include <vector>
#include <iostream>

class BATConfig {
public:
  /// BATConfig default constructor
  BATConfig();

  /// Set the maximum number of iterations
  void setNMaxIterations(size_t);

  /// Set the maximum number of consecutive iterations with approximately the same cost
  void setNMaxIterationsAtSameCost(size_t);

  /// Set the number of particles in the population
  void setPopulationSize(size_t);

  void setInitialLoudness(double);

  void setAlpha(double);

  void setInitialPulseRate(double);

  void setGamma(double);

  void setMinFrequency(double);

  void setMaxFrequency(double);

  /// Return the maximum number of iterations
  size_t getNMaxIterations() const;

  /// Return the maximum number of consecutive iterations with the same cost
  size_t getNMaxIterationsSameCost() const;

  /// Return the number of particles in the population
  size_t getNumberOfParticles() const;

  double getMaxVelocity(size_t) const;

  double getInitialLoudness() const;

  double getAlpha() const;

  double getInitialPulseRate() const;

  double getGamma() const;

  double getMinFrequency() const;

  double getMaxFrequency() const;

private:
  int                 m_nmax_iter;          /**< Maximum number of iterations */
  int                 m_nmax_iter_scost;    /**< Maximum number of consecutive iterations with approximately the same cost */
  int                 m_nparticles;         /**< Number of particles */
  double              m_initial_loudness;   /**< Initial loudness */
  double              m_alpha;              /**< Parameter in [0, 1] to control how quickly the loudness changes */
  double              m_initial_pulse_rate;
  double              m_gamma;
  double              m_fmin;  /**< Minimum frequency */
  double              m_fmax;  /**< Maximum frequency */
};

#endif
