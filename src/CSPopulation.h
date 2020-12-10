#ifndef EmiR_CSPopulation_h
#define EmiR_CSPopulation_h

#include "Nest.h"
#include "CSConfig.h"
#include "ParametersRange.h"
#include <random>
#include <functional>
#include <algorithm>

class CSPopulation {
public:
  /// CSPopulation default constructor assigning the configuration Config.
  /// The population is initialized with random starting eggs
  CSPopulation(const CSConfig&, const ParametersRange&);

  /// Return the number of chromosomes in the population
  size_t size() const;

  /// Sort the particles according to the best cost
  void sort();

  /// Start the mutation process
  void mutation();

  /// Start the search of a new nest
  void newNest();

  /// Return the specified egg of the population
  const Nest &getNest(size_t i) const;

  /// Compute the cost for the population using the provided cost function
  void ComputeCost(std::function<double (double*)>);

  Nest &operator[](size_t i) { return m_nest[i]; };

  /// Show on video the sequence of eggs for the best nest
  friend std::ostream &operator<<(std::ostream &os, CSPopulation &rhs) {
    os << "CS population:\n";
    for (size_t i = 0; i < rhs.size(); ++i) {
      os << "  " << rhs[i];
    };
    os << "\n";
    return os;
  };

private:
  /// Population initialization with random starting eggs
  void init();

  CSConfig          m_config; /**< Configuration used in the population */
  std::mt19937      m_mt;
  ParametersRange   m_par_range;
  std::vector<Nest> m_nest; /**< Vector of nests that compose the population */
};

#endif
