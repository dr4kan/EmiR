#ifndef EmiR_GAConfig_h
#define EmiR_GAConfig_h

#include "../Base/Config.h"
#include <string>

class GAConfig : public Config {
public:

  /// Default empty constructor
  GAConfig();

  /// Set the mutation rate
  void setMutationRate(double);

  /// Set the selection rate
  void setKeepFraction(double);

  /// Set the values for m_keep and m_prob
  void setConfigCrossover();

  /// Return the mutation rate
  double getMutationRate() const;

  /// Return the selection rate
  double getKeepFraction() const;

  /// Return m_keep
  int getKeep() const;

  /// Return m_prob
  double getProb(int) const;

private:

  double m_keep_fraction;     /**< Selection rate */
  double m_mutation_rate;     /**< Mutation rate */

  int                 m_keep; /**< Number of chromosomes that survives to selection */
  std::vector<double> m_prob; /**< Vector of probabilities used in the Roulette Wheel selection */
  };
#endif
