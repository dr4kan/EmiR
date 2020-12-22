#ifndef EmiR_Particle_h
#define EmiR_Particle_h

#include "../Base/Individual.h"

class Particle : public Individual {
public:
  /// Empty constructor
  Particle();

  /// Bat default constructor
  Particle(int n);

  void setCharge(int);

  void setVelocity(size_t, double);

  int getCharge();

  double& getVelocity(size_t);

private:
  std::vector<double> m_velocity;
  int m_charge;
};

#endif
