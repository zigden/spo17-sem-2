#include "Server.h"

Server::Server()
{
}

Server::~Server()
{
}

void Server::signUp(std::string username, std::string salt, int password_verifier)
{
	database.push_back({ username, salt, password_verifier });
}

int Server::signIn(std::string username, int a, std::string &salt, int &B, std::hash<std::string> &H)
{
	std::cout << "-->Работает сервер\n\n";
	if (a == 0)
		return 1;

	int password_verifier;

	for (accInfo &acc : database)
		if (!acc.username.compare(username)) {
			salt = acc.salt;
			password_verifier = acc.password_verifier;
			break;
		}

	std::cout << "Для логина " << username << " найдены соль и верификатор пароля: " << salt << ", " << password_verifier << "\n";

	int g = 128;
	int N = 15;
	int k = 3;

	int b = rand() % 117;
	std::cout << "b = " << b << "\n";
	B = g;

	for (long i = 0; i < b; ++i) {
		if (i % 10000000 == 0)
			std::cout << "\rПрогресс " << ((float)i / a) * 100 << "%   ";
		B = B * g;
		if (B > N)
			B = fmod(B, N);
	}
	B = B + k * password_verifier;
	std::cout << "\rСекретное одноразовое число B равено " << B << "\n";

	std::cout << "Числа А и В сервера = " << a << " " << B << "\n";

	size_t u = H(std::to_string(a) + std::to_string(B));
	std::cout << "u сервера = " << u << "\n";

	int temp = a*(fmod(pow(password_verifier, u), N));
	long long S = temp;
	for (long i = 0; i < B; ++i) {
		if (i % 10000000 == 0)
			std::cout << "\rПрогресс " << ((float)i / B) * 100 << "%   ";
		S = S * temp;
		if (S > N)
			S = fmod(S, N);
	}
	std::cout << "\rКлюч сессии сервера = " << S << "\n";

	size_t K = H(std::to_string(S));
	std::cout << "Искомый ключ для шифрования сервера = " << K << "\n";

	size_t M = H(std::to_string(N) + std::to_string(g) + username + salt + std::to_string(a) + std::to_string(B) + std::to_string(K));
	std::cout << "Подтверждение М сервера = " << M << "\n";

	size_t R = H(std::to_string(a) + std::to_string(M) + std::to_string(K));
	std::cout << "Подтверждалка сервера R = " << R << "\n";

	std::cout << "-->Сервер закончил работу\n\n";
	return 0;
}
