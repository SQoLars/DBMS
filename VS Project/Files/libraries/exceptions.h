#pragma once
#include <string>

namespace exc {
	class type : public std::exception {
	public: static const std::string typenotvalid(int a) {
		std::string x;
		x.append("Error in files.h Files::File -> type ");
		x.append(std::to_string(a));
		x.append(" not valid.");
		return x;
	}
	};

	class file : public std::exception {
	public: static const std::string filenotvalid(std::string a) {
		std::string x;
		x.append("Error in files.h Files::File -> file \"");
		x.append(a);
		x.append("\" was not found or could not be opened.");
		return x;
	}
	};
}
