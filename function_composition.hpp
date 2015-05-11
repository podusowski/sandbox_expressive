#pragma once

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
    composition(First first, Second second) : first(first), second(second)
    {
    }

    auto operator () (typename function_traits<First>::arg_type arg) -> typename function_traits<Second>::return_type
    {
        return second(first(arg));
    }

private:
    First first;
    Second second;
};

template<class First, class Second>
auto compose(First first, Second second) -> composition<First, Second>
{
    return composition<First, Second>{first, second};
}
