#ifndef EmiR_IHSConfig_h
#define EmiR_IHSConfig_h

#include "../Base/Config.h"

class IHSConfig : public Config {
public:
  /// IHSConfig default constructor
  IHSConfig();

  void setHmcr(double);

  void setParMin(double);

  void setParMax(double);

  void setBwMin(double);

  void setBwMax(double);

  double getHmcr() const;

  double getParMin() const;

  double getParMax() const;

  double getBwMin() const;

  double getBwMax() const;

private:
  double m_hmcr;    /**< Harmony memory considering rate */
  double m_par_min; /**< Minimum pitch adjusting rate */
  double m_par_max; /**< Maximum pitch adjusting rate */
  double m_bw_min;  /**< Minumum distance bandwidth */
  double m_bw_max;  /**< Maximum distance bandwidth */
};

#endif
