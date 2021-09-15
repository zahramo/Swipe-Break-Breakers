#include <string>
class User {
private:
	std::string name;
	int bestScore;
public:
	User(std::string name = "", int bestScore = 0);
	std::string getName();
	int getBestScore() const;
	bool operator<(const User user2) const;
};