#include "CSPopulation.h"

CSPopulation::CSPopulation(const CSConfig& t_config, const ParametersRange& t_par_range) : m_config(t_config), m_mt(std::random_device()()), m_par_range(t_par_range) {
  m_nest.resize(m_config.getPopulationSize(), m_par_range.getNumberOfParameters());
  init();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void CSPopulation::init() {
  for (size_t i = 0; i < m_nest.size(); ++i) {
    for (size_t j = 0; j < m_par_range.getNumberOfParameters(); ++j) {
      std::uniform_real_distribution<double> uni(m_par_range.getParameterMin(j), m_par_range.getParameterMax(j));
      m_nest[i].setEgg(j, uni(m_mt));
    };
  };
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

const Nest& CSPopulation::getNest(size_t t) const {
  return m_nest[t];
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
size_t CSPopulation::size() const{
  return m_nest.size();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void CSPopulation::sort(){
  std::sort(m_nest.begin(), m_nest.end());
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void CSPopulation::newNest(){
  double beta = 1.5;
  double sigma = 0.6966;
  std::uniform_int_distribution<int> uni(1, m_nest.size() - 1); // with elitism
  std::normal_distribution<double> norm_v{0, 1};
  std::normal_distribution<double> norm_u{0, sigma};

  int new_nest = uni(m_mt);

  //Levy step and substitute a nest with a new nest computed starting from the best solution
  for (size_t j = 0; j < m_par_range.getNumberOfParameters(); ++j) {
    double alpha = 0.1 * (m_par_range.getParameterMax(j) - m_par_range.getParameterMin(j));

    double step = alpha * norm_u(m_mt) / (pow(fabs(norm_v(m_mt)), 1 / beta));

    if (m_nest[0].getEgg(j) + step >= m_par_range.getParameterMax(j)) {
      m_nest[new_nest].setEgg(j, m_par_range.getParameterMax(j));
      m_nest[new_nest].setIndicatorDown();
    } else if (m_nest[0].getEgg(j) + step <=m_par_range.getParameterMin(j)) {
      m_nest[new_nest].setEgg(j, m_par_range.getParameterMin(j));
      m_nest[new_nest].setIndicatorDown();
    } else
    m_nest[new_nest].setEgg(j, m_nest[0].getEgg(j) + step);
    m_nest[new_nest].setIndicatorDown();
  };
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void CSPopulation::mutation(){
  std::uniform_int_distribution<int> uni(1, m_nest.size() - 1); // with elitism
  int new_nest = uni(m_mt);

  std::uniform_real_distribution<double> uni_1(0, 1); // with elitism
  double ran = uni_1(m_mt);

  if (ran < m_config.getMutationRate()){
    for (size_t j = 0; j < m_par_range.getNumberOfParameters(); ++j) {
      std::uniform_real_distribution<double> uni_2(m_par_range.getParameterMin(j), m_par_range.getParameterMax(j));
      m_nest[new_nest].setEgg(j, uni_2(m_mt));
      m_nest[new_nest].setIndicatorDown();
    };
  };
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void CSPopulation::ComputeCost(std::function<double (double*)> cost_function) {
  for (size_t i = 0; i < m_nest.size(); ++i) {
    m_nest[i].setCost(cost_function(&m_nest[i].getEggs()[0]));
    m_nest[i].setIndicatorUp();
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
