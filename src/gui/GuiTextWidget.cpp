#include "GuiTextWidget.hpp"

GuiTextWidget::GuiTextWidget(Window* window)
  : GuiObject(window)
{
  m_text.setFont(AssetsStorageSingleton::Instance().GetFont("GoudyBookletter.ttf"));

  m_margins.SetMargins(12.f, 12.f, 12.f, 12.f);

  m_color = sf::Color(255, 255, 255);
  m_hoverColor = sf::Color(230, 230, 230);

  m_hoverEffect = false;
}

GuiTextWidget::~GuiTextWidget()
{
}

void GuiTextWidget::Update(float deltaTime)
{
  if (m_mouseTracking == false)
  {
    return;
  }

  const sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*m_window->GetWindow()));

  if (m_text.getGlobalBounds().contains(mousePosition))
  {
    if (m_hoverEffect)
    {
      m_text.setFillColor(m_hoverColor);
    }

    if (EventHandlerSingleton::Instance().GetMouseInput().IsMouseKeyReleased(MouseInput::MouseKey::Left))
    {
      Clicked();
    }
  }
  else
  {
    m_text.setFillColor(m_color);
  }
}

sf::FloatRect GuiTextWidget::GetSize()
{
  return m_text.getGlobalBounds();
}

void GuiTextWidget::SetPosition(const float x, const float y)
{
  GuiObject::SetPosition(x, y);
  m_text.setPosition(m_position);
}
  
void GuiTextWidget::SetPosition(const sf::Vector2f &position)
{
  GuiObject::SetPosition(position);
  m_text.setPosition(m_position);
}

void GuiTextWidget::SetCharacterSize(const int size)
{
  m_text.setCharacterSize(size);
}

void GuiTextWidget::SetText(const std::string &text)
{
  m_text.setString(text);
}

void GuiTextWidget::SetText(const char *text)
{
  m_text.setString(text);
}

void GuiTextWidget::SetColor(const int r, const int g, const int b)
{
  m_color = sf::Color(r, g, b);
  m_text.setFillColor(m_color);
}

void GuiTextWidget::SetColor(const sf::Color &color)
{
  m_color = color;
  m_text.setFillColor(color);
}

void GuiTextWidget::SetHoverCapture(bool enabled)
{
  m_hoverEffect = enabled;
}

void GuiTextWidget::SetHoverColor(const int r, const int g, const int b)
{
  m_hoverColor = sf::Color(r, g, b);
}

void GuiTextWidget::SetHoverColor(const sf::Color &color)
{
  m_hoverColor = color;
}

void GuiTextWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(m_text, states);
}
