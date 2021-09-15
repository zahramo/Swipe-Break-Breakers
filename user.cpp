#include "user.hpp"

User :: User(std::string name_, int bestScore_)
{
	name = name_;
	bestScore = bestScore_;
}

std::string User :: getName()
{
	return name;
}

int User :: getBestScore() const
{
	return bestScore;
}

bool User::operator<(const User user2) const
{
	return bestScore > user2.getBestScore();
}