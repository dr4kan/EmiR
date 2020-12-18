#ifndef EmiR_Individual_h
#define EmiR_Individual_h

#include <vector>

class Individual {
public:
  /// Empty constructor
  Individual();

  /// Individual default constructor
  Individual(int n);

  /// Set a position component
  void setPosition(size_t, double);

  /// Set the cost
  void setCost(double);

  /// Return the the number of dimensions of the search space
  size_t getDimension() const;

  /// Return a position component
  double getPosition(size_t t);

  /// Return the position
  const std::vector<double>& getPosition() const { return m_position; };

  /// Return the cost
  double getCost();

  friend bool operator<(const Individual &l, const Individual &r) { return l.m_cost < r.m_cost; };

protected:
  
  std::vector<double> m_position;
  double              m_cost;
};

#endif
