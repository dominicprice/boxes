////////////////////////////////////////////////////////////
// Copyright 2018 Dominic Price
//
// Permission is hereby granted, free of charge, to any
// person obtaining a copy of this software and associated
// documentation files(the "Software"), to deal in the
// Software without restriction, including without
// limitation the rights to use, copy, modify, merge,
// publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software
// is furnished to do so, subject to the following
// conditions :
//
// The above copyright notice and this permission notice 
// shall be included in all copies or substantial portions
// of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF 
// ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
// CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
////////////////////////////////////////////////////////////

#ifndef DOM_CARDS_HPP
#define DOM_CARDS_HPP


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <exception>
#include <string>

////////////////////////////////////////////////////////////
// Macros
////////////////////////////////////////////////////////////

// These macros allow preprocessor macros to emulate overloading by number of arguments
#define DOM_EXPAND_(X) X
#define DOM_PP_NARG_(...) DOM_EXPAND_( DOM_PP_NARG__(__VA_ARGS__, DOM_PP_RSEQ_N_()) )
#define DOM_PP_NARG__(...) DOM_EXPAND_( DOM_PP_ARG_N_(__VA_ARGS__) )
#define DOM_PP_ARG_N_(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, N, ...) N
#define DOM_PP_RSEQ_N_() 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

// Specialised macros to create a suit class for between 1 and 10 values
#define DOM_CREATE_SUIT_3(name, _1A, _1B) class name { public: name() = delete; enum class suit_t : char { _1A }; static const suit_t _1A = suit_t::_1A; static const char n = 1;      static const char* to_string(suit_t suit) { static const char* names[] = { #_1A }; return names[static_cast<int>(suit)]; } static char to_char(suit_t suit) { static const char names[] = { _1B }; return names[static_cast<int>(suit)]; } };
#define DOM_CREATE_SUIT_5(name, _1A, _1B, _2A, _2B) class name { public: name() = delete; enum class suit_t : char { _1A, _2A }; static const suit_t _1A = suit_t::_1A;static const suit_t _2A = suit_t::_2A; static const char n = 2; static const char* to_string(suit_t suit) { static const char* names[] = { #_1A, #_2A }; return names[static_cast<int>(suit)]; } static char to_char(suit_t suit) { static const char names[] = { _1B, _2B }; return names[static_cast<int>(suit)]; } };
#define DOM_CREATE_SUIT_7(name, _1A, _1B, _2A, _2B, _3A, _3B) class name { public: name() = delete; enum class suit_t : char { _1A, _2A, _3A }; static const suit_t _1A = suit_t::_1A;static const suit_t _2A = suit_t::_2A;static const suit_t _3A = suit_t::_3A; static const char n = 3;    static const char* to_string(suit_t suit) { static const char* names[] = { #_1A, #_2A, #_3A }; return names[static_cast<int>(suit)]; } static char to_char(suit_t suit) { static const char names[] = { _1B, _2B, _3B }; return names[static_cast<int>(suit)]; } };
#define DOM_CREATE_SUIT_9(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B) class name { public: name() = delete; enum class suit_t : char { _1A, _2A, _3A, _4A }; static const suit_t _1A = suit_t::_1A;static const suit_t _2A = suit_t::_2A;static const suit_t _3A = suit_t::_3A;static const suit_t _4A = suit_t::_4A; static const char n = 4;   static const char* to_string(suit_t suit) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A }; return names[static_cast<int>(suit)]; } static char to_char(suit_t suit) { static const char names[] = { _1B, _2B, _3B, _4B }; return names[static_cast<int>(suit)]; } };
#define DOM_CREATE_SUIT_11(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B) class name { public: name() = delete; enum class suit_t : char { _1A, _2A, _3A, _4A, _5A }; static const suit_t _1A = suit_t::_1A;static const suit_t _2A = suit_t::_2A;static const suit_t _3A = suit_t::_3A;static const suit_t _4A = suit_t::_4A;static const suit_t _5A = suit_t::_5A; static const char n = 5; static const char* to_string(suit_t suit) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A }; return names[static_cast<int>(suit)]; } static char to_char(suit_t suit) { static const char names[] = { _1B, _2B, _3B, _4B, _5B }; return names[static_cast<int>(suit)]; } };
#define DOM_CREATE_SUIT_13(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B) class name { public: name() = delete; enum class suit_t : char { _1A, _2A, _3A, _4A, _5A, _6A }; static const suit_t _1A = suit_t::_1A;static const suit_t _2A = suit_t::_2A;static const suit_t _3A = suit_t::_3A;static const suit_t _4A = suit_t::_4A;static const suit_t _5A = suit_t::_5A;static const suit_t _6A = suit_t::_6A; static const char n = 6;    static const char* to_string(suit_t suit) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A }; return names[static_cast<int>(suit)]; } static char to_char(suit_t suit) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B }; return names[static_cast<int>(suit)]; } };
#define DOM_CREATE_SUIT_15(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B) class name { public: name() = delete; enum class suit_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A }; static const suit_t _1A = suit_t::_1A;static const suit_t _2A = suit_t::_2A;static const suit_t _3A = suit_t::_3A;static const suit_t _4A = suit_t::_4A;static const suit_t _5A = suit_t::_5A;static const suit_t _6A = suit_t::_6A;static const suit_t _7A = suit_t::_7A; static const char n = 7;       static const char* to_string(suit_t suit) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A }; return names[static_cast<int>(suit)]; } static char to_char(suit_t suit) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B }; return names[static_cast<int>(suit)]; } };
#define DOM_CREATE_SUIT_17(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B) class name { public: name() = delete; enum class suit_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A }; static const suit_t _1A = suit_t::_1A;static const suit_t _2A = suit_t::_2A;static const suit_t _3A = suit_t::_3A;static const suit_t _4A = suit_t::_4A;static const suit_t _5A = suit_t::_5A;static const suit_t _6A = suit_t::_6A;static const suit_t _7A = suit_t::_7A;static const suit_t _8A = suit_t::_8A; static const char n = 8;  static const char* to_string(suit_t suit) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A }; return names[static_cast<int>(suit)]; } static char to_char(suit_t suit) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B }; return names[static_cast<int>(suit)]; } };
#define DOM_CREATE_SUIT_19(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B) class name { public: name() = delete; enum class suit_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A }; static const suit_t _1A = suit_t::_1A;static const suit_t _2A = suit_t::_2A;static const suit_t _3A = suit_t::_3A;static const suit_t _4A = suit_t::_4A;static const suit_t _5A = suit_t::_5A;static const suit_t _6A = suit_t::_6A;static const suit_t _7A = suit_t::_7A;static const suit_t _8A = suit_t::_8A;static const suit_t _9A = suit_t::_9A; static const char n = 9;     static const char* to_string(suit_t suit) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A }; return names[static_cast<int>(suit)]; } static char to_char(suit_t suit) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B }; return names[static_cast<int>(suit)]; } };
#define DOM_CREATE_SUIT_21(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B) class name { public: name() = delete; enum class suit_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A }; static const suit_t _1A = suit_t::_1A;static const suit_t _2A = suit_t::_2A;static const suit_t _3A = suit_t::_3A;static const suit_t _4A = suit_t::_4A;static const suit_t _5A = suit_t::_5A;static const suit_t _6A = suit_t::_6A;static const suit_t _7A = suit_t::_7A;static const suit_t _8A = suit_t::_8A;static const suit_t _9A = suit_t::_9A;static const suit_t _10A = suit_t::_10A; static const char n = 10;  static const char* to_string(suit_t suit) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A }; return names[static_cast<int>(suit)]; } static char to_char(suit_t suit) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B }; return names[static_cast<int>(suit)]; } };
// Call correct macro depending on number of arguments
#define DOM_CREATE_SUIT_(N) DOM_CREATE_SUIT_##N
#define DOM_CREATE_SUIT_EVAL(N) DOM_CREATE_SUIT_(N)

