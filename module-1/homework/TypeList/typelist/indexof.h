#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct IndexOf;


template <class T>
struct IndexOf<NullType, T>{
    enum{
        pos = -1
    };
};

template <typename TargetType, typename Tail>
struct IndexOf<TypeList<TargetType,Tail>,TargetType>{
    enum{
        pos = 0
    };
};
template<typename Head, typename Tail, typename TargetType>
struct IndexOf<TypeList<Head, Tail>, TargetType>{
private:
    enum{
        temp = IndexOf<Tail, TargetType>::pos
    };
public:
    enum{
        pos = (temp == -1 ? -1 : 1 + temp)
    };
};