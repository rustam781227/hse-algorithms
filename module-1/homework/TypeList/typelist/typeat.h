#pragma once

#include "typelist.h"

template<typename TList, std::size_t index>
struct TypeAt {
private:
    typedef typename TList::tail tail;

public:
    typedef typename TypeAt<tail, index - 1>::TargetType TargetType;
};

template<typename TList>
struct TypeAt<TList, 0> {
public:
    typedef typename TList::head TargetType;
};