// Specialised macros to create a value class for between 1 and 30 values
#define DOM_CREATE_VALUE_3(name, _1A, _1B) class name { public: name() = delete; enum class value_t : char { _1A }; static const value_t _1A = value_t::_1A; static const char n = 1;  static const char* to_string(value_t value) { static const char* names[] = { #_1A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_5(name, _1A, _1B, _2A, _2B) class name { public: name() = delete; enum class value_t : char { _1A, _2A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A; static const char n = 2;static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_7(name, _1A, _1B, _2A, _2B, _3A, _3B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A; static const char n = 3;    static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_9(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A; static const char n = 4;     static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_11(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A; static const char n = 5;     static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_13(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A; static const char n = 6;  static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_15(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A; static const char n = 7;       static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_17(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A; static const char n = 8;        static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_19(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A; static const char n = 9; static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_21(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A; static const char n = 10;    static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_23(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A; static const char n = 11;        static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_25(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B, _12A, _12B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A, _12A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A;static const value_t _12A = value_t::_12A; static const char n = 12;    static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A, #_12A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B, _12B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_27(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B, _12A, _12B, _13A, _13B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A, _12A, _13A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A;static const value_t _12A = value_t::_12A;static const value_t _13A = value_t::_13A; static const char n = 13;        static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A, #_12A, #_13A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B, _12B, _13B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_29(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B, _12A, _12B, _13A, _13B, _14A, _14B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A, _12A, _13A, _14A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A;static const value_t _12A = value_t::_12A;static const value_t _13A = value_t::_13A;static const value_t _14A = value_t::_14A; static const char n = 14;    static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A, #_12A, #_13A, #_14A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B, _12B, _13B, _14B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_31(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B, _12A, _12B, _13A, _13B, _14A, _14B, _15A, _15B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A, _12A, _13A, _14A, _15A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A;static const value_t _12A = value_t::_12A;static const value_t _13A = value_t::_13A;static const value_t _14A = value_t::_14A;static const value_t _15A = value_t::_15A; static const char n = 15;        static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A, #_12A, #_13A, #_14A, #_15A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B, _12B, _13B, _14B, _15B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_33(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B, _12A, _12B, _13A, _13B, _14A, _14B, _15A, _15B, _16A, _16B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A, _12A, _13A, _14A, _15A, _16A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A;static const value_t _12A = value_t::_12A;static const value_t _13A = value_t::_13A;static const value_t _14A = value_t::_14A;static const value_t _15A = value_t::_15A;static const value_t _16A = value_t::_16A; static const char n = 16;    static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A, #_12A, #_13A, #_14A, #_15A, #_16A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B, _12B, _13B, _14B, _15B, _16B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_35(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B, _12A, _12B, _13A, _13B, _14A, _14B, _15A, _15B, _16A, _16B, _17A, _17B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A, _12A, _13A, _14A, _15A, _16A, _17A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A;static const value_t _12A = value_t::_12A;static const value_t _13A = value_t::_13A;static const value_t _14A = value_t::_14A;static const value_t _15A = value_t::_15A;static const value_t _16A = value_t::_16A;static const value_t _17A = value_t::_17A; static const char n = 17;        static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A, #_12A, #_13A, #_14A, #_15A, #_16A, #_17A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B, _12B, _13B, _14B, _15B, _16B, _17B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_37(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B, _12A, _12B, _13A, _13B, _14A, _14B, _15A, _15B, _16A, _16B, _17A, _17B, _18A, _18B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A, _12A, _13A, _14A, _15A, _16A, _17A, _18A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A;static const value_t _12A = value_t::_12A;static const value_t _13A = value_t::_13A;static const value_t _14A = value_t::_14A;static const value_t _15A = value_t::_15A;static const value_t _16A = value_t::_16A;static const value_t _17A = value_t::_17A;static const value_t _18A = value_t::_18A; static const char n = 18;    static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A, #_12A, #_13A, #_14A, #_15A, #_16A, #_17A, #_18A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B, _12B, _13B, _14B, _15B, _16B, _17B, _18B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_39(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B, _12A, _12B, _13A, _13B, _14A, _14B, _15A, _15B, _16A, _16B, _17A, _17B, _18A, _18B, _19A, _19B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A, _12A, _13A, _14A, _15A, _16A, _17A, _18A, _19A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A;static const value_t _12A = value_t::_12A;static const value_t _13A = value_t::_13A;static const value_t _14A = value_t::_14A;static const value_t _15A = value_t::_15A;static const value_t _16A = value_t::_16A;static const value_t _17A = value_t::_17A;static const value_t _18A = value_t::_18A;static const value_t _19A = value_t::_19A; static const char n = 19;        static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A, #_12A, #_13A, #_14A, #_15A, #_16A, #_17A, #_18A, #_19A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B, _12B, _13B, _14B, _15B, _16B, _17B, _18B, _19B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_41(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B, _12A, _12B, _13A, _13B, _14A, _14B, _15A, _15B, _16A, _16B, _17A, _17B, _18A, _18B, _19A, _19B, _20A, _20B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A, _12A, _13A, _14A, _15A, _16A, _17A, _18A, _19A, _20A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A;static const value_t _12A = value_t::_12A;static const value_t _13A = value_t::_13A;static const value_t _14A = value_t::_14A;static const value_t _15A = value_t::_15A;static const value_t _16A = value_t::_16A;static const value_t _17A = value_t::_17A;static const value_t _18A = value_t::_18A;static const value_t _19A = value_t::_19A;static const value_t _20A = value_t::_20A; static const char n = 20;    static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A, #_12A, #_13A, #_14A, #_15A, #_16A, #_17A, #_18A, #_19A, #_20A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B, _12B, _13B, _14B, _15B, _16B, _17B, _18B, _19B, _20B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_43(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B, _12A, _12B, _13A, _13B, _14A, _14B, _15A, _15B, _16A, _16B, _17A, _17B, _18A, _18B, _19A, _19B, _20A, _20B, _21A, _21B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A, _12A, _13A, _14A, _15A, _16A, _17A, _18A, _19A, _20A, _21A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A;static const value_t _12A = value_t::_12A;static const value_t _13A = value_t::_13A;static const value_t _14A = value_t::_14A;static const value_t _15A = value_t::_15A;static const value_t _16A = value_t::_16A;static const value_t _17A = value_t::_17A;static const value_t _18A = value_t::_18A;static const value_t _19A = value_t::_19A;static const value_t _20A = value_t::_20A;static const value_t _21A = value_t::_21A; static const char n = 21;        static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A, #_12A, #_13A, #_14A, #_15A, #_16A, #_17A, #_18A, #_19A, #_20A, #_21A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B, _12B, _13B, _14B, _15B, _16B, _17B, _18B, _19B, _20B, _21B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_45(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B, _12A, _12B, _13A, _13B, _14A, _14B, _15A, _15B, _16A, _16B, _17A, _17B, _18A, _18B, _19A, _19B, _20A, _20B, _21A, _21B, _22A, _22B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A, _12A, _13A, _14A, _15A, _16A, _17A, _18A, _19A, _20A, _21A, _22A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A;static const value_t _12A = value_t::_12A;static const value_t _13A = value_t::_13A;static const value_t _14A = value_t::_14A;static const value_t _15A = value_t::_15A;static const value_t _16A = value_t::_16A;static const value_t _17A = value_t::_17A;static const value_t _18A = value_t::_18A;static const value_t _19A = value_t::_19A;static const value_t _20A = value_t::_20A;static const value_t _21A = value_t::_21A;static const value_t _22A = value_t::_22A; static const char n = 22;    static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A, #_12A, #_13A, #_14A, #_15A, #_16A, #_17A, #_18A, #_19A, #_20A, #_21A, #_22A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B, _12B, _13B, _14B, _15B, _16B, _17B, _18B, _19B, _20B, _21B, _22B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_47(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B, _12A, _12B, _13A, _13B, _14A, _14B, _15A, _15B, _16A, _16B, _17A, _17B, _18A, _18B, _19A, _19B, _20A, _20B, _21A, _21B, _22A, _22B, _23A, _23B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A, _12A, _13A, _14A, _15A, _16A, _17A, _18A, _19A, _20A, _21A, _22A, _23A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A;static const value_t _12A = value_t::_12A;static const value_t _13A = value_t::_13A;static const value_t _14A = value_t::_14A;static const value_t _15A = value_t::_15A;static const value_t _16A = value_t::_16A;static const value_t _17A = value_t::_17A;static const value_t _18A = value_t::_18A;static const value_t _19A = value_t::_19A;static const value_t _20A = value_t::_20A;static const value_t _21A = value_t::_21A;static const value_t _22A = value_t::_22A;static const value_t _23A = value_t::_23A; static const char n = 23;        static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A, #_12A, #_13A, #_14A, #_15A, #_16A, #_17A, #_18A, #_19A, #_20A, #_21A, #_22A, #_23A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B, _12B, _13B, _14B, _15B, _16B, _17B, _18B, _19B, _20B, _21B, _22B, _23B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_49(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B, _12A, _12B, _13A, _13B, _14A, _14B, _15A, _15B, _16A, _16B, _17A, _17B, _18A, _18B, _19A, _19B, _20A, _20B, _21A, _21B, _22A, _22B, _23A, _23B, _24A, _24B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A, _12A, _13A, _14A, _15A, _16A, _17A, _18A, _19A, _20A, _21A, _22A, _23A, _24A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A;static const value_t _12A = value_t::_12A;static const value_t _13A = value_t::_13A;static const value_t _14A = value_t::_14A;static const value_t _15A = value_t::_15A;static const value_t _16A = value_t::_16A;static const value_t _17A = value_t::_17A;static const value_t _18A = value_t::_18A;static const value_t _19A = value_t::_19A;static const value_t _20A = value_t::_20A;static const value_t _21A = value_t::_21A;static const value_t _22A = value_t::_22A;static const value_t _23A = value_t::_23A;static const value_t _24A = value_t::_24A; static const char n = 24;    static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A, #_12A, #_13A, #_14A, #_15A, #_16A, #_17A, #_18A, #_19A, #_20A, #_21A, #_22A, #_23A, #_24A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B, _12B, _13B, _14B, _15B, _16B, _17B, _18B, _19B, _20B, _21B, _22B, _23B, _24B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_51(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B, _12A, _12B, _13A, _13B, _14A, _14B, _15A, _15B, _16A, _16B, _17A, _17B, _18A, _18B, _19A, _19B, _20A, _20B, _21A, _21B, _22A, _22B, _23A, _23B, _24A, _24B, _25A, _25B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A, _12A, _13A, _14A, _15A, _16A, _17A, _18A, _19A, _20A, _21A, _22A, _23A, _24A, _25A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A;static const value_t _12A = value_t::_12A;static const value_t _13A = value_t::_13A;static const value_t _14A = value_t::_14A;static const value_t _15A = value_t::_15A;static const value_t _16A = value_t::_16A;static const value_t _17A = value_t::_17A;static const value_t _18A = value_t::_18A;static const value_t _19A = value_t::_19A;static const value_t _20A = value_t::_20A;static const value_t _21A = value_t::_21A;static const value_t _22A = value_t::_22A;static const value_t _23A = value_t::_23A;static const value_t _24A = value_t::_24A;static const value_t _25A = value_t::_25A; static const char n = 25;        static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A, #_12A, #_13A, #_14A, #_15A, #_16A, #_17A, #_18A, #_19A, #_20A, #_21A, #_22A, #_23A, #_24A, #_25A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B, _12B, _13B, _14B, _15B, _16B, _17B, _18B, _19B, _20B, _21B, _22B, _23B, _24B, _25B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_53(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B, _12A, _12B, _13A, _13B, _14A, _14B, _15A, _15B, _16A, _16B, _17A, _17B, _18A, _18B, _19A, _19B, _20A, _20B, _21A, _21B, _22A, _22B, _23A, _23B, _24A, _24B, _25A, _25B, _26A, _26B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A, _12A, _13A, _14A, _15A, _16A, _17A, _18A, _19A, _20A, _21A, _22A, _23A, _24A, _25A, _26A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A;static const value_t _12A = value_t::_12A;static const value_t _13A = value_t::_13A;static const value_t _14A = value_t::_14A;static const value_t _15A = value_t::_15A;static const value_t _16A = value_t::_16A;static const value_t _17A = value_t::_17A;static const value_t _18A = value_t::_18A;static const value_t _19A = value_t::_19A;static const value_t _20A = value_t::_20A;static const value_t _21A = value_t::_21A;static const value_t _22A = value_t::_22A;static const value_t _23A = value_t::_23A;static const value_t _24A = value_t::_24A;static const value_t _25A = value_t::_25A;static const value_t _26A = value_t::_26A; static const char n = 26;    static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A, #_12A, #_13A, #_14A, #_15A, #_16A, #_17A, #_18A, #_19A, #_20A, #_21A, #_22A, #_23A, #_24A, #_25A, #_26A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B, _12B, _13B, _14B, _15B, _16B, _17B, _18B, _19B, _20B, _21B, _22B, _23B, _24B, _25B, _26B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_55(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B, _12A, _12B, _13A, _13B, _14A, _14B, _15A, _15B, _16A, _16B, _17A, _17B, _18A, _18B, _19A, _19B, _20A, _20B, _21A, _21B, _22A, _22B, _23A, _23B, _24A, _24B, _25A, _25B, _26A, _26B, _27A, _27B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A, _12A, _13A, _14A, _15A, _16A, _17A, _18A, _19A, _20A, _21A, _22A, _23A, _24A, _25A, _26A, _27A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A;static const value_t _12A = value_t::_12A;static const value_t _13A = value_t::_13A;static const value_t _14A = value_t::_14A;static const value_t _15A = value_t::_15A;static const value_t _16A = value_t::_16A;static const value_t _17A = value_t::_17A;static const value_t _18A = value_t::_18A;static const value_t _19A = value_t::_19A;static const value_t _20A = value_t::_20A;static const value_t _21A = value_t::_21A;static const value_t _22A = value_t::_22A;static const value_t _23A = value_t::_23A;static const value_t _24A = value_t::_24A;static const value_t _25A = value_t::_25A;static const value_t _26A = value_t::_26A;static const value_t _27A = value_t::_27A; static const char n = 27;        static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A, #_12A, #_13A, #_14A, #_15A, #_16A, #_17A, #_18A, #_19A, #_20A, #_21A, #_22A, #_23A, #_24A, #_25A, #_26A, #_27A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B, _12B, _13B, _14B, _15B, _16B, _17B, _18B, _19B, _20B, _21B, _22B, _23B, _24B, _25B, _26B, _27B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_57(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B, _12A, _12B, _13A, _13B, _14A, _14B, _15A, _15B, _16A, _16B, _17A, _17B, _18A, _18B, _19A, _19B, _20A, _20B, _21A, _21B, _22A, _22B, _23A, _23B, _24A, _24B, _25A, _25B, _26A, _26B, _27A, _27B, _28A, _28B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A, _12A, _13A, _14A, _15A, _16A, _17A, _18A, _19A, _20A, _21A, _22A, _23A, _24A, _25A, _26A, _27A, _28A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A;static const value_t _12A = value_t::_12A;static const value_t _13A = value_t::_13A;static const value_t _14A = value_t::_14A;static const value_t _15A = value_t::_15A;static const value_t _16A = value_t::_16A;static const value_t _17A = value_t::_17A;static const value_t _18A = value_t::_18A;static const value_t _19A = value_t::_19A;static const value_t _20A = value_t::_20A;static const value_t _21A = value_t::_21A;static const value_t _22A = value_t::_22A;static const value_t _23A = value_t::_23A;static const value_t _24A = value_t::_24A;static const value_t _25A = value_t::_25A;static const value_t _26A = value_t::_26A;static const value_t _27A = value_t::_27A;static const value_t _28A = value_t::_28A; static const char n = 28;    static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A, #_12A, #_13A, #_14A, #_15A, #_16A, #_17A, #_18A, #_19A, #_20A, #_21A, #_22A, #_23A, #_24A, #_25A, #_26A, #_27A, #_28A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B, _12B, _13B, _14B, _15B, _16B, _17B, _18B, _19B, _20B, _21B, _22B, _23B, _24B, _25B, _26B, _27B, _28B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_59(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B, _12A, _12B, _13A, _13B, _14A, _14B, _15A, _15B, _16A, _16B, _17A, _17B, _18A, _18B, _19A, _19B, _20A, _20B, _21A, _21B, _22A, _22B, _23A, _23B, _24A, _24B, _25A, _25B, _26A, _26B, _27A, _27B, _28A, _28B, _29A, _29B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A, _12A, _13A, _14A, _15A, _16A, _17A, _18A, _19A, _20A, _21A, _22A, _23A, _24A, _25A, _26A, _27A, _28A, _29A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A;static const value_t _12A = value_t::_12A;static const value_t _13A = value_t::_13A;static const value_t _14A = value_t::_14A;static const value_t _15A = value_t::_15A;static const value_t _16A = value_t::_16A;static const value_t _17A = value_t::_17A;static const value_t _18A = value_t::_18A;static const value_t _19A = value_t::_19A;static const value_t _20A = value_t::_20A;static const value_t _21A = value_t::_21A;static const value_t _22A = value_t::_22A;static const value_t _23A = value_t::_23A;static const value_t _24A = value_t::_24A;static const value_t _25A = value_t::_25A;static const value_t _26A = value_t::_26A;static const value_t _27A = value_t::_27A;static const value_t _28A = value_t::_28A;static const value_t _29A = value_t::_29A; static const char n = 29;        static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A, #_12A, #_13A, #_14A, #_15A, #_16A, #_17A, #_18A, #_19A, #_20A, #_21A, #_22A, #_23A, #_24A, #_25A, #_26A, #_27A, #_28A, #_29A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B, _12B, _13B, _14B, _15B, _16B, _17B, _18B, _19B, _20B, _21B, _22B, _23B, _24B, _25B, _26B, _27B, _28B, _29B }; return names[static_cast<int>(value)]; } };
#define DOM_CREATE_VALUE_61(name, _1A, _1B, _2A, _2B, _3A, _3B, _4A, _4B, _5A, _5B, _6A, _6B, _7A, _7B, _8A, _8B, _9A, _9B, _10A, _10B, _11A, _11B, _12A, _12B, _13A, _13B, _14A, _14B, _15A, _15B, _16A, _16B, _17A, _17B, _18A, _18B, _19A, _19B, _20A, _20B, _21A, _21B, _22A, _22B, _23A, _23B, _24A, _24B, _25A, _25B, _26A, _26B, _27A, _27B, _28A, _28B, _29A, _29B, _30A, _30B) class name { public: name() = delete; enum class value_t : char { _1A, _2A, _3A, _4A, _5A, _6A, _7A, _8A, _9A, _10A, _11A, _12A, _13A, _14A, _15A, _16A, _17A, _18A, _19A, _20A, _21A, _22A, _23A, _24A, _25A, _26A, _27A, _28A, _29A, _30A }; static const value_t _1A = value_t::_1A;static const value_t _2A = value_t::_2A;static const value_t _3A = value_t::_3A;static const value_t _4A = value_t::_4A;static const value_t _5A = value_t::_5A;static const value_t _6A = value_t::_6A;static const value_t _7A = value_t::_7A;static const value_t _8A = value_t::_8A;static const value_t _9A = value_t::_9A;static const value_t _10A = value_t::_10A;static const value_t _11A = value_t::_11A;static const value_t _12A = value_t::_12A;static const value_t _13A = value_t::_13A;static const value_t _14A = value_t::_14A;static const value_t _15A = value_t::_15A;static const value_t _16A = value_t::_16A;static const value_t _17A = value_t::_17A;static const value_t _18A = value_t::_18A;static const value_t _19A = value_t::_19A;static const value_t _20A = value_t::_20A;static const value_t _21A = value_t::_21A;static const value_t _22A = value_t::_22A;static const value_t _23A = value_t::_23A;static const value_t _24A = value_t::_24A;static const value_t _25A = value_t::_25A;static const value_t _26A = value_t::_26A;static const value_t _27A = value_t::_27A;static const value_t _28A = value_t::_28A;static const value_t _29A = value_t::_29A;static const value_t _30A = value_t::_30A; static const char n = 30;    static const char* to_string(value_t value) { static const char* names[] = { #_1A, #_2A, #_3A, #_4A, #_5A, #_6A, #_7A, #_8A, #_9A, #_10A, #_11A, #_12A, #_13A, #_14A, #_15A, #_16A, #_17A, #_18A, #_19A, #_20A, #_21A, #_22A, #_23A, #_24A, #_25A, #_26A, #_27A, #_28A, #_29A, #_30A }; return names[static_cast<int>(value)]; } static char to_char(value_t value) { static const char names[] = { _1B, _2B, _3B, _4B, _5B, _6B, _7B, _8B, _9B, _10B, _11B, _12B, _13B, _14B, _15B, _16B, _17B, _18B, _19B, _20B, _21B, _22B, _23B, _24B, _25B, _26B, _27B, _28B, _29B, _30B }; return names[static_cast<int>(value)]; } };
// Call correct macro depending on number of arguments
#define DOM_CREATE_VALUE_(N) DOM_CREATE_VALUE_##N
#define DOM_CREATE_VALUE_EVAL(N) DOM_CREATE_VALUE_(N)

