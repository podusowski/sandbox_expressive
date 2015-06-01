Some `expressive` c++ toys.

## Functional primitives

You can do pretty much everything with `std::bind` but this library tends to name things in more comprehensive way. Check out [this example](examples/advanced_function_composition.cpp) to see how to do the same thing in `std::bind` and `expressive` way.

* [`functional::compose`](examples/simple_function_composition.cpp) - variadic function composition
* `functional::curry` - partial application
* `functional::member` - member fetch function - `member(&some_struct::some_member) -> f(some_struct) -> decltype(some_struct::some_member)`
* `functional::method` - method bind, but without need for placeholders

## More utilities
* `match` - switch / if substitution which behaves like expression and can take predicates
* [`strong_type`](examples/strong_type_example.cpp) - strong typing for primitives
* `factory` - `std::make_shared` wrapper
* `enumerate` - iterate over container with index
