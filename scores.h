#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <fstream>

class Scores{
    private:
    std::string date;
    public:
    Scores();
    bool save(const std::string& filename, int points);
};

Scores::Scores(){

}

bool Scores::save(const std::string& filename, int points){
    std::time_t now = std::time(nullptr);
    std::tm* t = std::localtime(&now);

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << t->tm_mday << "-"
        << std::setw(2) << std::setfill('0') << t->tm_mon + 1 << "-"
        << std::setw(2) << std::setfill('0') << (t->tm_year % 100) << " "
        << std::setw(2) << std::setfill('0') << t->tm_hour << ":"
        << std::setw(2) << std::setfill('0') << t->tm_min << ":"
        << std::setw(2) << std::setfill('0') << t->tm_sec;

    date = oss.str();

    std::vector<std::string> lines;
    std::ifstream infile(filename);
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            lines.push_back(line);
        }
        infile.close();
    }

    if (lines.size() >= 10) {
        lines.erase(lines.begin());
    }

    lines.push_back(date + "   " + std::to_string(points));

    std::ofstream outfile(filename, std::ios::trunc);
    if (!outfile.is_open()) return false;

    for (size_t i = 0; i < lines.size(); i++) {
        outfile << lines[i] << "\n";
        }

    outfile.close();
    return true;
}

class ScoreMenu
{

private:
    int scoreNumber;
    std::vector<std::string> lines;
	sf::Font font;
    sf::Text wyjscie;
	std::vector<sf::Text> menu;
public:
	ScoreMenu(float width, float height, const std::string& filename);
	void draw(sf::RenderWindow &window);
};


ScoreMenu::ScoreMenu(float width, float height, const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line))
        lines.push_back(line);
    file.close();

    scoreNumber = std::min((int)lines.size(), 10);

    menu.resize(scoreNumber);

    if (!font.loadFromFile("arial.ttf")) return;

    for (int i = 0; i < scoreNumber; i++) {
        menu[i].setFont(font);	
        menu[i].setFillColor(sf::Color::White);
        menu[i].setString(lines[i]);

        if (i < 5)
            menu[i].setPosition(width / 24, (height / 7) * (i + 1));
        else
            menu[i].setPosition(width / 2, (height / 7) * (i - 4));
    }

    wyjscie.setFont(font);	
    wyjscie.setFillColor(sf::Color::White);
    wyjscie.setString("Nacisnij dowolna strzalke,\naby wrocic do menu glownego");
    wyjscie.setPosition(width / 24, (height / 7) * 6);
}

void ScoreMenu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < scoreNumber; i++)
	{
		window.draw(menu[i]);
	}
    window.draw(wyjscie);
}
