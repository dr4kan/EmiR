#ifndef EmiR_Bat_h
#define EmiR_Bat_h

#include "../Base/Individual.h"

class Bat : public Individual {
public:
  /// Empty constructor
  Bat();

  /// Bat default constructor
  Bat(int n);

  /// Set frequency range
  void setFrequency(double);

  /// Set a velocity component
  void setVelocity(size_t, double);

  /// Return a velocity component
  double getVelocity(size_t t);

  double getFrequency() const;

private:
  std::vector<double> m_velocity;
  double              m_freq;
};

#endif
