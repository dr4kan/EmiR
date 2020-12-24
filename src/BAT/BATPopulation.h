#ifndef EmiR_BATPopulation_h
#define EmiR_BATPopulation_h

#include "Bat.h"
#include "BATConfig.h"
#include "../Base/Population.h"

class BATPopulation : public Population {
public:

  BATPopulation(Function);

  void init();

  void setConfig(const BATConfig&);

  /// Sort the particles according to the best cost
  void sort();

  /// Return the number of particles in the BATPopulation
  size_t size() const;

  /// Access the specified particle
  Bat &operator[](size_t t) { return m_bats[t]; };

  /// Return the position of all particles
  std::vector<std::vector<double> > getPopulationPosition();

  double getPulseRate() const;

  double getLoudness() const;

  void updateLoudnessAndPulse(size_t);

  void moveBats();

  void evaluate();

  void evaluate(Bat&);

private:

  BATConfig           m_config;   /**< Configuration */
  Bat                 m_best_solution;
  std::vector<Bat>    m_bats;    /**< Bats in the population */
  double              m_loudness;
  double              m_pulse_rate;
};

#endif
