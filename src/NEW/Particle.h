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

  double getVelocity(size_t);

  Particle& operator=(const Particle& rhs) {
    if (this != &rhs) {
      m_position = rhs.m_position;
      m_cost     = rhs.m_cost;
      m_velocity = rhs.m_velocity;
      m_charge   = rhs.m_charge;
    }
    return *this;
  };

private:
  std::vector<double> m_velocity;
  int m_charge;
};

#endif
