#ifndef EmiR_CSConfig_h
#define EmiR_CSConfig_h

#include "../Base/Config.h"

class CSConfig : public Config {
public:
  /// CSConfig default constructor
  CSConfig();

  void setPa(double);

  void setAlpha(double);

  double getPa() const;

  double getAlpha() const;

private:
  double m_pa;     /**< Discovery rate */
  double m_alpha;  /**< Step size */
};

#endif
