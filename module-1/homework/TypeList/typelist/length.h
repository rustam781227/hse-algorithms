#pragma once

#include "typelist.h"

template<typename TList>
struct Length {
private:
    typedef typename TList::tail tail;

public:
    const static std::size_t length = 1 + Length<tail>::length;
};

template<>
struct Length<NullType> {
public:
    const static std::size_t length = 0;
};