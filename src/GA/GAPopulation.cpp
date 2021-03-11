#include "GAPopulation.h"

GAPopulation::GAPopulation(Function func) : Population(func) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GAPopulation::init() {
  m_config.setConfigCrossover();

  size_t pop_size = m_config.getPopulationSize();
  size_t d = m_search_space.getNumberOfParameters();
  m_chromosomes.resize(pop_size, GAChromosome(d));

  for (size_t i = 0; i < m_chromosomes.size(); ++i) { // loop on population
      m_chromosomes[i].setPosition(m_search_space.getRandom());
  };
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GAPopulation::setConfig(const GAConfig& t_config) {
  m_config = t_config;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GAPopulation::sort() {
  std::sort(m_chromosomes.begin(), m_chromosomes.end());

  m_best_solution = m_chromosomes[0];

};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


size_t GAPopulation::size() const {
  return m_chromosomes.size();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GAPopulation::evaluate() {
  for (size_t i = 0; i < m_chromosomes.size(); ++i) {
    if (m_chromosomes[i].getIndicator() == 0){
    evaluate(m_chromosomes[i]);
  }
  };
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GAPopulation::evaluate(GAChromosome& solution) {
    double value = evaluateCost(solution.getPosition());
    solution.setCost(value);
    solution.setIndicatorDown();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double>> GAPopulation::getPopulationPosition() {
  std::vector<std::vector<double>> positions(m_chromosomes.size());
  for (size_t i = 0; i < m_chromosomes.size(); ++i) positions[i] = m_chromosomes[i].getPosition();
  return positions;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GAPopulation::crossover()
{
   // uniform crossover
   std::uniform_real_distribution<double> uni(0.0, 1.0);

   // generate offspring

   double size = m_chromosomes.size();
   double ndof = m_search_space.getNumberOfParameters();
   size_t keep = m_config.getKeep();

   for (size_t i = 0; i < (size - keep); i = i + 2) {
      m_chromosomes[size - 1 - i].setIndicatorDown();
      m_chromosomes[size - 2 - i].setIndicatorDown();
      int    ma = 0, pa = 0;

      // mother
      double ra1 = uni(m_mt);
      for (int u = 1; u < (size_t)keep; u++) {
         if (ra1 > m_config.getProb(u - 1) && ra1 <= m_config.getProb(u)) ma = u;
      };

      // father
      double ra2 = uni(m_mt);
      for (int u = 1; u < (size_t)keep; u++) {
         if (ra2 > m_config.getProb(u - 1) && ra2 <= m_config.getProb(u)) pa = u;
      };
      for (size_t k = 0; k < ndof; k++) {
         double beta = uni(m_mt);
         m_chromosomes[size - 1 - i][k] = m_chromosomes[ma][k] -
                                                       beta * (m_chromosomes[ma][k] - m_chromosomes[pa][k]);
         m_chromosomes[size - 2 - i][k] = m_chromosomes[pa][k] +
                                                       beta * (m_chromosomes[ma][k] - m_chromosomes[pa][k]);
      };
   };

   evaluate();

   sort();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GAPopulation::mutation() {
   // random generator engine
  double ndof = m_search_space.getNumberOfParameters();
  double size = m_chromosomes.size();
   int mutat = floor(m_config.getMutationRate() * m_config.getPopulationSize() * ndof);

   for (int i = 0; i < mutat; i++) {
      std::uniform_int_distribution<int> uni_1(0, ndof - 1);
      int                                ra1 = uni_1(m_mt);

      std::uniform_int_distribution<int> uni_2(1, size - 1); // elitism
      int                                ra2 = uni_2(m_mt);

      m_chromosomes[ra2][ra1] = m_search_space[ra1].getRandom();
      m_chromosomes[ra2].setIndicatorDown();
   };

   evaluate();

   sort();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
