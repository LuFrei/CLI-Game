#pragma once

namespace CLGEngine {
	namespace CORE {
		template<typename T>
		struct Vector2 {
			// TODO: REstrict T to numeric types (?)
			//	*(?) May not be needed unless we allow for type casting.
			// -> static_assert();
			T x, y;
			Vector2<T> operator+(Vector2<T> const& vec) {
				Vector2<T> sum;
				sum.x = x + vec.x;
				sum.y = y + vec.y;
				return sum;
			}
			void operator+=(Vector2<T> const& vec) {
				x += vec.x;
				y += vec.y;
			}
			Vector2<T> operator-(Vector2<T> const& vec) {
				Vector2<T> diff;
				diff.x = x - vec.x;
				diff.y = y - vec.y;
				return diff;
			}
			Vector2<T> operator*(T factor) {
				Vector2<T> product;
				product.x = factor * x;
				product.y = factor * y;
				return product;
			}
			T dot(Vector2<T> factor) {
				T product = (factor.x * x)
						  + (factor.y * y);
				return product;
			}
			//TODO: would be nice to find a way to make type casting work on this.
			// Something in the lines of (float)Vector2<int>.
			// For now: explicitly create a new temp Vector2 with type casted vars.
		};
	}
}

