#include "GAPopulation.h"

GAPopulation::GAPopulation(const GAConfig& t_config, const ParametersRange& t_par_range) : m_config(t_config), m_mt(std::random_device()()), m_par_range(t_par_range) {
  m_chrom.resize(m_config.getPopulationSize(), m_par_range.getNumberOfParameters());
  init();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void GAPopulation::init() {
  for (size_t i = 0; i < m_chrom.size(); ++i) {
    for (size_t j = 0; j < m_par_range.getNumberOfParameters(); ++j) {
      std::uniform_real_distribution<double> uni(m_par_range.getParameterMin(j), m_par_range.getParameterMax(j));
      m_chrom[i].setGene(j, uni(m_mt));
    };
  };
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

const Chromosome& GAPopulation::getChromosome(size_t t) const {
  return m_chrom[t];
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

size_t GAPopulation::size() const {
  return m_chrom.size();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void GAPopulation::sort() {
  std::sort(m_chrom.begin(), m_chrom.end());
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void GAPopulation::crossover() {
  // uniform crossover
  std::uniform_real_distribution<double> uni(0.0, 1.0);

  // generate offspring
  for (size_t i = 0; i < (m_chrom.size() - m_config.getKeep()); i = i + 2) {
    m_chrom[m_chrom.size() - 1 - i].setIndicatorDown();
    m_chrom[m_chrom.size() - 2 - i].setIndicatorDown();
    int    ma = 0, pa = 0;
    double ra1 = uni(m_mt);
    // mother
    for (int u = 1; u < m_config.getKeep(); u++) {
      if (ra1 > m_config.getProb(u - 1) && ra1 <= m_config.getProb(u)) ma = u;
    };
    double ra2 = uni(m_mt);
    // father
    for (int u = 1; u < m_config.getKeep(); u++) {
      if (ra2 > m_config.getProb(u - 1) && ra2 <= m_config.getProb(u)) pa = u;
    };
    for (size_t u = 0; u < m_par_range.getNumberOfParameters(); u++) {
      double beta = uni(m_mt);
      m_chrom[m_chrom.size() - 1 - i].setGene(u, m_chrom[ma].getGene(u) -
        beta * (m_chrom[ma].getGene(u) - m_chrom[pa].getGene(u)));
      m_chrom[m_chrom.size() - 2 - i].setGene(u, m_chrom[pa].getGene(u) +
        beta * (m_chrom[ma].getGene(u) - m_chrom[pa].getGene(u)));
    };
  };
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void GAPopulation::mutation() {
  // random generator engine
  int mutat = floor(m_config.getMutationRate() * m_config.getPopulationSize() * m_par_range.getNumberOfParameters());

  for (int i = 0; i < mutat; i++) {
    std::uniform_int_distribution<int> uni_1(0, m_par_range.getNumberOfParameters() - 1);
    int ra1 = uni_1(m_mt);

    std::uniform_int_distribution<int> uni_2(1, m_chrom.size() - 1); //elitism
    int ra2 = uni_2(m_mt);

    std::uniform_real_distribution<double> uni_3(m_par_range.getParameterMin(ra1),
                                                 m_par_range.getParameterMax(ra1));
    m_chrom[ra2].setGene(ra1, uni_3(m_mt));
    m_chrom[ra2].setIndicatorDown();
  };
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void GAPopulation::ComputeCost(std::function<double (double*)> cost_function) {
  for (size_t i = 0; i < m_chrom.size(); ++i) {
    m_chrom[i].setCost(cost_function(&m_chrom[i].getGenes()[0]));
    m_chrom[i].setIndicatorUp();
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