////////////////////////////////////////////////////////////
/// \brief Create a suit class which can be used as a 
///        template paramater to initialize a Deck class
///
/// Supports up to 10 suits. Suits are entered by their 
/// long name, unquoted, followed by their single character
/// shortform enclosed in single quotes.
///
/// Example usage:
///   DOM_CREATE_SUIT(ExampleSuit,
///     Suit1, '1',
///     Suit2, '2',
///     Suit3, '3'
///   )
///
////////////////////////////////////////////////////////////
#define DOM_CREATE_SUIT( ... ) DOM_EXPAND_( DOM_CREATE_SUIT_EVAL(DOM_EXPAND_( DOM_PP_NARG_(__VA_ARGS__) ))(__VA_ARGS__) )

////////////////////////////////////////////////////////////
/// \brief Create a value class which can be used as a 
///        template paramater to initialize a Deck class
///
/// Supports up to 30 values. Values are entered by their 
/// long name, unquoted, followed by their single character
/// shortform enclosed in single quotes.
///
/// Example usage:
///   DOM_CREATE_VALUE(ExampleValue,
///     Value1, '1',
///     Value2, '2',
///     Value3, '3'
///   )
///
////////////////////////////////////////////////////////////
#define DOM_CREATE_VALUE( ... ) DOM_EXPAND_( DOM_CREATE_VALUE_EVAL(DOM_EXPAND_( DOM_PP_NARG_(__VA_ARGS__) ))(__VA_ARGS__) )

