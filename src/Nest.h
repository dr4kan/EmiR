#ifndef EmiR_Nest_h
#define EmiR_Nest_h

#include <vector>
#include <iostream>
#include <iomanip>

class Nest {
public:
  /// Nest default constructor for a model with _n_ parameters
  Nest(size_t n);

  /// Nest copy constructor
  Nest(const Nest &);

  /// Nest constructor from a vector of Eggs
  Nest(const std::vector<double> &n_egg);

  /// Set the specified Egg
  void setEgg(size_t, double);

  /// Set the cost of the Nests
  void setCost(double);

  /// Set the value of the indicator equal to 1;
  void setIndicatorUp();

  /// Set the value of the indicator equal to 0
  void setIndicatorDown();

  /// Return the number of Eggs
  size_t size() const;

  /// Return the specified Egg
  double getEgg(size_t i) const;

  /// Return the Eggs of the Nest
  std::vector<double> getEggs() const;

  /// Referenced by Evaluate::computeCostFit()
  double getIndicator() const;

  /// Return the cost of the Nest
  double getCost() const;

  /// Access the specified Egg
  double &operator[](size_t t) { return m_eggs[t]; };

  friend std::ostream &operator<<(std::ostream &os, Nest &rhs) {
    os << "CS Nest [";
    for (size_t i = 0; i < rhs.size(); ++i) {
      os << rhs[i];
      if (i < rhs.size() - 1) os << ", ";
    }
    os << "] - cost: " << rhs.getCost() << "\n";
    return os;
  };

  friend bool operator<(const Nest &l, const Nest &r) { return l.m_cost < r.m_cost; }

private:
  std::vector<double> m_eggs;     /**< Vector storing the Eggs of the Nest*/
  double              m_cost;      /**< Cost of the Nest*/
  int                 m_indicator; /**< When 0 the cost needs to be revaluated */
};

#endif
