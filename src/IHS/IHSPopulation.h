#ifndef EmiR_IHSPopulation_h
#define EmiR_IHSPopulation_h

#include "../Base/Individual.h"
#include "IHSConfig.h"
#include "../Base/Population.h"

class IHSPopulation : public Population {
public:

  IHSPopulation(Function);

  void init();

  void setConfig(const IHSConfig&);

  /// Sort the particles according to the best cost
  void sort();

  /// Return the number of particles in the BATPopulation
  size_t size() const;

  /// Access the specified solution
  Individual &operator[](size_t t) { return m_harmonies[t]; };

  /// Return the position of all particles
  std::vector<std::vector<double>> getPopulationPosition();

  void updateParameters(size_t);

  void generateNewHarmony();

  void evaluate();

  void evaluate(Individual&);

private:
  IHSConfig             m_config;
  std::vector<Individual>  m_harmonies;
  double                m_current_par;
  double                m_current_bw;
};

#endif
