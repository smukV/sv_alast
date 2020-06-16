#pragma once
namespace sv_alast {
	class String
	{
	private:
		char* data;
		size_t size;
	public:
		String(): data(nullptr), size(0){}
		String(const char* str);
		String(const String& other);
		String& operator=(const String& other);
	};

	size_t strlen(const char* str);
	void strcpy(char* destStr, const char* srcStr);
	void strcpy(const char* inStr, const char* outStr, size_t size);
}

