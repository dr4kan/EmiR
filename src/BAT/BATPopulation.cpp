#include "BATPopulation.h"

BATPopulation::BATPopulation(Function func) : Population(func) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void BATPopulation::init() {
  size_t pop_size = m_config.getPopulationSize();
  size_t d = m_search_space.getNumberOfParameters();
  m_loudness = m_config.getInitialLoudness();
  m_pulse_rate = m_config.getInitialPulseRate() * (1 - exp(-m_config.getGamma()));
  m_bats.resize(pop_size, Bat(d));

  std::uniform_real_distribution<double> u_freq(m_config.getMinFrequency(), m_config.getMaxFrequency());

  // Generate randomly frequency and position
  // initial velocity is set to zero in the constructor of
  // the Bat class
  for (size_t i = 0; i < m_bats.size(); ++i) {
    m_bats[i].setFrequency(u_freq(m_mt));
    m_bats[i].setPosition(m_search_space.getRandom());
  };

};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void BATPopulation::setConfig(const BATConfig& t_config) {
  m_config = t_config;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


size_t BATPopulation::size() const {
  return m_bats.size();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void BATPopulation::sort() {
  std::sort(m_bats.begin(), m_bats.end());
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double> > BATPopulation::getPopulationPosition() {
  std::vector<std::vector<double> > positions(m_bats.size());
  for (size_t i = 0; i < m_bats.size(); ++i) positions[i] = m_bats[i].getPosition();
  return positions;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void BATPopulation::updateLoudnessAndPulse(size_t t) {
  m_loudness = m_config.getAlpha() * m_loudness;
  m_pulse_rate = m_config.getInitialPulseRate() * (1 - exp(-m_config.getGamma() * (t+1)));
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void BATPopulation::moveBats() {
  size_t d = m_search_space.getNumberOfParameters();
  std::uniform_real_distribution<double> u_freq(m_config.getMinFrequency(), m_config.getMaxFrequency());
  double v = 0.;
  bool update_p = false;
  bool update_l = false;
  m_best_solution = m_bats[0];
  Bat tmp(d);

  for (size_t i = 0; i < m_bats.size(); ++i) { // loop on population

    update_p = getRand_0_1() < m_pulse_rate ? true : false;
    update_l = getRand_0_1() < m_loudness ? true : false;

    // update the frequency
    tmp.setFrequency(u_freq(m_mt));

    // update position and velocity
    for (size_t j = 0; j < d; ++j) { // loop on dimension
      v = tmp.getVelocity(j) + (tmp[j] - m_best_solution[j])*tmp.getFrequency();
      tmp.setVelocity(j, v);
      tmp[j] = tmp[j] + v;

      // improving the best solution
      if (update_p) {
        tmp[j] = m_best_solution[j] + getRand_1_1()*m_loudness;
      }

      // if the position is not in the range a new solution is generated
      if (tmp[j] < m_search_space[j].getMin() || tmp[j] > m_search_space[j].getMax()) {
        tmp[j] = m_search_space[j].getRandom();
        tmp.setVelocity(j, 0);
      }
    }

    // evaluate
    evaluate(tmp);

    // conditionally save of the new solution
    if (update_l && tmp.getCost() < m_bats[i].getCost()) {
      m_bats[i] = tmp;
    }

    // update the best solution
    if (tmp.getCost() < m_best_solution.getCost()) {
      m_best_solution = tmp;
    }

  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void BATPopulation::evaluate() {
  for (size_t i = 0; i < m_bats.size(); ++i) {
    evaluate(m_bats[i]);
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void BATPopulation::evaluate(Bat& solution) {
  NumericVector tmp_v = m_obj_func(solution.getPosition());
  double value = tmp_v[0];
  bool violated_constr = false;

  for (int i = 0; i < m_constraints.length(); ++i) {
    S4 constraint = m_constraints[i];
    Function g = constraint.slot("func");
    std::string inequality = constraint.slot("inequality");
    tmp_v = g(solution.getPosition());
    double tmp_d = tmp_v[0];

    if (inequality == "<" && tmp_d >= 0) {
      violated_constr = true;
    } else if (inequality == "<=" && tmp_d > 0) {
      violated_constr = true;
    } else if (inequality == ">=" && tmp_d < 0) {
      violated_constr = true;
    } else if (inequality == ">" && tmp_d <= 0) {
      violated_constr = true;
    }
  }

  if (violated_constr) value = std::numeric_limits<double>::max();

  solution.setCost(value);
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double BATPopulation::getPulseRate() const {
  return m_pulse_rate;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double BATPopulation::getLoudness() const {
  return m_loudness;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
