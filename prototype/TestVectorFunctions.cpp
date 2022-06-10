#include <vector>
#include <iostream>
#include <cmath>
#include <concepts>
#include <type_traits>
#include <algorithm>
#include <functional>
#include <tuple>

/*
 * todo
 * - variadic functions
 * */

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
// template <typename R, typename ... P> 
// auto apply_function(const std::function<auto (P...) -> R>& f) -> void {
//	apply_function(std::function<auto (P...) -> R>(f));
// }

template <typename T>
auto f(const std::function<T(T...)>& fn, 
		const std::tuple<T>& tp) -> T {
	
	return std::apply(fn, tp);
}

auto dd(const std::vector<double>& t1,
		const std::vector<double>& t2) -> std::vector<double> {
	return t1;
}

template <typename T> 
auto vector_function(const std::vector<std::function<std::vector<T>(std::vector<T>)>>& fn,
		const std::vector<T>& v) -> std::vector<std::vector<T>> {
	
	std::vector<std::vector<T>> results{};
	for(const auto i: fn)
		results.push_back(i(v));
	return results;
} 

typedef std::function<std::vector<double>(std::vector<double>)> Function;

auto main(void) -> int {
	std::vector<double> v {1.3,2.4,5.6};
	Function f = sin<>;
	Function g = cos<>;
	auto fn  = std::vector<Function>{f, g};

	std::cout << vector_function(fn, std::vector<double>{1.2,2.3,2.5});
}