namespace dom
{
	////////////////////////////////////////////////////////////
	/// \brief Generic exception class for throwing
	///        exceptions due to logic errors 
	///
	////////////////////////////////////////////////////////////
	class CardError : public std::exception
	{
	public:
		CardError(std::string message) : message(message) {}
		std::string what() { return message; }
	private:
		std::string message;
	};

	namespace decks
	{
		////////////////////////////////////////////////////////////
		/// \brief The standard french suits (Clubs, Diamonds, 
		///        Hearts and spades)
		///
		////////////////////////////////////////////////////////////
		DOM_CREATE_SUIT(Suits_French,
			Clubs,	  'C',
			Diamonds, 'D',
			Hearts,   'H',
			Spades,   'S'
		)

		////////////////////////////////////////////////////////////
		/// \brief The standard french card value (2-A) with
		///        the ace higher than all other values
		///
		////////////////////////////////////////////////////////////
		DOM_CREATE_VALUE(Values_French_High,
			Two,      '2',
			Three,    '3',
			Four,     '4',
			Five,     '5',
			Six,      '6',
			Seven,    '7',
			Eight,    '8',
			Nine,     '9',
			Ten,      'T',
			Jack,     'J',
			Queen,    'Q',
			King,     'K',
			Ace,      'A'
		)

