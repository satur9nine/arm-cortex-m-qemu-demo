/*
 * Copyright (c) 2024 Jacob Whitaker Abrams
 * 
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE
 * FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY
 * DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "strntoint_r.h"

static int64_t strntoint_r(const char *str, size_t len, int base, uint8_t size,
                          bool is_signed, int *error) {
    int64_t min;
    uint64_t max;
    uint64_t abs_result = 0;  // Changed to track absolute value
    bool is_negative = false;
    const char *const end = str + len;
    
    if (len == 0 || !str || str >= end) {
        if (error) *error = EINVAL;
        return 0;
    }

    switch (size | (is_signed ? 0x80 : 0)) {
        case 0x81: // int8_t
            min = INT8_MIN;
            max = INT8_MAX;
            break;
        case 0x01: // uint8_t
            min = 0;
            max = UINT8_MAX;
            break;
        case 0x82: // int16_t
            min = INT16_MIN;
            max = INT16_MAX;
            break;
        case 0x02: // uint16_t
            min = 0;
            max = UINT16_MAX;
            break;
        case 0x84: // int32_t
            min = INT32_MIN;
            max = INT32_MAX;
            break;
        case 0x04: // uint32_t
            min = 0;
            max = UINT32_MAX;
            break;
        case 0x88: // int64_t
            min = INT64_MIN;
            max = INT64_MAX;
            break;
        case 0x08: // uint64_t
            min = 0;
            max = UINT64_MAX;
            break;
        default:
            if (error) *error = EINVAL;
            return 0;
    }

    while (str < end && isspace((int) *str)) str++;
    if (str >= end) {
        if (error) *error = EINVAL;
        return 0;
    }

    if (is_signed) {
        if (*str == '-') {
            is_negative = true;
            if (++str >= end) {
                if (error) *error = EINVAL;
                return 0;
            }
        } else if (*str == '+' && ++str >= end) {
            if (error) *error = EINVAL;
            return 0;
        }
    } else if (*str == '-') {
        if (error) *error = EINVAL;
        return 0;
    }

    if (str + 1 < end && (base == 0 || base == 16) && *str == '0') {
        if (str[1] == 'x' || str[1] == 'X') {
            base = 16;
            str += 2;
            if (str >= end) {
                if (error) *error = EINVAL;
                return 0;
            }
        } else if (base == 0) {
            base = 8;
            str++;
        }
    } else if (base == 0) {
        base = 10;
    }

    static const int8_t digit_vals[256] = {
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         0, 1, 2, 3, 4, 5, 6, 7, 8, 9,-1,-1,-1,-1,-1,-1,
        -1,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,
        25,26,27,28,29,30,31,32,33,34,35,-1,-1,-1,-1,-1,
        -1,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,
        25,26,27,28,29,30,31,32,33,34,35,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
    };

    int digit = digit_vals[(unsigned char)*str];
    if (digit < 0 || digit >= base) {
        if (error) *error = EINVAL;
        return 0;
    }
    abs_result = digit;
    str++;

    // Handle negative overflow differently for INT64_MIN
    uint64_t abs_limit = is_negative ? (uint64_t)-(min) : max;

    while (str < end) {
        digit = digit_vals[(unsigned char)*str];
        if (digit < 0 || digit >= base) {
            if (error) *error = EINVAL;
            return 0;
        }

        if (abs_result > abs_limit/base || 
            (abs_result == abs_limit/base && (uint64_t)digit > abs_limit % base)) {
            if (error) *error = ERANGE;
            return is_negative ? min : (int64_t)max;
        }
        abs_result = abs_result * base + digit;
        str++;
    }

    if (error) *error = 0;

    // Convert back to signed, checking for INT64_MIN special case
    if (is_negative) {
        if (abs_result > (uint64_t)-(min)) {
            if (error) *error = ERANGE;
            return min;
        }
        return -(int64_t)abs_result;
    }
    return abs_result;
}

int8_t strntoi8_r(const char *str, size_t len, int base, int *error) {
    return (int8_t)strntoint_r(str, len, base, 1, true, error);
}

uint8_t strntou8_r(const char *str, size_t len, int base, int *error) {
    return (uint8_t)strntoint_r(str, len, base, 1, false, error);
}

int16_t strntoi16_r(const char *str, size_t len, int base, int *error) {
    return (int16_t)strntoint_r(str, len, base, 2, true, error);
}

uint16_t strntou16_r(const char *str, size_t len, int base, int *error) {
    return (uint16_t)strntoint_r(str, len, base, 2, false, error);
}

int32_t strntoi32_r(const char *str, size_t len, int base, int *error) {
    return (int32_t)strntoint_r(str, len, base, 4, true, error);
}

uint32_t strntou32_r(const char *str, size_t len, int base, int *error) {
    return (uint32_t)strntoint_r(str, len, base, 4, false, error);
}

int64_t strntoi64_r(const char *str, size_t len, int base, int *error) {
    return strntoint_r(str, len, base, 8, true, error);
}

uint64_t strntou64_r(const char *str, size_t len, int base, int *error) {
    return (uint64_t)strntoint_r(str, len, base, 8, false, error);
}
