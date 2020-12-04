#ifndef EmiR_Chromosome_h
#define EmiR_Chromosome_h

#include <vector>
#include <iostream>
#include <iomanip>

class Chromosome {
public:
  /// Chromosome default constructor for a model with _n_ parameters
  Chromosome(size_t n);

  /// Chromosome copy constructor
  Chromosome(const Chromosome &);

  /// Chromosome constructor from a vector of genes
  Chromosome(const std::vector<double> &n_gene);

  /// Set the specified gene
  void setGene(size_t, double);

  /// Set the cost of the chromosomes
  void setCost(double);

  /// Set the value of the indicator equal to 1;
  void setIndicatorUp();

  /// Set the value of the indicator equal to 0
  void setIndicatorDown();

  /// Return the number of genes
  size_t size() const;

  /// Return the specified gene
  double getGene(size_t i) const;

  /// Return the genes of the chromosome
  std::vector<double> getGenes() const;

  /// Referenced by Evaluate::computeCostFit()
  double getIndicator() const;

  /// Return the cost of the chromosome
  double getCost() const;

  /// Access the specified gene
  double &operator[](size_t t) { return m_genes[t]; };

  friend std::ostream &operator<<(std::ostream &os, Chromosome &rhs) {
    os << "GA chromosome [";
    for (size_t i = 0; i < rhs.size(); ++i) {
      os << rhs[i];
      if (i < rhs.size() - 1) os << ", ";
    }
    os << "] - cost: " << rhs.getCost() << "\n";
    return os;
  };

  friend bool operator<(const Chromosome &l, const Chromosome &r) { return l.m_cost < r.m_cost; }

private:
  std::vector<double> m_genes;     /**< Vector storing the genes of the chromosome*/
  double              m_cost;      /**< Cost of the chromosome*/
  int                 m_indicator; /**< When 0 the cost needs to be revaluated */
};

#endif
