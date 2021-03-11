#include "PSPopulation.h"

PSPopulation::PSPopulation(Function func) : Population(func) {};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void PSPopulation::init() {
  size_t pop_size = m_config.getPopulationSize();
  size_t d = m_search_space.getNumberOfParameters();
  double vmax = m_config.getVmaxParameter();
  m_particles.resize(pop_size, PSParticle(d));

  for (size_t j = 0; j < d; ++j) {
    double delta = m_search_space[j].getWidth();
    std::uniform_real_distribution<double> uni(- delta * vmax, + delta * vmax);
    for (size_t i = 0; i < pop_size; ++i) {
        size_t position_random = m_search_space[j].getRandom();
        m_particles[i][j] = position_random;
        m_particles[i].setVelocity(j, uni(m_mt));
     };
  };
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void PSPopulation::setConfig(const PSConfig& t_config) {
  m_config = t_config;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void PSPopulation::sort() {
  std::sort(m_particles.begin(), m_particles.end());

  m_best_solution = m_particles[0];

};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


size_t PSPopulation::size() const {
  return m_particles.size();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void PSPopulation::evaluate() {
  for (size_t i = 0; i < m_particles.size(); ++i) {
    evaluate(m_particles[i]);
  }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void PSPopulation::evaluate(PSParticle& solution) {
  double value = evaluateCost(solution.getPosition());
  solution.setCost(value);
  solution.setBest();
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double>> PSPopulation::getPopulationPosition() {
  std::vector<std::vector<double>> positions(m_particles.size());
  for (size_t i = 0; i < m_particles.size(); ++i) positions[i] = m_particles[i].getPosition();
  return positions;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void PSPopulation::setVelocity()
{
   std::uniform_real_distribution<double> uni(0, 1);
   double cognitive_par = m_config.getCognitiveParameter();
   double social_par = m_config.getSocialParameter();
   double inertia_par = m_config.getInertiaParameter();
  for (size_t j = 0; j < m_particles[0].getDimension(); ++j) {
        // Scale the maximum step with the width of the search space
        double vmax = m_config.getVmaxParameter() * m_search_space[j].getWidth();

        for (size_t i = 0; i < m_particles.size(); ++i) {
          // Compute the step and assign if it satisfies the constraint on the maximum velocity
         double cognitive = cognitive_par * uni(m_mt) *
                            (m_particles[i].getBestPositionParticle(j) - m_particles[i][j]);
         double social = social_par * uni(m_mt) *
                         (m_particles[0].getBestPositionParticle(j) - m_particles[i][j]);
         double vel = (m_particles[i].getVelocity(j) * inertia_par + cognitive + social);
         // TODO: Vmax in function of parameter
         if (fabs(vel) < vmax) {
            m_particles[i].setVelocity(j, vel);
         } else {
            if (vel > vmax) {
               m_particles[i].setVelocity(j, vmax);
            } else {
               m_particles[i].setVelocity(j, -vmax);
            }
         };
      };
   };
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void PSPopulation::moveParticles() {
  // Change the velocity of the particles
  setVelocity();

  // TODO: Implement with reflection or other mechanisms of control to the border
  for (size_t j = 0; j < m_particles[0].getDimension(); ++j) {
    for (size_t i = 0; i < m_particles.size(); ++i) {
        double par_min =  m_search_space[j].getMin();
        double par_max = m_search_space[j].getMax();
        double step = m_particles[i][j] + m_particles[i].getVelocity(j);
        if (step >= par_max) {
           m_particles[i].setPosition(j, par_max);
        } else if (step <= par_min) {
           m_particles[i].setPosition(j, par_min);
        } else
           m_particles[i].setPosition(j, step);
     }
  }

  //Evaluate the population in the new positions
  evaluate();

  //Sort the particles in the new population
  sort();

};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
