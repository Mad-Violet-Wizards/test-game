#pragma once

class Debug
{

  public:

    static void Draw(Window &window);

    static void AddRect(const sf::FloatRect &rect, sf::Color color = sf::Color::White);

  private:

    static std::vector<sf::RectangleShape> m_rects;
};
