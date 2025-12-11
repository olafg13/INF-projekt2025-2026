#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <fstream>

class Scores{ //klasa zapisu wyniku
    private:
    std::string date;
    public:
    Scores();
    bool save(const std::string& filename, int points);
};

Scores::Scores(){

}

bool Scores::save(const std::string& filename, int points){ //zapis wyniku - pobranie ilości punktów oraz dodanie do tego daty
    std::time_t now = std::time(nullptr); //przypisanie aktualnego czasu do now
    std::tm* t = std::localtime(&now); //zamiana czasu na lokalną datę

    std::ostringstream oss; //stworzenie string do którego trafi data
    oss << std::setw(2) << std::setfill('0') << t->tm_mday << "-" //setw ustawia minimalną szerokość, setfill uzupełnia niewypełnione miejsca zerami
        << std::setw(2) << std::setfill('0') << t->tm_mon + 1 << "-" //tm_mday, tm_mon itd. zwracają w liczbie dzień, miesiąc itd.
        << std::setw(2) << std::setfill('0') << (t->tm_year % 100) << " " //%100, aby zwrócić ostatnie 2 cyfry roku (2025-25)
        << std::setw(2) << std::setfill('0') << t->tm_hour << ":"
        << std::setw(2) << std::setfill('0') << t->tm_min << ":"
        << std::setw(2) << std::setfill('0') << t->tm_sec;

    date = oss.str(); //przypisanie oss w formie stringa do zmiennej date (string)

    std::vector<std::string> lines;
    std::ifstream infile(filename);
    if (infile.is_open()) { //wczytanie pliku z wynikami
        std::string line;
        while (std::getline(infile, line)) {
            lines.push_back(line);
        }
        infile.close();
    }

    if (lines.size() >= 10) {
        lines.erase(lines.begin()); //usunięcie najstarszych wyników, jeżeli lines.size >= 10
    }

    lines.push_back(date + "   " + std::to_string(points)); //dodanie aktualnego wyniku do lines 

    std::ofstream outfile(filename, std::ios::trunc);
    if (!outfile.is_open()) return false; //sprawdzenie poprawności wczytania pliku

    for (size_t i = 0; i < lines.size(); i++) { //nadpisanie pliku nowymi danymi
        outfile << lines[i] << "\n";
        }

    outfile.close();
    return true;
}
// klasa odpowiedzialna za menu z najnowszymi wynikami
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
        lines.push_back(line); //utworzenie wektora z wynikami
    file.close();

    scoreNumber = std::min((int)lines.size(), 10); //ustalenie ilości wyników

    menu.resize(scoreNumber); //dopasowanie wielkości wektora do ilości elementów

    if (!font.loadFromFile("LiberationSans-Regular.ttf")) return; //sprawdzenie czy istnieje pli z czcionką

    for (int i = 0; i < scoreNumber; i++) { //utworzenie napisów z wynikami
        menu[i].setFont(font);	
        menu[i].setFillColor(sf::Color::White);
        menu[i].setString(lines[i]);

        if (i < 5) //rozstawienie napisów z wynikami na ekranie
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
	for (int i = 0; i < scoreNumber; i++) //rysowanie napisów z wynikami
	{
		window.draw(menu[i]);
	}
    window.draw(wyjscie);
}
