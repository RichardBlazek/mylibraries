#pragma once

class Button: public CentredLabel
{
public:
	enum class State {Normal, MouseOn, MouseDown};
private:
	State state=State::Normal;
public:
	using CentredLabel::CentredLabel;
	virtual void DrawOn(SDL::Renderer& rend)override
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
		CentredLabel::DrawOn(rend);
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
			if(state==State::Normal&&position.EnclosesPoint(evt.GetMouseMotion().Absolute))
			{
				state=State::MouseOn;
			}
			if(state!=State::Normal&&!position.EnclosesPoint(evt.GetMouseMotion().Absolute))
			{
				state=State::Normal;
			}
		}
		return false;
	}
};