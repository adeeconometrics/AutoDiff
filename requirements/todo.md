# todo 
- [ ] Documentation in Sphinx
## Template library
- [ ] `const` and `constexpr` when see fit
- [ ] handle `std::domain_exception`
- [x] inverse trigonometric functions
- [ ] higher-order differentiation
- [x] vectorize functions 
- [x] Resolve recursion using lambdas
- [x] Resolve Segmentation faults
- [x] Build the computational graph
- [x] Implementation of forward pass
- [x] Implementation of reverse pass

## Prototypes
- [x] Reverse mode
- [x] Forward mode
- [ ] Higher-order partial differentiation
- [x] Template specialization of vectorized function
- [x] Printing format for matrix
- [ ] JVP
- [ ] VJP
- [ ] Jacobian matrix
- [ ] Directional derivative
- [ ] Total derivative 


Test
- [ ] composable gradient for reverse-mode higher-order PD
- [ ] composing forward-mode functions for higher-order PD


Future Features
- [ ] Loop fusion
- [ ] Concurrency

--- 
Questions
- how well does the compiler identify loop fusion for optimization? 
- which is more efficient: list, vector, or map for insertion and retrieval tasks?
    - does all containers have total ordering properties?*
    - does all containers have hash?*  
- is applying functions into a for loop just as efficient as `numpy`?

