Some functional toys.

# Function composition

```
auto foo(int i) -> int;
auto bar(int i) -> int;

int main()
{
    auto foobar = compose(foo, bar);
    auto result = foobar(1); // equivalent to foo(bar(1))
}
```
