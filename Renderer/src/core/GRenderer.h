﻿#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Xinput.lib")
#pragma warning(disable : 4595)

#include <mutex>
#include <atomic>
#include <initializer_list>
#include <vector>
#include <map>
#include <cmath>

//#ifndef _WIN32
//#error Only Windows is Supported!
//#elif _WIN64
//#error There is no 64x support!
//#endif

//#ifdef _DEBUG
//#define EXTENDED_MEMORYTRACKING
//#define IF_EXTENDED_MEM(expression) expression
//#else
//#define IF_EXTENDED_MEM(expression)
//#endif // _DEBUG
//
/** Var print define */
#define MSVC_BUG(x, y) x y

#define VAR_PRINT(x) GGeneral::toString(#x) + " = " + GGeneral::toString(x) + ", "
#define VAR_PRINTEND(x) GGeneral::toString(#x) + " = " + GGeneral::toString(x)

#define RETURN_ARG_COUNT(_1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _10_, _11_, _12_, _13_, _14_, _15_, _16_, _17_, _18_, _19_, _20_, _21_, _22_, _23_, _24_, _25_, _26_, _27_, _28_, _29_, _30_, _31_, _32_, _33_, _34_, _35_, _36_, _37_, _38_, _39_, _40_, _41_, _42_, _43_, _44_, _45_, _46_, _47_, _48_, _49_, _50_, _51_, _52_, _53_, _54_, _55_, _56_, _57_, _58_, _59_, _60_, _61_, _62_, _63_, _64_, _65_, _66_, _67_, _68_, _69_, _70_, _71_, _72_, _73_, _74_, _75_, _76_, _77_, _78_, _79_, _80_, _81_, _82_, _83_, _84_, _85_, _86_, _87_, _88_, _89_, _90_, _91_, _92_, _93_, _94_, _95_, _96_, _97_, _98_, _99_, _100_, _101_, _102_, _103_, _104_, _105_, _106_, _107_, _108_, _109_, _110_, _111_, _112_, _113_, _114_, _115_, _116_, _117_, _118_, _119_, _120_, _121_, _122_, _123_, _124_, _125_, count, ...) count
#define EXPAND_ARGS(args) RETURN_ARG_COUNT args
#define COUNT_ARGS_MAX(...) EXPAND_ARGS((__VA_ARGS__, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0))

#define VAR_NAME1(x) VAR_PRINTEND(x)
#define VAR_NAME2(x0, x1) VAR_PRINT(x0) + VAR_NAME1(x1)
#define VAR_NAME3(x0, x1, x2) VAR_PRINT(x0) + VAR_NAME2(x1, x2)
#define VAR_NAME4(x0, x1, x2, x3) VAR_PRINT(x0) + VAR_NAME3(x1, x2, x3)
#define VAR_NAME5(x0, x1, x2, x3, x4) VAR_PRINT(x0) + VAR_NAME4(x1, x2, x3, x4)
#define VAR_NAME6(x0, x1, x2, x3, x4, x5) VAR_PRINT(x0) + VAR_NAME5(x1, x2, x3, x4, x5)
#define VAR_NAME7(x0, x1, x2, x3, x4, x5, x6) VAR_PRINT(x0) + VAR_NAME6(x1, x2, x3, x4, x5, x6)
#define VAR_NAME8(x0, x1, x2, x3, x4, x5, x6, x7) VAR_PRINT(x0) + VAR_NAME7(x1, x2, x3, x4, x5, x6, x7)
#define VAR_NAME9(x0, x1, x2, x3, x4, x5, x6, x7, x8) VAR_PRINT(x0) + VAR_NAME8(x1, x2, x3, x4, x5, x6, x7, x8)
#define VAR_NAME10(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) VAR_PRINT(x0) + VAR_NAME9(x1, x2, x3, x4, x5, x6, x7, x8, x9)
#define VAR_NAME11(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) VAR_PRINT(x0) + VAR_NAME10(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10)
#define VAR_NAME12(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) VAR_PRINT(x0) + VAR_NAME11(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11)
#define VAR_NAME13(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) VAR_PRINT(x0) + VAR_NAME12(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12)
#define VAR_NAME14(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) VAR_PRINT(x0) + VAR_NAME13(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13)
#define VAR_NAME15(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) VAR_PRINT(x0) + VAR_NAME14(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14)
#define VAR_NAME16(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) VAR_PRINT(x0) + VAR_NAME15(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15)
#define VAR_NAME17(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) VAR_PRINT(x0) + VAR_NAME16(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16)
#define VAR_NAME18(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) VAR_PRINT(x0) + VAR_NAME17(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17)
#define VAR_NAME19(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) VAR_PRINT(x0) + VAR_NAME18(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18)
#define VAR_NAME20(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) VAR_PRINT(x0) + VAR_NAME19(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19)
#define VAR_NAME21(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20) VAR_PRINT(x0) + VAR_NAME20(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20)
#define VAR_NAME22(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21) VAR_PRINT(x0) + VAR_NAME21(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21)
#define VAR_NAME23(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22) VAR_PRINT(x0) + VAR_NAME22(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22)
#define VAR_NAME24(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23) VAR_PRINT(x0) + VAR_NAME23(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23)
#define VAR_NAME25(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24) VAR_PRINT(x0) + VAR_NAME24(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24)
#define VAR_NAME26(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25) VAR_PRINT(x0) + VAR_NAME25(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25)
#define VAR_NAME27(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26) VAR_PRINT(x0) + VAR_NAME26(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26)
#define VAR_NAME28(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27) VAR_PRINT(x0) + VAR_NAME27(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27)
#define VAR_NAME29(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28) VAR_PRINT(x0) + VAR_NAME28(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28)
#define VAR_NAME30(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29) VAR_PRINT(x0) + VAR_NAME29(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29)
#define VAR_NAME31(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30) VAR_PRINT(x0) + VAR_NAME30(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30)
#define VAR_NAME32(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31) VAR_PRINT(x0) + VAR_NAME31(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31)
#define VAR_NAME33(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32) VAR_PRINT(x0) + VAR_NAME32(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32)
#define VAR_NAME34(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33) VAR_PRINT(x0) + VAR_NAME33(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33)
#define VAR_NAME35(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34) VAR_PRINT(x0) + VAR_NAME34(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34)
#define VAR_NAME36(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35) VAR_PRINT(x0) + VAR_NAME35(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35)
#define VAR_NAME37(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36) VAR_PRINT(x0) + VAR_NAME36(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36)
#define VAR_NAME38(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37) VAR_PRINT(x0) + VAR_NAME37(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37)
#define VAR_NAME39(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38) VAR_PRINT(x0) + VAR_NAME38(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38)
#define VAR_NAME40(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39) VAR_PRINT(x0) + VAR_NAME39(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39)
#define VAR_NAME41(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40) VAR_PRINT(x0) + VAR_NAME40(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40)
#define VAR_NAME42(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41) VAR_PRINT(x0) + VAR_NAME41(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41)
#define VAR_NAME43(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42) VAR_PRINT(x0) + VAR_NAME42(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42)
#define VAR_NAME44(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43) VAR_PRINT(x0) + VAR_NAME43(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43)
#define VAR_NAME45(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44) VAR_PRINT(x0) + VAR_NAME44(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44)
#define VAR_NAME46(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45) VAR_PRINT(x0) + VAR_NAME45(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45)
#define VAR_NAME47(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46) VAR_PRINT(x0) + VAR_NAME46(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46)
#define VAR_NAME48(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47) VAR_PRINT(x0) + VAR_NAME47(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47)
#define VAR_NAME49(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48) VAR_PRINT(x0) + VAR_NAME48(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48)
#define VAR_NAME50(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49) VAR_PRINT(x0) + VAR_NAME49(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49)
#define VAR_NAME51(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50) VAR_PRINT(x0) + VAR_NAME50(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50)
#define VAR_NAME52(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51) VAR_PRINT(x0) + VAR_NAME51(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51)
#define VAR_NAME53(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52) VAR_PRINT(x0) + VAR_NAME52(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52)
#define VAR_NAME54(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53) VAR_PRINT(x0) + VAR_NAME53(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53)
#define VAR_NAME55(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54) VAR_PRINT(x0) + VAR_NAME54(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54)
#define VAR_NAME56(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55) VAR_PRINT(x0) + VAR_NAME55(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55)
#define VAR_NAME57(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56) VAR_PRINT(x0) + VAR_NAME56(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56)
#define VAR_NAME58(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57) VAR_PRINT(x0) + VAR_NAME57(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57)
#define VAR_NAME59(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58) VAR_PRINT(x0) + VAR_NAME58(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58)
#define VAR_NAME60(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59) VAR_PRINT(x0) + VAR_NAME59(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59)
#define VAR_NAME61(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60) VAR_PRINT(x0) + VAR_NAME60(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60)
#define VAR_NAME62(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61) VAR_PRINT(x0) + VAR_NAME61(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61)
#define VAR_NAME63(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62) VAR_PRINT(x0) + VAR_NAME62(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62)
#define VAR_NAME64(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63) VAR_PRINT(x0) + VAR_NAME63(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63)
#define VAR_NAME65(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64) VAR_PRINT(x0) + VAR_NAME64(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64)
#define VAR_NAME66(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65) VAR_PRINT(x0) + VAR_NAME65(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65)
#define VAR_NAME67(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66) VAR_PRINT(x0) + VAR_NAME66(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66)
#define VAR_NAME68(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67) VAR_PRINT(x0) + VAR_NAME67(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67)
#define VAR_NAME69(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68) VAR_PRINT(x0) + VAR_NAME68(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68)
#define VAR_NAME70(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69) VAR_PRINT(x0) + VAR_NAME69(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69)
#define VAR_NAME71(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70) VAR_PRINT(x0) + VAR_NAME70(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70)
#define VAR_NAME72(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71) VAR_PRINT(x0) + VAR_NAME71(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71)
#define VAR_NAME73(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72) VAR_PRINT(x0) + VAR_NAME72(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72)
#define VAR_NAME74(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73) VAR_PRINT(x0) + VAR_NAME73(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73)
#define VAR_NAME75(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74) VAR_PRINT(x0) + VAR_NAME74(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74)
#define VAR_NAME76(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75) VAR_PRINT(x0) + VAR_NAME75(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75)
#define VAR_NAME77(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76) VAR_PRINT(x0) + VAR_NAME76(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76)
#define VAR_NAME78(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77) VAR_PRINT(x0) + VAR_NAME77(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77)
#define VAR_NAME79(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78) VAR_PRINT(x0) + VAR_NAME78(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78)
#define VAR_NAME80(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79) VAR_PRINT(x0) + VAR_NAME79(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79)
#define VAR_NAME81(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80) VAR_PRINT(x0) + VAR_NAME80(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80)
#define VAR_NAME82(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81) VAR_PRINT(x0) + VAR_NAME81(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81)
#define VAR_NAME83(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82) VAR_PRINT(x0) + VAR_NAME82(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82)
#define VAR_NAME84(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83) VAR_PRINT(x0) + VAR_NAME83(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83)
#define VAR_NAME85(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84) VAR_PRINT(x0) + VAR_NAME84(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84)
#define VAR_NAME86(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85) VAR_PRINT(x0) + VAR_NAME85(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85)
#define VAR_NAME87(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86) VAR_PRINT(x0) + VAR_NAME86(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86)
#define VAR_NAME88(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87) VAR_PRINT(x0) + VAR_NAME87(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87)
#define VAR_NAME89(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88) VAR_PRINT(x0) + VAR_NAME88(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88)
#define VAR_NAME90(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89) VAR_PRINT(x0) + VAR_NAME89(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89)
#define VAR_NAME91(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90) VAR_PRINT(x0) + VAR_NAME90(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90)
#define VAR_NAME92(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91) VAR_PRINT(x0) + VAR_NAME91(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91)
#define VAR_NAME93(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92) VAR_PRINT(x0) + VAR_NAME92(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92)
#define VAR_NAME94(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93) VAR_PRINT(x0) + VAR_NAME93(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93)
#define VAR_NAME95(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94) VAR_PRINT(x0) + VAR_NAME94(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94)
#define VAR_NAME96(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95) VAR_PRINT(x0) + VAR_NAME95(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95)
#define VAR_NAME97(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96) VAR_PRINT(x0) + VAR_NAME96(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96)
#define VAR_NAME98(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97) VAR_PRINT(x0) + VAR_NAME97(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97)
#define VAR_NAME99(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98) VAR_PRINT(x0) + VAR_NAME98(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98)
#define VAR_NAME100(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99) VAR_PRINT(x0) + VAR_NAME99(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99)
#define VAR_NAME101(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100) VAR_PRINT(x0) + VAR_NAME100(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100)
#define VAR_NAME102(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101) VAR_PRINT(x0) + VAR_NAME101(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101)
#define VAR_NAME103(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102) VAR_PRINT(x0) + VAR_NAME102(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102)
#define VAR_NAME104(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103) VAR_PRINT(x0) + VAR_NAME103(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103)
#define VAR_NAME105(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104) VAR_PRINT(x0) + VAR_NAME104(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104)
#define VAR_NAME106(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105) VAR_PRINT(x0) + VAR_NAME105(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105)
#define VAR_NAME107(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106) VAR_PRINT(x0) + VAR_NAME106(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106)
#define VAR_NAME108(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107) VAR_PRINT(x0) + VAR_NAME107(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107)
#define VAR_NAME109(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108) VAR_PRINT(x0) + VAR_NAME108(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108)
#define VAR_NAME110(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109) VAR_PRINT(x0) + VAR_NAME109(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109)
#define VAR_NAME111(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110) VAR_PRINT(x0) + VAR_NAME110(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110)
#define VAR_NAME112(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111) VAR_PRINT(x0) + VAR_NAME111(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111)
#define VAR_NAME113(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112) VAR_PRINT(x0) + VAR_NAME112(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112)
#define VAR_NAME114(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113) VAR_PRINT(x0) + VAR_NAME113(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113)
#define VAR_NAME115(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114) VAR_PRINT(x0) + VAR_NAME114(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114)
#define VAR_NAME116(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115) VAR_PRINT(x0) + VAR_NAME115(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115)
#define VAR_NAME117(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116) VAR_PRINT(x0) + VAR_NAME116(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116)
#define VAR_NAME118(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117) VAR_PRINT(x0) + VAR_NAME117(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117)
#define VAR_NAME119(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117, x118) VAR_PRINT(x0) + VAR_NAME118(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117, x118)
#define VAR_NAME120(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117, x118, x119) VAR_PRINT(x0) + VAR_NAME119(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117, x118, x119)
#define VAR_NAME121(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117, x118, x119, x120) VAR_PRINT(x0) + VAR_NAME120(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117, x118, x119, x120)
#define VAR_NAME122(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117, x118, x119, x120, x121) VAR_PRINT(x0) + VAR_NAME121(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117, x118, x119, x120, x121)
#define VAR_NAME123(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117, x118, x119, x120, x121, x122) VAR_PRINT(x0) + VAR_NAME122(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117, x118, x119, x120, x121, x122)
#define VAR_NAME124(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117, x118, x119, x120, x121, x122, x123) VAR_PRINT(x0) + VAR_NAME123(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117, x118, x119, x120, x121, x122, x123)
#define VAR_NAME125(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117, x118, x119, x120, x121, x122, x123, x124) VAR_PRINT(x0) + VAR_NAME124(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117, x118, x119, x120, x121, x122, x123, x124)
#define VAR_NAME126(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117, x118, x119, x120, x121, x122, x123, x124, x125) VAR_PRINT(x0) + VAR_NAME125(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117, x118, x119, x120, x121, x122, x123, x124, x125)
#define VAR_NAME127(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117, x118, x119, x120, x121, x122, x123, x124, x125, x126) VAR_PRINT(x0) + VAR_NAME126(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65, x66, x67, x68, x69, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88, x89, x90, x91, x92, x93, x94, x95, x96, x97, x98, x99, x100, x101, x102, x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117, x118, x119, x120, x121, x122, x123, x124, x125, x126)

