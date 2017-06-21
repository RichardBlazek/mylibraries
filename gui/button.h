#pragma once

class Button
{
public:
	enum class State {Normal, MouseOn, MouseDown};
private:
	std::string text;
	SDL::Rect position;
	State state=State::Normal;
public:
	Button()=default;
	Button(const std::string& text, const SDL::Rect& position)
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
	void DrawOn(SDL::Renderer& rend)
	{
		if(state==State::MouseDown)
		{
			rend.Draw(position, SDL::Color(150, 150, 255));
		}
		else if(state==State::MouseOn)
		{
			rend.Draw(position, SDL::Color(175, 175, 250));
		}
		else
		{
			rend.Draw(position, SDL::Color(200, 200, 200));
		}
		rend.DrawBorder(position, SDL::Color::Black());
		rend.Draw(font, text, SDL::Color::Black(), position);
	}
	bool Catch(const SDL::Event& evt)
	{
		if(state==State::MouseOn&&evt.GetType()==SDL::Event::Type::MouseButtonDown)
		{
			state=State::MouseDown;
		}
		if(state==State::MouseDown&&evt.GetType()==SDL::Event::Type::MouseButtonUp)
		{
			state=State::Normal;
			return true;
		}
		if(evt.GetType()==evt.Type::MouseMotion)
		{
			if(state==State::Normal&&position.IsEnclosingPoint(evt.GetMouseMotion().Absolute))
			{
				state=State::MouseOn;
			}
			if(state!=State::Normal&&!position.IsEnclosingPoint(evt.GetMouseMotion().Absolute))
			{
				state=State::Normal;
			}
		}
		return false;
	}
};