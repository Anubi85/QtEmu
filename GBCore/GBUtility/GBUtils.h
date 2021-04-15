#ifndef GBUTILS_H
#define GBUTILS_H

#include <QtGlobal>

template<typename T>
constexpr inline typename std::enable_if<std::is_enum<T>::value, std::underlying_type<T>>::type::type operator*(T val)
{
    return static_cast<typename std::underlying_type<T>::type>(val);
}

#endif // GBUTILS_H
