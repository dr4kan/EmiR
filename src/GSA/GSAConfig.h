#ifndef EmiR_GSAConfig_h
#define EmiR_GSAConfig_h

#include "../Base/Config.h"
#include <string>

class GSAConfig : public Config {
public:

  /// GSAConfig default constructor
  GSAConfig();

  /// Set the gravitational constant
  void setGrav(double);

  void setVmaxParameter(double t);

  /// Get the gravitational constant
  double getGrav() const;

  double getVmaxParameter() const;

private:
   double m_grav;              /**< Gravitaional constant */
   double m_vmax;              /**< Maximum velocity in % of the range of parameters */
};
#endif
