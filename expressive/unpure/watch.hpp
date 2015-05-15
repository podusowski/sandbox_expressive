#pragma once

#include <functional>
#include <map>

namespace unpure
{

template<class Value>
struct watch
{
    using action_type = std::function<void()>;

    watch() : value{}
    {
    }

    explicit watch(Value value) : value(value)
    {
    }

    auto operator = (Value value) -> void
    {
        std::swap(this->value, value);

        if (not this->value == value)
        {
            action();
        }
    }

    auto operator * () const -> Value
    {
        return value;
    }

    auto when_changed(action_type action) -> void
    {
        this->action = action;
    }

private:
    Value value;
    action_type action;
};

} // namespace unpure
