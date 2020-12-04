#ifndef EmiR_Parameter_h
#define EmiR_Parameter_h

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

class Parameter {
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
  double getRangeMin() const;

  /// Return the min value of the range
  double getRangeMax() const;

  std::string sciPrint() {
    std::stringstream ss;
    ss << std::scientific << "[" << m_min_val << ", " << m_max_val << "]";
    return ss.str();
  };

  friend std::ostream &operator<<(std::ostream &os, Parameter &rhs) {
    os << rhs.m_name << ": [ " << rhs.m_min_val << ", " << rhs.m_max_val << " ]\n";
    return os;
  };

private:
  std::string m_name;    /**< Name of the parameter */
  double      m_min_val; /**< Minimum value of the range */
  double      m_max_val; /**< Maximum value of the range */
};
#endif
