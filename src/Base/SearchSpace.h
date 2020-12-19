#ifndef EmiR_SearchSpace_h
#define EmiR_SearchSpace_h

#include "Parameter.h"
#include <vector>

class SearchSpace {
public:
   /// Empty constructor
   SearchSpace();

   /// SearchSpace constructor
   SearchSpace(int n);

   /// Set a parameter
   void setParameter(size_t t, const std::string& t_name, double t_min, double t_max);

   /// Return the number of parameters
   size_t getNumberOfParameters() const;

   /// Return a random point in the search space
   std::vector<double> getRandom();

   /// Access the specified parameter
   Parameter &operator[](size_t t) { return m_par[t]; };

private:
   std::vector<Parameter> m_par;
};

#endif
