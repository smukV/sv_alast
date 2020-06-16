#include "String.h"

namespace sv_alast{
	String::String(const char * str) 
	{
		//size = strlen(str);
		data = new char[size + 1];
		//strcpy(data, str);
	}
	String::String(const String & other)
	{
	}
	String & String::operator=(const String & other)
	{
		// TODO: insert return statement here
	}
	//size_t strlen(const char * str)
	//{
	//	size_t result = 0;
	//	for (result; str[result] != '\0'; result++);
	//	return result;
	//}
	//void strcpy(char * destStr, const char * srcStr)
	//{
	//	size_t i = 0;
	//	for (i; srcStr[i] != '\0'; i++)
	//		destStr[i] = srcStr[i];
	//	destStr[i] = '\0';
	//}
	//void strcpy(char * destStr, const char * srcStr, size_t size)
	//{
	//	size_t i;
	//	for(i = 0; i <= size; i++)
	//		destStr[i] = srcStr[i];
	//	destStr[i] = '\0';
	//}
}