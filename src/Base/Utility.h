#ifndef EmiR_Utility_h
#define EmiR_Utility_h

#include <sstream>
#include <limits>
#include <math.h>

class Utility {
public:

  /// Check if two numbers are approximately equal
  template<typename T>
  static typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type areEqual(T x, T y, int ulp = 2) {
    return fabs(x-y) <= std::numeric_limits<T>::epsilon() * fabs(x+y) * ulp
    || fabs(x-y) < std::numeric_limits<T>::min();
  };

  template<typename T>
  static int sgn(T val) {
    return (T(0) < val) - (val < T(0));
  }

  /// Center-align a string within a field of specified width
  static std::string centerAlign(const std::string s, const int w) {
    std::stringstream ss, spaces;
    int padding = w - s.size();
    for(int i=0; i<padding/2; ++i) spaces << " ";
    ss << spaces.str() << s << spaces.str();
    if(padding>0 && padding%2!=0) ss << " ";
    return ss.str();
  };

  /// Right-align a string within a field of specified width
  static std::string rightAlign(const std::string s, const int w) {
    std::stringstream ss, spaces;
    int padding = w - s.size();
    for(int i=0; i<padding; ++i) spaces << " ";
    ss << spaces.str() << s;
    return ss.str();
  };

  /// Left-align a string within a field of specified width
  static std::string leftAlign(const std::string s, const int w) {
    std::stringstream ss, spaces;
    int padding = w - s.size();
    for(int i=0; i<padding; ++i) spaces << " ";
    ss << s << spaces.str();
    return ss.str();
  };

  /// Convert a double to string
  static std::string toStringScientific(double d) {
    std::stringstream ss;
    ss << std::scientific << d;
    return ss.str();
  };
};
#endif