#define CHOOSER126(count) VAR_NAME##count
#define CHOOSER125(count) CHOOSER126(count)
#define CHOOSER124(count) CHOOSER125(count)
#define CHOOSER123(count) CHOOSER124(count)
#define CHOOSER122(count) CHOOSER123(count)
#define CHOOSER121(count) CHOOSER122(count)
#define CHOOSER120(count) CHOOSER121(count)
#define CHOOSER119(count) CHOOSER120(count)
#define CHOOSER118(count) CHOOSER119(count)
#define CHOOSER117(count) CHOOSER118(count)
#define CHOOSER116(count) CHOOSER117(count)
#define CHOOSER115(count) CHOOSER116(count)
#define CHOOSER114(count) CHOOSER115(count)
#define CHOOSER113(count) CHOOSER114(count)
#define CHOOSER112(count) CHOOSER113(count)
#define CHOOSER111(count) CHOOSER112(count)
#define CHOOSER110(count) CHOOSER111(count)
#define CHOOSER109(count) CHOOSER110(count)
#define CHOOSER108(count) CHOOSER109(count)
#define CHOOSER107(count) CHOOSER108(count)
#define CHOOSER106(count) CHOOSER107(count)
#define CHOOSER105(count) CHOOSER106(count)
#define CHOOSER104(count) CHOOSER105(count)
#define CHOOSER103(count) CHOOSER104(count)
#define CHOOSER102(count) CHOOSER103(count)
#define CHOOSER101(count) CHOOSER102(count)
#define CHOOSER100(count) CHOOSER101(count)
#define CHOOSER99(count) CHOOSER100(count)
#define CHOOSER98(count) CHOOSER99(count)
#define CHOOSER97(count) CHOOSER98(count)
#define CHOOSER96(count) CHOOSER97(count)
#define CHOOSER95(count) CHOOSER96(count)
#define CHOOSER94(count) CHOOSER95(count)
#define CHOOSER93(count) CHOOSER94(count)
#define CHOOSER92(count) CHOOSER93(count)
#define CHOOSER91(count) CHOOSER92(count)
#define CHOOSER90(count) CHOOSER91(count)
#define CHOOSER89(count) CHOOSER90(count)
#define CHOOSER88(count) CHOOSER89(count)
#define CHOOSER87(count) CHOOSER88(count)
#define CHOOSER86(count) CHOOSER87(count)
#define CHOOSER85(count) CHOOSER86(count)
#define CHOOSER84(count) CHOOSER85(count)
#define CHOOSER83(count) CHOOSER84(count)
#define CHOOSER82(count) CHOOSER83(count)
#define CHOOSER81(count) CHOOSER82(count)
#define CHOOSER80(count) CHOOSER81(count)
#define CHOOSER79(count) CHOOSER80(count)
#define CHOOSER78(count) CHOOSER79(count)
#define CHOOSER77(count) CHOOSER78(count)
#define CHOOSER76(count) CHOOSER77(count)
#define CHOOSER75(count) CHOOSER76(count)
#define CHOOSER74(count) CHOOSER75(count)
#define CHOOSER73(count) CHOOSER74(count)
#define CHOOSER72(count) CHOOSER73(count)
#define CHOOSER71(count) CHOOSER72(count)
#define CHOOSER70(count) CHOOSER71(count)
#define CHOOSER69(count) CHOOSER70(count)
#define CHOOSER68(count) CHOOSER69(count)
#define CHOOSER67(count) CHOOSER68(count)
#define CHOOSER66(count) CHOOSER67(count)
#define CHOOSER65(count) CHOOSER66(count)
#define CHOOSER64(count) CHOOSER65(count)
#define CHOOSER63(count) CHOOSER64(count)
#define CHOOSER62(count) CHOOSER63(count)
#define CHOOSER61(count) CHOOSER62(count)
#define CHOOSER60(count) CHOOSER61(count)
#define CHOOSER59(count) CHOOSER60(count)
#define CHOOSER58(count) CHOOSER59(count)
#define CHOOSER57(count) CHOOSER58(count)
#define CHOOSER56(count) CHOOSER57(count)
#define CHOOSER55(count) CHOOSER56(count)
#define CHOOSER54(count) CHOOSER55(count)
#define CHOOSER53(count) CHOOSER54(count)
#define CHOOSER52(count) CHOOSER53(count)
#define CHOOSER51(count) CHOOSER52(count)
#define CHOOSER50(count) CHOOSER51(count)
#define CHOOSER49(count) CHOOSER50(count)
#define CHOOSER48(count) CHOOSER49(count)
#define CHOOSER47(count) CHOOSER48(count)
#define CHOOSER46(count) CHOOSER47(count)
#define CHOOSER45(count) CHOOSER46(count)
#define CHOOSER44(count) CHOOSER45(count)
#define CHOOSER43(count) CHOOSER44(count)
#define CHOOSER42(count) CHOOSER43(count)
#define CHOOSER41(count) CHOOSER42(count)
#define CHOOSER40(count) CHOOSER41(count)
#define CHOOSER39(count) CHOOSER40(count)
#define CHOOSER38(count) CHOOSER39(count)
#define CHOOSER37(count) CHOOSER38(count)
#define CHOOSER36(count) CHOOSER37(count)
#define CHOOSER35(count) CHOOSER36(count)
#define CHOOSER34(count) CHOOSER35(count)
#define CHOOSER33(count) CHOOSER34(count)
#define CHOOSER32(count) CHOOSER33(count)
#define CHOOSER31(count) CHOOSER32(count)
#define CHOOSER30(count) CHOOSER31(count)
#define CHOOSER29(count) CHOOSER30(count)
#define CHOOSER28(count) CHOOSER29(count)
#define CHOOSER27(count) CHOOSER28(count)
#define CHOOSER26(count) CHOOSER27(count)
#define CHOOSER25(count) CHOOSER26(count)
#define CHOOSER24(count) CHOOSER25(count)
#define CHOOSER23(count) CHOOSER24(count)
#define CHOOSER22(count) CHOOSER23(count)
#define CHOOSER21(count) CHOOSER22(count)
#define CHOOSER20(count) CHOOSER21(count)
#define CHOOSER19(count) CHOOSER20(count)
#define CHOOSER18(count) CHOOSER19(count)
#define CHOOSER17(count) CHOOSER18(count)
#define CHOOSER16(count) CHOOSER17(count)
#define CHOOSER15(count) CHOOSER16(count)
#define CHOOSER14(count) CHOOSER15(count)
#define CHOOSER13(count) CHOOSER14(count)
#define CHOOSER12(count) CHOOSER13(count)
#define CHOOSER11(count) CHOOSER12(count)
#define CHOOSER10(count) CHOOSER11(count)
#define CHOOSER9(count) CHOOSER10(count)
#define CHOOSER8(count) CHOOSER9(count)
#define CHOOSER7(count) CHOOSER8(count)
#define CHOOSER6(count) CHOOSER7(count)
#define CHOOSER5(count) CHOOSER6(count)
#define CHOOSER4(count) CHOOSER5(count)
#define CHOOSER3(count) CHOOSER4(count)
#define CHOOSER2(count) CHOOSER3(count)
#define CHOOSER1(count) CHOOSER2(count)
#define CHOOSER0(count) CHOOSER1(count)

#define PRINT_VAR(...) GGeneral::String("[") +  MSVC_BUG(CHOOSER0(COUNT_ARGS_MAX(__VA_ARGS__)), (__VA_ARGS__)) + "]"

#ifndef NO_LOGGER_DEF
 //Logger macros
#define LOG(...)      GGeneral::Logger::printMessage(GGeneral::toString(__VA_ARGS__), GGeneral::Logger::Severity::S_MSG)
#define LOGI(...)     GGeneral::Logger::printMessage(GGeneral::toString(__VA_ARGS__), GGeneral::Logger::Severity::S_INFO)
#define LOGS(...)     GGeneral::Logger::printMessage(GGeneral::toString(__VA_ARGS__), GGeneral::Logger::Severity::S_SUCCESS)
#define LOGW(...)     GGeneral::Logger::printMessage(GGeneral::toString(__VA_ARGS__), GGeneral::Logger::Severity::S_WARNING)
#define LOGE(...)     GGeneral::Logger::printMessage(GGeneral::toString(__VA_ARGS__), GGeneral::Logger::Severity::S_ERROR)
#define LOGF(...)     GGeneral::Logger::printMessage(GGeneral::toString(__VA_ARGS__), GGeneral::Logger::Severity::S_FATAL)
#endif //NO_LOGGER_DEF

#define	THROW(...)   GGeneral::ErrorHandler::add(GGeneral::toString(__VA_ARGS__))
#define	THROWW(...)  GGeneral::ErrorHandler::add(GGeneral::toString(__VA_ARGS__), GGeneral::Logger::Severity::S_WARNING)
#define	THROWF(...)  GGeneral::ErrorHandler::add(GGeneral::toString(__VA_ARGS__), GGeneral::Logger::Severity::S_FATAL)
#define	THROWI(...)  GGeneral::ErrorHandler::add(GGeneral::toString(__VA_ARGS__), GGeneral::Logger::Severity::S_INFO)


//Assert
#define G_ASSERT(x) if (!x) { LOGE("[Line: ", __LINE__, "]: Assertion failed '", #x, "'") }
#define G_ASSERT_EX(x, add) if (!(x)) { LOGE("[Line: ", __LINE__, "]: Assertion failed of variable: '", #x, "'"); add }

/**
 * The approx value of Pi used in this renderer
 */
#define G_PI 3.14159265359f

#define TO_RAD(deg) (deg * (G_PI / 180.0f))
#define TO_DEG(rad) (rad * (180.0f / G_PI))

#define STRING_ALPHABET_LOW "abcdefghijklmnopqrtsuvwxyz"
#define STRING_ALPHABET_HIGH "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

#define STRING_NUMBERS "1234567890"

 /*! Just a typedef so the code is better to read */
typedef unsigned char byte;

typedef unsigned long ulong_t;

typedef __int64 int64;
typedef __int32 int32;
typedef __int16 int16;
typedef __int8 int8;


#ifndef G_RENDERER_VERSION
 /** Versioning of this Renderer. Template: 'short description of the phase the engine is in' Major Version.Minor Version.Revision.Month.Year */
#define G_RENDERER_VERSION "early Alpha Build Version 0.0.8.03.21"
#endif // !G_RENDERER_VERSION

#ifndef G_RENDERER
#define G_RENDERER
#endif // !G_RENDERER

//Documentation is created using doxygen

 /**
  * This namespace holds all function, namespaces, structs and classes that are not directly part of the Renderer but still integrated.
  */

/**
 * This namespace includes the most important OpenGL math functions needed. It can be also used outside the engine and/or without OpenGL.
 * The Renderer doesn't need to be initialized to use the functions
 */
namespace GMath {
	/**
	 * This structure hold information of a vector.
	 */
	template<typename T, size_t size>
	struct vec {
	private:
		T* data = nullptr;
	public:

		/**
		 * Constructor for the vector. Will set all values to 0
		 */
		vec() {
			data = new T[size];
			memset(data, 0, sizeof(T) * size);
		}

		/**
		 * Will construct the vector and set all values to the given value
		 * @param value - The value of the vector
		 */
		vec(T value) {
			data = new T[size];
			for (size_t i = 0; i < size; i++) {
				data[i] = value;
			}
		}

		/**
		 * Will copy the contents of another vector
		 * @param other - The vector to copy
		 */
		vec(const vec<T, size>& other) {
			data = new T[size];
			memcpy(data, other.data, sizeof(T) * size);
		}

		/**
		 * Will move the vector
		 * @param other - The other vector
		 */
		vec(vec<T, size>&& other) {
			data = other.data;
			other.data = nullptr;
		}

		/** Destructor */
		~vec() { delete[] data; }

		/**
		 * @return A memory address of the data
		 */
		const T* const mem() const { return data; }

		/**
		 * Will perform normal vector to vector addition
		 * @param other - The other vector to add
		 * @return A new vector
		 */
		template<typename V>
		vec<T, size> operator+(const vec<V, size>& other) {
			auto cpy = vec(*this);
			for (size_t i = 0; i < size; i++) {
				cpy[i] += other[i];
			}
			return cpy;
		}

		/**
		 * Will perform normal vector to vector addition
		 * @param other - The other vector
		 * @return This vector
		 */
		template<typename V>
		vec<T, size> operator+=(const vec<V, size>& other) {
			for (size_t i = 0; i < size; i++) {
				data[i] += other[i];
			}
			return *this;
		}

		/**
		 * Will return a reference to the value of the index
		 * @param i - The index
		 * @return The value at this place
		 */
		T& operator[](size_t i) const {
			return data[i];
		}

		/**
		 * @return The size of the vector
		 */
		const size_t getSize() const { return size; }
	};

	/** Vector with 2 elements */
	template<typename T>
	using vec2 = vec<T, 2>;
	/** Vector with 3 elements */
	template<typename T>
	using vec3 = vec<T, 3>;
	/** Vector with 4 elements */
	template<typename T>
	using vec4 = vec<T, 4>;

	/** This struct hold the information of a matrix. All matrices are column major */
	template<typename T, size_t row, size_t column>
	struct mat {
	private:
		/** Data */
		T* data = nullptr;//  new T[row * column];
	public:

		/** Will create a Matrix.*/
		mat() {
			data = new T[row * column];
			memset(data, 0, sizeof(T) * row * column);
		}

		/**
		 * Will create a Matrix
		 * @param value - The value the matrix should hold
		 */
		mat(T value) {
			data = new T[row * column];
			memset(data, value, sizeof(T) * row * column);
		}

		/**
		 * Will copy the other matrix
		 * @param other - The other matrix to copy
		 */
		mat(const mat<T, row, column>& other) {
			data = new T[row * column];
			memcpy(data, other.data, sizeof(T) * row * column);
		}

		/**
		 * Will move the matrix
		 * @param other - The other matrix to move
		 */
		mat(mat<T, row, column>&& other) noexcept {
			data = other.data;
			other.data = nullptr;
		}

		/**
		 * Will copy the matrix
		 * @param other - The other matrix to copy
		 * @return This matrix
		 */
		mat& operator=(const mat<T, row, column>& other) {
			data = other.data;
			return *this;
		}

		/**
		 * Will move the matrix
		 * @param other - The other matrix to move
		 * @return This matrix
		 */
		mat& operator=(mat<T, row, column>&& other) noexcept {
			data = other.data;
			other.data = nullptr;
			return *this;
		}

		/** Destructor */
		~mat() { delete[] data; }

		/**
		 * @return The memory address of the first element
		 */
		const T* const mem() const { return data; }

		T* operator[](size_t i) {
			return &data[i * row];
		}
	};

#define USE_MAT(n)\
	template<typename T>\
	using mat##n##x##n = mat<T, n, n>;\
	template<typename T>\
	using mat##n = mat##n##x##n <T>;

	/** definition of a 2x2 Matrix */
	USE_MAT(2);
	/** definition of a 3x3 Matrix */
	USE_MAT(3);
	/** definition of a 4x4 Matrix */
	USE_MAT(4);

#undef USE_MAT

	/**
	 * Creates a new Identity Matrix 4x4
	 * @return a mat4x4
	 */
	template<typename T>
	mat4<T> mat4x4Identity() {
		mat4<T> returnValue;
		returnValue[0][0] = 1;
		returnValue[1][1] = 1;
		returnValue[2][2] = 1;
		returnValue[3][3] = 1;
		return returnValue;
	}

	template<typename T, size_t S>
	mat<T, S, S> matIdentity() {
		mat<T, S, S> returnValue;
		for (size_t i = 0; i < S; i++) {
			returnValue[i][i] = 1;
		}
		return returnValue;
	}

	/**
	 * Will create an orthographic projection matrix and return it
	 * @param left - Left coordinate of the frustum
	 * @param right - Right coordinate of the frustum
	 * @param bottom - Bottom coordinate of the frustum
	 * @param top - Top coordinate of the frustum
	 * @param _near - The near plane frustum
	 * @param _far - The far plane frustum
	 * @return An mat4x4
	 */
	template<typename T>
	mat4<T> ortho(T left, T right, T bottom, T top, T _near, T _far) {
		auto returnValue = mat4x4Identity<T>();
		returnValue[0][0] = 2 / (right - left);
		returnValue[1][1] = 2 / (top - bottom);
		returnValue[2][2] = -(2 / (_far - _near));
		returnValue[0][3] = -((right + left) / (right - left));
		returnValue[1][3] = -((top + bottom) / (top - bottom));
		returnValue[2][3] = -((_far + _near) / (_far - _near));
		return returnValue;
	}

	/**
	 * Will create an perspective projection matrix and return it
	 * @param FOV - The field of view in degrees
	 * @param aspect - The aspect ratio
	 * @param _near - Specifies the near plane frustum
	 * @param _far - Specifies the far plane frustum
	 * @return An mat4x4
	 */
	template<typename T>
	mat4<T> perpective(float FOV, T aspect, T _near, T _far) {
		mat4<T> returnValue;
		returnValue[0][0] = 1 / (aspect * tan(TO_RAD(FOV) / 2));
		returnValue[1][1] = 1 / (tan(TO_RAD(FOV) / 2));
		returnValue[2][2] = -((_far + _near) / (_far - _near));
		returnValue[3][2] = -1;
		returnValue[2][3] = -((2 * _far * _near) / (_far - _near));
		return returnValue;
	}
}

namespace GGeneral {
	struct BaseObject;

	class String {
	private:
		/** Amount of chars without \0!! */
		size_t size = 0;
		size_t bytesize = 0;
		char* buffer = nullptr;
		bool precise = false;
	public:
		/** Max size of string and used to indicate a failed find() */
		static const size_t npos = SIZE_MAX;

		/** Creates an empty string */
		String();
		/**
		 * Will copy the const char* into an internal buffer.
		 * @param c - The content of the String
		 */
		String(const char* c);
		/**
		 * Will copy the char* into an internal buffer
		 * @param c - The content of the String
		 */
		String(const unsigned char* c);
		/**
		 * Will allocate memory with the given size. May be useful if know how much chars are going to be appended.
		 * @param size - The size of the buffer
		 */
		String(size_t size);
		/**
		 * Move constructor
		 * @param other - The other string
		 */
		String(String&& other) noexcept;
		/**
		 * Copy constructor. Will not copy the memory address. It will allocated the size of the other buffer!
		 * @param other - The other string
		 */
		String(const String& other);

		/**
		 * Will append the chars given. If buffer is not big enough it will allocate a new one.
		 * @param c - The chars to append
		 * @return this string
		 */
		String& append(const char* c);
		/**
		 * Will call the toString() method and append the chars given. If buffer is not big enough it will allocate a new one.
		 * @param obj - The object to append
		 * @return this string
		 */
		String& append(BaseObject& obj);

		/**
		 * Will delete the current buffer and take over the given pointer instead of copying it. This also means that the pointer must not be manually freed. If the String class
		 * gets destructed it will free the buffer.
		 * @param string - The pointer to take over
		 * @param size - The size of the buffer in bytes
		 * @param create_null - Should a null termination char be created. If false no null termination char will be created but the size MUST include the null termination char
		 *						If true a null termination char will be created. The size should only describe the amount of chars in the current pointer without the null termination char
		 */
		void take(void* string, size_t size, bool create_null = false);

		/**
		 * @param i - The index
		 * @return The char at this position
		 */
		char operator[](size_t i);

		/**
		 * @param i - The index
		 * @return The char of the index
		 */
		const char operator[] (size_t i) const;

		/**
		 * Will just copy the String
		 * @param s - The other string
		 * @return A copy of the other string
		 */
		String& operator=(const String& s);
		/**
		 * Will just copy the String
		 * @param s - The other string
		 * @return A copy of the other string
		 */
		String& operator=(String&& other) noexcept;

