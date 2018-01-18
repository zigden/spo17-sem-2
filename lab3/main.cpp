#include <fstream>
#include "participant.h"

int main()
{
	int mod = 17;
	int gen = 3;

	std::ofstream donya;
	donya.open("talk.txt");
	donya << "Модуль = " << mod << "\n";
	donya << "Генератор = " << gen << "\n";

	Participant Bob("Bob", donya, mod, gen);
	Participant Alica("Alica", donya, mod, gen);

	Bob.set_interlocutor_value(Alica.get_eigenvalue());
	Alica.set_interlocutor_value(Bob.get_eigenvalue());

	donya.close();
	system("pause");

	return 0;
}