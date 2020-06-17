#pragma once
namespace sv_alast {
	class String
	{
	private:
		char* m_Data;
		size_t m_Size;
	public:
		String(): m_Data(nullptr), m_Size(0){}
		String(const char* str);
		String(const String& other);
		String(String&& other) noexcept;
		String& operator=(const String& other);
		String operator+(const String& other) const;
		String& operator+=(const String& other);
		const char* Data()const;
		const size_t Size() const;
	};

	size_t StrLen(const char* str);
	void StrCpy(char* destStr, const char* srcStr);
	void StrCpy(char* destStr, const char* srcStr, size_t size);
	void StrCpy(char* destStr, const char* srcStr, size_t start_Pos, size_t size);
}
