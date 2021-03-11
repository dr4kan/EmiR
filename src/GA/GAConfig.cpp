#include "GAConfig.h"
#include <math.h>

GAConfig::GAConfig()
{
   m_mutation_rate   = 0.10;
   m_keep_fraction   = 0.40;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void GAConfig::setMutationRate(double t)
{
   m_mutation_rate = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void GAConfig::setKeepFraction(double t)
{
   m_keep_fraction = t;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void GAConfig::setConfigCrossover()
{
   m_keep   = floor(m_keep_fraction * getPopulationSize());
   double k = m_keep * (m_keep + 1) / 2;
   m_prob.push_back(m_keep / k);
   for (int i = 2; i <= m_keep; i++) {
      m_prob.push_back((m_keep - i + 1) / k + m_prob[i - 2]);
   }
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double GAConfig::getMutationRate() const
{
   return m_mutation_rate;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double GAConfig::getKeepFraction() const
{
   return m_keep_fraction;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

int GAConfig::getKeep() const
{
   return m_keep;
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

double GAConfig::getProb(int t) const
{
   return m_prob[t];
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
