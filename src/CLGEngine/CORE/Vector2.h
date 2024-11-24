#pragma once

namespace CLGEngine {
// Using templates for cases like in ConsoleWindow.h 
//	where Win API's RECT uses LONG values 
//	and cant be converted to flaot.
template <typename T>
struct Vector2 {
	T x, y;
	Vector2<T> operator+(Vector2 const& vec) {
		Vector2<T> sum;
		sum.x = x + vec.x;
		sum.y = y + vec.y;
		return sum;
	}
	void operator+=(Vector2 const& vec) {
		x += vec.x;
		y += vec.y;
	}
	bool operator==(Vector2 const& vec) const{
		if (x == vec.x && y == vec.y){
			return true;
		}
		return false;
	}
	Vector2 operator-(Vector2 const& vec) {
		Vector2 diff;
		diff.x = x - vec.x;
		diff.y = y - vec.y;
		return diff;
	}
	Vector2 operator*(float factor) {
		Vector2 product;
		product.x = factor * x;
		product.y = factor * y;
		return product;
	}
	float dot(Vector2 factor) {
		return (factor.x * x) + (factor.y * y);
	}

	
	explicit operator Vector2<int>() const {return {(int)x, (int)y};}
	explicit operator Vector2<float>() const {return {(float)x, (float)y};}
};
}