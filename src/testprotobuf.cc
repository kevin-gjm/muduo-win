#include "Person.pb.h"  
#include <iostream>  
#include <fstream>  

#pragma comment(lib,"libprotobuf.lib") 
int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	Test::Person person;
	person.set_id(123);
	person.set_name("abc");
	person.set_email("abc@163.com");

	std::cout << "Before:" << std::endl;
	std::cout << "ID:" << person.id() << std::endl;
	std::cout << "name:" << person.name() << std::endl;
	std::cout << "email:" << person.email() << std::endl;

	std::string str;
	person.SerializeToString(&str);
	std::cout << str << std::endl;
	Test::Person person2;
	person2.ParseFromString(str);

	std::cout << "After:" << std::endl;
	std::cout << "ID:" << person2.id() << std::endl;
	std::cout << "Name:" << person2.name() << std::endl;
	std::cout << "Email:" << person2.email() << std::endl;


	system("pause");

	return 0;
}