#ifndef EmiR_GAConfig_h
#define EmiR_GAConfig_h

#include "Utility.h"
#include <iomanip>
#include <vector>
#include <iostream>

class GAConfig {
public:
  /// Default empty constructor
  GAConfig();

  /// Set the maximum number of iterations
  void setNMaxIterations(int);

  /// Set the maximum number of consecutive iterations with approximately the same cost
  void setNMaxIterationsAtSameCost(int);

  /// Return the maximum number of iterations
  int getNMaxIterations() const;

  /// Return the maximum number of consecutive iterations with the same cost
  int getNMaxIterationsSameCost() const;

  /// Set the number of chromosomes in the population
  void setPopulationSize(int);

  /// Set the mutation rate
  void setMutationRate(double);

  /// Set the selection rate
  void setKeepFraction(double);

  /// Set the values for m_keep and m_prob
  void setConfigCrossover();

  /// Return the number of chromosomes in the population
  int getPopulationSize() const;

  /// Return the mutation rate
  double getMutationRate() const;

  /// Return the selection rate
  double getKeepFraction() const;

  /// Return m_keep
  int getKeep() const;

  /// Return m_prob
  double getProb(int) const;

  friend std::ostream &operator<<(std::ostream &os, GAConfig &rhs) {
    os << " CONFIGURATION: " << "+" << std::string(24, '-') << "+" << std::string(11, '-') << "+" << "\n";
    os << std::string(16, ' ') << "| " << Utility::centerAlign("OPTION", 22) << " | " << Utility::centerAlign("VALUE", 10) << "|\n";
    os << std::string(16, ' ') << "+" << std::string(24, '-') << "+" << std::string(11, '-') << "+" << "\n";
    os << std::string(16, ' ') << "| " << Utility::rightAlign("max number iterations", 22) << " | " << Utility::leftAlign(std::to_string(rhs.m_nmax_iter), 10) << "|" << "\n";
    os << std::string(16, ' ') << "| " << Utility::rightAlign("max num. it. same cost", 22) << " | " << Utility::leftAlign(std::to_string(rhs.m_nmax_iter_scost), 10) << "|" << "\n";
    os << std::string(16, ' ') << "| " << Utility::rightAlign("population size", 22) << " | " << std::setw(10) << std::left << rhs.m_population_size << "|" << "\n";
    os << std::string(16, ' ') << "| " << Utility::rightAlign("keep fraction", 22) << " | " << std::setw(10) << std::left << rhs.m_keep_fraction << "|" << "\n";
    os << std::string(16, ' ') << "| " << Utility::rightAlign("mutation rate", 22) << " | " << std::setw(10) << std::left << rhs.m_mutation_rate << "|" << "\n";
    os << std::string(16, ' ') << "+" << std::string(24, '-') << "+" << std::string(11, '-') << "+" << "\n";
    return os;
  };

private:
  int                 m_nmax_iter;       /**< Maximum number of iterations */
  int                 m_nmax_iter_scost; /**< Maximum number of consecutive iterations with approximately the same cost */
  int                 m_population_size; /**< Number of chromosomes in the population */
  double              m_keep_fraction;   /**< Selection rate */
  double              m_mutation_rate;   /**< Mutation rate */

  int                 m_keep;            /**< Number of chromosomes that survives to selection */
  std::vector<double> m_prob;            /**< Vector of probabilities used in the Roulette Wheel selection */
};

#endif
