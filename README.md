Some expressive c++ toys.

## [Expressive bind primitives](examples/advanced_function_composition.cpp)
* [`functional::compose`](examples/simple_function_composition.cpp) - variadic function composition
* `functional::curry` - partial application
* `functional::member` - member fetch function - `member(&some_struct::some_member) -> f(some_struct) -> decltype(some_struct::some_member)`
* `functional::method` - method bind, but without need for placeholders

## More utilities
* unpure::match - switch / if substitution which behaves like expression
* [`strong_type`](examples/strong_type_example.cpp) - strong typing for primitives
* `factory` - `make_shared` wrapper
