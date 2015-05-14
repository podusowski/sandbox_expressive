Some functional toys.

# Function composition

```
auto foo(int i) -> int;
auto bar(int i) -> int;

// using functional
auto foobar = compose(foo, bar);
auto result = foobar(1); // equivalent to foo(bar(1))

// using std
auto foobar = std::bind(foo, std::bind(bar));
auto result = foobar(1); // equivalent to foo(bar(1))
```
