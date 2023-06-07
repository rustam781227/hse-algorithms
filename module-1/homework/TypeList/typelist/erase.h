#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct Erase {
private:
    typedef typename TList::head head;
    typedef typename TList::tail tail;

public:
    typedef TypeList<head, typename Erase<tail, TargetType>::NewTypeList> NewTypeList;
};

template<typename TList>
struct Erase<TList, typename TList::head> {
public:
    typedef typename TList::tail NewTypeList;
};

template<typename TargetType>
struct Erase<NullType, TargetType> {
public:
    typedef NullType NewTypeList;
};