#ifndef EmiR_Parameter_h
#define EmiR_Parameter_h

#include <string>
#include <random>

class Parameter {

  typedef std::uniform_real_distribution<double>::param_type rand_pt;

public:

  /// Empty constructor
  Parameter();

  /// Constructor with specified name for the parameter
  Parameter(const std::string&);

  /// Set the name of the parameter
  void setName(const std::string&);

  /// Set the range on the parameter
  void setRange(double,  double);

  /// Return the name of the parameter
  const std::string& getName() const;

  /// Return the min value of the range
  double getMin() const;

  /// Return the min value of the range
  double getMax() const;

  /// Return the width of the range
  double getWidth() const;

  /// Return a random value in the parameter range
  double getRandom();

private:
  std::mt19937 m_mt;
  std::string  m_name;    /**< Name of the parameter */
  double       m_min_val; /**< Minimum value of the range */
  double       m_max_val; /**< Maximum value of the range */

  rand_pt      m_range;
  std::uniform_real_distribution<double> m_r_range;
};
#endif
