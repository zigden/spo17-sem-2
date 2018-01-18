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

	// ���� �����������
	std::string I = "Username";
	std::string p = "password";

	std::cout << "-->�������� ����������� ������ �����������\n\n";
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
	std::cout << "��� �� ���� � ������ ����� " << x << "\n";

	long long v = g;

	for (long i = 0; i < x; ++i) {
		if (i % 10000000 == 0)
			std::cout << "\r�������� " << ((float)i / x) * 100 << "%   ";
		v = v * g;
		if (v > N)
			v = fmod(v, N);
	}
	std::cout << "\r����������� ������ �� ������� ������� ����� " << v << "\n";

	server->signUp(I, s, v);
	std::cout << "������� ���������� I, s, � v: " << I << " " << s << " " << v << "\n";

	// ���� �����������
	std::cout << "\n-->������� ������� �����������\n\n";
	
	int a = rand() % 117;
	std::cout << "a = " << a << "\n";
	long long A = g;

	for (long i = 0; i < a; ++i) {
		if (i % 10000000 == 0)
			std::cout << "\r�������� " << ((float)i / a) * 100 << "%   ";
		A = A * g;
		if (A > N)
			A = fmod(A, N);
	}
	std::cout << "\r��������� ����������� ����� � ������ " << A << "\n";

	std::string serverSalt;
	int B;
	server->signIn(I, A, serverSalt, B, H);
	
	std::cout << "����� � � � ������� = " << A << " " << B << "\n";

	if (B == 0) {
		std::cout << "B = 0 !";
		system("pause");
		return 0;
	}

	size_t u = H(std::to_string(A) + std::to_string(B));
	std::cout << "u ������� = " << u << "\n";

	x = H(serverSalt + p);
	long long S = B - k*v;
	for (long i = 0; i < a + u*x; ++i) {
		if (i % 10000000 == 0)
			std::cout << "\r�������� " << ((float)i / (a + u*x)) * 100 << "%   ";
		S = S * (B - k*v);
		if (A > N)
			S = fmod(S, N);
	}
	
	std::cout << "\r���� ������ ������� = " << S << "\n";
	size_t K = H(std::to_string(S));
	std::cout << "������� ���� ��� ���������� ������� = " << K << "\n";

	size_t M = H(std::to_string(N) + std::to_string(g) + I + s + std::to_string(A) + std::to_string(B) + std::to_string(K));
	std::cout << "������������� � ������� = " << M << "\n";

	size_t R = H(std::to_string(A) + std::to_string(M) + std::to_string(K));
	std::cout << "������������� ������� R = " << R << "\n";

	std::cout << "\n";
	system("pause");
	delete server;
	return 0;
}

std::string random_string()
{
	std::cout << "��������� ����\n";
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