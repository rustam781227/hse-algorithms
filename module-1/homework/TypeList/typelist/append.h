#pragma once

#include "typelist.h"

template<typename TList, typename NewType>
struct Append {
private:
    typedef typename TList::tail tail;
    typedef typename TList::head head;

public:
    typedef TypeList<head, typename Append<tail, NewType>::NewTypeList> NewTypeList;
};

template<typename NewType>
struct Append<NullType, NewType> {
public:
    typedef TypeList<NewType, NullType> NewTypeList;
};

template<>
struct Append<NullType, NullType> {
public:
    typedef NullType NewTypeList;
};