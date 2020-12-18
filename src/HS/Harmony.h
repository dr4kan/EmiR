#ifndef EmiR_Harmony_h
#define EmiR_Harmony_h

#include <vector>

class Harmony {
public:
  /// Empty constructor
  Harmony();

  /// Bat default constructor
  Harmony(int n);

  /// Set a position component
  void setPosition(size_t, double);

  /// Set the cost
  void setCost(double);

  /// Return the dimension
  size_t getDimension() const;

  /// Return a position component
  double getPosition(size_t t);

  /// Return the position
  const std::vector<double>& getPosition() const;

  /// Return the cost
  double getCost();

  friend bool operator<(const Harmony &l, const Harmony &r) { return l.m_cost < r.m_cost; };

private:
  std::vector<double> m_position;
  double              m_cost;
};

#endif
