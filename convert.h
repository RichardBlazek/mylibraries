#pragma once

#include <string>
#include <stdexcept>

#include "types.h"
#include "mat.h"

namespace convert
{
    uint64 Stoui(std::string text)
    {
        uint64 number=0;
        for(auto c:text)
        {
            if(isdigit(c))
            {
                number=number*10+c-'0';
            }
            else
            {
                throw std::invalid_argument("Conversion failed: '"+text+"' is not a number");
            }
        }
        return number;
    }
    int64 Stoi(std::string text)///String TO Int-------------------------------------------------------
    {
        int64 number=0;
        bool zapor=(text[0]=='-');
        if(zapor||text[0]=='+')
        {
        	number=Stoui(text.substr(1));
        }
        else
        {
            return Stoui(text);
        }
        if(zapor)
        {
            number=(-number);
        }
        return number;
    }
    double Stof(std::string text, char decimalSeparator='.')///String TO Float
    {
        uint8 pos=0;
        double number=0;
        bool zapor=(text[0]=='-');
        uint8 beg=0;
        if(zapor||text[0]=='+')
        {
			beg=1;
        }
		for(uint16 i=beg;i<text.size();++i)
		{
			if(isdigit(text[i]))
			{
				number=(number*10)+(text[i]-'0');
			}
			else if(text[i]==decimalSeparator)
			{
				pos=i;
				break;
			}
			else
			{
                throw std::invalid_argument("Conversion failed: '"+text+"' is not a number");
			}
		}
        if(pos>beg&&pos<text.size()-1)
        {
            double mocnina=10;
            for(uint16 i=pos;i<text.size();++i, mocnina*=10)
            {
                if(isdigit(text[i]))
                {
                    number+=(text[i]-'0')/mocnina;
                }
                else
                {
                    throw std::invalid_argument("Conversion failed: '"+text+"' is not a number");
                }
            }
        }
        else
        {
            throw std::invalid_argument("Conversion failed: '"+text+"' is not a number");
        }
        if(zapor)
        {
            number=(-number);
        }
        return number;
    }
    std::string ToString(uint64 number)
    {
        std::string text;
        do
        {
            text=char('0'+number%10)+text;
            number/=10;
        }while(number!=0);
        return text;
    }
    inline std::string ToString(int64 number, std::string plus="", std::string minus="-")
    {
        return (number<0?minus:plus)+ToString(uint64(std::abs(number)));
    }
    std::string ToString(double number, char dec_separ='.', uint64 precision=1'000'000)
    {
        std::string integral=ToString(int64(number)), rest=ToString(uint64(std::abs(number-int64(number))*precision));
        rest.resize(ToString(precision).size()-1, '0');
        return integral+(rest.empty()?"":dec_separ+rest);
    }
}