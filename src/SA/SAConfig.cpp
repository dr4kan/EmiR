#include "SAConfig.h"

SAConfig::SAConfig() {
  m_T0 = 50;
  m_annealing_schedule = LINEAR;
  m_alpha = 0.9;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SAConfig::setT0(double t) {
  m_T0 = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SAConfig::setAnnealingSchedule(AnnealingSchedule t) {
  m_annealing_schedule = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SAConfig::setAlpha(double t) {
  m_alpha = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SAConfig::setAnnealingScheduleString(std::string t) {
  if (t == "linear") m_annealing_schedule = LINEAR;
  if (t == "geometric") m_annealing_schedule = GEOMETRIC;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double SAConfig::getT0() const {
  return m_T0;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double SAConfig::getAlpha() const {
  return m_alpha;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


SAConfig::AnnealingSchedule SAConfig::getAnnealingSchedule() const {
  return m_annealing_schedule;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
