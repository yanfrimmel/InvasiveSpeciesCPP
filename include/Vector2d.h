#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cfloat>
#include <climits>

/*The Vector2d class is an object consisting of simply an x and
  y value. Certain operators are overloaded to make it easier
  for vector math to be performed.*/
template <class T> class Vector2d {
public:
  /*The x and y values are public to give easier access for
    outside funtions. Accessors and mutators are not really
    necessary*/
  T x;
  T y;

  // Constructor assigns the inputs to x and y.
  Vector2d();
  Vector2d(T, T);

  /*The following operators simply return Vector2ds that
    have operations performed on the relative (x, y) values*/
  auto operator+(const Vector2d &) const -> Vector2d;
  auto operator-(const Vector2d &) const -> Vector2d;
  auto operator*(const Vector2d &)const -> Vector2d;
  auto operator/(const Vector2d &) const -> Vector2d;

  // Check if the Vectors have the same values.
  auto operator==(const Vector2d &) const -> bool;

  /*Check which Vectors are closer or further from the
    origin.*/
  auto operator>(const Vector2d &) const -> bool;
  auto operator<(const Vector2d &) const -> bool;
  auto operator>=(const Vector2d &) const -> bool;
  auto operator<=(const Vector2d &) const -> bool;

  // Negate both the x and y values.
  auto operator-() const -> Vector2d;

  // Apply scalar operations.
  auto operator*(const T &)const -> Vector2d;
  auto operator/(const T &) const -> Vector2d;

  // Product functions
  static auto dotProduct(const Vector2d &, const Vector2d &) -> T;
  static auto crossProduct(const Vector2d &, const Vector2d &) -> T;

  // Returns the length of the vector from the origin.
  static auto magnitude(const Vector2d &) -> T;

  static auto distance(const Vector2d &, const Vector2d &) -> T;

  // Return the unit vector of the input
  static auto normal(const Vector2d &) -> Vector2d;

  // Return a vector perpendicular to the left.
  static auto perpendicular(const Vector2d &) -> Vector2d;

  // Return true if two line segments intersect.
  static auto intersect(const Vector2d &, const Vector2d &, const Vector2d &,
                        const Vector2d &) -> bool;

  // Return the point where two lines intersect.
  static auto getIntersect(const Vector2d &, const Vector2d &, const Vector2d &,
                           const Vector2d &) -> Vector2d;
};

#endif