		////////////////////////////////////////////////////////////
		/// \brief The standard french card value (A-K) with
		///        the ace lower than all other values
		///
		////////////////////////////////////////////////////////////
		DOM_CREATE_VALUE(Values_French_Low,
			Ace,      'A',
			Two,      '2',
			Three,    '3',
			Four,     '4',
			Five,     '5',
			Six,      '6',
			Seven,    '7',
			Eight,    '8',
			Nine,     '9',
			Ten,      '10',
			Jack,     'J',
			Queen,    'Q',
			King,     'K'
		)

		////////////////////////////////////////////////////////////
		/// \brief The standard italian suits (Bastoni, Denari, 
		///        Coppe and Spade)
		///
		////////////////////////////////////////////////////////////
		DOM_CREATE_SUIT(Suits_Italian,
			Bastoni,  'B',
			Denari,   'D',
			Coppe,    'C',
			Spade,    'S'
		)

		////////////////////////////////////////////////////////////
		/// \brief The standard italian values (A-R)
		///
		////////////////////////////////////////////////////////////
		DOM_CREATE_VALUE(Values_Italian,
			Ace,      'A',
			Two,      '2',
			Three,    '3',
			Four,     '4',
			Five,     '5',
			Six,      '6',
			Seven,    '7',
			Fante,    'F',
			Cavallo,  'C',
			Re,       'R'
		)

