#pragma once

namespace CLGEngine {
	namespace CORE {
		// Using templates for cases like in MainWindow.h 
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
			//TODO: would be nice to find a way to make type casting work on this.
			// Something in the lines of (float)Vector2<int>.
			// For now: explicitly create a new temp Vector2 with type casted vars.
		};
	}
}

