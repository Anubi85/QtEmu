#ifndef GBUTILS_H
#define GBUTILS_H

#include <QtCore>

template<typename T>
constexpr inline typename std::enable_if<std::is_enum<T>::value, bool>::type operator*(T val)
{
    return static_cast<typename std::underlying_type<T>::type>(val);
}

#endif // GBUTILS_H
