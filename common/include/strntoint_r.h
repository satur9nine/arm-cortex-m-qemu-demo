#ifndef STRNTOINT_R_H_
#define STRNTOINT_R_H_

#include <stddef.h>
#include <stdint.h>

/// @brief Like strtol but returns int8_t, stops at len instead of nul char,
///        also reentrant and more strict, must contain valid digits but still
///        allows whitespace prefix.
/// @param str string to extract
/// @param len limit of characters from string to parse
/// @param base numerical base of input string
/// @param error optional, populated with EINVAL or ERANGE depending on error
/// @return converted value
int8_t strntoi8_r(const char *str, size_t len, int base, int *error);

/// @brief Like strtol but returns uint8_t, stops at len instead of nul char,
///        also reentrant and more strict, must contain valid digits but still
///        allows whitespace prefix.
/// @param str string to extract
/// @param len limit of characters from string to parse
/// @param base numerical base of input string
/// @param error optional, populated with EINVAL or ERANGE depending on error
/// @return converted value
uint8_t strntou8_r(const char *str, size_t len, int base, int *error);

/// @brief Like strtol but returns int16_t, stops at len instead of nul char,
///        also reentrant and more strict, must contain valid digits but still
///        allows whitespace prefix.
/// @param str string to extract
/// @param len limit of characters from string to parse
/// @param base numerical base of input string
/// @param error optional, populated with EINVAL or ERANGE depending on error
/// @return converted value
int16_t strntoi16_r(const char *str, size_t len, int base, int *error);

/// @brief Like strtol but returns uint16_t, stops at len instead of nul char,
///        also reentrant and more strict, must contain valid digits but still
///        allows whitespace prefix.
/// @param str string to extract
/// @param len limit of characters from string to parse
/// @param base numerical base of input string
/// @param error optional, populated with EINVAL or ERANGE depending on error
/// @return converted value
uint16_t strntou16_r(const char *str, size_t len, int base, int *error);

/// @brief Like strtol but returns int32_t, stops at len instead of nul char,
///        also reentrant and more strict, must contain valid digits but still
///        allows whitespace prefix.
/// @param str string to extract
/// @param len limit of characters from string to parse
/// @param base numerical base of input string
/// @param error optional, populated with EINVAL or ERANGE depending on error
/// @return converted value
int32_t strntoi32_r(const char *str, size_t len, int base, int *error);

/// @brief Like strtol but returns uint32_t, stops at len instead of nul char,
///        also reentrant and more strict, must contain valid digits but still
///        allows whitespace prefix.
/// @param str string to extract
/// @param len limit of characters from string to parse
/// @param base numerical base of input string
/// @param error optional, populated with EINVAL or ERANGE depending on error
/// @return converted value
uint32_t strntou32_r(const char *str, size_t len, int base, int *error);

/// @brief Like strtol but returns int64_t, stops at len instead of nul char,
///        also reentrant and more strict, must contain valid digits but still
///        allows whitespace prefix.
/// @param str string to extract
/// @param len limit of characters from string to parse
/// @param base numerical base of input string
/// @param error optional, populated with EINVAL or ERANGE depending on error
/// @return converted value
int64_t strntoi64_r(const char *str, size_t len, int base, int *error);

/// @brief Like strtol but returns uint64_t, stops at len instead of nul char,
///        also reentrant and more strict, must contain valid digits but still
///        allows whitespace prefix.
/// @param str string to extract
/// @param len limit of characters from string to parse
/// @param base numerical base of input string
/// @param error optional, populated with EINVAL or ERANGE depending on error
/// @return converted value
uint64_t strntou64_r(const char *str, size_t len, int base, int *error);

#endif // STRNTOINT_R_H_