#ifndef object_h
#define object_h

namespace game::object
{
	class Object
	{
	public:
		// ����������
		virtual void initialize() {};
		// �I������
		virtual void finalize() {};

		// ���͂ɂ��ω�
		virtual void action() {};
		// �X�e�b�v���Ƃɐi�ޏ���
		virtual void update() {};
		// ��Ԃ̕`��
		virtual void draw() const {};
	};
}

#endif // !object_h