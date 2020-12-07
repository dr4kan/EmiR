#ifndef EmiR_Constraint_h
#define EmiR_Constraint_h

#include <functional>

class Constraint {
public:
  enum Inequality {LEQ, LESS, GEQ, GREATER};

  /// Constraint default constructor
  Constraint();

private:
  std::function<double (double*)> m_func;
  Inequality                      m_inequality;
};

#endif
