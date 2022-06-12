#include <cmath>                                                                                
#include <cstdint>                                                                              
#include <iomanip>                                                                              
#include <iostream>                                                                             
#include <vector>                                                                               
#include <type_traits>

const std::vector<std::vector<double>> array = {                                                
  // OP's data.                                                                                 
    {0, 6.0303, 16.052, 40.523, 100, 40.557, 16.167, 6.7314, 1.8967, 0},                        
    {0, 4.5593, 13.16, 25.342, 41.927, 25.354, 13.312, 4.9988, 1.9527, 0},                      
    {0, 3.0952, 6.6864, 13.531, 17.01, 13.544, 6.7291, 3.466, 0.91553, 0},                      
    {0, 1.1353, 3.466, 5.0842, 7.3242, 5.0842, 3.4981, 1.2207, 0.56076, 0},                     
    {0, 0.54474, 0.95825, 2.153, 2.1179, 2.153, 0.95825, 0.5928, 0.10681, 0},                   
    {0, 0.085449, 0.38452, 0.45166, 0.78392, 0.45166, 0.38452, 0.085449, 0.048065, 0},          
    {0, 0.032043, 0.042725, 0.15221, 0.11444, 0.15221, 0.042725, 0.032043, 0, 0},               
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},                                                             
  // My test data.                                                                              
    {1e-7, 1.12031e-34, 1e-34, 1e-6, 1e33, 1e-8, 1.3123233e93, 1e32, 1.e99, 1.e100},            
    {-1e-7, -1.12031e-34, -1e-34, -1e-6, -1e33, -1e-8, -1.3123233e93, -1e32, -1.e99, -1.09e100},
};                                                                                                                         

const struct {
	uint8_t Width = 8;
	uint8_t DecimalSign = 1;
	uint8_t NegativeSign = 1;
	uint8_t SciNotation = 2;
	uint8_t Exponent = 2;
} TextSpace;

template <typename T>
auto operator<< (std::ostream& os, const std::vector<T>& v) -> std::ostream& {
    for(const auto  i: v)
        os << i;
    return os;
}

template <typename T>
inline typename std::enable_if_t<std::is_arithmetic_v<T>>
auto operator<<(std::ostream& os, const std::vector<double>& v) -> std::ostream& {
	for(const auto i: v){
		const float log = std::log10(std::abs(i));
		const uint8_t available_space = TextSpace.Width - (i < 0) * TextSpace.DecimalSign;
		const bool has_scientific_notation = 
			i != 0.0 && 
			(log < -1.0 * available_space + 
			 TextSpace.DecimalSign + 
			 TextSpace.NegativeSign || 
			 log > available_space);
		os << "  " << std::setw(TextSpace.Width);
		if(has_scientific_notation){
			double llog = std::log10(log);
			const uint8_t digits_after_exponent = std::max(TextSpace.Exponent,
													static_cast<uint8_t>(llog));
			const uint8_t digits_after_dot = std::max(1.0, llog);
			uint8_t new_precision = available_space - digits_after_exponent -
									TextSpace.Exponent - TextSpace.DecimalSign -
									digits_after_dot;
			if (new_precision > available_space){
				new_precision = 0;
		    }
			os << std::scientific << std::setprecision(new_precision);
		} else {
			const uint8_t fixed_digitspace_before_decimal = std::max(log + 1.0, 1.0);
			const uint8_t fixed_digitspace_after_decimal = available_space - TextSpace.DecimalSign - fixed_digitspace_before_decimal;
			os << std::fixed << std::setprecision(fixed_digitspace_after_decimal);
		}
		
	    os << i;
	}
	return os << '\n';
}

int main() {      
    std::vector<std::vector<std::vector<double>>> barray {
                                                            {
                                                                {1,2,3}, {1,2,3}
                                                                
                                                            }
    };
	std::cout << barray;
	//std::cout << array[2];
	//std::cout << array[3];
	std::cout << array;
}
