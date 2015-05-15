#pragma once

namespace functional
{

template<class Signature>
struct function_traits : public function_traits<decltype(&Signature::operator())>
{
};

// two parameter specializations

template<class Result, class Class, class Arg, class Second>
struct function_traits<Result(Class::*)(Arg, Second) const>
{
    typedef Result return_type;
    typedef Arg arg_type;
    typedef Second second_arg_type;
};

template<class Result, class Class, class Arg, class Second>
struct function_traits<Result(Class::*)(Arg, Second)>
{
    typedef Result return_type;
    typedef Arg arg_type;
    typedef Second second_arg_type;
};

template<class Result, class Arg, class Second>
struct function_traits<Result(*)(Arg, Second)>
{
    typedef Result return_type;
    typedef Arg arg_type;
    typedef Second second_arg_type;
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

} // namespace functional
