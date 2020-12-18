#ifndef EmiR_Bat_h
#define EmiR_Bat_h

#include <vector>

class Bat {
public:
  /// Empty constructor
  Bat();

  /// Bat default constructor
  Bat(int n);

  /// Set a position component
  void setPosition(size_t, double);

  /// Set frequency range
  void setFrequency(double);

  /// Set a velocity component
  void setVelocity(size_t, double);

  /// Set the cost
  void setCost(double);

  /// Return the the number of dimensions of the search space
  size_t getDimension() const;

  /// Return a position component
  double getPosition(size_t t);

  /// Return the position
  const std::vector<double>& getPosition() const { return m_position; };

  /// Return a velocity component
  double getVelocity(size_t t);

  /// Return the cost
  double getCost();

  double getFrequency() const;

  friend bool operator<(const Bat &l, const Bat &r) { return l.m_cost < r.m_cost; };

private:
  std::vector<double> m_position;
  std::vector<double> m_velocity;
  double              m_cost;
  double              m_freq;
};

#endif
