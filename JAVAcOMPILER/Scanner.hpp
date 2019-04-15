#pragma once

#include <fstream>
#include <string>
#include <unordered_map>
#include <initializer_list>
#include <cctype>
#include <cstdlib>
#include <numeric>
#include "Error.hpp"
#include "Token.hpp"


class Scanner
{
public:
	typedef unsigned long line_type;

	Scanner(std::string filename) :
		file(filename), line(1), max_num(std::numeric_limits<unsigned long>::max())
	{
		if (!file.is_open())
			throw Error("Error : can't open the file");

		symbol = file.get();
		init_tables(); 
	}

	Token get_token();

	line_type get_line() const {
		return line; 
	}

private:

	void init_tables();

	enum state_type { START, IDENT, NUMBER, PLUS, MINUS, EQU, AND, OR, DIV, COMMENT, STRING, SCREENING, DELIM };

	using pair_type = std::pair<std::string, token_type>;
	using init_pair_type = std::initializer_list<pair_type>;

	std::unordered_map<std::string, token_type> table_words, table_delimiters;
	std::fstream file;
	state_type state;
	int symbol;
	std::string current_token;
	line_type line;
	unsigned max_num;

	Token look_delimiters(std::string);
	Token look_words(std::string);
	Token to_number(std::string);
};