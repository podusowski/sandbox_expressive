#pragma once

namespace expressive
{

template<class Signature>
struct function_traits : public function_traits<decltype(&Signature::operator())>
{
};

template<class Result, class Class>
struct function_traits<Result(Class::*)() const>
{
    typedef Result return_type;
};

template<class Result, class Class>
struct function_traits<Result(Class::*)()>
{
    typedef Result return_type;
};

template<class Result>
struct function_traits<Result(*)()>
{
    typedef Result return_type;
};

// one or N parameters

template<class Result, class Class, class Arg, class... Rest>
struct function_traits<Result(Class::*)(Arg, Rest...) const>
{
    typedef Result return_type;
    typedef Arg arg_type;
};

template<class Result, class Class, class Arg, class... Rest>
struct function_traits<Result(Class::*)(Arg, Rest...)>
{
    typedef Result return_type;
    typedef Arg arg_type;
};

template<class Result, class Arg, class... Rest>
struct function_traits<Result(*)(Arg, Rest...)>
{
    typedef Result return_type;
    typedef Arg arg_type;
};

} // namespace expressive
