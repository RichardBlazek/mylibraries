#pragma once

//Třída pro uchovávající zvuková data
class WAVBuffer
{
private:
	size_t len=0;
	uint8* buf=nullptr;
public:
	//Konstruktory
	WAVBuffer()=default;
	WAVBuffer(uint8* buf, size_t len):len(len), buf(buf){}
	//Buffer je jen jeden
	WAVBuffer(const WAVBuffer& init)=delete;
	WAVBuffer& operator=(const WAVBuffer& init)=delete;
	//Přesun
	WAVBuffer(WAVBuffer&& init):len(init.len), buf(init.buf)
	{
		init.buf=nullptr;
		init.len=0;
	}
	WAVBuffer& operator=(WAVBuffer&& init)
	{
		len=init.len;
		buf=init.buf;
		init.buf=nullptr;
		init.len=0;
		return *this;
	}
	~WAVBuffer()
	{
		if(buf)SDL_FreeWAV(buf);
	}
	size_t size()const
	{
		return len;
	}
    uint8* data()const
    {
    	return buf;
    }
};