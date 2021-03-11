#include "GSAPopulation.h"
#include <limits>

GSAPopulation::GSAPopulation(Function func) : Population(func) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GSAPopulation::init() {
  size_t pop_size = m_config.getPopulationSize();
  size_t d = m_search_space.getNumberOfParameters();
  double vmax = m_config.getVmaxParameter();
  m_planets.resize(pop_size, GSAPlanets(d));

  for (size_t i = 0; i < pop_size; ++i) {
    m_planets[i].setPosition(m_search_space.getRandom());
    for (size_t j = 0; j < d; ++j) {
      double delta = m_search_space[j].getWidth();
      std::uniform_real_distribution<double> uni(- delta * vmax, + delta * vmax);
      m_planets[i].setVelocity(j, uni(m_mt));
    };
  };
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GSAPopulation::setConfig(const GSAConfig& t_config) {
  m_config = t_config;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void GSAPopulation::firstSort() {
  std::sort(m_planets.begin(), m_planets.end());
  m_best_solution = m_planets[0];
};

void GSAPopulation::sort() {
  std::sort(m_planets.begin(), m_planets.end());

  // The best solution is not conserved along time
  if (m_best_solution.getCost() > m_planets[0].getCost()) {
    m_best_solution = m_planets[0];
  };
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


size_t GSAPopulation::size() const {
  return m_planets.size();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GSAPopulation::evaluate() {
  for (size_t i = 0; i < m_planets.size(); ++i) {
    evaluate(m_planets[i]);
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GSAPopulation::evaluate(Individual& solution) {
  double value = evaluateCost(solution.getPosition());
  solution.setCost(value);
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double>> GSAPopulation::getPopulationPosition() {
  std::vector<std::vector<double>> positions(m_planets.size());
  for (size_t i = 0; i < m_planets.size(); ++i) positions[i] = m_planets[i].getPosition();
  return positions;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GSAPopulation::setMass()
{
  double              sum_mass = 0.;
  std::vector<double> mass;
  double size = m_planets.size();
  double delta_mass = m_planets[size - 1].getCost() - m_planets[0].getCost();

  for (size_t i = 0; i < size ; ++i) {
    mass.push_back((m_planets[size - 1].getCost() - m_planets[i].getCost())/delta_mass);
    sum_mass += mass[i];
  };
  for (size_t j = 0; j < size; ++j) {
    m_planets[j].setMass(mass[j] / sum_mass);
  };
};

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void GSAPopulation::setVelocity(size_t iter)
{

  double grav    = m_config.getGrav() * (m_config.getNMaxIterations() - iter) / (double)m_config.getNMaxIterations();
  double control = m_planets.size() * (m_config.getNMaxIterations() - iter) / (double)m_config.getNMaxIterations();

  double vmax = m_config.getVmaxParameter();
  std::uniform_real_distribution<double> uni(0, 1);

  double accel;

  double epsilon = 0.001; //only used to avoid /0

  /// Compute distances between planets
  std::vector<std::vector<double>> distance;
  distance.resize(m_planets.size(), std::vector<double>(m_planets.size(), 0.));
  for (size_t i = 0; i < m_planets.size(); i++) {
    for (size_t j = 0; j < m_planets.size(); j++) {
      distance[i][j] = 0.;
      if (i < j){
        for (size_t v = 0; v < m_planets[0].getDimension(); v++) {
          distance[i][j] += pow(m_planets[j][v] - m_planets[i][v],2);
        };
        distance[i][j] = pow(distance[i][j],0.5);
      };
      if (i > j) {
        distance [i][j] = distance [j][i];
      };
    };
  };

  /// Compute the resulting acceleration of the i-planet due to the external gravitational forces
  for (size_t i = 0; i < m_planets.size(); i++) {
    for (size_t k = 0; k < m_planets[0].getDimension(); k++) {
      double ref_accel    = 0.;
      for (size_t j = 0; j < m_planets.size(); j++) {

        accel = grav * m_planets[j].getMass() / (distance[i][j] + epsilon) * (m_planets[j][k] - m_planets[i][k]);

        if (j < control) {
          ref_accel += uni(m_mt) * accel;
        };
      };
      /// Compute the velocity taking into account the previous velocity and the forces applied
      /// TODO: vmax in function of the range
      double vel = m_planets[i].getVelocity(k) * uni(m_mt) + ref_accel;
      if (fabs(vel) < vmax) {
        m_planets[i].setVelocity(k, vel);
      } else {
        if (vel > vmax) {
          m_planets[i].setVelocity(k, vmax);
        } else {
          m_planets[i].setVelocity(k, -vmax);
        };
      };
    };
  };
};

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void GSAPopulation::movePlanets(size_t iter)
{
  // Change the mass of planets
  setMass();
  // Change the velocity of planets
  setVelocity(iter);

  // TODO: Implement with reflection or other mechanisms of control to the border
  for (size_t j = 0; j < m_planets[0].getDimension(); ++j) {
    for (size_t i = 0; i < m_planets.size(); ++i) {
      double par_min =  m_search_space[j].getMin();
      double par_max = m_search_space[j].getMax();
      double step = m_planets[i][j] + m_planets[i].getVelocity(j);
      if (step >= par_max) {
        m_planets[i][j] = par_max;
      } else if (step <= par_min) {
        m_planets[i][j] = par_min;
      } else
      m_planets[i][j]= step;
    };
  };

  evaluate();

  sort();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