		/**
		 * Will create a new String and append both of the parameters
		 */
		friend String operator+(const String& s, const String& s2);
		/**
		 * Will create a new String and append both of the parameters
		 */
		friend String operator+(const String& s, const char* c);
		/**
		 * Will create a new String and append both of the parameters
		 */
		friend String operator+(const char* c, const String& s);
		/**
		 * Will just call append
		 * @param c - The chars to append
		 * @return this string
		 */
		String& operator+=(const char* c);

		String& operator<< (char c);
		/**
		 * Will just call append
		 * @param c - The chars to append
		 * @return this string
		 */
		String& operator<< (const char* c);
		/**
		 * Will just call append and cast the bytes into chars
		 * @param b - The bytes to append
		 * @return this string
		 */
		String& operator<< (const byte* b);
		/**
		 * Will just call append
		 * @param s - The string to append
		 * @return this string
		 */
		String& operator<< (const String& s);
		/**
		 * Will just call append
		 * @param c - The obj to append
		 * @return this string
		 */
		String& operator<< (const BaseObject& obj);
		/**
		 * Will format the void* into a char* and will then call append
		 * @param adress - The void* to append
		 * @return this string
		 */
		String& operator<< (const void* adress);
		/**
		 * Will format the number into a char* and will then call append
		 * @param b - The number to append
		 * @return this string
		 */
		String& operator<< (const byte b);
		/**
		 * Will format the number into a char* and will then call append
		 * @param i - The number to append
		 * @return this string
		 */
		String& operator<< (const int i);
		/**
		 * Will format the number into a char* and will then call append
		 * @param ui64 - The number to append
		 * @return this string
		 */
		String& operator<< (uint64_t ui64);
		/**
		 * Will format the number into a char* and will then call append
		 * @param ui32 - The number to append
		 * @return this string
		 */
		String& operator<< (uint32_t ui32);
		/**
		 * Will format the number into a char* and will then call append
		 * @param ui16 - The number to append
		 * @return this string
		 */
		String& operator<< (uint16_t ui16);

		String& operator<< (long l);

		String& operator<< (ulong_t ul);

		/**
		 * Will format the number into a char* and will then call append
		 * @param d - The number to append
		 * @return this string
		 */
		String& operator<< (double d);

		template<typename T, size_t S>
		String& operator<< (GMath::vec<T, S> v) {
			*this << "[size = " << S;
			for (size_t i = 0; i < S; i++) {
				*this << ", x" << i << " = " << v[i];
			}
			*this << "]";
			return *this;
		}

		/**
		 * Will set the precise flag. If the precise flag is set to true the string will be the most memory efficient. Every time something is append the buffer will only allocate just enough space for the chars given.
		 * If this flag is set to false the buffer will always allocate more space than needed for better performance.
		 * @param b The new precise flag
		 */
		void setPrecise(const bool b);

		/**
		 * Will search for the first occurrence of the string
		 * @param c - The string to search for
		 * @return The index if find is successful or npos if nothing has been found
		 */
		size_t find(const char* c);
		/**
		 * Will compare both string
		 * @param c - The char to compare with
		 * @return true - If the comparison was successful
		 * @return false - If the comparison was not successful
		 */
		bool compare(const char* c);

		/**
		 * Will clear the contents of the String
		 * @param alloc - If set to true, the buffer will stay the same size and will not be deleted. If set to false the buffer will be completely deleted
		 */
		void clear(bool alloc);

		/**
		 * Will compare both strings. If there is a char in the parameter that matches one of the chars in this string it will return true.
		 * @param c - A list of chars
		 * @return true - If both strings share at least one char
		 * @return false - If both strings have no common char
		 */
		bool in(const char* c);
		/**
		 * Will erase part of the string.
		 * @param beginning - The starting index
		 * @param offset - The amount of chars to be deleted
		 * @return this string
		 */
		String& erase(size_t beginning, size_t amount);

		/**
		 * Will return the memory address of this buffer
		 * @return the memory address
		 */
		const char* cStr() const;
		/**
		 * Will return the size of the string without the null termination char
		 * @return The size
		 */
		const size_t getSize() const;

		/**
		 * @return The memory address of the buffer
		 */
		operator const char* () const;

		/** Will delete the buffer */
		~String();
	};

	/**
	 * Will try to convert given argument into a string using stringstream
	 * @param arg - The argument to convert
	 * @return A string
	 */
	template<typename T>
	String toString(T arg) {
		String s;
		s << arg;

		return s;
	}

	/**
	 * Will try to convert given arguments using the String class into a string
	 * @param arg - The first needed argument
	 * @param ...args - More arguments
	 * @return A combined string of all arguments
	 */
	template<typename T_FIRST, typename... T_MORE>
	String toString(T_FIRST arg, T_MORE... args) {
		String returnValue;
		returnValue += toString(arg);
		returnValue += toString(args...);
		return returnValue;
	}

	/** Every struct whose will inherit from this struct */
	struct BaseObject {
		virtual GGeneral::String toString() const = 0;
	};

	struct HSVColor;
	/**
	 * A struct containing Red Green and Blue values
	 */
	struct RGBColor : public GGeneral::BaseObject {
		/** The red component */
		byte red;
		/** The green component */
		byte green;
		/** The blue component */
		byte blue;

		/**
		 * Creates a new Color struct with given values
		 * @param red - The red value
		 * @param green - The green value
		 * @param blue - The blue value
		 */
		RGBColor(byte red = 0, byte green = 0, byte blue = 0);

		RGBColor(const RGBColor& other) = default;
		RGBColor(RGBColor&& other) noexcept = default;
		RGBColor& operator=(const RGBColor& other) = default;
		RGBColor& operator=(RGBColor&& other) noexcept = default;

		/**
		 * Returns the red, green or blue color values depending on the given index. Index may not be higher than 2 nor lower than 0
		 * @param i - The index
		 * @return A color value
		 */
		byte operator[](byte i);

		static RGBColor HSVtoRGB(HSVColor color);

		GGeneral::String toString() const override {
			return PRINT_VAR(red, green, blue);
		}
	};

	struct HSVColor : public GGeneral::BaseObject {
		/** The hue component */
		uint16_t h;
		/** The saturation */
		float s;
		/** The value or brightness */
		float v;

		/**
		 * Creates a new Color struct with given values
		 * @param red - The red value
		 * @param green - The green value
		 * @param blue - The blue value
		 */
		HSVColor(uint16_t hue = 0, float saturation = 0, float value = 0);
		
		HSVColor(const HSVColor& other) = default;
		HSVColor(HSVColor&& other) noexcept = default;
		HSVColor& operator=(const HSVColor& other) = default;
		HSVColor& operator=(HSVColor&& other) noexcept = default;

		RGBColor HSVtoRGB();

		GGeneral::String toString() const override {
			return PRINT_VAR(h, s, v);
		}
	};

	struct aRGBColor : public GGeneral::RGBColor {
		/** Alpha component */
		byte alpha;

		aRGBColor(byte red = 0, byte green = 0, byte blue = 0, byte alpha = 255);

		aRGBColor(const aRGBColor& other) = default;
		aRGBColor(aRGBColor&& other) noexcept = default;
		aRGBColor& operator=(const aRGBColor& other) = default;
		aRGBColor& operator=(aRGBColor&& other) noexcept = default;

		byte operator[](byte i);

		GGeneral::String toString() const override {
			return PRINT_VAR(this->red, this->green, this->blue, alpha);
		}
	};

	/** A namespace containing mostly time functions.*/
	namespace Time {
		/** This struct holds the information of any timepoint */
		struct TimePoint : public GGeneral::BaseObject {
			/** The time since 1970 in nanoseconds */
			uint64_t timepoint = 0;
			/** Years since 0 */
			uint32_t year = 0;
			/** Amount of months */
			uint16_t month = 0;
			/** Amount of days */
			uint16_t day = 0;
			/** Amount of hours */
			uint16_t hour = 0;
			/** Amount of minutes */
			uint16_t minute = 0;
			/** Amount of seconds */
			uint16_t seconds = 0;
			/** Amount of milliseconds */
			uint32_t millisecond = 0;
			/** Amount of microseconds */
			uint32_t microsecond = 0;
			/** Amount of nanoseconds */
			uint32_t nanosecond = 0;

			/**
			 * Will set the timepoint member to the given value
			 * @param timepoint - The value of the timepoint in nanoseconds since 1970
			 */
			TimePoint(uint64_t timepoint) : timepoint(timepoint) {}

			/**
			 * Will initialize all members to the value 0
			 */
			TimePoint() = default;
			TimePoint(const TimePoint& other) = default;
			TimePoint(TimePoint&& other) noexcept = default;
			TimePoint& operator=(const TimePoint& other) = default;
			TimePoint& operator=(TimePoint&& other) noexcept = default;

			/**
			 * Will return the current timepoint
			 * @return The time since 1980
			 */
			operator uint64_t() {
				return timepoint;
			}

			GGeneral::String toString() const override {
				return PRINT_VAR(timepoint, year, month, day, hour, minute, seconds, millisecond, microsecond, nanosecond);
			}
		};

		/** Will return true if the year was a leap year */
		const bool isLeapYear(const TimePoint& point);
		/** Will return true if the year was a leap year */
		const bool isLeapYear(const uint32_t year);

		/**
		 * This will fetch the current UTC time. Timezones are not taken into account.
		 * @return A new Timepoint with filled out values
		 */
		TimePoint getCurrentTime();

		/** Returns the time since 1980 in nanoseconds */
		uint64_t getNanoTime();

		/**
		 * Will convert the given days (since 1970) into the correct amount of years. This function will take
		 * leap years into account
		 * @param day - days since 1970
		 * @return Years since 1970
		 */
		uint32_t daysToYears(uint32_t day);

		/**
		 * Will convert the given year (since 1970) to the equivalent amount of days. This function will take leap years
		 * into account
		 * @param year - Years since 1970
		 * @return Days since 1970
		 */
		uint32_t yearsToDays(uint32_t year);

		/**
		 * Will convert the given months since year begin and return the equivalent amount of days. Will not take leap years into
		 * account.
		 * @param m - Month since the beginning of the current year
		 *
		 * @return Days since the beginning of the year
		 */
		uint32_t monthsToDays(byte m);
		/**
		 * Will convert the given months since year begin and return the equivalent amount of days. Can take leap years into
		 * account.
		 *
		 * @param m - Month since the beginning of the current year
		 * @param leap - If set to true it will consider the year a leap year
		 *
		 * @return Days since the beginning of the year
		 */
		uint32_t monthsToDays(byte m, bool leap);

		/**
		 * Will convert the days into the corresponding months. It will consider the year not a leap year
		 * @param d - Days since the beginning of the year in question
		 *
		 * @return The months since the beginning of the year
		 */
		byte daysToMonths(uint16_t d);

		/**
		 * Will convert the days into the corresponding months. It can consider the year a leap year
		 * @param d - Days since the beginning of the year in question
		 * @param leap - If set to true it will consider the current year a leap year
		 *
		 * @return The months since the beginning of the year
		 */
		byte daysToMonths(uint16_t d, bool leap);

		/**
		 * Will try to fill out missing data from an Timepoint. This will only work if TimePoint.timepoint is valid
		 * This function will change the values of the timepoint given
		 */
		TimePoint& fillTimePoint(TimePoint& t);

		/** On construction it will start an internal timer. If the stop method is called the timer will return the time sice its construction */
		struct Timer {
			/** The time the Time was constructed in nanoseconds */
			uint64_t startTime;
			/** Will start the timer */
			Timer();
			/**
			 * Will calculate the time since construction of this struct and return the time in nanoseconds
			 * @return The time sice constuction in nanoseconds
			 */
			uint64_t stop() const;
		};
	}

	/**
	 * The class is multi threaded meaning that there is a buffer all messages will go into. All message in the buffer thread are being read from the worker thread, formatted and in the end printed to the console.
	 * You can set the maximum size of the buffer via setMaxBufferSize variable. If you try to send a message into the buffer, while the buffer size is larger or the same size as the maximum buffer size, the program will halt until there is enough free space to add new message
	 * NOTE: If Logger::init() is not called the function printMsg() will not be multi threaded. Instead it will be processed by the same thread that called the function
	 */
	namespace Logger {
		/**
		 * Max Buffer Size is a variable that can be set to any number. If set to a number larger than 0 and the message buffer size is bigger than the max buffer size the function will halt until the message buffer has a smaller size.
		 */
		volatile static long maxBufferSize = -1;

		/**
		 * The Severity is an Enum that can indicate how important a message sent to the message buffer may be.
		 */
		enum class Severity {
			S_MSG /*! A plain message in gray. Used for unimportant messages*/
			, S_INFO /*! A info message in blue. Should be used for somewhat important messages*/
			, S_SUCCESS /*! A success message in green. Should be used to indicate that some process with somewhat importance was successful*/
			, S_WARNING /*! A warning message in yellow/orange. Should be used to warn the people*/
			, S_ERROR /*! A error message in red. Should be used to indicate that something went wrong*/
			, S_FATAL /*! A fatal error message in background red. Should be used to indicate that something really went wrong*/
		};

		/**
		 * A struct that holds all informations of a Message used in the worker thread-
		 */
		struct Message {
			GGeneral::String msg;
			Severity sev;
			uint64_t time;
		};

		/**
		 * Needs to be called before sending any messages to the message buffer. It will create a worker thread that will print all messages from the buffer.
		 *
		 * @return A bool indicating if the initialization was successful
		 */
		bool init();

		/**
		 * Will add the given message to the buffer to be printed in the console when the thread is ready
		 *
		 * @param in - The Message to print
		 */
		void printMessage(Message in);

		/**
		 * Will create a new Message and then add it to the message buffer
		 *
		 * @param message - The message to print
		 * @param sev - The severity of the message
		 * @param ID - the user ID to be printed with the message
		 */
		template<typename T_TYPE>
		void printMessage(T_TYPE message, Severity sev) {
			String s;
			s << message;
			printMessage({s, sev, Time::getNanoTime()});
		}

		/**
		 * Sets the SeverityFilter to the given filter. All message that have a lower value of the filter will be discarded.
		 *
		 * @param filter - The new filter level
		 */
		void setSeverityFilter(Severity filter);

		/**
		 * Will return the current used filter level
		 *
		 * @return The current filter
		 */
		Severity getSeverityFilter();

		/**
		 * Will halt the thread that called that function until all message from the message buffer have been printed to the console.
		 */
		void wait();

		/**
		 * Will try to terminate the thread as early as possible. The message buffer will be cleared and the init function needs to be called if one wants to log messages again.
		 */
		void terminateThread();
	};

	/**
	 * A struct containing tow values representing the dimension of anything in 2D.
	 */
	template<typename T>
	struct Dimension : public GGeneral::BaseObject {
		/*! The width component of the Dimension */
		T width;
		/*! The height component of the Dimension */
		T height;
		/*! Creates a new Dimension with the given width and height. The type is up to the user but floats and doubles are recommended. Default values are 0 */
		Dimension(T w = 0, T h = 0) : width(w), height(h) {}

		Dimension(const Dimension& other) = default;
		Dimension(Dimension&& other) noexcept = default;
		Dimension& operator=(const Dimension& other) = default;
		Dimension& operator=(Dimension&& other) noexcept = default;

		/**
		 * @return A string with the current values of the Dimension struct
		 */
		GGeneral::String toString() const override {
			return PRINT_VAR(width, height);
		}
	};

	template<typename T>
	struct Dimension3D : public Dimension<T> {
		/*! The depth component of the Dimension */
		T depth;
		/*! Creates a new Dimension with the given width, depth and height. The type is up to the user but floats and doubles are recommended. Default values are 0 */
		Dimension3D(T w = 0, T h = 0, T d = 0) : depth(d) {
			this->width = w;
			this->height = h;
		}

		Dimension3D(const Dimension3D& other) = default;
		Dimension3D(Dimension3D&& other) noexcept = default;
		Dimension3D& operator=(const Dimension3D& other) = default;
		Dimension3D& operator=(Dimension3D&& other) noexcept = default;

		/**
		 * @return A string with the current values of the Point struct
		 */
		GGeneral::String toString() const override {
			return PRINT_VAR(this->width, this->height, depth);
		}
	};

	/**
	 * A struct containing two values representing a point in 2D space.
	 */
	template<typename T>
	struct Point : public GGeneral::BaseObject {
		/*! The x coordinate*/
		T x;
		/*! The y coordinate*/
		T y;
		/*! Creates a new Point with the given coordinates. The type is up to the user but floats and doubles are recommended. Default values are 0*/
		Point(T x = 0, T y = 0) : x(x), y(y) {}

		Point(const Point& other) = default;
		Point(Point&& other) noexcept = default;
		Point& operator=(const Point& other) = default;
		Point& operator=(Point&& other) noexcept = default;

		bool operator==(GGeneral::Point<T> point) {
			return point.x == x && point.y == y;
		}

		/**
		 * @return A string with the current values of the Point struct
		 */
		GGeneral::String toString() const override {
			return PRINT_VAR(x, y);
		}
	};

	/**
	 * A struct extending the Point struct. This struct adds one more coordinate to define Points in 3D space.
	 */
	template<typename T>
	struct Point3D : public Point<T> {
		/*! The z coordinate*/
		T z;
		/*! Creates a new Point with the given coordinates. The type is up to the user but floats and doubles are recommended. Default values are 0*/
		Point3D(T x = 0, T y = 0, T z = 0) : z(z) {
			this->x = x;
			this->y = y;
		}

		Point3D(const Point3D& other) = default;
		Point3D(Point3D&& other) noexcept = default;
		Point3D& operator=(const Point3D& other) = default;
		Point3D& operator=(Point3D&& other) noexcept = default;

		/**
		 * @return A string with the current values of the Point struct
		 */
		GGeneral::String toString() const override {
			return PRINT_VAR(this->x, this->y, z);
		}
	};

