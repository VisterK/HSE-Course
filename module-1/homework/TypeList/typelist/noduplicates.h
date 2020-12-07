#pragma once

#include "erase.h"
#include "typelist.h"

template<typename TList>
struct NoDuplicates;

template<>
struct NoDuplicates<NullType>{
    typedef NullType NewTypeList;
};

template<typename Head, typename Tail>
struct NoDuplicates<TypeList<Head,Tail>>{
private:
    typedef typename NoDuplicates<Tail>::NewTypeList List1;
    typedef typename Erase<List1, Head>::NewTypeList List2;
public:
    typedef TypeList<Head, List2> NewTypeList;

};