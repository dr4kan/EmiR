#ifndef EmiR_Particle_h
#define EmiR_Particle_h

#include "../Base/Individual.h"

class Particle : public Individual {
public:
  /// Empty constructor
  Particle();

  /// Bat default constructor
  Particle(int n);

private:
  std::vector<double> m_velocity;
  double m_charge;
};

#endif
