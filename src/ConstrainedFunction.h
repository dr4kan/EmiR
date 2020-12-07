#ifndef EmiR_ConstrainedFunction_h
#define EmiR_ConstrainedFunction_h

#include "Constraint.h"
#include <vector>

class ConstrainedFunction {
public:
  /// ConstrainedFunction default constructor
  ConstrainedFunction(const std::function<double (double*)>&);

  void addConstraint(const Constraint&);

private:
  std::function<double (double*)> m_func;
  std::vector<Constraint> m_constraints;
};

#endif
