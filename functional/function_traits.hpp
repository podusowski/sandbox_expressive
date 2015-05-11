#pragma once

namespace functional
{

template<class Signature>
struct function_traits : public function_traits<decltype(&Signature::operator())>
{
};

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

} // namespace functional
