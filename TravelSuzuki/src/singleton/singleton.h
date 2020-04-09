#ifndef singleton_h
#define singleton_h

#include <memory>

template <typename T>
class Singleton
{
private:
	static T* instance_; // �V���O���g���C���X�^���X

	// �R�s�[�R���X�g���N�^���֎~����
	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;

	// �R�s�[������Z�q���֎~����
	void operator=(const Singleton&) = delete;
	void operator=(Singleton&&) = delete;

protected:
	Singleton() {} // �O���ł̃C���X�^���X�쐬�͋֎~
	virtual ~Singleton() {}

public:
	// �V���O���g���C���X�^���X�ւ̎Q�Ƃ��擾����
	static T& instance()
	{
		return *instance_;
	}
	// �V���O���g���C���X�^���X�𐶐�����
	static void create()
	{
		if (!instance_) instance_ = new T();
	}
	// �V���O���g���C���X�^���X��j������
	static void destroy()
	{
		delete instance_;
		instance_ = nullptr;
	}
};

template <typename T> T* Singleton<T>::instance_ = nullptr;

#endif // !singleton_h