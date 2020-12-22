#ifndef EmiR_SAParticle_h
#define EmiR_SAParticle_h

#include "../Base/Individual.h"

class SAParticle : public Individual {
public:
  /// Empty constructor
  SAParticle();

  /// Bat default constructor
  SAParticle(int n);

  void setVelocity(size_t, double);

  double getVelocity(size_t);

private:
  std::vector<double> m_velocity;
};

#endif