	template<typename T>
	struct Rectangle : public BaseObject {
		/*! The upper left coordinate of the rectangle*/
		Point<T> position;
		/*! The width and height of the rectangle*/
		Dimension<T> dimension;

		Rectangle(T x = 0, T y = 0, T width = 0, T height = 0) {
			this->position = Point(x, y);
			this->dimension = Dimension(width, height);
		}

		Rectangle(Point<T> p, T width = 0, T height = 0) {
			this->position = p;
			this->dimension = Dimension(width, height);
		}

		Rectangle(Point<T> p, Dimension<T> d) {
			this->position = p;
			this->dimension = d;
		}

		Rectangle(const Rectangle& other) = default;
		Rectangle(Rectangle&& other) noexcept = default;
		Rectangle& operator=(const Rectangle& other) = default;
		Rectangle& operator=(Rectangle&& other) noexcept = default;

		/**
		 * Will check if this rectangle is overlapping or touching with the other rectangle
		 * @param other - The other rectangle to check
		 * @return true - If the two rectangles overlap
		 * @return false - If the two rectangles don't overlap
		 */
		template<typename O>
		bool isColliding(Rectangle<O>& other) {
			return !(position.y <= (other.position.y - other.dimension.height) || other.position.y <= position.y - dimension.height) && !(position.x >= (other.position.x + other.dimension.width) || other.position.x >= (position.x + dimension.width));
		}

		/**
		 * Will check if this rectangle is overlapping or touching with the other rectangle
		 * @param other - The other rectangle to check
		 * @return true - If the two rectangles overlap
		 * @return false - If the two rectangles don't overlap
		 */
		template<typename O>
		bool isColliding(Rectangle<O>&& other) {
			return !(position.y <= (other.position.y - other.dimension.height) || other.position.y <= position.y - dimension.height) && !(position.x >= (other.position.x + other.dimension.width) || other.position.x >= (position.x + dimension.width));
		}

		/**
		 * @return A string with the current values of the Rectangle struct
		 */
		GGeneral::String toString() const override {
			return PRINT_VAR(position, dimension);
		}
	};

	/**
	 * This namespace contains some Win32 API calls that don't fit the GWindow namespace.
	 */
	namespace OS {
		/**
		 * Will fetch the current computer name and return it
		 * @returns The computer name
		 */
		GGeneral::String getComputerName();

		/**
		 * Will fetch the current user name and return it
		 * @returns The user name
		 */
		GGeneral::String getUserName();

		/**
		 * Will move the mouse cursor to the given screen space coordinates. Please note that the cursor is a shared recourse.
		 * @param newPos - The new position of the cursor
		 */
		void moveMouse(GGeneral::Point<int> newPos);
	}

	/** Small namespace to retrieve all errors from this engine */
	namespace ErrorHandler {
		/**
		 * Will add an Error message to the buffer
		 * @param errorMessage - A descriptive message of the error
		 * @param sev - The severity of the error. This parameter is defaulted to S_ERROR
		 */
		void add(GGeneral::String errorMessage, Logger::Severity sev = Logger::Severity::S_ERROR);

		/**
		 * Will print out all messages caught in the buffer. If there are no error it will print nothing
		 */
		void printAll();

		/**
		 * Will retunrn the message of the last error posted
		 */
		GGeneral::String getLastError();

		/**
		 * Will clear the buffer from all error messages
		 */
		void clearBuffer();
	}
}

/**
 * A namespace containing all function around file loading and reading.
 */
namespace GFile {
	/**
	 * A struct containing the most important information about a file. All classes that are loading in files should derive from it
	 */
	struct File : public GGeneral::BaseObject {
		/**
		 * The data of the file
		 */
		byte* data = nullptr;

		/**
		 * The size of data in bytes
		 */
		uint64_t size = 0;

		/**
		 * The filepath of this file
		 */
		GGeneral::String filepath;

		File(byte* data, uint32_t size) : data(data), size(size) {}

		/** Default constructor */
		File() = default;
		File(const File& other) = default;
		File(File&& other) noexcept = default;
		File& operator=(const File& other) = default;
		File& operator=(File&& other) noexcept = default;

		/**
		 * Returns the data of the given index. The index may not be higher than the size nor lower than 0
		 * @param i -  The index
		 * @return The data
		 */
		virtual byte operator[](uint32_t i) {
			return data[i];
		}

		GGeneral::String toString() const override {
			return PRINT_VAR(size);
		}

		/** Deletes all data allocated */
		~File() { delete[] data; }
	};

	/**
	 * Loads in the file and return the file size. If an error occurs the returned value is 0
	 * @returns The file size in bytes
	 */
	uint64_t getFileSize(GGeneral::String& filepath);

	/**
	 * Will create a file, load and allocated the memory for the data. If an error occurs the returned value will be a nullptr
	 * @returns A Pointer to a file struct
	 */
	File* loadFile(GGeneral::String filepath);

	/**
	 * Will load in the data and interpret it as a text file.
	 * @returns The String information of the file
	 */
	GGeneral::String loadFileS(GGeneral::String filepath);

	/**
	 * Will try to write the file to the given filepath.
	 */
	void writeFile(File* f);

	/**
	 * Fetches and returns the filepath of the executable
	 * @returns The file path of the .exe file
	 */
	GGeneral::String getWorkingDirectionary();

	/**
	 * This namespace contains all functions to load in images
	 */
	namespace Graphics {
		enum class ImageType {
			UNKNOWN
			, BITMAP
			, PORTABLE_NETWORK_GRAPHICS
			, CURSOR
		};
		/**
		 * A struct containing information about a image. The data will always be:
		 * RED, GREEN, BLUE, (if available) ALPHA
		 */
		struct Image : public File {
			/**
			 * The size of the image
			 */
			GGeneral::Dimension<uint32_t> dim;
			/**
			 * Does the image contain alpha values
			 */
			bool hasAlpha = false;

			/**
			 * Specifies the type of the image.
			 * NOTE: If the image type is a BITMAP the bytes will be ordered in BGR instead of RGB. This only occurs if there is no alpha
			 */
			ImageType type = ImageType::UNKNOWN;

			GGeneral::String toString() const override {
				return PRINT_VAR(this->size, dim);
			}

			/**
			 * Will flip the image
			 */
			void flip();

			Image() = default;
			Image(const Image& other) = default;
			Image(Image&& other) noexcept = default;
			Image& operator=(const Image& other) = default;
			Image& operator=(Image&& other) noexcept = default;
		};

		/**
		 * Check if there is an implementation to load the image. Will return false if an error occurs
		 * @return true - The image can be parsed
		 * @return false - An error occurred and/or the image cannot be parsed
		 */
		ImageType isParseble(GGeneral::String& filepath);
		/**
		 * Check if there is an implementation to load the image. Will return false if an error occurs
		 * @return true - The image can be parsed
		 * @return false - An error occurred and/or the image cannot be parsed
		 */
		ImageType isParseble(byte* data);

		Image* resizeImage(const Image& i, GGeneral::Dimension<uint32_t> newSize);

		/**
		 * Will check if the image can be parsed. If the image can be parse it will load in the image, parse it and return a pointer to a created image struct with all information about the image
		 * @returns If successful a image struct
		 */
		Image* loadImage(GGeneral::String filepath);

		struct Cursor : public Image {
			void* instance = nullptr;

			GGeneral::String toString() const override {
				return PRINT_VAR(this->size, this->dim, instance);
			}

			void flip() = delete;

			Cursor() = default;
			Cursor(const Cursor& other) = default;
			Cursor(Cursor&& other) noexcept = default;
			Cursor& operator=(const Cursor& other) = default;
			Cursor& operator=(Cursor&& other) noexcept = default;
			~Cursor();
		};

		Cursor* loadCursor(GGeneral::String filepath);
	}
}

/**
 * The GWindow namespace is for all window specific calls
 *
 * A REWRITE IS IN CONSIDERATION
 *
 */
namespace GWindow {
	/*! An Enum describing the different states the window can be in */
	enum class WindowState {
		HIDDEN /*! The Window is not visible by the user nor is it in the taskbar*/
		, MAXIMIZED /*! The Window is maximized and visible*/
		, MINIMIZED /*! The Window is not visible by the user but the icon can be seen on the taskbar*/
		, NORMAL /*! The Window is visible but not maximized*/
	};

	/*! These are all Keys that the event system is tracking. All other keys that are pressed will be discarded*/
	enum class VK {
		LEFT_MB            /*! Left Mouse Button */
		, RIGHT_MB		   /*! Right Mouse Button*/
		, MIDDLE_MB		   /*! Middle Mouse Button */
		, X1_MB			   /*! X1 Button (Usually on the side of the mouse)*/
		, X2_MB			   /*! X2 Button (Usually on the side of the mouse)*/
		, CANCEL		   /*! Control Breaking Key (Most likely deprecated)*/
		, LEFT_SHIFT	   /*! Left Shift Key*/
		, RIGHT_SHIFT	   /*! Right Shift Key*/
		, LEFT_CONTROL	   /*! Left Control Key*/
		, RIGHT_CONTROL	   /*! Right Control Key*/
		, BACKSPACE		   /*! Backspace*/
		, TAB			   /*! Tabulator Key*/
		, ENTER			   /*! Enter Key*/
		, ALT			   /*! Alt Key*/
		, PAUSE			   /*! Pause Key. Also known as the Break key*/
		, CAPSLOCK		   /*! Capslock Key*/
		, ESCAPE		   /*! Escape Key. Also known as ESC*/
		, SPACE			   /*! Space Key*/
		, PAGE_UP		   /*! Page up Key*/
		, PAGE_DOWN		   /*! Page down Key*/
		, END			   /*! End Key*/
		, HOME			   /*! Home Key. Also known as Pos1*/
		, LEFTARROW		   /*! The Left Arrow Key*/
		, UPARROW		   /*! The Up Arrow Key*/
		, RIGHTARROW	   /*! The Right Arrow Key*/
		, DOWNARROW		   /*! The Down Arrow Key*/
		, SELECT		   /*! Select Key (Most likely deprecated)*/
		, PRINT			   /*! Print Key. Not to be confused with the Print Screen Key which are somehow different key for windows (Most likely deprecated)*/
		, EXECUTE		   /*! Execute Key (Most likely deprecated)*/
		, PRINT_SCREEN	   /*! Print Screen Key. Use this instead of Print key*/
		, INSERT		   /*! Insert Key*/
		, DEL			   /*! Delete Key*/
		, HELP			   /*! Help Key */
		, KEY_0			   /*! Number 0 Key */
		, KEY_1			   /*! Number 1 Key */
		, KEY_2			   /*! Number 2 Key */
		, KEY_3			   /*! Number 3 Key */
		, KEY_4			   /*! Number 4 Key */
		, KEY_5			   /*! Number 5 Key */
		, KEY_6			   /*! Number 6 Key */
		, KEY_7			   /*! Number 7 Key */
		, KEY_8			   /*! Number 8 Key */
		, KEY_9			   /*! Number 9 Key */
		, A				   /*! A Key*/
		, B				   /*! B Key*/
		, C				   /*! C Key*/
		, D				   /*! D Key*/
		, E				   /*! E Key*/
		, F				   /*! F Key*/
		, G				   /*! G Key*/
		, H				   /*! H Key*/
		, I				   /*! I Key*/
		, J				   /*! J Key*/
		, K				   /*! K Key*/
		, L				   /*! L Key*/
		, M				   /*! M Key*/
		, N				   /*! N Key*/
		, O				   /*! O Key*/
		, P				   /*! P Key*/
		, Q				   /*! Q Key*/
		, R				   /*! R Key*/
		, S				   /*! S Key*/
		, T				   /*! T Key*/
		, U				   /*! U Key*/
		, V				   /*! V Key*/
		, W				   /*! W Key*/
		, X				   /*! X Key*/
		, Y				   /*! Y Key*/
		, Z				   /*! Z Key*/
		, LEFT_WINDOWS	   /*! The left Windows key*/
		, RIGHT_WINDOWS	   /*! The right Window key*/
		, APPLICATION	   /*! Application Key. Usually used as a replacement for the left mouse button key*/
		, SLEEP			   /*! Sleep Key*/
		, SCROLL_LOCK	   /*! Scroll Lock Key (Who uses this?) */
		, LEFT_MENU		   /*! Left Alt key (Not used! Please just use Alt) */
		, RIGHT_MENU	   /*! Right Alt key (Not used! Please just use Alt) */
		, VOLUME_MUTE	   /*! Volume Mute key*/
		, VOLUME_DOWN	   /*! Volume decrease button */
		, VOLUME_UP		   /*! Volume increase button */
		, MEDIA_NEXT	   /*! Skip button for media (music, films...)*/
		, MEDIA_LAST	   /*! Previous button for media (music, films...)*/
		, MEDIA_STOP	   /*! Stop button for media (music, films...)*/
		, MEDIA_PLAY_PAUSE /*! Play/Pause button for media (music, films...)*/
		, OEM_1			   /*! Keyboard specific key. On German keyboards the OEM key is usually 'ü'*/
		, OEM_2			   /*! Keyboard specific key. On German keyboards the OEM key is usually '#'*/
		, OEM_3			   /*! Keyboard specific key. On German keyboards the OEM key is usually 'ö'*/
		, OEM_4			   /*! Keyboard specific key. On German keyboards the OEM key is usually 'ß'*/
		, OEM_5			   /*! Keyboard specific key. On German keyboards the OEM key is usually '^'*/
		, OEM_6			   /*! Keyboard specific key. On German keyboards the OEM key is usually '´'*/
		, OEM_7			   /*! Keyboard specific key. On German keyboards the OEM key is usually 'ä'*/
		, OEM_8			   /*! Keyboard specific key.*/
		, OEM_102		   /*! Keyboard specific key. On German keyboards the OEM key is usually '<'*/
		, OEM_CLEAR		   /*! Clear Key*/
		, OEM_PLUS		   /*! Plus Key*/
		, OEM_COMMA		   /*! Comma Key*/
		, OEM_MINUS		   /*! Minus Key*/
		, OEM_PERIOD	   /*! Period Key*/
		, NUMPAD_0		   /*! Numpad 0 Key*/
		, NUMPAD_1		   /*! Numpad 1 Key*/
		, NUMPAD_2		   /*! Numpad 2 Key*/
		, NUMPAD_3		   /*! Numpad 3 Key*/
		, NUMPAD_4		   /*! Numpad 4 Key*/
		, NUMPAD_5		   /*! Numpad 5 Key*/
		, NUMPAD_6		   /*! Numpad 6 Key*/
		, NUMPAD_7		   /*! Numpad 7 Key*/
		, NUMPAD_8		   /*! Numpad 8 Key*/
		, NUMPAD_9		   /*! Numpad 9 Key*/
		, NUMPAD_MULTIPLY  /*! Numpad Multiply Key*/
		, NUMPAD_ADD	   /*! Numpad Plus Key*/
		, NUMPAD_SEPERATOR /*! Numpad Separator Key*/
		, NUMPAD_SUBTRACT  /*! Numpad Minus Key*/
		, NUMPAD_COMMA	   /*! Numpad Comma Key*/
		, NUMPAD_DIVIDE	   /*! Numpad Divide Key*/
		, NUMPAD_LOCK	   /*! Numpad lock*/
		, F1			   /*! F1 Key*/
		, F2			   /*! F2 Key*/
		, F3			   /*! F3 Key*/
		, F4			   /*! F4 Key*/
		, F5			   /*! F5 Key*/
		, F6			   /*! F6 Key*/
		, F7			   /*! F7 Key*/
		, F8			   /*! F8 Key*/
		, F9			   /*! F9 Key*/
		, F10			   /*! F10 Key*/
		, F11			   /*! F11 Key*/
		, F12			   /*! F12 Key*/
		, F13			   /*! F13 Key*/
		, F14			   /*! F14 Key*/
		, F15			   /*! F15 Key*/
		, F16			   /*! F16 Key*/
		, F17			   /*! F17 Key*/
		, F18			   /*! F18 Key*/
		, F19			   /*! F19 Key*/
		, F20			   /*! F20 Key*/
		, F21			   /*! F21 Key*/
		, F22			   /*! F22 Key*/
		, F23			   /*! F23 Key*/
		, F24			   /*! F24 Key*/
		, PLAY			   /*! Play Key (Most likely deprecated)*/
		, ZOOM			   /*! Zoom Key  (Most likely deprecated)*/
		, UNKWON		   /*! Key that can not be indetefied or are not in this list are unknown keys*/
	};

	enum class WindowEvent {
		WINDOW_STATE /*! A change in the extended state of the Window. Possible values is a WindowState emum*/
		, WINDOW_RESIZE /*! A window resize. Possible value is GGeneral::Dimension<long>*/
		, WINDOW_FOCUS /*! Marks if the window is able to receive keyboard input. Possible values are true if window gained focus and false otherwise */
		, WINDOW_MOVE /*! The Window is moving. The returned value in a callback is GGeneral::Point<long> */
		, KEY_PRESS /*! A Key or Mouse button press. The value that will be returned, will be a VK enum */
		, KEY_RELEASE /*! A Key or Mouse button release. The value that will be returned, will be a VK enum */
		, MOUSE_MOVE /*! The Mouse is moving. Most of the time this message will get posted when the mouse is*
						 inside the client area but if the mouse button has been pressed the mouse move message *
						 can also be posted even when outside window. Possible value is GGeneral::Point<int> */
		, WINDOW_CLOSE /*! Close Request of the window. The value returned can be ignored */
	};

	/**
	 * General Function used to get all callback messages that a GWindow instance will be able to send
	 */
	typedef void(*GWindowCallback)(int, WindowEvent, void*);

	/**
	 * Will create an dummy OpenGL context and activate it. It will also init all OpenGL calls meaning that this function needs to be called before calling any other rendering functions. If GRenderer::init() this will also
	 * be initialized. After activation it will delete itself
	 */
	bool init();

