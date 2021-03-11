#ifndef EmiR_GAChromosome_h
#define EmiR_GAChromosome_h

#include "../Base/Individual.h"

class GAChromosome : public Individual {
public:
  /// Empty constructor
  GAChromosome();

  /// Chromosome default constructor
  GAChromosome(int n);

  /// Set the value of the indicator equal to 1;
  void setIndicatorUp();

  /// Set the value of the indicator equal to 0
  void setIndicatorDown();

  double getIndicator() const;

private:
   int  m_indicator; /**< When 0 the cost needs to be revaluated */
};

#endif
