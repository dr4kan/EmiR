#ifndef EmiR_PSConfig_h
#define EmiR_PSConfig_h

#include "Utility.h"
#include <iomanip>
#include <vector>
#include <iostream>

class PSConfig {
public:
  /// PSConfig default constructor
  PSConfig();

  /// Set the maximum number of iterations
  void setNMaxIterations(int);

  /// Set the maximum number of consecutive iterations with approximately the same cost
  void setNMaxIterationsAtSameCost(int);

  /// Return the maximum number of iterations
  int getNMaxIterations() const;

  /// Return the maximum number of consecutive iterations with the same cost
  int getNMaxIterationsSameCost() const;

  /// Set the number of particles in the population
  void setNumberOfParticles(int);

  /// Set the cognitive learning factor, by deafult = 2.0
  void setCognitiveParameter(double);

  /// Set the social learning factor, by deafult = 2.0
  void setSocialParameter(double);

  /// Set the inertia factor, by default 0.4
  void setInertia(double);

  /// Set the maximum distance of movement-per-iteration allowed
  void setVMaxParameter(double);

  /// Set the penalty parameter for constrained optimization
  void setPenaltyParameter(double);

  /// Return the number of particles in the population
  int getNumberOfParticles() const;

  /// Return the cognitive learning factor
  double getCognitiveParameter() const;

  /// Return the social learning factor
  double getSocialParameter() const;

  /// Return the intertia factor
  double getInertia() const;

  /// Return the maximum distance of movement-per-iteration allowed
  double getVMaxParameter() const;

  /// the penalty parameter for constrained optimization
  double getPenaltyParameter() const;

  friend std::ostream &operator<<(std::ostream &os, PSConfig &rhs) {
    os << " CONFIGURATION: " << "+" << std::string(24, '-') << "+" << std::string(11, '-') << "+" << "\n";
    os << std::string(16, ' ') << "| " << Utility::centerAlign("OPTION", 22) << " | " << Utility::centerAlign("VALUE", 10) << "|\n";
    os << std::string(16, ' ') << "+" << std::string(24, '-') << "+" << std::string(11, '-') << "+" << "\n";
    os << std::string(16, ' ') << "| " << Utility::rightAlign("max number iterations", 22) << " | " << Utility::leftAlign(std::to_string(rhs.m_nmax_iter), 10) << "|" << "\n";
    os << std::string(16, ' ') << "| " << Utility::rightAlign("max num. it. same cost", 22) << " | " << Utility::leftAlign(std::to_string(rhs.m_nmax_iter_scost), 10) << "|" << "\n";
    os << std::string(16, ' ') << "| " << Utility::rightAlign("population size", 22) << " | " << std::setw(10) << std::left << rhs.m_nparticles << "|" << "\n";
    os << std::string(16, ' ') << "| " << Utility::rightAlign("cognitive learning", 22) << " | " << std::setw(10) << std::left << rhs.m_cognitive << "|" << "\n";
    os << std::string(16, ' ') << "| " << Utility::rightAlign("social learning", 22) << " | " << std::setw(10) << std::left << rhs.m_social << "|" << "\n";
    os << std::string(16, ' ') << "| " << Utility::rightAlign("inertia", 22) << " | " << std::setw(10) << std::left << rhs.m_inertia << "|" << "\n";
    os << std::string(16, ' ') << "| " << Utility::rightAlign("max velocity", 22) << " | " << std::setw(10) << std::left << rhs.m_vmax << "|" << "\n";
    os << std::string(16, ' ') << "+" << std::string(24, '-') << "+" << std::string(11, '-') << "+" << "\n";
    return os;
  };

private:
  int    m_nmax_iter;        /**< Maximum number of iterations */
  int    m_nmax_iter_scost;  /**< Maximum number of consecutive iterations with approximately the same cost */
  int    m_nparticles; /**< Number of particles */
  double m_cognitive;  /**< Cognitive learning factor */
  double m_social;     /**< Social learning factor */
  double m_inertia;    /**< Inertia factor*/
  double m_vmax;       /**< Maximum distance of movement-per-iteration */
  double m_penalty_parameter; /**< Penalty parameter in constrained optimization */
};
#endif
