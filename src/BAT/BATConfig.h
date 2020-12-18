#ifndef EmiR_BATConfig_h
#define EmiR_BATConfig_h

#include "../Base/Config.h"

class BATConfig : public Config {
public:
  /// BATConfig default constructor
  BATConfig();

  void setInitialLoudness(double);

  void setAlpha(double);

  void setInitialPulseRate(double);

  void setGamma(double);

  void setMinFrequency(double);

  void setMaxFrequency(double);

  double getMaxVelocity(size_t) const;

  double getInitialLoudness() const;

  double getAlpha() const;

  double getInitialPulseRate() const;

  double getGamma() const;

  double getMinFrequency() const;

  double getMaxFrequency() const;

private:
  double              m_initial_loudness;   /**< Initial loudness */
  double              m_alpha;              /**< Parameter in [0, 1] to control how quickly the loudness changes */
  double              m_initial_pulse_rate;
  double              m_gamma;
  double              m_fmin;  /**< Minimum frequency */
  double              m_fmax;  /**< Maximum frequency */
};

#endif
