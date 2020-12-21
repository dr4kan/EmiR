#ifndef EmiR_CSPopulation_h
#define EmiR_CSPopulation_h

#include "Nest.h"
#include "CSConfig.h"
#include "../Base/Population.h"

class CSPopulation : public Population {
public:

  CSPopulation(Function);

  void init();

  void setConfig(const CSConfig&);

  /// Sort the particles according to the best cost
  void sort();

  /// Return the number of particles in the BATPopulation
  size_t size() const;

  /// Access the specified solution
  Nest &operator[](size_t t) { return m_nests[t]; };

  /// Return the position of all particles
  std::vector<std::vector<double>> getPopulationPosition();

  void evaluate();

  void evaluate(Nest&);

  //// begin of custom methods

  void generateCuckooEgg();

private:
  /// Choose a random nest excluding the one with the best cost
  Nest& chooseRndNest();

  CSConfig          m_config;
  std::vector<Nest> m_nests;

};

#endif
