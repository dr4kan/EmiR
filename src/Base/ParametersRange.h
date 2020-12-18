#ifndef EmiR_ParametersRange_h
#define EmiR_ParametersRange_h

#include "Parameter.h"
#include <vector>

class ParametersRange {
public:
   /// ParametersRange default constructor
   ParametersRange();

   /// ParametersRange constructor for a set of _n_ - parameters
   ParametersRange(int n);

   /// Set the _t_ - parameter assigning the name and the domain extreme values
   void setParameterRange(size_t t, const std::string& t_name, double t_min, double t_max);

   /// Return the number of parameters
   size_t getNumberOfParameters() const;

   /// Return the names of the specified parameter
   const std::string& getParameterName(size_t) const;

   /// Return the minimum value allowed for the _t_ - parameter
   double getParameterMin(size_t t) const;

   /// Return the maximum value allowed for the _t_ - parameter
   double getParameterMax(size_t t) const;

   double getRangeLenght(size_t) const;

   /// Access the specified parameter
   Parameter &operator[](size_t t) { return m_par[t]; };

   friend std::ostream &operator<<(std::ostream &os, ParametersRange &rhs) {
     os << "Parameters range: \n";
     for (size_t i = 0; i < rhs.getNumberOfParameters(); ++i) {
       os << rhs[i];
     };
     return os;
   };

private:
   std::vector<Parameter> m_par;
};

#endif
