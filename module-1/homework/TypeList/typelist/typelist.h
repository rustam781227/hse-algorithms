#pragma once

template<typename Head, typename Tail>
struct TypeList {
public:

    typedef Head head;
    typedef Tail tail;
};

struct NullType {};