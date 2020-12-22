#ifndef EmiR_SAConfig_h
#define EmiR_SAConfig_h

#include "../Base/Config.h"
#include <string>

class SAConfig : public Config {
public:
  enum AnnealingSchedule {LINEAR, GEOMETRIC};

  /// SAConfig default constructor
  SAConfig();

  /// Set the initial temperature
  void setT0(double t);

  void setAlpha(double);

  /// Set the annealing schedule
  void setAnnealingSchedule(AnnealingSchedule);
  void setAnnealingScheduleString(std::string);

  /// Return the initial temperature
  double getT0() const;

  double getAlpha() const;

  AnnealingSchedule getAnnealingSchedule() const;

private:

  double              m_T0;                 /**< Initial temperature */
  AnnealingSchedule   m_annealing_schedule; /**< Annealing schedule (default: geometric) */
  double              m_alpha;              /**< Cooling factor */
  };
#endif
