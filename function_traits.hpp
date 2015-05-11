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