		////////////////////////////////////////////////////////////
		/// \brief The standard german suits (Eichel, Laub, 
		///        Herz and Schelle)
		///
		////////////////////////////////////////////////////////////
		DOM_CREATE_SUIT(Suits_German,
			Eichel,   'E',
			Laub,     'L',
			Herz,     'H',
			Schelle,  'S'
		)

		////////////////////////////////////////////////////////////
		/// \brief The standard south german values (6-A)
		///
		////////////////////////////////////////////////////////////
		DOM_CREATE_VALUE(Values_German_South,
			Six,      '6',
			Seven,    '7',
			Eight,    '8',
			Nine,     '9',
			Ten,      'T',
			Unter,    'U',
			Ober,     'O',
			Konig,    'K',
			Ass,      'A'
		)

		////////////////////////////////////////////////////////////
		/// \brief The standard north german values (7-A)
		///
		////////////////////////////////////////////////////////////
		DOM_CREATE_VALUE(Values_German_North,
			Seven, '7',
			Eight, '8',
			Nine, '9',
			Ten, 'T',
			Unter, 'U',
			Ober, 'O',
			Konig, 'K',
			Ass, 'A'
		)

	} // namespace decks

	////////////////////////////////////////////////////////////
	/// \brief Encapsulates the idea of a deck of cards. 
	///
	/// Provides the suit_t and value_t types for the deck, as
	/// well as a means of 
	///
	////////////////////////////////////////////////////////////
	template <typename Suit, typename Value>
	class Deck_t
	{
	public:
		Deck_t() = delete;
		using suit_t = typename Suit::suit_t;
		using value_t = typename Value::value_t;
		using Suits = Suit;
		using Values = Value;
	};

