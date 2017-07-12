#pragma once

class TextInputBox: public CentredLabel
{
public:
	enum class State {Normal, Active, MouseDown, ShiftDown};
	virtual void SetPosition(const SDL::Rect& pos)override
	{
		CentredLabel::SetPosition(pos);
		CentredLabel::position.h=font.TextSize("").y+4;
	}
private:
	State state=State::Normal;
	size_t shift=0;
	size_t cursor=0;
	size_t selection_start=0;
	bool star;
	size_t MoveIndex(size_t now, int change)const
	{
		if(text.size()==0)
		{
			return now;
		}
		size_t new_index=now;
		if(new_index+change<=text.size()&&new_index+change>=0)
		{
			new_index+=change;
		}
		while(new_index+change<=text.size()&&new_index+change>=0&&!IsMultibyteStart(text[new_index+1])&&!IsASCII(text[new_index]))
		{
			new_index+=change;
		}
		return new_index;
	}
	size_t SelectionStart()const
	{
		return std::min(cursor, selection_start);
	}
	size_t SelectionSize()const
	{
		return std::abs(int(cursor)-int(selection_start));
	}
	size_t StarToUtf(size_t star)const
	{
		size_t i=0;
		while(star>0)
		{
			if(!IsMultibyteByte(text[i]))
			{
				--star;
			}
			++i;
		}
		return i;
	}
	size_t UtfToStar(size_t utf)const
	{
		size_t count=0;
		for(size_t i=0; i<utf; ++i)
		{
			if(!IsMultibyteByte(text[i]))
			{
				++count;
			}
		}
		return count;
	}
	std::string StarText()const
	{
		return std::string(UtfToStar(text.size()), '*');
	}
	int RangePixelSize(size_t beg, size_t size)const
	{
		return font.TextSize(text.substr(beg, size)).x;
	}
	int IndexToPixelPosition(size_t i)const
	{
		return RangePixelSize(shift, i<shift?0:i-shift);
	}
	size_t PixelPositionToIndex(int pos)const
	{
		size_t i=shift;
		while(i<=text.size()&&MoveIndex(i,1)!=i)
		{
			i=MoveIndex(i,1);
			if(IndexToPixelPosition(i)>=pos)
			{
				return MoveIndex(i,-1);
			}
		}
		return i;
	}
	size_t MaxSize()const
	{
		return PixelPositionToIndex(position.w-4)-shift;
	}
	size_t GetCursorPositionFromMouse(SDL::Point mousepos)
	{
		if(star)
		{
			std::string backup_text=text;
			text=StarText();
			size_t index=PixelPositionToIndex(mousepos.x-position.x);
			text=backup_text;
			return StarToUtf(index);
		}
		else
		{
			return PixelPositionToIndex(mousepos.x-position.x);
		}
	}
	SDL::Rect Limit(const SDL::Rect& value)
	{
		return SDL::Rect(std::max(position.x+2, std::min(value.x, position.x+position.w-4)), value.y, value.x+value.w>position.x+position.w-4?(position.x+position.w-4)-std::max(position.x+2, std::min(value.x, position.x+position.w-4)):value.w, value.h);
	}
	void MoveCursorAt(size_t pos)
	{
		selection_start=cursor=pos;
	}
	void MoveCursorOnMouse(SDL::Point mousepos)
	{
		MoveCursorAt(GetCursorPositionFromMouse(mousepos));
	}
	void SetSelectionToMouse(SDL::Point mousepos)
	{
		cursor=GetCursorPositionFromMouse(mousepos);
	}
	std::string VisibleText()const
	{
		return text.substr(shift, MaxSize());
	}
	void EraseSelection()
	{
		text.erase(SelectionStart(), SelectionSize());
		selection_start=cursor=SelectionStart();
	}
	std::string GetSelection()const
	{
		return text.substr(SelectionStart(), SelectionSize());
	}
	void InsertText(const std::string& inserted)
	{
		EraseSelection();
		if(text.size()+inserted.size()>1000)
		{
			SDL::MessageBox::Show("Warning", "Too long", SDL::MessageBox::Flags::Warning);
			return;
		}
		text.insert(cursor, inserted);
		cursor+=inserted.size();
		selection_start=cursor;
	}
	bool ShiftLeft()
	{
		auto help=shift;
		auto text=VisibleText();
		shift=MoveIndex(shift, -1);
		help=help-shift;
		auto next=VisibleText();
		shift=shift+help;
		return next.substr(help)==text&&next.size()==text.size()+help;
	}
	void ShiftRight()
	{
		while(IndexToPixelPosition(cursor)>position.w-4)
		{
			shift=MoveIndex(shift, 1);
		}
	}
	void Shift()
	{
		std::string backup_text=text;
		size_t backup_cursor=cursor;
		size_t backup_ss=selection_start;
		if(star)
		{
			cursor=UtfToStar(backup_cursor);
			selection_start=UtfToStar(backup_ss);
			text=StarText();
		}
		if(shift>text.size())
		{
			shift=text.size();
		}
		while(shift>0&&(cursor<=shift||ShiftLeft()))
		{
			shift=MoveIndex(shift, -1);
		}
		ShiftRight();
		if(star)
		{
			text=backup_text;
			cursor=backup_cursor;
			selection_start=backup_ss;
		}
	}
public:
	TextInputBox()=default;
	TextInputBox(const SDL::Rect& position, bool star)
		:CentredLabel("", position), star(star)
	{
		CentredLabel::position.h=font.TextSize("").y+4;
	}
	size_t GetCursorPosition()const
	{
		return cursor;
	}
	size_t GetSelectionStart()const
	{
		return selection_start;
	}
	void SetCursorPosition(size_t cur)
	{
		MoveCursorAt(cur);
	}
	virtual void DrawOn(SDL::Renderer& rend)override
	{
		std::string backup_text=text;
		size_t backup_cursor=cursor;
		size_t backup_ss=selection_start;
		if(star)
		{
			cursor=UtfToStar(backup_cursor);
			selection_start=UtfToStar(backup_ss);
			text=StarText();
		}
		if(state!=State::Normal)
		{
			rend.Draw(Limit(SDL::Rect(position.x+IndexToPixelPosition(SelectionStart())+2, position.y+2, RangePixelSize(SelectionStart(), SelectionSize()), position.h-4)), SDL::Color(160,200,160));
			rend.Draw(Limit(SDL::Rect(position.x+IndexToPixelPosition(cursor)+2, position.y+2, 1, position.h-4)), SDL::Color::Black());
		}
		rend.DrawBorder(position, SDL::Color::Black());
		rend.Draw(font, VisibleText(), SDL::Color::Black(), SDL::Point(position.x+2, position.y+2));
		if(star)
		{
			text=backup_text;
			cursor=backup_cursor;
			selection_start=backup_ss;
		}
	}
	virtual bool Catch(const SDL::Event& evt)override
	{
		if(evt.GetType()==evt.Type::MouseButtonDown)
		{
			if(position.EnclosesPoint(evt.GetMouseButton().Position))
			{
				state=State::MouseDown;
				MoveCursorOnMouse(evt.GetMouseButton().Position);
			}
			else
			{
				state=State::Normal;
			}
		}
		else if(state==State::MouseDown&&evt.GetType()==evt.Type::MouseButtonUp)
		{
			state=State::Active;
		}
		else if(state==State::MouseDown&&evt.GetType()==evt.Type::MouseMotion)
		{
			SetSelectionToMouse(evt.GetMouseMotion().Absolute);
		}
		else if((state==State::Active||(state==State::ShiftDown&&cursor==selection_start))&&evt.GetType()==evt.Type::TextInput)
		{
			InsertText(evt.GetTextInput().Text);
			Shift();
			return true;
		}
		else if(state==State::Active&&evt.GetType()==evt.Type::Keydown&&(evt.GetKeyboard().Mod&SDL::Keymod::Shift)!=SDL::Keymod::None)
		{
			state=State::ShiftDown;
		}
		if(state==State::ShiftDown)
		{
			if(evt.GetType()==evt.Type::Keyup&&(evt.GetKeyboard().Mod&SDL::Keymod::Shift)==SDL::Keymod::None)
			{
				state=State::Active;
			}
			else if(evt.GetType()==evt.Type::Keydown&&evt.GetKeyboard().Key==SDL::Keycode::Left)
			{
				cursor=MoveIndex(cursor, -1);
				Shift();
			}
			else if(evt.GetType()==evt.Type::Keydown&&evt.GetKeyboard().Key==SDL::Keycode::Right)
			{
				cursor=MoveIndex(cursor, 1);
				Shift();
			}
			else if(evt.GetKeyboard().Key==SDL::Keycode::Home)
			{
				cursor=0;
				Shift();
			}
			else if(evt.GetKeyboard().Key==SDL::Keycode::End)
			{
				cursor=text.size();
				Shift();
			}
		}
		if(state==State::Active&&evt.GetType()==evt.Type::Keydown)
		{
			if(evt.GetKeyboard().Key==SDL::Keycode::Backspace)
			{
				if(SelectionSize()==0&&cursor>0)
				{
					cursor=MoveIndex(cursor, -1);
				}
				EraseSelection();
				Shift();
			}
			else if(evt.GetKeyboard().Key==SDL::Keycode::Delete)
			{
				if(SelectionSize()==0&&cursor<text.size())
				{
					selection_start=MoveIndex(selection_start, 1);
				}
				EraseSelection();
				Shift();
			}
			else if(evt.GetKeyboard().Key==SDL::Keycode::Left)
			{
				MoveCursorAt(MoveIndex(cursor, -1));
				Shift();
			}
			else if(evt.GetKeyboard().Key==SDL::Keycode::Right)
			{
				MoveCursorAt(MoveIndex(cursor, 1));
				Shift();
			}
			else if(evt.GetKeyboard().Key==SDL::Keycode::Home)
			{
				MoveCursorAt(0);
				Shift();
			}
			else if(evt.GetKeyboard().Key==SDL::Keycode::End)
			{
				MoveCursorAt(text.size());
				Shift();
			}
			else if((evt.GetKeyboard().Mod&SDL::Keymod::Ctrl)!=SDL::Keymod::None)
			{
				if(evt.GetKeyboard().Key==SDL::Keycode::V)
				{
					InsertText(SDL::Clipboard::GetText());
					Shift();
				}
				else if(evt.GetKeyboard().Key==SDL::Keycode::C)
				{
					SDL::Clipboard::SetText(GetSelection());
				}
				else if(evt.GetKeyboard().Key==SDL::Keycode::X)
				{
					SDL::Clipboard::SetText(GetSelection());
					EraseSelection();
					Shift();
				}
				else if(evt.GetKeyboard().Key==SDL::Keycode::A)
				{
					selection_start=0;
					cursor=text.size();
					Shift();
				}
			}
		}
		return false;
	}
};