#include <iostream>
#include <sstream>
#include <type_traits>


template <typename INT_SIZE> void handle_input();
template <typename INT_SIZE> std::string handle_input(std::string);
template <typename INT_SIZE> bool read_num(INT_SIZE&);
template <typename INT_SIZE> INT_SIZE endian0(INT_SIZE);
template <typename INT_SIZE> INT_SIZE endian(INT_SIZE);
template <typename INT_SIZE> INT_SIZE endian2(INT_SIZE);
bool is_big_endian();


template <typename INT_SIZE>
void handle_input()
{
	while(true)
	{
		INT_SIZE num;
		if (!read_num(num))
			return;
		//std::cout << num << " converts 1 " << endian0<INT_SIZE>(num) << '\n'; 
		std::cout << num << " converts to " << endian<INT_SIZE>(num) << '\n'; 
		//std::cout << num << " converts 3 " << endian2<INT_SIZE>(num) << '\n'; 
	}
}

template <typename INT_SIZE>
bool read_num(INT_SIZE& num)
{
	if (std::cin >> num)
		return true;
	return false;
}

template <typename INT_SIZE>
std::string handle_input(std::string data)
{
	std::stringstream ss(data);
	std::stringstream output;

	//auto x = { 1, 2, 3 };
	//for (auto i = 0; auto xx : x) {}

	while(!ss.eof())
	{
		INT_SIZE num;
		ss >> num;
		output << num << " converts to " << endian<INT_SIZE>(num) << '\n'; 
	}

	return output.str();
}

template <typename INT_SIZE>
INT_SIZE endian0(INT_SIZE num)
{
	if (std::is_same<INT_SIZE, int16_t>::value)
		//warning: implicit conversion loses integer precision: 'int' to 'unsigned short' [-Wimplicit-int-conversion]
		return __builtin_bswap16(num);
	else if (std::is_same<INT_SIZE, int32_t>::value)
		//warning: implicit conversion changes signedness: 'unsigned int' to 'int' [-Wsign-conversion]
		return __builtin_bswap32(num);
	else if (std::is_same<INT_SIZE, int64_t>::value)
		//warning: implicit conversion changes signedness: 'int' to 'unsigned long' [-Wsign-conversion]
		return __builtin_bswap64(num);
}

template <typename INT_SIZE>
INT_SIZE endian(INT_SIZE n)
{
	// FIXME fuj hardcode
	uint32_t num = static_cast<uint32_t>(n);
	/*
	 * endians.cpp:54:83: warning: implicit conversion changes signedness: 'unsigned int' to 'int' [-Wsign-conversion]
	 */
    return (((num) >> 24) | ((num << 8) & 0x00FF0000) | ((num >> 8) & 0x0000FF00) | ((num) << 24));
}

/*
 * INEFFICIENT UNION APROACH stolen from wiki(http://cs.wikipedia.org/wiki/Endianita) 
 */
template <typename INT_SIZE>
INT_SIZE endian2(INT_SIZE data)
{
	INT_SIZE i, i2;
	uint8_t tmp;
	union
	{
		INT_SIZE val;
		uint8_t bytes[sizeof(INT_SIZE)];
	} lf;

	lf.val = data;

	for (i = 0, i2 = sizeof(INT_SIZE) - 1; i < sizeof(INT_SIZE) / 2; i++, i2--)
	{
		tmp = lf.bytes[i];
		lf.bytes[i] = lf.bytes[i2];
		lf.bytes[i2] = tmp;
	}

	return lf.val;
}

//bool is_big_endian()
//{
//    static const int i = 1;
//    return *((char *)&i) == 0;
//}
