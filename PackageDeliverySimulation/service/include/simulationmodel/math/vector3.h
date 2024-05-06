#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <cmath>
#include <iostream>
#include <vector>

/**
 * @class Vector3
 * @brief a simple class used for vector math
 **/
class Vector3 {
 public:
  double x = 0;
  double y = 0;
  double z = 0;
  /**
   * @brief Default constructor for Vector3
   */
  Vector3();
  /**
   * @brief Parameter constructor.
   * @param a converts type double for Vector3
   */
  Vector3(double a);
  /**
   * @brief Parameter constructor.
   *
   * @param[in] a x-coordinate
   * @param[in] b y-coordinate
   * @param[in] c z-coordinate
   */
  Vector3(double a, double b, double c);
  /**
   * @brief Parameter constructor.
   * @param v converts type vector<double>& for Vector3
   */
  Vector3(const std::vector<double>& v);
  /**
   * @brief Parameter constructor.
   * @param v type vector<float>& for Vector3
   */
  Vector3(const std::vector<float>& v);
  /**
   * @brief Overloads == operator
   * @param v type const Vector3& for Vector3
   * @return bool of whether the vector is equal or not
   */
  bool operator==(const Vector3& v) const;
  /**
   * @brief Reference double for an array for Vector3
   * @param i type int for Vector3
   * @return The Vector3 Object double&
   */
  double& operator[](int i);
  /**
   * @brief Const double for an array for Vector3
   * @param i type int for Vector3
   * @return The Vector3 Object double
   */
  double operator[](int i) const;
  /**
   * @brief Overrides + operator.
   * @param[in] v The Vector3 object you would like to add to this Vector3
   * object
   * @return The Vector3 Object comprised of the sum of the two objects
   */
  Vector3 operator+(const Vector3& v) const;
  /**
   * @brief Overrides - operator.
   * @param[in] v The Vector3 object you would like to subtract to this Vector3
   * object
   * @return The Vector3 Object comprised of the subtraction of the two objects
   */
  Vector3 operator-(const Vector3& v) const;
  /**
   * @brief Overrides * operator.
   * @param[in] v The Vector3 object you would like to multiply to this Vector3
   * object
   * @return The Vector3 Object comprised of the multiplication of the two
   * objects
   */
  Vector3 operator*(double s) const;
  /**
   * @brief Overrides / operator.
   * @param[in] v The Vector3 object you would like to divide to this Vector3
   * object
   * @return The Vector3 Object comprised of the division of the two objects
   */
  Vector3 operator/(double s) const;
  /**
   * @brief Overrides * operator.
   * @param[in] v The Vector3 object you would like to take the dot product to this Vector3
   * object
   * @return The Vector3 Object comprised of the dot product of the two objects
   */
  double operator*(const Vector3& v) const;  // dot product
  // template function should be defined in same file
  // with template keyword
  template <class T>
  /**
   * @brief Returns vector version of Vector3
   * @return std::vector version of this Vector3
   */
  std::vector<T> vec() const {
    return {static_cast<T>(x), static_cast<T>(y), static_cast<T>(z)};
  }
    /**
   * @brief Calculates cross product of Vector3
   * @param v of type const Vector3& contains Vector3& for calculation
   */
  Vector3 cross(const Vector3& v) const;
  /**
   * @brief Calculates magnitude
   * @return magnitude of Vector3   
   */
  double magnitude() const;
  /**
   * @brief Calculates normalization
   * @return normalized Vector3   
   */
  Vector3& normalize();
    /**
   * @brief Normal vector in same direction
   * @return normal vector of Vector3
   */
  Vector3 unit() const;
    /**
   * @brief Calculates distance of Vector3&
   * @param v type Vector3& contains Vector3 for calculation
   * @return distance of Vector3
   */
  double dist(const Vector3& v) const;
  /**
   * @brief Overloaded << operator for outputting Vector3 to an output stream
   * @param[in] strm type std::ostream& contains output stream to write to
   * @param[in] v type Vector3& of the Vector3 to output
   * @return The output stream
   */
  friend std::ostream& operator<<(std::ostream& strm, const Vector3& v);
};

#endif  // VECTOR3_H_
