#include <algorithm>

#include <gtest/gtest.h>
#include "memory_stream.h"

using namespace core;

template <typename T>
void TestSerialization(T input_value, T initial_output_value) {
    MemoryStream ms;
    ms << input_value;
    T output_value = initial_output_value;
    ms >> output_value;
    EXPECT_EQ(input_value, output_value);
}

TEST(MemoryStream, DefaultConstraction) {
    MemoryStream ms;
    EXPECT_EQ(ms.size(), size_t(0));
}

TEST(MemoryStream, Constraction) {
    const Byte input[5] = {1, 2, 3, 4, 5};
    MemoryStream ms(input, sizeof(input));
    EXPECT_EQ(ms.size(), sizeof(input));
    EXPECT_TRUE(std::equal(ms.bytes().begin(), ms.bytes().end(), std::begin(input), std::end(input)));
}

TEST(MemoryStream, ConstractionThrowExceptionIfDataIsNullAndSizeIsNotZero) {
    ASSERT_THROW(MemoryStream(nullptr, 1), std::invalid_argument);
}

TEST(MemoryStream, ToString) {
    const Byte input[5] = {0xa0, 0xb0, 0x10, 0x40, 0x50};
    MemoryStream ms(input, sizeof(input));
    EXPECT_EQ(ms.ToString(), "{ size=5 offset=0 a0 b0 10 40 50 }");
}

TEST(MemoryStream, ReadWrite) {
    MemoryStream ms;
    const Byte input[5] = {1, 2, 3, 4, 5};
    ms.Write(input, sizeof(input));
    Byte output[5] = {0};
    ms.Read(output, sizeof(output));
    EXPECT_TRUE(std::equal(std::begin(input), std::end(input), std::begin(output), std::end(output)));
}

TEST(MemoryStream, SerializationBool) {
    TestSerialization<bool>(true, false);
}

TEST(MemoryStream, SerializationChar) {
    TestSerialization<char>('a', '\0');
}

TEST(MemoryStream, SerializationUnsignedChar) {
    TestSerialization<unsigned char>(255, 0);
}

TEST(MemoryStream, SerializationWChar) {
    TestSerialization<wchar_t>(L'a', L'\0');
}

TEST(MemoryStream, SerializationChar16) {
    TestSerialization<char16_t>(L'a', L'\0');
}

TEST(MemoryStream, SerializationWChar32) {
    TestSerialization<char32_t>(L'a', L'\0');
}

TEST(MemoryStream, SerializationShort) {
    TestSerialization<short>(-32767, 0);
}

TEST(MemoryStream, SerializationUnsignedShort) {
    TestSerialization<unsigned short>(65535, 0);
}

TEST(MemoryStream, SerializationInt) {
    TestSerialization<int>(-32767, 0);
}

TEST(MemoryStream, SerializationUnsignedInt) {
    TestSerialization<unsigned int>(32767, 0);
}

TEST(MemoryStream, SerializationLong) {
    TestSerialization<long>(-2147483647, 0);
}

TEST(MemoryStream, SerializationUnsignedLong) {
    TestSerialization<unsigned long>(4294967295, 0);
}

TEST(MemoryStream, SerializationLongLong) {
    TestSerialization<long long>(-9223372036854775807, 0);
}

TEST(MemoryStream, SerializationUnsignedLongLong) {
    TestSerialization<unsigned long long>(18446744073709551615, 0);
}

TEST(MemoryStream, SerializationFloat) {
    TestSerialization<float>(-2e10, 0.0);
}

TEST(MemoryStream, SerializationDouble) {
    TestSerialization<double>(-2e100, 0.0);
}

TEST(MemoryStream, SerializationLongDouble) {
    TestSerialization<long double>(-2e300, 0.0);
}

TEST(MemoryStream, SerializationSize) {
    TestSerialization<size_t>(1000, 0);
}

TEST(MemoryStream, SerializationString) {
    TestSerialization<std::string>("Hello", "");
}

TEST(MemoryStream, SerializationWString) {
    TestSerialization<std::wstring>(L"1", L"");
}

TEST(MemoryStream, SerializationVector) {
    TestSerialization<std::vector<int>>({1, 2, 3, 4, 5}, {});
}

TEST(MemoryStream, SerializationBytes) {
    TestSerialization<Bytes>({1, 2, 3, 4, 5}, {});
}
