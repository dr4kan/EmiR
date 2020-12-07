#include "ConstrainedFunction.h"

ConstrainedFunction::ConstrainedFunction(const std::function<double (double*)>& func) : m_func(func) {}

void ConstrainedFunction::addConstraint(const Constraint& constraint) {
  m_constraints.push_back(constraint);
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
