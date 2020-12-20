#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct IndexOf {
private:
    typedef typename TList::tail tail;
    const static int interimPos = IndexOf<tail, TargetType>::pos;

public:
    const static int pos = (interimPos == -1) ? -1 : interimPos + 1;
};

template<typename TList>
struct IndexOf <TList, typename TList::head> {
public:
    const static int pos = 0;
};

template<typename TargetType>
struct IndexOf<NullType, TargetType> {
public:
    const static int pos = -1;
};