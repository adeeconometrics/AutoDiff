#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <functional>

template<typename T>
using VectorFunction = std::function<std::vector<T>(std::vector<T>)>;

template <typename T>
auto operator<<(std::ostream& os, 
		const std::vector<T>& vec) -> std::ostream& {
	for(auto i: vec)
		os << i << " ";
	return os << '\n';
}

template <typename T = double>
auto sin(const std::vector<T>& vec) -> std::vector<T> {
	std::vector<T> result {};

	std::for_each(vec.cbegin(), vec.cend(), 
			[&result](auto i) -> void {result.push_back(sin(i));}
	);
	return result;
}

template <typename T = double>
auto cos(const std::vector<T>& vec) -> std::vector<T> {
	std::vector<T> result {};

	std::for_each(vec.cbegin(), vec.cend(), 
			[&result](auto i) -> void {result.push_back(cos(i));}
	);
	return result;
}


template <typename T = double>
auto tan(const std::vector<T>& vec) -> std::vector<T> {
	std::vector<T> result {};

	std::for_each(vec.cbegin(), vec.cend(), 
			[&result](auto i) -> void {result.push_back(tan(i));}
	);
	return result;
}

template <typename T> 
auto vector_function(const std::vector<VectorFunction<T>>& fn,
		const std::vector<T>& v) -> std::vector<std::vector<T>> {
	
	std::vector<std::vector<T>> results{};
	for(const auto i: fn)
		results.push_back(i(v));
	return results;
} 

auto main(void) -> int {
	std::vector<double> v {1.3,2.4,5.6};
	VectorFunction<double> f = sin<>;
	VectorFunction<double> g = cos<>;
	auto fn  = std::vector<VectorFunction<double>>{f, g};

	std::cout << vector_function(fn,v);
}
