#ifndef EmiR_CSConfig_h
#define EmiR_CSConfig_h

#include "Utility.h"
#include <iomanip>
#include <vector>
#include <iostream>

class CSConfig {
public:

  /// Default empty constructor
  CSConfig();

  /// Set the maximum number of iterations
  void setNMaxIterations(int);

  /// Set the maximum number of consecutive iterations with approximately the same cost
  void setNMaxIterationsAtSameCost(int);

  /// Return the maximum number of iterations
  int getNMaxIterations() const;

  /// Return the maximum number of consecutive iterations with the same cost
  int getNMaxIterationsSameCost() const;

  /// Set the number of nests in the population
  void setPopulationSize(int);

  /// Set the mutation rate
  void setMutationRate(double);

  /// Return the number of nests in the population
  int getPopulationSize() const;

  /// Return the mutation rate
  double getMutationRate() const;

  friend std::ostream &operator<<(std::ostream &os, CSConfig &rhs) {
    os << " CONFIGURATION: " << "+" << std::string(24, '-') << "+" << std::string(11, '-') << "+" << "\n";
    os << std::string(16, ' ') << "| " << Utility::centerAlign("OPTION", 22) << " | " << Utility::centerAlign("VALUE", 10) << "|\n";
    std::cout << std::string(16, ' ') << "+" << std::string(24, '-') << "+" << std::string(11, '-') << "+" << "\n";
    os << std::string(16, ' ') << "| " << Utility::rightAlign("max number iterations", 22) << " | " << Utility::leftAlign(std::to_string(rhs.m_nmax_iter), 10) << "|" << "\n";;
    os << std::string(16, ' ') << "| " << Utility::rightAlign("max num. it. same cost", 22) << " | " << Utility::leftAlign(std::to_string(rhs.m_nmax_iter_scost), 10) << "|" << "\n";
    os << std::string(16, ' ') << "| " << Utility::rightAlign("population size", 22) << " | " << std::setw(10) << std::left << rhs.m_population_size << "|" << "\n";
    os << std::string(16, ' ') << "| " << Utility::rightAlign("mutation rate", 22) << " | " << std::setw(10) << std::left << rhs.m_mutation_rate << "|" << "\n";
    os << std::string(16, ' ') << "+" << std::string(24, '-') << "+" << std::string(11, '-') << "+" << "\n";
    return os;

  };

private:
  int m_nmax_iter;        /**< Maximum number of iterations */
  int m_nmax_iter_scost;  /**< Maximum number of consecutive iterations with approximately the same cost */
  int                 m_population_size;  /**< Number of chromosomes that survives to selection */
  double              m_mutation_rate; /**< Mutation rate */
};

#endif
