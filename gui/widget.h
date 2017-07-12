#pragma once

class Widget
{
protected:
	SDL::Rect position;
public:
	virtual void DrawOn(SDL::Renderer& rend)=0;
	virtual bool Catch(const SDL::Event& evt)=0;
	Widget()=default;
	Widget(SDL::Rect position):position(position){}
	virtual ~Widget(){}
	SDL::Rect GetPosition()const
	{
		return position;
	}
	virtual void SetPosition(const SDL::Rect& pos)
	{
		position=pos;
	}
};