#include "TextProcessor.h"
using namespace std;


void TextProcessor::setText(const string& text)
{
	text_ = text;
}

string TextProcessor::getText() const
{
	return text_;
}



string TextProcessor::removeSpaces()
{
	string ret = text_;
	if (ret.empty())
		return ret;

	int icount = 0;

	int pos = 0;
	for (pos = 0; pos < ret.size();icount++)
	{
		if (ret[pos] == ' ')
		{
			ret.erase(pos, 1);
		}
		else
			++pos;
	}

	return ret;
}

string TextProcessor::toLowerCase()
{
	string ret = text_;
	
	int siz = ret.size();
	if (siz == 0)
		return ret;

	for (int i = 0; i < siz; i++)
	{
		if (isAlpha(ret[i]) && ret[i] < 'a')
		{
			ret[i] += 32;
		}
	}

	return ret;
}

string TextProcessor::toUpperCase()
{
	string ret = text_;

	int siz = ret.size();
	if (siz == 0)
		return ret;

	for (int i = 0; i < siz; i++)
	{
		if (isAlpha(ret[i]) && ret[i] > 'Z')
		{
			ret[i] -= 32;
		}
	}

	return ret;
}

string TextProcessor::reverse()
{
	string ret = text_;

	int siz = ret.size();
	if (siz == 0)
		return ret;

	for (int i = 0; i < siz; i++)
	{
		ret[i] = text_[siz - i - 1];
	}

	return ret;
}



int TextProcessor::countOccurrences(const std::string& substr)
{
	int len = substr.size();
	int siz = text_.size();
	int icount = 0;

	if (text_.empty())
		return icount;

	int pos = 0;
	int dest = siz - len;

	while (pos <= dest)
	{
		string sub = text_.substr(pos, len);
		if (sub == substr)
		{
			icount++;
			pos += len;
		}
		else
			pos++;
	}

	return icount;
}

vector<int> TextProcessor::findPositions(const string& substr)
{
	vector<int> poses;

	if (text_.empty())
		return poses;

	int len = substr.size();
	int siz = text_.size();
	int icount = 0;

	int pos = 0;
	int dest = siz - len;

	while (pos <= dest)
	{
		string sub = text_.substr(pos, len);
		if (sub == substr)
		{
			poses.push_back(pos);
			pos += len;
		}
		else
			pos++;
	}

	return poses;
}

string TextProcessor::replaceAll(const std::string& from, const std::string& to)
{
	string ret = text_;

	int len = from.size();
	int lent = to.size();
	int siz = ret.size();

	if (siz == 0)
	{
		return ret;
	}

	int pos = 0;

	while (pos <= (ret.size()-len))
	{
		string sub = ret.substr(pos, len);
		if (sub == from)
		{
			ret.replace(pos, len, to);
			pos += lent;
		}
		else
			pos++;
	}


	return ret;
}



vector<string> TextProcessor::split(char delimiter)
{
	vector<string> slices;

	if (text_.empty())
		return slices;

	string delim(1, delimiter);
	vector<int> vec = findPositions(delim);

	int n = vec.size() + 1;
	vec.push_back(text_.size());
	int start = -1;

	for (int i = 0; i < n; i++)
	{
		int len = vec[i] - start - 1;

		if (len == 0)
		{
			start = vec[i];
			continue;
		}
		else
		{
			string temp = text_.substr(start + 1, len);
			slices.push_back(temp);
			start = vec[i];
		}
	}

	return slices;
}



int TextProcessor::getCharCount()
{
	return text_.size();
}

int TextProcessor::getCharCountNoSpaces()
{
	return (text_.size() - countOccurrences(" "));
}

int TextProcessor::getLineCount()
{
	return (countOccurrences("\n") + 1);
}



bool TextProcessor::isPalindrome()
{
	if (text_.empty())
		return false;

	TextProcessor utemp1(removeSpaces());
	TextProcessor temp2(utemp1.reverse());
	if (utemp1.toLowerCase() == temp2.toLowerCase())
		return true;
	return false;
}

bool TextProcessor::isNumeric()
{
	if (text_.empty())
		return false;
	else
	{
		if (text_[0] == '-' || text_[0] == '+')
		{
			if (isDigit(text_[1]))
			{
				bool flag = true;
				for (int i = 2; i < text_.size(); i++)
				{
					if (isDigit(text_[i]))
						continue;
					else if (text_[i] == '.' && flag)
					{
						flag = false;
						continue;
					}
					else
						return false;
				}

				return true;
			}
			else return false;
		}
		else if (isDigit(text_[0]))
		{
			bool flag = true;
			for (int i = 1; i < text_.size(); i++)
			{
				if (isDigit(text_[i]))
					continue;
				else if (text_[i] == '.' && flag)
				{
					flag = false;
					continue;
				}
				else
					return false;
			}
			return true;
		}
		else
			return false;
	}
}

bool TextProcessor::containsOnly(const std::string& charset)
{
	if (text_.empty())
		return true;


	int len = text_.size();

	for (int i = 0; i < len; i++)
	{
		if (charset.find(text_.substr(i, 1)) == string::npos)
			return false;
	}

	return true;
}



string TextProcessor::centerAlign(int width, char fillChar) // 居中对齐
{
	int len = text_.size();

	if (len >= width)
		return text_;

	else
	{
		int l = (width - len) / 2;
		int r = (width - len) - l;
		string left(l, fillChar);
		string right(r, fillChar);
		left += text_;
		left += right;
		return left;
	}
}

string TextProcessor::leftAlign(int width, char fillChar)   // 左对齐
{
	int len = text_.size();

	if (len >= width)
		return text_;

	else
	{
		int r = width - len;
		string right(r, fillChar);
		string ret(text_);
		ret += right;
		return ret;
	}
}

string TextProcessor::rightAlign(int width, char fillChar)  // 右对齐
{
	int len = text_.size();

	if (len >= width)
		return text_;

	else
	{
		int l = width - len;
		string left(l, fillChar);
		string ret(text_);
		left += ret;
		return left;
	}
}