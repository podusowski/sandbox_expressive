#include <type_traits>

struct type1 {};
struct type2 {};
struct type3 {};

auto foo(type1) -> type2
{
    return type2{};
}

auto bar(type2) -> type3
{
    return type3{};
}

template<class Signature>
struct function_traits : public function_traits<decltype(&Signature::operator())>
{
};

template<class Result, class Class, class Arg>
struct function_traits<Result(Class::*)(Arg) const>
{
    typedef Result return_type;
    typedef Arg arg_type;
};

template<class Result, class Class, class Arg>
struct function_traits<Result(Class::*)(Arg)>
{
    typedef Result return_type;
    typedef Arg arg_type;
};

template<class Result, class Arg>
struct function_traits<Result(*)(Arg)>
{
    typedef Result return_type;
    typedef Arg arg_type;
};

template<class First, class Second>
struct composition
{
    auto operator () (typename function_traits<First>::arg_type) -> typename function_traits<Second>::return_type
    {
        return typename function_traits<Second>::return_type{};
    }
};

template<class First, class Second>
auto compose(First, Second) -> composition<First, Second>
{
    return composition<First, Second>{};
}

int main()
{
    auto composed = compose(&foo, &bar);
    type3 ret = composed(type1{});
}
