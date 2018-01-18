#include "participant.h"

void Participant::generateKey()
{
	setlocale(LC_ALL, "Russian");

	m_key = pow(m_interlocutor_value, m_random_number);
	m_key = fmod(m_key, m_module);

	std::cout << m_name << " знает:\n";
	std::cout << "Модуль = " << m_module << "\n";
	std::cout << "Генератор = " << m_generator << "\n";
	std::cout << "Собственное значение = " << m_eigenvalue << "\n";
	std::cout << "Полученное значение = " << m_interlocutor_value << "\n";
	std::cout << "Ключ = " << m_key << "\n\n";
}
