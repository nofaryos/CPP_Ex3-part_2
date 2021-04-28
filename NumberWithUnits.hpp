#pragma once
#include <string>
#include <map>
#include <fstream>
namespace ariel{
	class NumberWithUnits{

		private:
			
			double value;
			std::string type;
		 
		public:
			NumberWithUnits(double value, const std::string& type);
			
			double getVal() const{
				return this->value;
			}
			
			std::string getName() const{
				return this->type;
			}
			
			static void read_units(std::ifstream& f);
				
			
			
			NumberWithUnits& operator+=(const NumberWithUnits& other);
			NumberWithUnits& operator-=(const NumberWithUnits& other);
			
			NumberWithUnits operator+() const;
			NumberWithUnits operator-() const;
			
			NumberWithUnits& operator++();
			NumberWithUnits& operator--();
			
			NumberWithUnits operator++(int dummy_flag_for_postfix_increment);
			NumberWithUnits operator--(int dummy_flag_for_postfix_increment);		
			
			friend bool operator==(const NumberWithUnits& c1, const NumberWithUnits& c2);
			friend bool operator!=(const NumberWithUnits& c1, const NumberWithUnits& c2);
			
			friend bool operator<(const NumberWithUnits& c1, const NumberWithUnits& c2);
			friend bool operator>(const NumberWithUnits& c1, const NumberWithUnits& c2);
			friend bool operator<=(const NumberWithUnits& c1, const NumberWithUnits& c2);
			friend bool operator>=(const NumberWithUnits& c1, const NumberWithUnits& c2);
			
			friend NumberWithUnits operator-(const NumberWithUnits& c1, const NumberWithUnits& c2);
			friend NumberWithUnits operator+(const NumberWithUnits& c1, const NumberWithUnits& c2);
			
			friend NumberWithUnits operator*(const NumberWithUnits& c1, double d);
			friend NumberWithUnits operator*(double d, const NumberWithUnits& c1);
			
			friend std::ostream& operator<< (std::ostream& os, const NumberWithUnits& c);
			friend std::istream& operator>> (std::istream& is, NumberWithUnits& c);
			
	};
}
		
		