#include "participant.h"

void Participant::generateKey()
{
	setlocale(LC_ALL, "Russian");

	m_key = pow(m_interlocutor_value, m_random_number);
	m_key = fmod(m_key, m_module);

	std::cout << m_name << " �����:\n";
	std::cout << "������ = " << m_module << "\n";
	std::cout << "��������� = " << m_generator << "\n";
	std::cout << "����������� �������� = " << m_eigenvalue << "\n";
	std::cout << "���������� �������� = " << m_interlocutor_value << "\n";
	std::cout << "���� = " << m_key << "\n\n";
}
