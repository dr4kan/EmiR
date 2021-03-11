#ifndef EmiR_PSConfig_h
#define EmiR_PSConfig_h

#include "../Base/Config.h"
#include <string>

class PSConfig : public Config {
public:

  /// PSConfig default constructor
  PSConfig();

  /// Set the initial parameters
  void setCognitiveParameter(double t);

  void setSocialParameter(double t);

  void setVmaxParameter(double t);

  void setInertiaParameter(double t);

  /// Return the initial parameters
  double getCognitiveParameter() const;

  double getSocialParameter() const;

  double getVmaxParameter() const;

  double getInertiaParameter() const;

private:

  double              m_social;               /**< Social parameter */
  double              m_cognitive;            /**< Cognitive parameter */
  double              m_vmax;                 /**< Maximum velocity in % of the range of parameters */
  double              m_inertia;              /**< Inertia factor */
  };
#endif