	/**
	 * A class including all functions to create a window and fetch events from it using the WinAPI. When the class is constructed, it can only be accessed from the thread that constructed it.
	 * This also counts for the fetchEvents() function but not the init() function!
	 */
	class Window {
	private:
		/*! Window ID used to identify any window */
		bool closeRequest                          = false;
		GGeneral::Dimension<int> minimumWindowSize = { 300, 200 };

		void* deviceContext                        = nullptr;
		void* WindowID                             = nullptr;
		GWindowCallback callbackFunction           = nullptr;
	public:
		/*! Creates a new Window with default values */
		Window() : Window("G-Renderer Window Instance", {50, 50}, {1280, 720}) {}
		Window(GGeneral::String name) : Window(name, {50, 50}, {1280, 720}) {}
		/**
		 * Creates a new window and enables input for it
		 * @param name - The name of the window to be displayed
		 * @param pos - The Position in screen space of the upper left corner
		 * @param dim - The dimension of the whole window
		 */
		Window(GGeneral::String name, GGeneral::Point<int> pos, GGeneral::Dimension<int> dim);

		/** Destructor */
		~Window();

		enum class ContextHints {
			MAJOR_VERSION /*! The major part of the version ->3.4*/,
			MINOR_VERSION /*! The minor part of the version 3.4 <-*/,
			PROFILE_MASK  /*! The Profile. Can be either Core or Compatibility profile.*/,
		    CONTEXT_FLAGS /*! The context that will be created. Can be either null(0), debug(1) or forward compatible(2)*/
		};

		/**
		 * Will set a context hint. The values set in this hint function are global meaning every Window class who would call createOpenGLcontext() will use the values set by this function.
		 * Always call the function before calling createOpenGLcontext() else it wouldn't have any effect.
		 * If c has either the value MAJOR_VERSION or MINOR_VERSION an integer specifying the new version is expected.
		 * If c has the value PROFILE_MASK the value 1 or 0 is expected. If the value has the value 1 than the CORE_PROFILE is chosen else the COMPATIBILITY_PROFILE is chosen.
		 * If c is CONTEXT_FLAGS the value could be either 0, 1 or 2. 
		 * The default values are Version 3.3 CORE_PROFILE
		 * @param c - The context hint to modify
		 * @param value - The new value
		 */
		static void setWindowHints(ContextHints c, uint32_t value);

		/**
		 * This will create a global OpenGL context. Only use this function once! If the function was successful the context can be used with any window.
		 * @return True if the function was succeful. False if not
		 */
		bool createOpenGLcontext();

		/**
		 * Will set the context active/inactive
		 * @param b - If true the context will be made active
		 */
		bool setOpenGLContextActive(bool b = true);

		/**
		 * Will swap the buffers of the windows
		 */
		bool swapBuffers();

		/**
		 * Set the extended window state of the window instance. Is used to change the visibility of the window.
		 * @param state - The new State the window should take
		 */
		void setState(GWindow::WindowState state);

		/**
		 * Will retrieve all messages/events from the current queue from all Windows. It can only process all events from every window instance used owned/constructed from the current thread
		 * 
		 * @param blocking - if set to true the program will halt until a new window message is retrieved
		 */
		static void fetchEvents(bool blocking = false);

		/**
		 * Will fetch if there is a close request for the current window
		 * @return True if there is one. Otherwise it will return false
		 */
		const bool getCloseRequest() const;

		/**
		 * Will immediately sent a close request to the Window and wait until it processed it.
		 */
		void sendCloseRequest();

		/**
		 * Will fetch the current window state and return it. If an error occurs the window state will be "NORMAL"
		 * @return The current Window state of the window
		 */
		WindowState getCurrentWindowState() const;

		/**
		 * Will set change if the user can resize the window or not
		 * @param b - If set to true the user will be able to resize the window
		 */
		void setResizable(bool b);
		
		/**
		 * Will change the minimum size the user can produce by using the borders
		 * @param size - The minimum size
		 */
		void setMinimumWindowSize(GGeneral::Dimension<int> size);

		/**
		 * @return The current set minimum Window size that can be produced by using the window borders
		 */
		GGeneral::Dimension<int> getMinimumWindowSize();

		/**
		 * Will fetch the size of the whole window
		 * @return The window size
		 */
		GGeneral::Dimension<int> getWindowSize() const;

		void setIcon(GGeneral::String filepath) const;

		/**
		 * Will fetch the size of the client region
		 * @return Client size
		 */
		GGeneral::Dimension<int> getWindowDrawSize() const;

		/**
		 * Add a callback function that will be called even an Event happens. There is only one callback function per window. Use the GEventWrapper namespace for multiple functions support.
		 * List of possible events and their parameters:
		 *  -If the Event is WindowEvent::WINDOW_STATE the returned value will be a WindowState enum
		 *  -If the Event is WindowEvent::WINDOW_RESIZE the returned value will be a GGeneral::Dimension struct
		 *	-If the Event is WindowEvent::WINDOW_FOCUS the returned value will be true if the window gained focus
		 *  -If the Event is WindowEvent::WINDOW_MOVE the returned value will be a GGeneral::Point<long>
		 *  -If the Event is WindowEvent::either KEY_PRESS or KEY_RELEASE the void* is an integer that should be casted into a VK enum. This also includes Mouse buttons!
		 *  -If the Event is WindowEvent::MOUSE_MOVE the returned value will be GGeneral::Point<int>
		 *  -If the Event is WindowEvent::WINDOW_CLOSE the returned value can be ignored. This event will always be called upon receiving a close request from the window
		 */
		void setCallbackFunction(GWindowCallback fun);

		/**
		 * @return Internal window ID. Can be casted into a HWND Handle
		 */
		const void* getID() const { return WindowID; }

		void sendMessage(WindowEvent event, void* data);
	};

	/*! This namespace contains all important functions for getting informations of all virtual monitors. The init() function must be called before any other functions. if init() is not called before any other functions they will return 0*/
	namespace Monitor {
		/*! A struct containing all informations of a virtual monitor*/
		struct Screen : public GGeneral::BaseObject {
			/*!Name of the screen*/
			GGeneral::String screenName;
			/*!The digital Position of the Screen relative to the primary Monitor*/
			GGeneral::Point<int> digitalPosition;
			/*!The Resolution of the Monitor*/
			GGeneral::Dimension<int> screenDimension;
			/*!The size the digital coordinate system.*/
			GGeneral::Dimension<int> workDimension;

			/**
			 * Creates a new Screen struct with given values
			 * @param name - The screenName
			 * @param pos - The digitalPosition
			 * @param sdim - The screenDimension
			 * @param wdim - The workDimension
			 */
			Screen(GGeneral::String name = "", GGeneral::Point<int> pos = {0,0}, GGeneral::Dimension<int> sdim = {0,0}, GGeneral::Dimension<int> wdim = {}) : screenName(name), digitalPosition(pos), screenDimension(sdim), workDimension(wdim) {}

			Screen(const Screen& other) = default;
			Screen(Screen&& other) noexcept = default;
			Screen& operator=(const Screen& other) = default;
			Screen& operator=(Screen&& other) noexcept = default;

			/**
			 * @return A string representing the Screen struct
			 */
			GGeneral::String toString() const override {
				return PRINT_VAR(screenName, digitalPosition, screenDimension, workDimension);
			}
		};

		/**
		 * Fetches all Monitor Informations. Needs to be called before calling any other functions
		 *
		 * @return True if no error occurs
		 * @return False if an error occurs
		 */
		bool init();

		/**
		 * Returns a bool
		 *
		 * @return True if the information is already fetched
		 * @return False if the information is not fetched or an error occurred
		 */
		const bool isInit();

		/*
		 * Returns a screen struct with the information of the primary Monitor
		 *
		 * @returns a Screen struct
		 */
		Screen const* getPrimaryMonitorInformation();

		/**
		 * @return an integer with the amount of virtual monitors
		 */
		const uint32_t getAmountOfMonitors();

		/**
		 * @return the index of the primary monitor
		 */
		const uint32_t getPrimaryMonitorIndex();

		/**
		 * Will return the information of the monitor with the given index.
		 *
		 * @return a monitor struct
		 */
		Screen const* getMonitorInformation(uint32_t i);

		/**
		 * Will return the maximum amount of supported Monitor devices
		 *
		 * @return The amount of monitors supported by the users GPU
		 */
		const uint32_t getSupportedAmountOfMonitorDevices();
	}
}

/**
 * Namespace with functions all about game pad inputs. For now this namespace uses the XInput library. Only Controller with XInput support can be recognized by this namespace.
 * There may be support for DirectInput in the future
 */
namespace GGamepad {
	/** A number identifying the left rumble motor of an xbox gamepad. This motor is a low frequency motor */
#define GAMEPAD_LEFT_MOTOR 0b1
	/** A number identifying the right rumble motor of an xbox gamepad. This motor is a high frequency motor */
#define GAMEPAD_RIGHT_MOTOR 0b10

	/** A struct containing all informations about the state of the gamepad */
	struct GamepadState : public GGeneral::BaseObject {
		//Those two small buttons
		/** The start button */
		bool start = false;
		/** back button. Sometimes also the select button */
		bool back = false;
		//Buttons
		/** The a button. On dualshock its the X button */
		bool button_a = false;
		/** The b button. On dualshock its the O button */
		bool button_b = false;
		/** The x button. On dualshock its the ▄ button */
		bool button_x = false;
		/** The y button. On dualshock its the Δ button */
		bool button_y = false;
		//DPad
		/** Down on the directional pad */
		bool dpad_down = false;
		/** Down left the directional pad */
		bool dpad_left = false;
		/** Down right the directional pad */
		bool dpad_right = false;
		/** Down up the directional pad */
		bool dpad_up = false;
		//Shoulder Buttons
		/** Left shoulder button. Also known as LB */
		bool button_left_shoulder = false;
		/** Right shoulder button. Also known as RB */
		bool button_right_shoulder = false;
		/** Left trigger button. Also known as LT. Max value is 255 */
		byte left_trigger = 0;
		/** Right trigger button. Also known as RT. Max value is 255 */
		byte right_trigger = 0;
		//Thumb stick
		/** Left thumbstick button press */
		bool button_left_thumbstick = false;
		/** Right thumbstick button press */
		bool button_right_thumbstick = false;
		/** The position of the left thumbstick on a digital coordinate system. Max value of any axis is 32747 and the minimum value is -32768*/
		GGeneral::Point<short> left_thumbstick = {0, 0};
		/** The position of the right thumbstick on a digital coordinate system. Max value of any axis is 32747 and the minimum value is -32768 */
		GGeneral::Point<short> right_thumbstick = {0, 0};

		GGeneral::String toString() const override {
			return PRINT_VAR(start, back, button_a, button_b, button_x, button_y, dpad_down, dpad_left, dpad_right, dpad_up, button_left_shoulder, button_right_shoulder, left_trigger, right_trigger, button_left_thumbstick, button_right_thumbstick, left_thumbstick, right_thumbstick);
		}

		GamepadState() = default;
		GamepadState(const GamepadState& other) = default;
		GamepadState(GamepadState&& other) noexcept = default;
		GamepadState& operator=(const GamepadState& other) = default;
		GamepadState& operator=(GamepadState&& other) noexcept = default;
	};

	class Gamepad {
	private:
		byte num = -1;
	public:
		/** Default Constructor */
		Gamepad() {}
		/**
		 * Will set the listen number to the given value. The value may not be higher than 3 nor smaller than 0
		 * @param num - The number of the gamepad
		 */
		Gamepad(byte num);
		/**
		 * Will set the listen number to the given value. The value may not be higher than 3 nor smaller than 0
		 * @param num - The number of the gamepad
		 */
		void listen(byte num);
		/**
		 * Will make the gamepad vibrate. The amount controls the force of the vibration. The higher the value, the more the gamepad will vibrate. The max value may not be higher than 65535 nor lower than 0
		 * @param amount - The force of the vibration
		 * @param param - Which motor to control. Values accepter are GAMEPAD_LEFT_MOTOR, GAMEPAD_RIGHT_MOTOR or GAMEPAD_LEFT_MOTOR | GAMEPAD_RIGHT_MOTOR
		 * @return true if the function succeeded
		 * @return false if the function fails
		 */
		bool vibrate(uint16_t amount = 0xffff, byte param = GAMEPAD_LEFT_MOTOR | GAMEPAD_RIGHT_MOTOR);
		/**
		 * Will stop all vibration of the gamepad
		 * @return true if the function succeeded
		 * @return false if the function fails
		 */
		bool stopvibrate();

		/**
		 * @return The current state of the gamepad
		 */
		GamepadState getState();
	};

	/**
	 * @return the amount of gamepads currently connected
	 */
	short getAmountOfConnectedGPad();

	/**
	 * Will enable/disable all input or output to all gamepads. Gamepad::getState will return a GamepadState struct with all values being 0.
	 * This function can be used to disable gamepad controls if the main window looses focus.
	 */
	void enable(bool enable);
}

/** Default maximum buffer size used by this namespace. */
#define MAX_NET_BUFFER_SIZE 1024
/**
 * This namespace has the most important functions for Web Sockets. This class will only support IPv4 for now
 */
namespace GNetworking {
	class Socket;
	/**
	 * A package contains the information that can be received via a receive function
	 */
	struct Package {
		/** The size of this Package in bytes */
		ulong_t size = 0;
		/** The raw data of the package */
		byte* data = nullptr;

		/** Default Constructor */
		Package() {}

		/**
		 * Copy constructor will only copy the memory address
		 */
		Package(const Package& other) {
			data = other.data;
			size = other.size;
		}

		/**
		 * Move constructor
		 */
		Package(Package&& other) noexcept {
			size = other.size;
			data = other.data;

			other.data = nullptr;
			other.size = 0;
		}

		/**
		 * Mover operator. Will dereference the other Object
		 */
		Package& operator=(Package&& other) noexcept {
			size = other.size;
			data = other.data;

			other.data = nullptr;
			other.size = 0;

			return *this;
		}

		/**
		 * Will copy the memory address
		 */
		Package& operator= (const Package& other) {
			data = other.data;
			size = other.size;

			return *this;
		}

		/** Destructor. Will delete the data */
		~Package() {
			delete[] data;
		}
	};
	/**
	 *  Needs to be called before using any other function in this namespace
	 *  @return True if function was successful
	 */
	bool init();

	/** This class can be used to connect to server sockets */
	class Socket {
	private:
		uint64_t socketNr = ~0;
		bool connected = false;
		bool blocking = true;
	public:
		/** Default constructor */
		Socket();

		/**
		 * Will initialize the socket and try to connect to the given IP address and port. If not successful the isConnected() function will return false
		 * @param IP - The IP address to connect to
		 * @param port - The port
		 */
		Socket(GGeneral::String ip, uint16_t port);

		/** Will forcefully close the socket */
		~Socket();

		/**
		 * Will try to connect to the given IP address and port. If not successful the return value will be false. For more information about the error use the GGeneral::ErrorHandler
		 * @param IP - The IP address to connect to
		 * @param port - The port
		 * @return true if a connection has been established
		 */
		bool connect(GGeneral::String ip, GGeneral::String port);
		/**
		 * Will try to make a graceful disconnect to the connected socket. This function will also close the socket. If a new connection is needed a new Socket must be created
		 */
		void disconnect();

		/**
		 * This function may return true even if the connection is already terminated.
		 * @return true if a connection is established
		 */
		bool isConnected();
		/**
		 * Will mark the socket as blocking or non blocking. if the socket is blocking receive and send may block the whole thread until further events. A socket is blocking by default
		 * @param block - True if the Socket should be marked as blocking
		 * @return true if the function was successful
		 */
		bool setBlockingMode(bool block);

		/**
		 * Will send the data to the connected socket.
		 * @param data - The data to send
		 * @param size - The size of the data in bytes
		 */
		void send(byte* data, ulong_t size = MAX_NET_BUFFER_SIZE);
		/**
		 * Will retrieve the first data that is currently in the queue. If there is no data and the socket is set as non blocking or any other error occur the data that the package is pointing to will be a nullptr.
		 * @return A Package struct
		 */
		Package receive();
	};

	/** This class can be used to let other Sockets connect to */
	class ServerSocket {
	private:
		std::vector<uint64_t> sockets;
		uint64_t listenSocket = ~0;
		bool blocking = true;
	public:
		/** Default constructor */
		ServerSocket();
		/**
		 * Will create a Socket and set it to listen on the port given.
		 * @param port - The port to listen on
		 */
		ServerSocket(uint16_t port);

		/** Will Disconnect all connected sockets and then close the listening socket */
		~ServerSocket();

		/**
		 * Will accept the first Socket in the queue
		 * @return If successful a uint64_t representing the socket. If not the return value will be ~0
		 */
		uint64_t accept();

		/**
		 * Will create a socket that will listen on the port given.
		 * @param port - The port to listen on
		 * @return true if no error occurs
		 */
		bool listen(uint16_t port);

		/**
		 * Will try to gracefully disconnect the given socket. Will also close the socket that is connected
		 * @param socket - The socket to disconnect
		 */
		void disconnect(uint64_t socket);

		void forceDisconnect(uint64_t socket);

		/**
		 * Will check if messages can still be received or send to the socket. This function may not deliever correct results.
		 * @param socket - The socket to check for
		 * @return true - The socket is still connected
		 * @return false - The socket is not connected anymore
		 */
		bool isConnected(uint64_t socket);

		/**
		 * Will set the blocking mode of the listening socket
		 * @param block - True if the socket should be marked as blocking. false otherwise
		 * @return true if the function was successful
		 */
		bool setBlockingMode(bool block);
		/**
		 * Will mark the socket as blocking or non blocking. if the socket is blocking receive and send may block the whole thread until further events. A socket is blocking by default
		 * @param block - True if the Socket should be marked as blocking
		 * @param socket - The socket to mark
		 * @return true if the function was successful
		 */
		bool setBlockingMode(bool block, uint64_t socket);

