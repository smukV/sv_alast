#pragma once

namespace sv_alast {

	template<typename TFirst, typename TSecond>
	struct Pair {
	public:
		TFirst first;
		TSecond second;

		Pair()
			: first(), second(){}
		Pair(TFirst first, TSecond second)
			: first(first), second(second){}
		Pair(const Pair& other)
			: first(other.first), second(other.second){}
		Pair& operator=(const Pair& other) {
			this->first = other->first;
			this->second = other->second;
			return *this;
		}
	};
}