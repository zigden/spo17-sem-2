#include <iostream>
#include <iterator>
#include "Client.h"
#include "Server.h"
#include <time.h>

std::string random_string();

int main()
{
	setlocale(LC_ALL, "Russian");
	Server* server = new Server();

	// Этап регистрации
	std::string I = "Username";
	std::string p = "password";

	std::cout << "-->Началась регистрация нового польователя\n\n";
	int q = 7;
	int N = 2 * q + 1;
	int g = 128;
	int k = 3;
	std::cout << "I = " << I << "\n";
	std::cout << "p = " << p << "\n";
	std::cout << "q = " << q << "\n";
	std::cout << "N = " << N << "\n";
	std::cout << "g = " << g << "\n";
	std::cout << "k = " << k << "\n\n";

	std::string s = random_string();
	std::hash<std::string> H;
	size_t x = H(s + p);
	std::cout << "Хеш от соли и пароля равен " << x << "\n";

	long long v = g;

	for (long i = 0; i < x; ++i) {
		if (i % 10000000 == 0)
			std::cout << "\rПрогресс " << ((float)i / x) * 100 << "%   ";
		v = v * g;
		if (v > N)
			v = fmod(v, N);
	}
	std::cout << "\rВерификатор пароля на стороне сервера равен " << v << "\n";

	server->signUp(I, s, v);
	std::cout << "Серверу отправлены I, s, и v: " << I << " " << s << " " << v << "\n";

	// Этап авторизации
	std::cout << "\n-->Начался процесс авторизации\n\n";
	
	int a = rand() % 117;
	std::cout << "a = " << a << "\n";
	long long A = g;

	for (long i = 0; i < a; ++i) {
		if (i % 10000000 == 0)
			std::cout << "\rПрогресс " << ((float)i / a) * 100 << "%   ";
		A = A * g;
		if (A > N)
			A = fmod(A, N);
	}
	std::cout << "\rСекретное одноразовое число А равено " << A << "\n";

	std::string serverSalt;
	int B;
	server->signIn(I, A, serverSalt, B, H);
	
	std::cout << "Числа А и В клиента = " << A << " " << B << "\n";

	if (B == 0) {
		std::cout << "B = 0 !";
		system("pause");
		return 0;
	}

	size_t u = H(std::to_string(A) + std::to_string(B));
	std::cout << "u клиента = " << u << "\n";

	x = H(serverSalt + p);
	long long S = B - k*v;
	for (long i = 0; i < a + u*x; ++i) {
		if (i % 10000000 == 0)
			std::cout << "\rПрогресс " << ((float)i / (a + u*x)) * 100 << "%   ";
		S = S * (B - k*v);
		if (A > N)
			S = fmod(S, N);
	}
	
	std::cout << "\rКлюч сессии клиента = " << S << "\n";
	size_t K = H(std::to_string(S));
	std::cout << "Искомый ключ для шифрования клиента = " << K << "\n";

	size_t M = H(std::to_string(N) + std::to_string(g) + I + s + std::to_string(A) + std::to_string(B) + std::to_string(K));
	std::cout << "Подтверждение М клиента = " << M << "\n";

	size_t R = H(std::to_string(A) + std::to_string(M) + std::to_string(K));
	std::cout << "Подтверждалка клиента R = " << R << "\n";

	std::cout << "\n";
	system("pause");
	delete server;
	return 0;
}

std::string random_string()
{
	std::cout << "Генерация соли\n";
	std::string rand_str;
	int rand_size = rand() % 30;
	std::cout << "rand_size = " << rand_size << "\n";
	rand_str.resize(rand_size);

	for (char &symbol : rand_str) // 65:90
		symbol = rand() % 25 + 65;

	copy(rand_str.begin(), rand_str.end(), std::ostream_iterator<char>(std::cout));

	std::cout << "\n\n";
	return rand_str;
}