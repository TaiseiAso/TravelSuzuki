#ifndef split_h
#define split_h

#include <vector>
#include <string>

class StringUtil
{
public:
	// ��������w�肵�������ŕ������������񃊃X�g�ɂ��ĕԂ�
	static std::vector<std::string> split(std::string str, char del);
};

#endif // !split_h