		/**
		 * Always call receive(uint32_t) before calling this function
		 * @return The amount of connected sockets. May be higher or lower than the real value
		 */
		size_t getConnectedAmount() const;

		/**
		 * Will send data to the given connected socket
		 * @param socket - The socket to send the data to
		 * @param data - A pointer to the data
		 * @param size - The size in bytes of the data
		 */
		void send(uint64_t socket, byte* data, uint32_t size = MAX_NET_BUFFER_SIZE);

		/**
		 * Will receive the data of the connected socket
		 * @param socket - The socket to receive from
		 * @return A package. If the data of the package is a nullptr an error occured
		 */
		Package receive(uint64_t socket);
	};
}

/**
 * This namespace contains functions and classes for receiving information from the GWindow namespace.
 */
namespace GEventWrapper {
	/** Separate enum class for all possible mouse button inputs */
	enum class MouseButtons {
		LEFT_BUTTON      /*! Left Mouse Button */
		, RIGTH_BUTTON	 /*! Right Mouse Button*/
		, MIDDLE_BUTTON	 /*! Middle Mouse Button */
		, X1			 /*! X1 Button (Usually on the side of the mouse)*/
		, X2			 /*! X2 Button (Usually on the side of the mouse)*/
	};

	/** Function callback for change in extended window state */
	typedef void(*GEventWindowState)(GWindow::Window* window, GWindow::WindowState state);
	/** Function callback for change in window size */
	typedef void(*GEventWindowResize)(GWindow::Window* window, GGeneral::Rectangle<long> size);
	/** Function callback for change in window focus */
	typedef void(*GEventWindowFocus)(GWindow::Window* window, bool focus);
	/** Function callback for change in the position of the window */
	typedef void(*GEventWindowMove)(GWindow::Window* window, GGeneral::Point<long> pos);
	/** Function callback for keyboard input */
	typedef void(*GEventKeyboard)(GWindow::Window* window, bool pressed, GWindow::VK key);
	/** Function callback for mouse button input */
	typedef void(*GEventMouseButton)(GWindow::Window* window, bool pressed, MouseButtons);
	/** Function callback for change in mouse position */
	typedef void(*GEventMouseMove)(GWindow::Window* window, GGeneral::Point<int> pos);
	/** Function callback for the window close function */
	typedef void(*GEventWindowClose)(GWindow::Window* window);

	/**
	 * Class wrapper for Window callbacks. It supports multiple callback functions but only one window
	 */
	class Windowhandler {
	private:
		uint32_t ID = 0;
	public:
		/** Default constructor. Call registerWindow() to hook to the window callback */
		Windowhandler();
		/**
		 * Will initialize the wrapper and set the callback of the window to the internal callback.
		 * @param window - The window to listen to
		 */
		Windowhandler(GWindow::Window* window);

		/** Default destructor. Will set the callback of the listened window to a nullptr */
		~Windowhandler();

		/**
		 * Will set the callback function of the given window pointer to the internal callback function. Note that the user may not call the GWindow::setCallbackFunction() after calling this function or else this wrapper will stop listening to the window
		 * @param window - The window to listen to
		 */
		void registerWindow(GWindow::Window* window);

		/**
		 * Adds a callback function to call upon receiving events from the window
		 * @param callback - The callback function
		 */
		void addCallback(GEventWindowState callback);
		/**
		 * Adds a callback function to call upon receiving events from the window
		 * @param callback - The callback function
		 */
		void addCallback(GEventWindowResize callback);
		/**
		 * Adds a callback function to call upon receiving events from the window
		 * @param callback - The callback function
		 */
		void addCallback(GEventWindowFocus callback);
		/**
		 * Adds a callback function to call upon receiving events from the window
		 * @param callback - The callback function
		 */
		void addCallback(GEventWindowMove callback);
		/**
		 * Adds a callback function to call upon receiving events from the window
		 * @param callback - The callback function
		 */
		void addCallback(GEventKeyboard callback);
		/**
		 * Adds a callback function to call upon receiving events from the window
		 * @param callback - The callback function
		 */
		void addCallback(GEventMouseButton callback);
		/**
		 * Adds a callback function to call upon receiving events from the window
		 * @param callback - The callback function
		 */
		void addCallback(GEventMouseMove callback);
		/**
		 * Adds a callback function to call upon receiving events from the window
		 * @param callback - The callback function
		 */
		void addCallback(GEventWindowClose callback);

		/**
		 * Note that UNKNOWN key is not a valid key and will always return false
		 * @param key - The key to check for
		 * @return true If the key is pressed
		 * @return false otherwise
		 */
		bool isKeyPressed(GWindow::VK key);

		GGeneral::Point<int> getMousePosition();
	};
}

/**
 * A namespace containing all functions to get the renderer running and rendering
 */
namespace GRenderer {
	/**
	 * Will initialize the renderer
	 */
	const bool init();

	const GGeneral::String getVersion();
	/**
	 * Fetches the current OpenGL Version
	 */
	GGeneral::String getCurentOpenGLVersion();

	void enableBlend();

	/**
	 * @return The time since the last call of this function. If the function is called for the first time the returned value is 0
	 */
	double delta();

	/**
	 * @return The time since the very last call of draw()
	 */
	double ddelta();

	enum class GLString {
		VENDOR,
		RENDERER,
		VERSION,
		SHADER_VERSION
	};
	GGeneral::String getGLString(GLString s);

	/**
	 * Clears the current active OpenGL context with the given color
	 */
	void clear(GGeneral::RGBColor color);

	//definition for shaderprogram so friendships work
	class ShaderProgram;
	namespace Primitives {
		/**
		 * The type used by the IndexBuffer. No other types are allowed
		 */
		enum class IndexTypes {
			UNSIGNED_BYTE, UNSIGNED_SHORT, UNSIGNED_INT
		};

		/**
		 * The type used of the VertexBuffer. Other types can be used if the size of the type is the same like one of the given onces
		 */
		enum class VertexTypes {
			BYTE, SHORT, INT, FLOAT, DOUBLE
		};

		/**
		 * Class wrapper for the OpenGL IndexBuffer
		 */
		struct IndexBuffer {
		private:
			uint32_t amount;
			IndexTypes element;
			/**
			 * Internal OpenGL ID
			 */
			uint32_t ID;
		public:
			IndexBuffer() = default;

			/**
			 * Creates a new IndexBuffer
			 * @param data - The indexes
			 * @param amount - The amount of indexes given
			 */
			IndexBuffer(uint32_t data[], uint32_t amount);
			/**
			 * Creates a new IndexBuffer
			 * @param data - The indexes
			 * @param amount - The amount of indexes given
			 */
			IndexBuffer(byte data[], uint32_t amount);
			/**
			 * Creates a new IndexBuffer
			 * @param data - The indexes
			 * @param amount - The amount of indexes given
			 */
			IndexBuffer(uint16_t data[], uint32_t amount);

			/**
			 * Deletes the IndexBuffer
			 */
			~IndexBuffer();

			/**
			 * Binds the current IndexBuffer
			 */
			void bind();
			/**
			 * Unbind the current IndexBuffer
			 */
			static void unbind();

			friend struct VertexArray;
		};

		/**
		 * Class wrapper for the OpenGL VertexBuffer
		 */
		struct VertexBuffer {
		private:
			/**
			 * Internal OpenGL ID
			 */
			uint32_t ID = 0;
			uint32_t amount = 0;

		public:
			VertexBuffer() = default;
			/**
			 * Creates a new VertexBuffer
			 * @param data - The Data to use
			 * @param amount - The amount of elements
			 * @param count - The amount of Vertexes. Only needed if there is no indexbuffer present
			 */
			VertexBuffer(char data[], uint32_t amount, uint32_t count = 3);
			/**
			 * Creates a new VertexBuffer
			 * @param data - The Data to use
			 * @param amount - The amount of elements
			 * @param count - The amount of Vertexes. Only needed if there is no indexbuffer present
			 */
			VertexBuffer(short data[], uint32_t amount, uint32_t count = 3);
			/**
			 * Creates a new VertexBuffer
			 * @param data - The Data to use
			 * @param amount - The amount of elements
			 * @param count - The amount of Vertexes. Only needed if there is no indexbuffer present
			 */
			VertexBuffer(int data[], uint32_t amount, uint32_t count = 3);
			/**
			 * Creates a new VertexBuffer
			 * @param data - The Data to use
			 * @param amount - The amount of elements
			 * @param count - The amount of Vertexes. Only needed if there is no indexbuffer present
			 */
			VertexBuffer(float data[], uint32_t amount, uint32_t count = 3);
			/**
			 * Creates a new VertexBuffer
			 * @param data - The Data to use
			 * @param amount - The amount of elements
			 * @param count - The amount of Vertexes. Only needed if there is no indexbuffer present
			 */
			VertexBuffer(double data[], uint32_t amount, uint32_t count = 3);
			/**
			 * Deletes the VertexBuffer
			 */
			~VertexBuffer();

			/**
			 * Binds the current VertexBuffer
			 */
			void bind();
			/**
			 * Unbinds the curernt VertexBuffer
			 */
			static void unbind();

			friend struct VertexArray;
		};

		/**
		 * Class wrapper and manager for the OpenGL VertexArray class
		 */
		struct VertexArray {
			/**
			 * A struct that hold the information about the layout of any VertexBuffer. Is most likely needed for the VertexArray construction
			 */
			struct VertexArrayLayout {
			private:
				std::vector<byte> layout;
				byte size;
			public:
				VertexArrayLayout() = default;
				/**
				 * Creates a new VertexArrayLayout. This is used for the VertexArray to identify how big the VertexBuffer is and how many elements it has
				 * @param data - All elements e.g.: {3, 2, 1}
				 * @param type - The type of the VertexBuffer used
				 */
				VertexArrayLayout(std::initializer_list<byte> data, VertexTypes type);

				/**
				 * Calculates the Stride
				 * @return The stride
				 */
				const uint32_t getStride() const;

				/**
				 * Calculates the offset of the given element index
				 * @param index - The element
				 * @return The offset
				 */
				const uint32_t getOffset(const uint32_t index) const;

				friend struct VertexArray;
			};
		private:
			bool isOnlyVertexBuffer = false;
			uint32_t amount = 0;
			IndexTypes type = IndexTypes::UNSIGNED_BYTE;
			/**
			 * Internal OpenGL ID
			 */
			uint32_t ID;

		public:
			VertexArray();
			/**
			 * Creates a new VertexArray Object.
			 * @param vertex - The vertexes used by the VertexArray
			 * @param index - The indexes used by the VertexArray
			 * @param layout - The layout of the VertexBuffer
			 */
			VertexArray(VertexBuffer vertex, IndexBuffer index, VertexArrayLayout layout);

			/**
			 * Creates a new VertexArray Object
			 * @param vertex - The vertexes used by the VertexArray
			 * @param layout - The indexes used by the VertexArray
			 */
			VertexArray(VertexBuffer vertex, VertexArrayLayout layout);

			/** Deconstructer */
			~VertexArray();

			/**
			 * Binds the current VertexArray
			 */
			void bind();
			/**
			 * Unbinds the current VertexArray
			 */
			static void unbind();

			/**
			 * @return True if there is no IndexBuffer in this VertexArray
			 */
			bool isOnlyVertex() const { return isOnlyVertexBuffer; }

			/**
			 * Will return the amount of indexes or the amount of vertexes (to be rendered). The return value will depend if there is an IndexBuffer in this VertexArray (see isOnlyVertex())
			 */
			uint32_t getAmount() const { return amount; }

			IndexTypes getIndexType() const { return type; }
		};

		/**
		 * All possible shaders
		 */
		enum class ShaderTypes {
			COMPUTE_SHADER,          /*! A COMPUTE_SHADER*/
			VERTEX_SHADER,			 /*! A VERTEX_SHADER*/
			TESS_CONTROL_SHADER,	 /*! A TESS_CONTROL_SHADER*/
			TESS_EVALUATION_SHADER,	 /*! A TESS_EVALUATION_SHADER*/
			GEOMETRY_SHADER,		 /*! A GEOMETRY_SHADER*/
			FRAGMENT_SHADER,		 /*! A FRAGMENT_SHADER*/
			UNKOWN_SHADER			 /*! If the shader is unknown or cannot be parsed it is an UNKOWN_SHADER*/
		};

		/**
		 * A class wrapper for an shader
		 */
		class Shader {
		private:
			/**
			 * Internal OpenGL ID
			 */
			uint32_t ID;
			/**
			 * The source code
			 */
			GGeneral::String sourceCode;
			ShaderTypes type = ShaderTypes::UNKOWN_SHADER;
			bool fail = true;
		public:
			/**
			 * Will create an invalid shader
			 */
			Shader() = default;

			/**
			 * Will try to guess the Shader and load it in
			 * @param filepath - The filepath to the shader
			 */
			Shader(GGeneral::String filepath);

			/**
			 * Will load in the shader and set the shader type
			 * @param filepath - The filepath to the shader
			 * @param type - The type of the shader
			 */
			Shader(GGeneral::String filepath, ShaderTypes type);

			~Shader();

			/**
			 * Will load in the shader and try to guess it's type
			 * @param filepath - The filepath to the shader
			 * @return true If successful and no errors occurred
			 * @return false If an error occurred
			 */
			bool loadShader(GGeneral::String filepath);

			bool sourceShader(GGeneral::String source, ShaderTypes type);

			/**
			 * Will try to compile the shader
			 * @return true If the shader compilation was successful
			 * @return false If the shader type is not know or and error occurred while trying to compile it
			 */
			bool compileShader();

			/**
			 * @return true If no errors occurred
			 * @return false If an error occurred and the fail bit is set to true
			 */
			bool failed() const;

			/**
			 * Returns an info message of the shader if any errors occurred
			 * @return A string of the info message
			 */
			GGeneral::String getInfoMessage();

			friend class GRenderer::ShaderProgram;
		};
	}

	/**
	 * A class wrapper for OpenGL textures
	 */
	class Texture {
		uint32_t ID = 0;
		uint32_t textureSlot = 0;
		GGeneral::Dimension<uint32_t> defaultSize;

	public:
		/**
		 * Default constructor. The texture is invalid
		 */
		Texture() = default;

		Texture(const Texture& t);

		Texture(Texture&& t) noexcept;

		/**
		 * Will create a new Texture with the given image
		 * @param i
		 */
		Texture(const GFile::Graphics::Image& i);

		Texture& operator=(const Texture& other);

		Texture& operator=(Texture&& t) noexcept;

		/**
		 * Will create the shader
		 * @param i - The Image to convert to a texture
		 * @return Always true
		 */
		const bool createTexture(const GFile::Graphics::Image& i);

		void createTexture(GGeneral::Dimension<int> size, bool alpha = false);

		/**
		 * Deconstructor
		 */
		~Texture();

		/**
		 * Will bind the texture to the given texture slot
		 * @param slot - The texture slot to bind to
		 */
		void bind(uint32_t slot);

		/**
		 * Will bind the texture to the last texture slot given
		 */
		void bind();

		void setTextureSlot(uint32_t slot);

		GGeneral::Dimension<uint32_t> getSize() const;

		/**
		 * Will unbind the current texture from the texture slot
		 */
		static void unbind();

		const uint32_t getID() const { return ID; }

		friend class FrameBuffer;
	};

	/**
	 * A class wrapper for a Shader program
	 */
	class ShaderProgram {
	private:
		uint32_t ID = 0;
		std::vector<uint32_t*> shaderIDs;
		bool fail = true;
	public:
		/**
		 * Default shader program constructor. The program is invalid
		 */
		ShaderProgram() = default;
		/**
		 * Will try to link all given shaders and create a shader program
		 * @param shaders - All shaders to bind
		 */
		ShaderProgram(std::initializer_list<Primitives::Shader*> shaders);

		~ShaderProgram();

		/**
		 * Will link the shaders
		 * @return true - If linking was successful
		 * @return false - If an error occured while linking
		 */
		bool link();

		/**
		 * Returns an info message of the shader program if any errors occurred
		 * @return A string of the info message
		 */
		GGeneral::String getInfoMessage();

		/**
		 * Will fetch the uniform location.
		 * @param name - The name of the uniform
		 * @return If successful the location of the uniform
		 */
		const uint32_t getUniformLocation(const GGeneral::String& name) const;

		/**
		 * Will fetch the uniform location and if found will set the the uniform to the value given
		 * @param name - Name of the uniform
		 * @param mat - The matrix
		 */
		void set(const GGeneral::String& name, GMath::mat2<float>& mat);
		/**
		 * Will fetch the uniform location and if found will set the the uniform to the value given
		 * @param name - Name of the uniform
		 * @param mat - The matrix
		 */
		void set(const GGeneral::String& name, GMath::mat3<float>& mat);
		/**
		 * Will fetch the uniform location and if found will set the the uniform to the value given
		 * @param name - Name of the uniform
		 * @param mat - The matrix
		 */
		void set(const GGeneral::String& name, GMath::mat4<float>& mat);

		/**
		 * Will fetch the uniform location and if found will set the the uniform to the value given
		 * @param name - Name of the uniform
		 * @param f - The new value
		 */
		void set(const GGeneral::String& name, float f);
		/**
		 * Will fetch the uniform location and if found will set the the uniform to the value given
		 * @param name - Name of the uniform
		 * @param f - The new value
		 */
		void set(const GGeneral::String& name, GMath::vec2<float>& f);
		/**
		 * Will fetch the uniform location and if found will set the the uniform to the value given
		 * @param name - Name of the uniform
		 * @param f - The new value
		 */
		void set(const GGeneral::String& name, GMath::vec3<float>& f);
		/**
		 * Will fetch the uniform location and if found will set the the uniform to the value given
		 * @param name - Name of the uniform
		 * @param f - The new value
		 */
		void set(const GGeneral::String& name, GMath::vec4<float>& f);