	template <typename Deck>
	class PlayingCard_t
	{
	public:
		using suit_t = typename Deck::suit_t;
		using value_t = typename Deck::value_t;
		PlayingCard_t() {}
		PlayingCard_t(suit_t suit, value_t value) : suit(suit), value(value) {}
		PlayingCard_t(char suit_, char value_)
		{
			bool found_suit = false;
			for (int i = 0; i < Deck::Suits::n; ++i) {
				if (Deck::Suits::to_char(static_cast<suit_t>(i)) == suit_) {
					suit = static_cast<suit_t>(i);
					found_suit = true;
					break;
				}
			}

			bool found_value = false;
			for (int i = 0; i < Deck::Values::n; ++i) {
				if (Deck::Values::to_char(static_cast<value_t>(i)) == value_) {
					value = static_cast<value_t>(i);
					found_value = true;
					break;
				}
			}
			if (!found_value || !found_suit) {
				throw CardError("Could not create card from given suit and value");
			}
		}
		PlayingCard_t(const char* name) : PlayingCard_t(name[1], name[0]) {}
		suit_t suit;
		value_t value;
		const char* name() const { name_[0] = Deck::Values::to_char(value); name_[1] = Deck::Suits::to_char(suit); name_[2] = '\0'; return name_; }
		bool operator == (const PlayingCard_t other) const { return suit == other.suit && value == other.value; }
	private:
		mutable char name_[3];
	};

	template <typename Deck>
	struct sort_by_suit
	{
		bool operator () (const PlayingCard_t<Deck>& lhs, const PlayingCard_t<Deck>& rhs) const
		{
			if (lhs.suit == rhs.suit)
				return lhs.value < rhs.value;
			return lhs.suit < rhs.suit;
		}
	};

	template <typename Deck>
	struct sort_by_value
	{
		bool operator () (const PlayingCard_t<Deck>& lhs, const PlayingCard_t<Deck>& rhs) const
		{
			if (lhs.value == rhs.value)
				return lhs.suit < rhs.suit;
			return lhs.value < rhs.value;
		}
	};

	class DefaultShuffler
	{
	public:
		DefaultShuffler() : gen(std::chrono::system_clock::now().time_since_epoch().count()) {}
		template <typename It>
		void operator() (It begin, It end) const
		{
			std::shuffle(begin, end, gen);
		}
		mutable std::mt19937 gen;
	};

	template <typename Deck, typename Compare, typename Shuffler = DefaultShuffler>
	class Hand_t
	{
	public:
		using suit_t = typename Deck::suit_t;
		using value_t = typename Deck::value_t;
		using card_t = PlayingCard_t<Deck>;
		using vector_t = std::vector<card_t>;
		using iterator = typename vector_t::iterator;
		using const_iterator = typename vector_t::const_iterator;
		using size_t = typename std::size_t;
		using compare_t = Compare;

		Hand_t(unsigned int n_decks = 0) 
		{ 
			while (n_decks--) {
				for (char i = 0; i < Deck::Suits::n; ++i) {
					for (char j = 0; j < Deck::Values::n; ++j) {
						cards.push_back(card_t(static_cast<suit_t>(i), static_cast<value_t>(j)));
					}
				}
			} 
			sort();
		}
		template <typename It> Hand_t(It begin, It end) : cards(begin, end) {}
		Hand_t(const std::initializer_list<card_t>& il) : Hand_t(il.begin(), il.end()) {}
		Hand_t(const card_t& card, size_t count = 1) : cards(count, card) {}
		Hand_t(const Hand_t& other) : cards(other.cards) {}
		Hand_t& operator = (const Hand_t& other) { cards = other.cards; return *this; }

		Hand_t& operator += (const Hand_t& other) { add_n(other.begin(), other.end()); }
		bool operator == (Hand_t other) const { Hand_t cpy(*this); cpy.sort(); other.sort(); return other.cards == cpy.cards; }
		bool operator != (Hand_t other) const { return !(*this == other); }
		iterator begin() { return cards.begin(); }
		const_iterator begin() const { return cards.cbegin(); }
		iterator end() { return cards.end(); }
		const_iterator end() const { return cards.cend(); }

		size_t length() const { return cards.size(); }
		size_t size() const { return cards.size(); }
		bool empty() const { return cards.empty(); }
		Hand_t clear() { Hand_t discards(*this); cards.clear(); return discards; }

		size_t count(const card_t& card) const { return std::count(cards.begin(), cards.end(), card); }
		template <typename Pred> size_t count(Pred pred) const { return std::count_if(cards.begin(), cards.end(), pred); }
		size_t count(suit_t suit) const { return count([&suit](const card_t& card) { return card.suit == suit; }); }
		size_t count(value_t value) const { return count([&value](const card_t& card) { return card.value == value; }); }

		bool contains(const card_t& card) const { return std::find(cards.begin(), cards.end(), card) != cards.end(); }
		template <typename Pred> bool contains(Pred pred) const { return std::find_if(cards.begin(), cards.end(), pred) != cards.end(); }
		bool contains(suit_t suit) const { return contains([&suit](const card_t& card) { return card.suit == suit; }); }
		bool contains(value_t value) const { return contains([&value](const card_t& card) { return card.value == value; }); }

		Hand_t filter(const card_t& card) const { return Hand_t(card, count(card)); }
		Hand_t filter(suit_t suit) const { Hand_t ret; for (const card_t& card : cards) if (card.suit == suit) ret.add(card); return ret; }
		Hand_t filter(value_t value) const { Hand_t ret; for (const card_t& card : cards) if (card.value == value) ret.add(card); return ret; }

		Hand_t sort() { std::sort(cards.begin(), cards.end(), compare_t()); return *this; }
		template <typename Comp> Hand_t sort_by() { std::sort(cards.begin(), cards.end(), Comp()); return *this; }
		Hand_t shuffle() { Shuffler()(cards.begin(), cards.end()); return *this; }

		card_t examine_top() const { return cards.back(); }
		Hand_t examine_top_n(int n) const { return Hand_t(cards.end() - n, cards.end()); }
		card_t examine_bottom() const { return cards.front(); }
		Hand_t examine_bottom_n(int n) const { return Hand_t(cards.begin(), cards.begin() + n); }

