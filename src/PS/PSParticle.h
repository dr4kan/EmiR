#ifndef EmiR_PSParticle_h
#define EmiR_PSParticle_h

#include <vector>

class PSParticle {

  //NOTE: It was uncomfortable to inglobe the individual class in this case, because of the boolean used to compare particles

public:
  /// Empty constructor
  PSParticle();

  /// Particle Swarm default constructor
  PSParticle(int n);

  /// Set the cost
  void setCost(double);

  /// Update the best position and particle
  void setBest();

  /// Set the positions

  void setPosition(size_t, double);

  void setVelocity(size_t, double);

  /// Return the the number of dimensions of the search space
  size_t getDimension() const;

  /// Return the position
  const std::vector<double>& getPosition() const { return m_position; };

  /// Return the cost
  double getCost();

  double getVelocity(size_t);

  double getBestPositionParticle(size_t);

  const std::vector<double>& getBestPositionParticle() const { return m_position_best; };

  double getBestCostParticle();

  /// Access the specified component
  double &operator[](size_t t) { return m_position[t]; };

  friend bool operator<(const PSParticle &l, const PSParticle &r) { return l.m_cost_best < r.m_cost_best; };

private:
  std::vector<double> m_position;
  double              m_cost;
  std::vector<double> m_velocity;
  std::vector<double> m_position_best;
  double              m_cost_best;
};

#endif