		/**
		 * Will fetch the uniform location and if found will set the the uniform to the value given
		 * @param name - Name of the uniform
		 * @param i - The new value
		 */
		void set(const GGeneral::String& name, int i);
		/**
		 * Will fetch the uniform location and if found will set the the uniform to the value given
		 * @param name - Name of the uniform
		 * @param i - The new value
		 */
		void set(const GGeneral::String& name, GMath::vec2<int>& i);
		/**
		 * Will fetch the uniform location and if found will set the the uniform to the value given
		 * @param name - Name of the uniform
		 * @param i - The new value
		 */
		void set(const GGeneral::String& name, GMath::vec3<int>& i);
		/**
		 * Will fetch the uniform location and if found will set the the uniform to the value given
		 * @param name - Name of the uniform
		 * @param i - The new value
		 */
		void set(const GGeneral::String& name, GMath::vec4<int>& i);

		/**
		 * Will fetch the uniform location and if found will set the the uniform to the value given
		 * @param name - Name of the uniform
		 * @param ui - The new value
		 */
		void set(const GGeneral::String& name, uint32_t ui);
		/**
		 * Will fetch the uniform location and if found will set the the uniform to the value given
		 * @param name - Name of the uniform
		 * @param ui - The new value
		 */
		void set(const GGeneral::String& name, GMath::vec2<uint32_t>& ui);
		/**
		 * Will fetch the uniform location and if found will set the the uniform to the value given
		 * @param name - Name of the uniform
		 * @param ui - The new value
		 */
		void set(const GGeneral::String& name, GMath::vec3<uint32_t>& ui);
		/**
		 * Will fetch the uniform location and if found will set the the uniform to the value given
		 * @param name - Name of the uniform
		 * @param ui - The new value
		 */
		void set(const GGeneral::String& name, GMath::vec4<uint32_t>& ui);

		/**
		 * Will bind the shader program
		 */
		void bind();

		/**
		 * Will unbind the shader program
		 */
		static void unbind();

		/**
		 * @return The internal OpenGL Shaderprogram ID
		 */
		const uint32_t getID() const { return ID; }
	};

	class FrameBuffer {
	private:
		uint32_t ID = 0;
		Texture* boundTexture = nullptr;
	public:
		FrameBuffer();
		~FrameBuffer();

		void attach(Texture& t);
		void attachTex(GGeneral::Dimension<int> size);

		const Texture* getBoundTexture() const { return boundTexture; }
		void bind();
		static void unbind();
	};

	/** A struct containing the Information to render an Object in 2D and 3D space */
	struct Mesh {
		/** The vertexes of the Mesh */
		Primitives::VertexArray* vertex = nullptr;
		/** The texture of the Mesh */
		Texture* tex = nullptr;
		Mesh(Primitives::VertexArray* vertex, Texture* tex) : vertex(vertex), tex(tex) {}

		~Mesh() {
			delete tex;
			delete vertex;
		}
	};

	void setWireFrameMode(bool b);

	/**
	 * Will bind the needed VertexArrays and Textures and then render the Mesh using the currently bound shaders
	 * @param m - The Mesh to be drawn
	 * @param buffer - Optional buffer to draw on. If nullptr the default buffer will be used (Most likely the window buffer)
	 */
	void draw(Mesh& m, FrameBuffer* buffer = nullptr);
}

namespace GGraphics {
	/**
	 * Will initialize the namespace
	 */
	const bool init();

	/**
	 * Will set the default color to the given color. All draw calls in the namespace will draw with the default color
	 * @param c - The Color to use
	 */
	void setColor(GGeneral::aRGBColor c);

	void setViewport(GGeneral::Dimension<int> size);

	/**
	 * Will draw a rectangle at the coordinates specified
	 * @param r - The coordinates
	 */
	void drawRect(GGeneral::Rectangle<int> r);

	/**
	 * Will draw an image at the given coordinates
	 * @param pos - The position of the image
	 * @param img - The image to draw
	 */
	void drawImg(GGeneral::Point<int> pos, const GFile::Graphics::Image& img, GGeneral::Dimension<uint32_t> dim = {0,0});

	/**
	 * Will draw an image at the given coordinates.
	 * @param pos - The position of the image
	 * @param img - The image to draw
	 */
	void drawImg(GGeneral::Point<int> pos, GRenderer::Texture& tex, GGeneral::Dimension<uint32_t> dim = {0,0});
}

/**
 * Special :>
 */
namespace GFScript {
	/**
	 * All tokens
	 */
	enum class TokenID {
		UNKNOWN /*! Unknown token. Only used for the default constructor of the Token struct */
		, NUMBER_LITERAL /*! A Number literal with a comma '5.23', '0.2', '.23' */
		, STRING_LITERAL /*! A char literal ' "Hello there buddy!" '*/
		, IDENTIFIER_VAR
		, NUM_IDENTIFIER
		, STRING_IDENTIFIER
		, NUMARRAY_IDENTIFIER
		, STRINGARRAY_IDENTIFIER
		, FUNCTION_PRINT
		, FUNCTION_RANDOM
		, FUNCTION_SETARRAY
		, FUNCTION_ADDARRAY
		, FUNCTION_GETARRAY
		, FUNCTION_SIZEARRAY
		, FUNTION_FLOOR
		, FUNTION_CEIL
		, FUNCTION_ABS
		, FUNCTION_ROUND
		, OP_PLUS /*! Plus symbol */
		, OP_MINUS /*! Minus symbol */
		, OP_MULTIPLY /*! Multiply symbol */
		, OP_DIVIDE /*! Divide symbol */
		, EQUALS
		, LPARAN /*! Left Parenthesizes symbol '(' */
		, RPARAN /*! Right Parenthesizes symbol ')'*/
		, BREAK /*! End of line/statement. ';' */
	};

	/**
	 * A token struct that holds the information of one token
	 */
	struct Token : GGeneral::BaseObject {
		/**
		 * The type of the token
		 */
		TokenID type = TokenID::UNKNOWN;
		uint32_t line = 0;
		void* data = nullptr;

		Token(TokenID t = TokenID::UNKNOWN, uint32_t line = 0, void* data = nullptr) : type(t), line(line), data(data) {}

		/**
		 * Copy constructor will only copy the mem address
		 */
		Token(const Token& other) {
			data = other.data;
			type = other.type;
			line = other.line;
		}

		/**
		 * Mover constructor. Will dereference the other Object
		 */
		Token(Token&& other) noexcept {
			data = other.data;
			type = other.type;
			line = other.line;
			other.data = nullptr;
			other.type = TokenID::UNKNOWN;
		}

		/**
		 * Mover operator. Will dereference the other Object
		 */
		Token& operator=(Token&& other) noexcept {
			data = other.data;
			type = other.type;
			line = other.line;
			other.data = nullptr;
			other.type = TokenID::UNKNOWN;

			return *this;
		}

		Token& operator= (const Token& other) {
			data = other.data;
			type = other.type;
			line = other.line;

			return *this;
		}

		GGeneral::String toString() const override {
			return PRINT_VAR(type, line, data);
		}

		~Token() { delete data; }
	};

	enum class VarType {
		INVALID
		, NUM
		, NUMARRAY
		, STRING
		, STRINGARRAY
	};

	struct Variable : GGeneral::BaseObject {
		VarType type = VarType::INVALID;
		void* data = nullptr;

		Variable(VarType t, void* data = nullptr) : type(t), data(data) {}

		/**
		 * Will only copy the mem adress
		 */
		Variable(const Variable& other) {
			type = other.type;
			data = other.data;
		}

		/**
		 * Mover constructor. Will dereference the other Object
		 */
		Variable(Variable&& other) noexcept {
			data = other.data;
			type = other.type;
			other.data = nullptr;
			other.type = VarType::INVALID;
		}

		/**
		 * Mover operator. Will dereference the other Object
		 */
		Variable& operator=(Variable&& other) noexcept {
			data = other.data;
			type = other.type;
			other.data = nullptr;
			other.type = VarType::INVALID;

			return *this;
		}

		Variable& operator=(const Variable& other) {
			type = other.type;
			data = other.data;

			return *this;
		}

		GGeneral::String toString() const override {
			return PRINT_VAR(type, data);
		}

		~Variable() { delete data; }
	};

	/**
	 * With this class one can tokenize a whole file. The tokens ca be given the Parser
	 */
	class Tokenizer {
		GGeneral::String source;
	public:
		/**
		 * Creates a new instance and sets the source
		 * @param source - Source code
		 */
		Tokenizer(GGeneral::String source) : source(source) {}

		/**
		 * @param source - Source code
		 */
		void setSource(GGeneral::String source) { this->source = source; }
		/**
		 * Will take the source and create the tokens
		 * @return -  An array filled with tokens. If nullptr a error occurred
		 */
		std::vector<Token>* createTokens();
	};

	/**
	 * The Interpreter class can execute the GFSL code. All graphical calls are made from the GGraphics namespace
	 */
	class Interpreter {
		std::vector<Token>* tokens;
		std::map<GGeneral::String*, Variable*> variableValues;
		std::vector<GGeneral::String*> variablesNames;

		std::vector<void*> functions;

		bool d_error = false;
		/**
		 * Number arithmetic
		 */
		static void op_plus1(Interpreter* i, Token* var, Token* num);
		static void d_op_plus1(Interpreter* i, Token* var, Token* num);
		static void op_minus1(Interpreter* i, Token* var, Token* num);
		static void d_op_minus1(Interpreter* i, Token* var, Token* num);
		static void op_multiply1(Interpreter* i, Token* var, Token* num);
		static void d_op_multiply1(Interpreter* i, Token* var, Token* num);
		static void op_divide1(Interpreter* i, Token* var, Token* num);
		static void d_op_divide1(Interpreter* i, Token* var, Token* num);
		/**
		 * abs round ceil...i think you get it
		 */
		static void fun_abs(Interpreter* i, Token* var);
		static void d_fun_abs(Interpreter* i, Token* var);
		static void fun_ceil(Interpreter* i, Token* var);
		static void d_fun_ceil(Interpreter* i, Token* var);
		static void fun_floor(Interpreter* i, Token* var);
		static void d_fun_floor(Interpreter* i, Token* var);
		static void fun_round(Interpreter* i, Token* var);
		static void d_fun_round(Interpreter* i, Token* var);
		/**
		 * create var num
		 */
		static void op_equalnum(Interpreter* i, Token* type, Token* identifier, Token* data);
		static void d_op_equalnum(Interpreter* i, Token* type, Token* identifier, Token* data);
		/**
		 * set value
		 */
		static void op_equalset(Interpreter* i, Token* identifier, Token* data);
		static void d_op_equalset(Interpreter* i, Token* identifier, Token* data);
		/**
		 * create var string
		 */
		static void op_equalstr(Interpreter* i, Token* type, Token* identifier, Token* data);
		static void d_op_equalstr(Interpreter* i, Token* type, Token* identifier, Token* data);
		/**
		 * create array num and string
		 */
		static void op_equalnumarray(Interpreter* i, Token* type, Token* identifier, Token* amount, std::vector<double*>* data);
		static void d_op_equalnumarray(Interpreter* i, Token* type, Token* identifier, Token* amount, std::vector<double*>* data);
		static void op_equalstrarray(Interpreter* i, Token* type, Token* identifier, Token* amount, std::vector<double*>* data);
		static void d_op_equalstrarray(Interpreter* i, Token* type, Token* identifier, Token* amount, std::vector<double*>* data);
		/**
		 * print function
		 */
		static void fun_print(Interpreter* i, Token* data);
		static void d_fun_print(Interpreter* i, Token* data);
		/**
		 * used to modify array
		 */
		static void fun_set_array(Interpreter* i, Token* var, Token* index, Token* data);
		static void d_fun_set_array(Interpreter* i, Token* var, Token* index, Token* data);
		/**
		 * used to add to array
		 */
		static void fun_add_array(Interpreter* i, Token* var, Token* data);
		static void d_fun_add_array(Interpreter* i, Token* var, Token* data);
		/**
		 * used to get value of array
		 */
		static void fun_get_array(Interpreter* i, Token* var, Token* index, Token* var2);
		static void d_fun_get_array(Interpreter* i, Token* var, Token* index, Token* var2);
		/**
		 * Get the size of the vector and save it in var2
		 */
		static void fun_size_array(Interpreter* i, Token* var, Token* var2);
		static void d_fun_size_array(Interpreter* i, Token* var, Token* var2);

		class Parser {
			friend class Interpreter;
			Interpreter* instance;
			Parser(Interpreter* instance) : instance(instance) {}

			bool createCode(bool debug = false);
		};
		friend class Parser;
	public:

		/**
		 * Creates a new instance with the tokens as source
		 * @param tokens - The tokens
		 */
		Interpreter(std::vector<Token>* tokens) : tokens(tokens) {}

		/**
		  * Will take the tokens and create the byte code that can be read and executed by the Interpreter. If the debug bool is set to true
		  * the code generated will be slower to execute, but safer. The byte code is also better to debug. If the debug bool is set to false
		  * the code generated will be faster but there will not be any safety meaning the Interpreter could crash at all times if bad code has been written.
		  * @param debug - Set to true to enable debug code
		  * @return true - If the code generation was successful. False otherwise
		  */
		bool prepare(bool debug = false);

		/**
		 * Will execute the internal byte code generated by the built in parser. prepare() must be called before hand and it must return true
		 * @return true - If the execution was successful
		 * @return false - Only if the code was generated with the debug flag and an error occured during the execution
		 */
		bool execute();
	};
}

/**
 * With this namespace one can interpret a script. The script has the ability to call most of the engines functions.
 */

 //namespace GScript {
 //	/**
 //	 * All tokens
 //	 */
 //	enum class TokenID {
 //		UNKNOWN /*! Unknown token. Only used for the default constructor of the Token struct */
 //		, DOUBLE_LITERAL /*! A Number literal with a comma '5.23', '0.2', '.23' */
 //		, INTEGER_LITERAL /*! A number literal without a comma '23'*/
 //		, CHAR_LITERAL /*! A char literal ' "Hello there buddy!" '*/
 //		, IDENTIFIER_VAR
 //		, IDENTIFIER_INT
 //		, IDENTIFIER_DOUBLE
 //		, FUNCTION_PRINT
 //		, OP_PLUS /*! Plus symbol */
 //		, OP_MINUS /*! Minus symbol */
 //		, OP_MULTIPLY /*! Multiply symbol */
 //		, OP_DIVIDE /*! Divide symbol */
 //		, EQUALS
 //		, LPARAN /*! Left Parenthesizes symbol '(' */
 //		, RPARAN /*! Right Parenthesizes symbol ')'*/
 //		, BREAK /*! End of line/statement. ';' */
 //	};
 //
 //	struct Token : public GGeneral::BaseObject {
 //		TokenID token;
 //		byte type = 0;
 //		double dvalue = 0; //type 1
 //		int ivalue = 0; //type 2
 //		GGeneral::String svalue; //type 3
 //		uint32_t line = 0;
 //
 //		Token() : token(TokenID::UNKNOWN) {}
 //		Token(TokenID token, double dvalue, uint32_t line, GGeneral::String rep = GGeneral::String()) : token(token), dvalue(dvalue), line(line), svalue(rep) { type = 1; }
 //		Token(TokenID token, int ivalue, uint32_t line, GGeneral::String rep = GGeneral::String()) : token(token), ivalue(ivalue), line(line), svalue(rep) { type = 2; }
 //		Token(TokenID token, GGeneral::String svalue, uint32_t line) : token(token), line(line), svalue(svalue) { type = 3; }
 //
 //		GGeneral::String toString() const override {
 //			return PRINT_VAR(token, type, dvalue, ivalue, svalue, line);
 //		}
 //
 //		~Token() {}
 //	};
 //
 //	struct Node : public GGeneral::BaseObject {
 //		/** Left side of the node */
 //		Node* left;
 //		/** The main Token of the node. Most likely a operator */
 //		Token main;
 //		/** Right side of the node. If nullptr the node is a unary node */
 //		Node* right;
 //
 //		GGeneral::String toString() const override {
 //			//Ik that this is breaking my own convention but this good
 //			GGeneral::String returnValue = "[";
 //			if (right != nullptr) {
 //				//returnValue += "right: " + right->toString() + ", ";
 //				returnValue += right->toString();
 //			}
 //			returnValue += main.svalue;
 //			if (left != nullptr) {
 //				//returnValue += ", left: " + left->toString();
 //				returnValue += left->toString();
 //			}
 //			returnValue += "]";
 //			return returnValue;
 //		}
 //
 //		/**
 //		 * Will remove all main reference to any tokens
 //		 */
 //		void dereference();
 //
 //		/** Destructor */
 //		~Node() {
 //			delete left;
 //			delete right;
 //		}
 //	};
 //
 //	/**
 //	 * Main class of this namespace. Just use this class for loading in scripts and executing them
 //	 */
 //	class Interpreter {
 //		/** Source code */
 //		GGeneral::String source;
 //	public:
 //		struct Var {
 //			byte type = 0;
 //			double dvalue = 0;
 //			int ivalue = 0;
 //			GGeneral::String svalue;
 //		};
 //	private:
 //		std::map<GGeneral::String, Var> variables;
 //
 //	public:
 //		/** Tokenizer will tokenize all code */
 //		class Lexer {
 //			const GGeneral::String* source = nullptr;
 //			std::vector<Token> tokens;
 //			uint32_t position = 0;
 //
 //		public:
 //			/**
 //			 * Will try to convert the given string to an array of tokens
 //			 * @param source - The source code
 //			 */
 //			Lexer(const GGeneral::String* source);
 //
 //			/** Default constructor */
 //			Lexer() {}
 //
 //			/**
 //			 * Will reset the lexer and set the source to the given string
 //			 * @param source - The source code
 //			 */
 //			void setSource(const GGeneral::String* source);
 //
 //			/**
 //			 * Will try to tokenize the pointed source
 //			 * @return true - If this operation was successful
 //			 * @return false - If an error occurred while tokenizing
 //			 */
 //			bool createTokens();
 //
 //			/**
 //			 * @return A vector with all tokens
 //			 */
 //			std::vector<Token> getTokens() { return tokens; }
 //			friend class Interpreter;
 //		};
 //
 //		// WILL BE REWRITTEN
 //		///** Can parse an array of tokens and create an abstract syntax tree */
 //		//class Parser {
 //		//	Node* abstractSyntaxTree = nullptr;
 //		//	const std::vector<Token>* tokens = nullptr;
 //		//	std::map<GGeneral::String, Var>* variables = nullptr;
 //		//	uint32_t position = 0;
 //		//public:
 //		//	/**
 //		//	 * Will set the tokens array. Does not create AST
 //		//	 *
 //		//	 * @param tok - The tokens to parse
 //		//	 */
 //		//	Parser(const std::vector<Token>* tok) : tokens(tok) {};
 //		//	/** Default constructor */
 //		//	Parser() {}
 //		//
 //		//	/**
 //		//	 * Will reset the parser and the the tokens array to the given tokens
 //		//	 * @param tok - The tokens to parse
 //		//	 */
 //		//	void setTokens(const std::vector<Token>* tok);
 //		//
 //		//	/**
 //		//	 * Will try to parse the given tokens and create an AST. Only run this method if there is a valid variable table and token vector set
 //		//	 * @return true - If the operation was successful
 //		//	 * @return false - If an error occurred
 //		//	 */
 //		//	bool createAbstractSyntaxTree();
 //		//	friend class Interpreter;
 //		//};
 //
 //		/**
 //		 * WIP
 //		 * @param gprojFile
 //		 */
 //		Interpreter(GFile::File gprojFile);
 //		/**
 //		 * WIP
 //		 * @param source
 //		 */
 //		Interpreter(GGeneral::String source);
 //
 //		/**
 //		 * WIP
 //		 * @return true
 //		 * @return false
 //		 */
 //		bool prepare();
 //
 //		bool execute();
 //	};
 //}
