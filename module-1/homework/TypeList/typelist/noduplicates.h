#pragma once

#include "erase.h"
#include "typelist.h"

template<typename TList>
struct NoDuplicates;

template<>
struct NoDuplicates<NullType> {
    typedef NullType NewTypeList;
};

template<typename TFirst, typename TSecond>
struct NoDuplicates<TypeList<TFirst, TSecond>> {
    typedef TypeList<TFirst, typename EraseAll<typename NoDuplicates<TSecond>::NewTypeList, TFirst>::NewTypeList> NewTypeList;
};