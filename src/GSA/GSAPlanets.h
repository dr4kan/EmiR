#ifndef EmiR_GSAPlanets_h
#define EmiR_GSAPlanets_h

#include "../Base/Individual.h"

class GSAPlanets : public Individual {
public:
  /// Empty constructor
  GSAPlanets();

  /// Planet default constructor
  GSAPlanets(int n);

  void setVelocity(size_t, double);

  void setMass(double);

  double getVelocity(size_t);

  double getMass();

private:
  std::vector<double> m_velocity; /**<Vector storing the velocity components*/
  double              m_mass;     /**<Planet's best cost found*/
};

#endif
