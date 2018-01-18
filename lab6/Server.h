#pragma once
#include <vector>
#include <iostream>
#include <iterator>
#include <string>
#include <random>

struct accInfo
{
	std::string		username;
	std::string		salt;
	int				password_verifier;
};

class Server
{
public:
	Server();
	~Server();

	void signUp(std::string username, std::string salt, int password_verifier);
	int  signIn(std::string username, int a, std::string &salt, int &B, std::hash<std::string> &H);


private:
	std::vector<accInfo> database;

	int m_module;
	int m_generator;
	int m_random_number;
};

