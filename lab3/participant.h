#pragma once
#include <fstream>
#include <iostream>
#include <math.h>

class Participant
{
public:
	Participant(const char* name, std::ofstream& file, int module, int generator)
	:
	m_name(name),
	m_file(file),
	m_module(module), 
	m_generator(generator)
	{
		m_random_number = rand() % 50 + 1; // от 1 до 50
		m_eigenvalue = pow(m_generator, m_random_number);
		m_eigenvalue = fmod(m_eigenvalue, m_module);

		m_file << m_name << " said: " << m_eigenvalue << "\n";
	};

	void set_interlocutor_value(double value) { m_interlocutor_value = value; generateKey(); }
	double  get_eigenvalue() { return m_eigenvalue; }

private:

	const char* m_name;
	std::ofstream& m_file;

	int m_module;
	int m_generator;
	int m_random_number;

	double m_eigenvalue;
	double m_interlocutor_value;

	double m_key;

	void generateKey();
};