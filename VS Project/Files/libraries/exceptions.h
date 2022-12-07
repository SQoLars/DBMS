#pragma once
#include <string>
using std::string;

namespace exc {
	class type : public std::exception {
	public:
		static const string typenotvalid(int a) {
			string x;
			x.append("Error in files.h Files::File -> type ");
			x.append(std::to_string(a));
			x.append(" not valid.");
			return x;
		}
	};

	class file : public std::exception {
	public:
		static const string filenotvalid(string a) {
			string x;
			x.append("Error in files.h Files::File -> file \"");
			x.append(a);
			x.append("\" was not found or could not be opened.");
			return x;
		}
		static const string inputnamenotvalid(string a) {
			string x;
			x.append("Error in files.h Files::File -> input name \"");
			x.append(a);
			x.append("\" is not valid.");
			return x;
		}
		static const string outofbounds(int a) {
			string x;
			x.append("Error in files.h Files::File operator[] -> \"");
			x.append(std::to_string(a));
			x.append("\" is trying to read/write out of array bounds.");
			return x;
		}
		static const string dirnotvalid(string a) {
			string x;
			x.append("Error in files.h Files::File -> directory \"");
			x.append(a);
			x.append("\" could not be fetched.");
			return x;
		}

	};

	class parsing : public std::exception {
	public:
		static const string emptyfile() {
			string x;
			x.append("Error in SQL_parse.h SQL::Commands -> the file was empty");
			return x;
		}
	};
}
