#pragma once

#include <numeric>
#include <iostream>
#include <string>

namespace yourname 
{
	template <typename T>
	class RationalNumber  
	{
	private:
		T numerator_;
		T denominator_;

		void simplify() 
		{
			T temp = std::gcd(numerator_, denominator_);
			numerator_ /= temp;
			denominator_ /= temp;
		}
	public:
		RationalNumber(T numerator = 0, T denominator = 1) : numerator_(numerator), denominator_(denominator) 
		{
			if (denominator_ == 0) throw std::invalid_argument("Denominator cannot be zero.");
			if (numerator_ < 0 && denominator_ < 0) 
			{
				numerator_ *= -1;
				denominator *= -1;
			}
			else if (denominator_ < 0)
			{
				numerator_ *= -1;
				denominator_ *= -1;
			}
			simplify();
		}

		/*friend RationalNumber<T> operator+(const RationalNumber& left, const RationalNumber& right);
		friend RationalNumber<T> operator-(const RationalNumber& left, const RationalNumber& right);
		friend RationalNumber<T> operator*(const RationalNumber& left, const RationalNumber& right);
		friend RationalNumber<T> operator/(const RationalNumber& left, const RationalNumber& right);*/

		friend RationalNumber<T> operator+(const RationalNumber<T>& left, const RationalNumber<T>& right)
		{
			T new_denominator = std::lcm(left.denominator_, right.denominator_);
			T new_numerator = left.numerator_ * (new_denominator / left.denominator_) + right.numerator_ * (new_denominator / right.denominator_);
			return RationalNumber<T>(new_numerator, new_denominator);
		}
		friend RationalNumber<T> operator-(const RationalNumber<T>& left, const RationalNumber<T>& right)
		{
			T new_denominator = std::lcm(left.denominator_, right.denominator_);
			T new_numerator = left.numerator_ * (new_denominator / left.denominator_) - right.numerator_ * (new_denominator / right.denominator_);
			return RationalNumber<T>(new_numerator, new_denominator);
		}
		friend RationalNumber<T> operator*(const RationalNumber<T>& left, const RationalNumber<T>& right)
		{
			T gcd1 = std::gcd(left.numerator_, right.denominator_);
			T gcd2 = std::gcd(left.denominator_, right.numerator_);
			T new_numerator = (left.numerator_ / gcd1) * (right.numerator_ / gcd2);
			T new_denominator = (left.denominator_ / gcd2) * (right.denominator_ / gcd1);

			RationalNumber<T> new_number(new_numerator, new_denominator);
			return new_number;
		}
		friend RationalNumber<T> operator/(const RationalNumber<T>& left, const RationalNumber<T>& right)
		{
			RationalNumber<T> temp(right.denominator_, right.numerator_);
			RationalNumber<T> new_number = left * temp;
			return new_number;
		}
		friend std::ostream& operator<<(std::ostream& os, const RationalNumber<T>& source)
		{
			os << source.numerator_ << "/" << source.denominator_;
			return os;
		}

		RationalNumber<T>& operator+=(const RationalNumber& right) 
		{
			*this = *this + right;
			return *this;
		}
		RationalNumber<T>& operator-=(const RationalNumber& right) 
		{
			*this = *this - right;
			return *this;
		}
		RationalNumber<T>& operator*=(const RationalNumber& right) 
		{
			*this = *this * right;
			return *this;
		}
		RationalNumber<T>& operator/=(const RationalNumber& right) 
		{
			*this = *this / right;
			return *this;
		}

		RationalNumber<T>& operator++() 
		{
			numerator_ += denominator_;
			simplify();
			return *this;
		}

		RationalNumber<T> operator++(int) 
		{
			RationalNumber<T> res = *this;
			numerator_ += denominator_;
			simplify();
			return res;
		}

		RationalNumber<T>& operator--()
		{
			numerator_ -= denominator_;
			simplify();
			return *this;
		}

		RationalNumber<T> operator--(int)
		{
			RationalNumber<T> res = *this;
			numerator_ -= denominator_;
			simplify();
			return res;
		}

		/*friend std::ostream operator<<(std::ostream& os, const RationalNumber& src);*/
		
	};
	
	 
} // namespace yourname
