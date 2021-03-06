#include "Vector2d.h"
#include <cmath>

template <class T> Vector2d<T>::Vector2d() : x(0), y(0) {}

template <class T>
Vector2d<T>::Vector2d(T sourceX, T sourceY) : x(sourceX), y(sourceY) {}

template <class T>
auto Vector2d<T>::operator+(const Vector2d &v) const -> Vector2d<T> {
	return Vector2d(x + v.x, y + v.y);
}

template <class T>
auto Vector2d<T>::operator-(const Vector2d<T> &v) const -> Vector2d<T> {
	return Vector2d(x - v.x, y - v.y);
}

template <class T>
auto Vector2d<T>::operator*(const Vector2d<T> &v) const -> Vector2d<T> {
	return Vector2d(x * v.x, y * v.y);
}

template <class T>
auto Vector2d<T>::operator/(const Vector2d<T> &v) const -> Vector2d<T> {
	return Vector2d<T>(x / v.x, y / v.y);
}

template<class T>
Vector2d<T>::operator Vector2d<float>()
{
	return Vector2d<float>((float)x, (float)y);
}

template<class T>
Vector2d<T>::operator Vector2d<int>()
{
	return Vector2d<int>((int)x, (int)y);
}

template <class T>
auto Vector2d<T>::operator==(const Vector2d<T> &v) const -> bool {
	return ((x == v.x) && (y == v.y));
}

template <class T>
auto Vector2d<T>::operator>(const Vector2d<T> &v) const -> bool {
	return (x * x + y * y) > (v.x * v.x + v.y * v.y);
}

template <class T>
auto Vector2d<T>::operator<(const Vector2d<T> &v) const -> bool {
	return (x * x + y * y) < (v.x * v.x + v.y * v.y);
}

template <class T>
auto Vector2d<T>::operator>=(const Vector2d<T> &v) const -> bool {
	return (x * x + y * y) > (v.x * v.x + v.y * v.y) ||
		(x * x + y * y) == (v.x * v.x + v.y * v.y);
}

template <class T>
auto Vector2d<T>::operator<=(const Vector2d<T> &v) const -> bool {
	return (x * x + y * y) < (v.x * v.x + v.y * v.y) ||
		(x * x + y * y) == (v.x * v.x + v.y * v.y);
}
template <class T>
auto Vector2d<T>::operator-() const -> Vector2d<T> {
	return Vector2d(-x, -y);
}

template <class T>
auto Vector2d<T>::operator*(const T &scalar) const -> Vector2d<T> {
	return Vector2d(x * scalar, y * scalar);
}

template <class T>
auto Vector2d<T>::operator/(const T &scalar) const -> Vector2d<T> {
	return Vector2d(x / scalar, y / scalar);
}

template <class T>
auto Vector2d<T>::dotProduct(const Vector2d<T> &a, const Vector2d<T> &b) -> T {
	return ((a.x * b.x) + (a.y * b.y));
}

template <class T>
auto Vector2d<T>::crossProduct(const Vector2d<T> &a, const Vector2d &b) -> T {
	return ((a.x * b.y) - (a.y * b.x));
}

template <class T> auto Vector2d<T>::magnitude(const Vector2d<T> &v) -> T {
	return std::sqrt((v.x * v.x) + (v.y * v.y));
}

template <class T>
auto Vector2d<T>::distance(const Vector2d &v1, const Vector2d &v2) -> T {
	return magnitude(v1 - v2);
}

template <class T> auto Vector2d<T>::normal(const Vector2d &v) -> Vector2d<T> {
	T m = magnitude(v);
	return Vector2d<T>(v.x / m, v.y / m);
}

template <class T>
auto Vector2d<T>::perpendicular(const Vector2d<T> &v) -> Vector2d<T> {
	return Vector2d<T>(v.y, -v.x);
}

template <class T>
auto Vector2d<T>::intersect(const Vector2d<T> &aa, const Vector2d<T> &ab,
	const Vector2d<T> &ba, const Vector2d<T> &bb)
	-> bool {
	Vector2d<T> p = aa;
	Vector2d<T> r = ab - aa;
	Vector2d<T> q = ba;
	Vector2d<T> s = bb - ba;

	T t = crossProduct((q - p), s) / crossProduct(r, s);
	T u = crossProduct((q - p), r) / crossProduct(r, s);

	return (0.0 <= t && t <= 1.0) && (0.0 <= u && u <= 1.0);
}

template <class T>
auto Vector2d<T>::getIntersect(const Vector2d<T> &aa, const Vector2d<T> &ab,
	const Vector2d<T> &ba, const Vector2d<T> &bb)
	-> Vector2d<T> {
	T pX = (aa.x * ab.y - aa.y * ab.x) * (ba.x - bb.x) -
		(ba.x * bb.y - ba.y * bb.x) * (aa.x - ab.x);
	T pY = (aa.x * ab.y - aa.y * ab.x) * (ba.y - bb.y) -
		(ba.x * bb.y - ba.y * bb.x) * (aa.y - ab.y);
	T denominator = (aa.x - ab.x) * (ba.y - bb.y) - (aa.y - ab.y) * (ba.x - bb.x);

	return Vector2d<T>(pX / denominator, pY / denominator);
}

template class Vector2d<float>;
template class Vector2d<int>;
