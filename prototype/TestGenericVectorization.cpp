#include <concepts>
#include <type_traits>
#include <algorithm>
#include <vector>
#include <list>
#include <cmath>
#include <iostream>

template <typename T>
concept HasPushBack = requires (T t, typename T::const_reference element) {
	typename T::const_iterator;
	typename T::const_reference;

	{t.push_back(element)} -> std::same_as<void>;
};

template <typename Param, template <typename T> typename Container>
requires HasPushBack<Container<Param>> && std::is_arithmetic<Param>
auto sin(const Container<Param> &v) noexcept -> Container<Param> {
  Container<Param> result; // {}
  std::for_each(v.cbegin(), v.cend(), [&result](const auto i) -> void {
    result.push_back(std::sin(i));
  });
  return result;
}

template <typename Param, template <typename T> typename Container>
requires HasPushBack<Container<Param>> 
auto operator<<(std::ostream& os, const Container<Param>& v) -> std::ostream& {
	for(const auto i: v)
		os << i << " ";
	return os << '\n';
}

auto main(void) -> int {
	std::vector<double> v {1,2,3,4,5,5,6,8};
	std::list<double> l {v.cbegin(), v.cend()};
	std::cout << "vector: " <<  sin(v); 
	std::cout << "list: " << sin(l);
}
