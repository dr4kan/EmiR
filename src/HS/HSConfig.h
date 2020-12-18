#ifndef EmiR_HSConfig_h
#define EmiR_HSConfig_h

#include "../Base/Config.h"

class HSConfig : public Config {
public:
  /// HSConfig default constructor
  HSConfig();

  void setHmcr(double);

  void setPar(double);

  void setBw(double);

  double getHmcr() const;

  double getPar() const;

  double getBw() const;

private:
  double m_hmcr;            /**< Harmony memory considering rate */
  double m_par;             /**< Pitch adjusting rate */
  double m_bw;              /**< Distance bandwidth */
};

#endif
