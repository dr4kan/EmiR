#ifndef EmiR_Individual_h
#define EmiR_Individual_h

#include <vector>

class Individual {
public:
  /// Empty constructor
  Individual();

  /// Individual default constructor
  Individual(int n);
  
  /// Set the cost
  void setCost(double);

  /// Set the positions
  void setPosition(const std::vector<double>&);

  /// Return the the number of dimensions of the search space
  size_t getDimension() const;

  /// Return the position
  const std::vector<double>& getPosition() const { return m_position; };

  /// Return the cost
  double getCost();

  /// Access the specified component
  double &operator[](size_t t) { return m_position[t]; };

  friend bool operator<(const Individual &l, const Individual &r) { return l.m_cost < r.m_cost; };

  Individual& operator=(const Individual& rhs) {
    if (this != &rhs) {
      m_position = rhs.m_position;
      m_cost = rhs.m_cost;
    }
    return *this;
  };

protected:

  std::vector<double> m_position;
  double              m_cost;
};

#endif
