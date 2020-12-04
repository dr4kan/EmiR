#ifndef EmiR_GAPopulation_h
#define EmiR_GAPopulation_h

#include "Chromosome.h"
#include "GAConfig.h"
#include "ParametersRange.h"
#include <random>

class GAPopulation {
public:

  /// GAPopulation constructor from a configuration of and a range on the parameters
  GAPopulation(GAConfig*, const ParametersRange&);

  /// Return the number of chromosomes in the population
  size_t size() const;

  /// Sort chromosomes according to their cost
  void sort();

  /// Start the mutation process
  void mutation();

  /// Start the crossover process
  void crossover();

  /// Return the specified chromosome of the population
  const Chromosome& getChromosome(size_t) const;

  /// Compute the cost for the population using the provided cost function
  void ComputeCost(std::function<double (double*)>);

  /// Access the specified chromosome
  Chromosome &operator[](size_t t) { return m_chrom[t]; };

  /// Show on video the sequence of genes for the best chromosome
  friend std::ostream &operator<<(std::ostream &os, GAPopulation &rhs) {
    os << "GA population:\n";
    for (size_t i = 0; i < rhs.size(); ++i) {
      os << "  " << rhs[i];
    };
    os << "\n";
    return os;
  };

private:
  /// Population initialization with random starting genes
  void init();

  GAConfig               *m_config;  /**< Configuration used in the population */
  std::mt19937            m_mt;
  ParametersRange         m_par_range;
  std::vector<Chromosome> m_chrom;    /**< Vector of chromosomes that compose the population */
};

#endif
