#include "security/md5.h"
#include "security/base64.h"
#include <iostream>
#include <string>

int main()
{
	std::string str = "hello";
	char md5[64] = { 0 };
	MD5_Calculate(str.c_str(), str.length(), md5);
	std::cout << md5 << std::endl;
	std::cout << base64_encode(str) << std::endl;
	std::cout << base64_decode(base64_encode(str)) << std::endl;

	std::cin.get();
}