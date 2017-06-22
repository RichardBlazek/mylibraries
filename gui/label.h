#pragma once

class Label
{
private:
	std::string text;
	SDL::Rect position;
public:
	Label()=default;
	Label(const std::string& text, const SDL::Rect& position)
		:text(text), position(position) {}
	std::string GetText()const
	{
		return text;
	}
	void SetText(const std::string& str)
	{
		text=str;
	}
	SDL::Rect GetPosition()const
	{
		return position;
	}
	void SetPosition(const SDL::Rect& pos)
	{
		position=pos;
	}
	virtual void DrawOn(SDL::Renderer& rend)
	{
		rend.Draw(font, text, SDL::Color::Black(), position);
	}
	bool Catch(const SDL::Event& evt)
	{
		return false;
	}
};