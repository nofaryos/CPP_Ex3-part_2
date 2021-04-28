#include  "NumberWithUnits.hpp"
#include <iostream>
using namespace std;
namespace ariel{
		
		static map<string, map<string, double> > units;
		NumberWithUnits::NumberWithUnits(double value, const string& type){
			units.at(type);
			this->value=value;
			this->type=type;
    }
		void NumberWithUnits::read_units(std::ifstream& f){
			string type_1, type_2;
			char operatorEq = '=';
			double val_1 = 0, val_2 = 0;
			
			while(f >> val_1 >> type_1 >> operatorEq >> val_2 >> type_2){
				units[type_1] [type_2] = val_2;
				units[type_2] [type_1] = val_1/val_2;
				
				for(auto &pair: units[type_1]){
					double tempVal = units[type_2][type_1] * pair.second;
					units[type_2][pair.first] = tempVal;
                    units[pair.first][type_2] = 1/tempVal; 
				}
				
				for(auto &pair: units[type_2]){
					double tempVal = units[type_1][type_2] * pair.second;
					units[type_1][pair.first] = tempVal;
                    units[pair.first][type_1] = 1/tempVal; 
				}
			}
				
				
		}
		
		double convert(const string& type_1, const string& type_2, double value){
			if(type_1 == type_2){
				return value;
			}
			if (units[type_1][type_2] != 0){
				return (units[type_1][type_2])*value;
			}
			
			throw invalid_argument{"illegal convert"};
		}
		
		
		NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& other){
			this-> value += convert(other.type, this->type, other.getVal());
			return *this;
		}
		
		NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& other){
			this-> value -= convert(other.type, this->type, other.getVal());
			return *this;
		}
		NumberWithUnits NumberWithUnits::operator+() const{
			return NumberWithUnits(this->value, this->type);
		}
		NumberWithUnits NumberWithUnits::operator-() const{
			return NumberWithUnits(-(this->value), this->type);
		}//^
		
		NumberWithUnits& NumberWithUnits::operator++(){
			++(this->value);
			return *this;
		}//^
		NumberWithUnits& NumberWithUnits::operator--(){//^
			--(this->value);
			return *this;
		}
		NumberWithUnits NumberWithUnits::operator++(int dummy_flag_for_postfix_increment){
			NumberWithUnits copy = *this;
			(this->value)++;
			return copy;
			
		}//^
		NumberWithUnits NumberWithUnits::operator--(int dummy_flag_for_postfix_increment){
			NumberWithUnits copy = *this;
			(this->value)--;
			return copy;
		}//^
		
		bool operator==(const NumberWithUnits& c1, const NumberWithUnits& c2){
			const double eps = 0.00001;
			return (abs(convert(c2.type, c1.type, c2.value) - c1.value) <= eps);
		}
		bool operator!=(const NumberWithUnits& c1, const NumberWithUnits& c2){
			return !(c1 == c2);
		}//^
		
		bool operator<(const NumberWithUnits& c1, const NumberWithUnits& c2){
			return ((c1.value - convert(c2.type, c1.type, c2.value)) < 0 );
		}
		bool operator>(const NumberWithUnits& c1, const NumberWithUnits& c2){
			return ((c1.value - convert(c2.type, c1.type, c2.value)) > 0 );
		}
		bool operator<=(const NumberWithUnits& c1, const NumberWithUnits& c2){
			return (c1 < c2 || c1 == c2);
		}
		bool operator>=(const NumberWithUnits& c1, const NumberWithUnits& c2){
			return (c1 > c2 || c1 == c2 );
		}
		
		NumberWithUnits operator-(const NumberWithUnits& c1, const NumberWithUnits& c2){
			return c1 + (-c2);
			}
		NumberWithUnits operator+(const NumberWithUnits& c1, const NumberWithUnits& c2){
			double d = convert(c2.type, c1.type, c2.value);
			double num = c1.value + d;
			return NumberWithUnits(num, c1.type);
		}
		
		NumberWithUnits operator*(const NumberWithUnits& c1, double d){
			
			return NumberWithUnits((c1.value)*d, c1.type);
		};
		NumberWithUnits operator*(double d, const NumberWithUnits& c1){
			return c1*d;
			
		};
		
		std::ostream& operator<< (std::ostream& os, const NumberWithUnits& c){
			return os <<  c.value << "[" << c.type << "]";;
		}
		std::istream& operator>> (std::istream& is, NumberWithUnits& c){
			string type;
			double value = 0;
            char ch = ']';
            is >> value >> ch;
            while(ch != ']') {
                if(ch != '[') { 
				type.insert(type.end(), ch);
				}
                is >> ch;
            }

            if(units[type].empty()){
				throw invalid_argument{"invalid unit"};
			}
                c.value = value;
                c.type = type;
                return is;
            }
		
};