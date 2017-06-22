#pragma once

class Widget
{
public:
	virtual void DrawOn(SDL::Renderer& rend)=0;
	virtual bool Catch(const SDL::Event& evt)=0;
	virtual ~Widget(){}
};