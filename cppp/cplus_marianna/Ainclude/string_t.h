#ifndef _STRING_H__
#define _STRING_H__


class string_h
{
	public:
		string_h();
		string_h(char* _other);
		string_h(const string_h _other);
		~string_h();
		string_h operator=(const string_h _other);
		inline int	Lenth()const;
		inline const string_h& GetString()const ; 
		
	private:
		char* m_str;
		
};


std::ostrem & operator<<(std::ostrem& os, const string_h _str);

#endif