inline GGeneral::String& operator<<(GGeneral::String& s, GFScript::VarType tok) {
	switch (tok) {
	case GFScript::VarType::INVALID:  return s.append("INVALID");
	case GFScript::VarType::NUM:	  return s.append("NUM");
	case GFScript::VarType::STRING:	  return s.append("STRING");
	}
	return s.append("Invalid Enum");
}

inline GGeneral::String& operator<<(GGeneral::String& s, GFScript::TokenID tok) {
	switch (tok) {
	case GFScript::TokenID::UNKNOWN:           return s.append("UNKNOWN");
	case GFScript::TokenID::NUMBER_LITERAL:    return s.append("NUMBER_LITERAL");
	case GFScript::TokenID::STRING_LITERAL:    return s.append("CHAR");
	case GFScript::TokenID::IDENTIFIER_VAR:    return s.append("IDENTIFIER_VAR");
	case GFScript::TokenID::STRING_IDENTIFIER: return s.append("STRING_IDENTIFIER");
	case GFScript::TokenID::NUM_IDENTIFIER:    return s.append("NUM_IDENTIFIER");
	case GFScript::TokenID::FUNCTION_PRINT:    return s.append("FUNCTION_PRINT");
	case GFScript::TokenID::OP_PLUS:           return s.append("OP_PLUS");
	case GFScript::TokenID::OP_MINUS:          return s.append("OP_MINUS");
	case GFScript::TokenID::OP_MULTIPLY:       return s.append("OP_MULTIPLY");
	case GFScript::TokenID::OP_DIVIDE:         return s.append("OP_DIVIDE");
	case GFScript::TokenID::EQUALS:            return s.append("EQUALS");
	case GFScript::TokenID::LPARAN:            return s.append("LPARAN");
	case GFScript::TokenID::RPARAN:            return s.append("RPARAN");
	case GFScript::TokenID::BREAK:             return s.append("BREAK");
	}
	return s.append("Invalid Enum");
}

inline GGeneral::String& operator<<(GGeneral::String& s, GGeneral::Logger::Severity e) {
	switch (e) {
	case GGeneral::Logger::Severity::S_MSG:     return s.append("MESSAGE");
	case GGeneral::Logger::Severity::S_INFO:    return s.append("INFO");
	case GGeneral::Logger::Severity::S_SUCCESS: return s.append("SUCCESS");
	case GGeneral::Logger::Severity::S_WARNING: return s.append("WARNING");
	case GGeneral::Logger::Severity::S_ERROR:   return s.append("ERROR");
	case GGeneral::Logger::Severity::S_FATAL:   return s.append("FATAL");
	}
	return s.append("Invalid Enum");
}

inline GGeneral::String& operator<<(GGeneral::String& s, GRenderer::Primitives::IndexTypes e) {
	switch (e) {
	case GRenderer::Primitives::IndexTypes::UNSIGNED_BYTE:	return s.append("UNSIGNED BYTE");
	case GRenderer::Primitives::IndexTypes::UNSIGNED_SHORT:	return s.append("UNSIGNED SHORT");
	case GRenderer::Primitives::IndexTypes::UNSIGNED_INT:	return s.append("UNSIGNED INT");
	}
	return s.append("Invalid Enum");
}

inline GGeneral::String& operator<<(GGeneral::String& s, GWindow::WindowEvent e) {
	switch (e) {
	case GWindow::WindowEvent::WINDOW_STATE:  return s.append("EXTENDED WINDOW STATE");
	case GWindow::WindowEvent::WINDOW_RESIZE: return s.append("WINDOW RESIZE");
	case GWindow::WindowEvent::KEY_PRESS:	  return s.append("KEY PRESS");
	case GWindow::WindowEvent::KEY_RELEASE:	  return s.append("KEY RELEASE");
	}
	return s.append("Invalid Enum");
}

inline GGeneral::String& operator<<(GGeneral::String& s, GRenderer::Primitives::VertexTypes e) {
	switch (e) {
	case GRenderer::Primitives::VertexTypes::BYTE:	 return s.append("BYTE");
	case GRenderer::Primitives::VertexTypes::SHORT:	 return s.append("SHORT");
	case GRenderer::Primitives::VertexTypes::INT:	 return s.append("INT");
	case GRenderer::Primitives::VertexTypes::FLOAT:	 return s.append("FLOAT");
	case GRenderer::Primitives::VertexTypes::DOUBLE: return s.append("DOUBLE");
	}
	return s.append("Invalid Enum");
}

inline GGeneral::String& operator<<(GGeneral::String& s, GRenderer::Primitives::ShaderTypes e) {
	switch (e) {
	case GRenderer::Primitives::ShaderTypes::COMPUTE_SHADER:		 return s.append("COMPUTE SHADER");
	case GRenderer::Primitives::ShaderTypes::VERTEX_SHADER:			 return s.append("VERTEX SHADER");
	case GRenderer::Primitives::ShaderTypes::TESS_CONTROL_SHADER:	 return s.append("TESS CONTROL SHADER");
	case GRenderer::Primitives::ShaderTypes::TESS_EVALUATION_SHADER: return s.append("TESS EVALUATION SHADER");
	case GRenderer::Primitives::ShaderTypes::GEOMETRY_SHADER:		 return s.append("GEOMETRY SHADER");
	case GRenderer::Primitives::ShaderTypes::FRAGMENT_SHADER:		 return s.append("FRAGMENT SHADER");
	case GRenderer::Primitives::ShaderTypes::UNKOWN_SHADER:			 return s.append("UNKOWN SHADER");
	}
	return s.append("Invalid Enum");
}

inline GGeneral::String& operator<<(GGeneral::String& s, GWindow::WindowState e) {
	switch (e) {
	case GWindow::WindowState::HIDDEN:    return s.append("HIDDEN");
	case GWindow::WindowState::MAXIMIZED: return s.append("MAXIMIZED");
	case GWindow::WindowState::MINIMIZED: return s.append("MINIMIZED");
	case GWindow::WindowState::NORMAL:	  return s.append("NORMAL");
	}
	return s.append("Invalid Enum");
}

inline GGeneral::String& operator<<(GGeneral::String& s, GWindow::VK e) {
	switch (e) {
	case GWindow::VK::LEFT_MB:		           return s.append("Left Mouse Button");
	case GWindow::VK::RIGHT_MB:		           return s.append("Right Mouse Button");
	case GWindow::VK::CANCEL:		           return s.append("Cancel Key");
	case GWindow::VK::MIDDLE_MB:		       return s.append("Middle Mouse Button");
	case GWindow::VK::X1_MB:			       return s.append("X1 Mouse Button");
	case GWindow::VK::X2_MB:			       return s.append("X2 Mouse Button");
	case GWindow::VK::LEFT_SHIFT:	           return s.append("Left Shift");
	case GWindow::VK::RIGHT_SHIFT:	           return s.append("Right Shift");
	case GWindow::VK::LEFT_CONTROL:	           return s.append("Left Control");
	case GWindow::VK::RIGHT_CONTROL:	       return s.append("Right Control");
	case GWindow::VK::BACKSPACE:		       return s.append("Backspace");
	case GWindow::VK::TAB:			           return s.append("Tab");
	case GWindow::VK::ENTER:			       return s.append("Enter");
	case GWindow::VK::ALT:			           return s.append("Alt");
	case GWindow::VK::PAUSE:			       return s.append("Pause");
	case GWindow::VK::CAPSLOCK:		           return s.append("Capslock");
	case GWindow::VK::ESCAPE:		           return s.append("Escape");
	case GWindow::VK::SPACE:			       return s.append("Space");
	case GWindow::VK::PAGE_UP:		           return s.append("Page Up");
	case GWindow::VK::PAGE_DOWN:		       return s.append("Page Down");
	case GWindow::VK::END:			           return s.append("End");
	case GWindow::VK::HOME:			           return s.append("Home");
	case GWindow::VK::LEFTARROW:		       return s.append("Left Arrow");
	case GWindow::VK::UPARROW:		           return s.append("Up Arrow");
	case GWindow::VK::RIGHTARROW:	           return s.append("Right Arrow");
	case GWindow::VK::DOWNARROW:		       return s.append("Down Arrow");
	case GWindow::VK::SELECT:		           return s.append("Select");
	case GWindow::VK::PRINT:			       return s.append("Print");
	case GWindow::VK::EXECUTE:		           return s.append("Execute");
	case GWindow::VK::PRINT_SCREEN:	           return s.append("Print Screen");
	case GWindow::VK::INSERT:		           return s.append("Insert");
	case GWindow::VK::DEL:			           return s.append("Delete");
	case GWindow::VK::HELP:			           return s.append("Help");
	case GWindow::VK::KEY_0:			       return s.append("0");
	case GWindow::VK::KEY_1:			       return s.append("1");
	case GWindow::VK::KEY_2:			       return s.append("2");
	case GWindow::VK::KEY_3:			       return s.append("3");
	case GWindow::VK::KEY_4:			       return s.append("4");
	case GWindow::VK::KEY_5:			       return s.append("5");
	case GWindow::VK::KEY_6:			       return s.append("6");
	case GWindow::VK::KEY_7:			       return s.append("7");
	case GWindow::VK::KEY_8:			       return s.append("8");
	case GWindow::VK::KEY_9:			       return s.append("9");
	case GWindow::VK::A:				       return s.append("A");
	case GWindow::VK::B:				       return s.append("B");
	case GWindow::VK::C:				       return s.append("C");
	case GWindow::VK::D:				       return s.append("D");
	case GWindow::VK::E:				       return s.append("E");
	case GWindow::VK::F:				       return s.append("F");
	case GWindow::VK::G:				       return s.append("G");
	case GWindow::VK::H:				       return s.append("H");
	case GWindow::VK::I:				       return s.append("I");
	case GWindow::VK::J:				       return s.append("J");
	case GWindow::VK::K:				       return s.append("K");
	case GWindow::VK::L:				       return s.append("L");
	case GWindow::VK::M:				       return s.append("M");
	case GWindow::VK::N:				       return s.append("N");
	case GWindow::VK::O:				       return s.append("O");
	case GWindow::VK::P:				       return s.append("P");
	case GWindow::VK::Q:				       return s.append("Q");
	case GWindow::VK::R:				       return s.append("R");
	case GWindow::VK::S:				       return s.append("S");
	case GWindow::VK::T:				       return s.append("T");
	case GWindow::VK::U:				       return s.append("U");
	case GWindow::VK::V:				       return s.append("V");
	case GWindow::VK::W:				       return s.append("W");
	case GWindow::VK::X:				       return s.append("X");
	case GWindow::VK::Y:				       return s.append("Y");
	case GWindow::VK::Z:				       return s.append("Z");
	case GWindow::VK::LEFT_WINDOWS:	           return s.append("Left Windows");
	case GWindow::VK::RIGHT_WINDOWS:	       return s.append("Right Windows");
	case GWindow::VK::APPLICATION:	           return s.append("Application");
	case GWindow::VK::SLEEP:			       return s.append("Sleep");
	case GWindow::VK::SCROLL_LOCK:	           return s.append("Scroll Lock");
	case GWindow::VK::LEFT_MENU:		       return s.append("Left Alt");
	case GWindow::VK::RIGHT_MENU:	           return s.append("Right Alt");
	case GWindow::VK::VOLUME_MUTE:	           return s.append("Volume Mute");
	case GWindow::VK::VOLUME_DOWN:	           return s.append("Volume Down");
	case GWindow::VK::VOLUME_UP:		       return s.append("Volume Up");
	case GWindow::VK::MEDIA_NEXT:	           return s.append("Media Next Track");
	case GWindow::VK::MEDIA_LAST:	           return s.append("Media Previous Track");
	case GWindow::VK::MEDIA_STOP:	           return s.append("Media Stop");
	case GWindow::VK::MEDIA_PLAY_PAUSE:        return s.append("Media Pause / Play");
	case GWindow::VK::OEM_1:			       return s.append("Oem 1");
	case GWindow::VK::OEM_2:			       return s.append("Oem 2");
	case GWindow::VK::OEM_3:			       return s.append("Oem 3");
	case GWindow::VK::OEM_4:			       return s.append("Oem 4");
	case GWindow::VK::OEM_5:			       return s.append("Oem 5");
	case GWindow::VK::OEM_6:			       return s.append("Oem 6");
	case GWindow::VK::OEM_7:			       return s.append("Oem 7");
	case GWindow::VK::OEM_8:			       return s.append("Oem 8");
	case GWindow::VK::OEM_102:                 return s.append("Oem 102");
	case GWindow::VK::OEM_CLEAR:		       return s.append("Clear");
	case GWindow::VK::OEM_PLUS:		           return s.append("Plus");
	case GWindow::VK::OEM_COMMA:		       return s.append("Comma");
	case GWindow::VK::OEM_MINUS:		       return s.append("Minus");
	case GWindow::VK::OEM_PERIOD:	           return s.append("Period");
	case GWindow::VK::NUMPAD_0:		           return s.append("Numpad 0");
	case GWindow::VK::NUMPAD_1:		           return s.append("Numpad 1");
	case GWindow::VK::NUMPAD_2:		           return s.append("Numpad 2");
	case GWindow::VK::NUMPAD_3:		           return s.append("Numpad 3");
	case GWindow::VK::NUMPAD_4:		           return s.append("Numpad 4");
	case GWindow::VK::NUMPAD_5:		           return s.append("Numpad 5");
	case GWindow::VK::NUMPAD_6:		           return s.append("Numpad 6");
	case GWindow::VK::NUMPAD_7:		           return s.append("Numpad 7");
	case GWindow::VK::NUMPAD_8:		           return s.append("Numpad 8");
	case GWindow::VK::NUMPAD_9:		           return s.append("Numpad 9");
	case GWindow::VK::NUMPAD_MULTIPLY:         return s.append("Numpad Multiply");
	case GWindow::VK::NUMPAD_ADD:	           return s.append("Numpad Add");
	case GWindow::VK::NUMPAD_SEPERATOR:        return s.append("Numpad Separator");
	case GWindow::VK::NUMPAD_SUBTRACT:         return s.append("Numpad Subtract");
	case GWindow::VK::NUMPAD_COMMA:	           return s.append("Numpad Comma");
	case GWindow::VK::NUMPAD_DIVIDE:	       return s.append("Numpad Divide");
	case GWindow::VK::NUMPAD_LOCK:	           return s.append("Numpad Lock");
	case GWindow::VK::F1:			           return s.append("F1");
	case GWindow::VK::F2:			           return s.append("F2");
	case GWindow::VK::F3:			           return s.append("F3");
	case GWindow::VK::F4:			           return s.append("F4");
	case GWindow::VK::F5:			           return s.append("F5");
	case GWindow::VK::F6:			           return s.append("F6");
	case GWindow::VK::F7:			           return s.append("F7");
	case GWindow::VK::F8:			           return s.append("F8");
	case GWindow::VK::F9:			           return s.append("F9");
	case GWindow::VK::F10:			           return s.append("F10");
	case GWindow::VK::F11:			           return s.append("F11");
	case GWindow::VK::F12:			           return s.append("F12");
	case GWindow::VK::F13:			           return s.append("F13");
	case GWindow::VK::F14:			           return s.append("F14");
	case GWindow::VK::F15:			           return s.append("F15");
	case GWindow::VK::F16:			           return s.append("F16");
	case GWindow::VK::F17:			           return s.append("F17");
	case GWindow::VK::F18:			           return s.append("F18");
	case GWindow::VK::F19:			           return s.append("F19");
	case GWindow::VK::F20:			           return s.append("F20");
	case GWindow::VK::F21:			           return s.append("F21");
	case GWindow::VK::F22:			           return s.append("F22");
	case GWindow::VK::F23:			           return s.append("F23");
	case GWindow::VK::F24:			           return s.append("F24");
	case GWindow::VK::PLAY:			           return s.append("Play");
	case GWindow::VK::ZOOM:			           return s.append("Zoom");
	case GWindow::VK::UNKWON:                  return s.append("Unknown Key");
	}
	return s.append("Invalid Enum");
}