		std::string to_string() const
		{
			std::string ret;
			for (const PlayingCard& card : cards) {
				ret += card.name();
				ret += " ";
			}
			return ret;
		}

		template <typename Pred>
		std::vector<Hand_t> subhands(Pred pred) const
		{
			if (cards.size() > 32)
				throw CardError("Too many cards in hand to generate all subhands, maximum size is 32");
			std::vector<Hand_t> hands;
			size_t n_subhands = pow2(cards.size());
			for (size_t i = 1; i < n_subhands; ++i) {
				Hand_t hand;
				size_t cur_index = 0, j = i;
				do {
					if (j % 2 == 1)
						hand.add(cards[cur_index]);
					++cur_index;
				} while (j >>= 1);
				if (pred(hand))
					hands.push_back(hand);
			}
			return hands;
		}

		std::vector<Hand_t> subhands() const
		{
			return subhands([](const Hand_t& hand) {return true; });
		}

		void add(const card_t& card) { cards.push_back(card); }
		void add_sorted(const card_t& card) { add(card); sort(); }
		template <typename It> void add_n(It begin, It end) { while (begin != end) add(*(begin++)); }
		void add_n(const Hand_t& other) { add_n(other.begin(), other.end()); }
		template <typename It> void add_n_sorted(It begin, It end) { add_n(begin, end); sort(); }
		void add_n_sorted(const Hand_t& other) { add_n_sorted(other.begin(), other.end()); }
		void add_unique(const card_t& card) { if (contains(card)) return; add(card); }
		void add_unique_sorted(const card_t& card) { if (!add_unique(card)) return; sort(); }
		template <typename It> void add_n_unique(It begin, It end) { while (begin != end) add_unique(*(begin++)); }
		void add_n_unique(const Hand_t& other) { add_n_unique(other.begin(), other.end()); }
		template <typename It> void add_n_unique_sorted(It begin, It end) { add_n_unique(begin, end); sort(); }
		void add_n_unique_sorted(const Hand_t& other) { add_n_unique_sorted(other.begin(), other.end()); }

		card_t remove_from_top() 
		{ 
			if (length() > 0) {
				card_t card = cards.back(); 
				cards.pop_back(); 
				return card; 
			} 
			throw CardError("Cannot remove a card from hand of zero length");
		}
		Hand_t remove_n_from_top(int n) 
		{ 
			Hand_t discards; 
			if (length() < n) { 
				discards = *this; 
				clear(); 
			} 
			else while (n-- > 0) { 
				card_t card = cards.back(); 
				cards.pop_back(); 
				discards.add(card); 
			} 
			return discards; 
		}
		card_t remove(const card_t& card) 
		{ 
			iterator position = std::find(cards.begin(), cards.end(), card); 
			if (position != cards.end()) { 
				cards.erase(position); 
				return card; } 
			throw CardError(std::string("Could not find ") + card.name() + " in this hand");
		}
		Hand_t remove_all(const card_t& card) 
		{ 
			size_t l = length();
			cards.erase(std::remove(cards.begin(), cards.end(), card), cards.end()); 
			return Hand_t(card, l - length());
		}
		template <typename It> Hand_t remove_n(It begin, It end) 
		{ 
			Hand_t other; 
			while (begin != end)
				other.add(remove(*(begin++)));
			return other; 
		}
		Hand_t remove_n(const Hand_t& hand)
		{
			return remove_n(hand.begin(), hand.end());
		}
		template <typename It> Hand_t remove_n_all(It begin, It end) 
		{ 
			Hand_t discards;
			while (begin != end) 
				discards += remove_all(*(begin++)); 
			return discards; 
		}
		Hand_t remove_n_all(const Hand_t& hand)
		{
			return remove_n_all(hand.begin(), hand.end());
		}

		void play(const card_t& card, Hand_t& to) { to.add(remove(card)); }
		template <typename It> void play_n(It begin, It end, Hand_t& to) { to.add_n(remove_n(begin, end)); }
		void play_n(const Hand_t& played_cards, Hand_t& to) { to.add_n(remove_n(played_cards)); }
		void play_from_top(Hand_t& to) { to.add(remove_from_top());  } 
		void play_n_from_top(int n, Hand_t& to) { to.add_n(remove_n_from_top(n)); }

	private:
		vector_t cards;
		size_t pow2(size_t n) const 
		{
			size_t result = 1, base = 2;
			while (n) {
				if (n & 1)
					result *= base;
				n >>= 1;
				base *= base;
			}
			return result;
		}
	};


	namespace Bridge
	{
		using suit_t = decks::Suits_French::suit_t;
		using value_t = decks::Values_French_High::value_t;
		using Deck = Deck_t<decks::Suits_French, decks::Values_French_High>;
		using PlayingCard = PlayingCard_t<Deck>;
		using Hand = Hand_t<Deck, sort_by_suit<Deck>>;
		PlayingCard operator"" _pc(const char* name) { return PlayingCard(name); }
	}

	namespace Rummy
	{
		using suit_t = decks::Suits_French::suit_t;
		using value_t = decks::Values_French_Low::value_t;
		using Deck = Deck_t<decks::Suits_French, decks::Values_French_Low>;
		using PlayingCard = PlayingCard_t<Deck>;
		using hand = Hand_t<Deck, sort_by_value<Deck>>;
		PlayingCard operator"" _pc(const char* name) { return PlayingCard(name); }
	}

	namespace Scopa
	{
		using suit_t = decks::Suits_Italian::suit_t;
		using value_t = decks::Values_Italian::value_t;
		using Deck = Deck_t<decks::Suits_Italian, decks::Values_Italian>;
		using PlayingCard = PlayingCard_t<Deck>;
		using Hand = Hand_t<Deck, sort_by_value<Deck>>;
		PlayingCard operator"" _pc(const char* name) { return PlayingCard(name); }
	}

} //namespace dom


#endif //DOM_CARDS_HPP