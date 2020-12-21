#ifndef EmiR_ABCConfig_h
#define EmiR_ABCConfig_h

#include "../Base/Config.h"

class ABCConfig : public Config {
public:
  /// ABCConfig default constructor
  ABCConfig();

  /// Set the fraction of onlooker bees in the colony
  void setEmployedFraction(double);

  /// Set the number of scout bees
  void setNScoutBees(size_t);

  double getEmployedFraction();

  size_t getNScoutBees();

private:
  double m_frac_employed;
  size_t m_n_scout;
};

#endif
