#ifndef EmiR_Particle_h
#define EmiR_Particle_h

#include <vector>
#include <iostream>
#include <iomanip>

class Particle {
public:
   /// Particle default constructor for an _n_ - dimensional search space (- _n_ fitting parameters)
   Particle(int n);

   /// Set the particle's _t_ - coordinate
   void setPosition(size_t t, double);

   /// Set the velocity
   /// Referenced by Population::setVelocity(), Population::init()
   void setVelocity(size_t, double);

   /// Set the cost of the current position
   /// Referenced by Evaluate::computeCostFit()
   void setCost(double);

   /// Return the the number of dimensions of the search space
   size_t getDimension() const;

   /// Return the _t_ - coordinate of the particle in the current position
   double getPosition(size_t t);

   /// Return the coordinates of the particle in the current position
   double* getPosition() { return &m_position[0]; };

   /// Return the coordinates of the particle in the current position
   std::vector<double> getPositionVector() { return m_position; };

   /// Return the _t_ - coordinate of the best position found by the particle
   double getBestPosition(size_t t);

   /// Return the best position of the particle
   std::vector<double>& getBestPosition() { return m_position_best; }

   /// Return the _t_ - component of the velocity
   double getVelocity(size_t t);

   /// Return the cost computed using the current position of the particle
   double getCost();

   /// Return the cost computed using the best position found by the particle
   double getBestCost();

   /// Show on video the characteristics of a particle
   friend std::ostream &operator<<(std::ostream &os, Particle &rhs) {
      os << "PS particle [";
      for (size_t i = 0; i < rhs.getDimension(); ++i) {
         os << rhs.getBestPosition(i);
         if (i < rhs.getDimension() - 1) os << ", ";
      };
      os << "] - cost: " << rhs.getBestCost() << std::endl;
      return os;
   };

   /// Compare two particles' best cost found
   friend bool operator<(const Particle &l, const Particle &r) { return l.m_cost_best < r.m_cost_best; };

private:
   std::vector<double> m_position;      /**<Vector storing the coordinates of the current position*/
   std::vector<double> m_position_best; /**<Vector storing the coordinates of the best position found*/
   std::vector<double> m_velocity;      /**<Vector storing the velocity components*/
   double              m_cost;          /**<Particle's cost evaluated in the current position*/
   double              m_cost_best;     /**<Particle's best cost found*/
};

#endif
