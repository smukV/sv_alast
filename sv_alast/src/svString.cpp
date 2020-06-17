#include "svString.h"

namespace sv_alast{
	String::String(const char * str) 
	{
		m_Size = StrLen(str);
		m_Data = new char[m_Size+ 1];
		StrCpy(m_Data, str);
	}
	String::String(const String& other)
	{
		m_Size = other.m_Size;
		m_Data = new char[m_Size + 1];
		StrCpy(m_Data, other.m_Data);
	}
	String::String(String && other) noexcept
	{
		m_Size = other.m_Size;
		m_Data = other.m_Data;

		other.m_Size = 0;
		other.m_Data = nullptr;
	}

	String & String::operator=(const String & other)
	{
		if (m_Data != nullptr)
			delete m_Data;
		m_Size = other.m_Size;
		m_Data = new char[m_Size + 1];
		StrCpy(m_Data, other.m_Data);
		return *this;
	}
	String & String::operator=(String && other)
	{
		if (m_Data != nullptr)
			delete m_Data;
		m_Size = other.m_Size;
		m_Data = other.m_Data;

		other.m_Size = 0;
		other.m_Data = nullptr;
		return *this;
	}
	String   String::operator+(const String & other) const
	{
		size_t res_Size = m_Size + other.m_Size;
		char* res_Data = new char[res_Size + 1];

		StrCpy(res_Data, this->m_Data);
		StrCpy(res_Data, other.m_Data, m_Size, other.m_Size);

		return String(res_Data);
	}
	String & String::operator+=(const String & other)
	{
		(*this) = (*this) + other;
		return *this;
	}

	const char * String::Data() const
	{
		return m_Data;
	}
	const size_t String::Size() const
	{
		return m_Size;
	}
	
	size_t StrLen(const char * str)
	{
		size_t result = 0;
		for (result; str[result] != '\0'; result++);
		return result;
	}
	void   StrCpy(char * destStr, const char * srcStr)
	{
		size_t i = 0;
		for (i; srcStr[i] != '\0'; i++)
			destStr[i] = srcStr[i];
		destStr[i] = '\0';
	}
	void   StrCpy(char * destStr, const char * srcStr, size_t size)
	{
		size_t i;
		for(i = 0; i <= size; i++)
			destStr[i] = srcStr[i];
		destStr[i] = '\0';
	}
	void   StrCpy(char * destStr, const char * srcStr, size_t start_Pos, size_t size)
	{
		size_t i;
		int end_Pos = start_Pos + size;
		for (i = start_Pos; i <= end_Pos; i++)
			destStr[i] = srcStr[i - start_Pos];
		destStr[i] = '\0'; 
	}
}