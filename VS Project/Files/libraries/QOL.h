#pragma once
#include <string>

namespace consts {
	inline std::string getProjectPath() {
		std::string s = EXPAND(UNITTESTPRJ);
		s.erase(0, 1); // erase the first quote
		s.erase(s.size() - 2); // erase the last quote and the dot
		s.append("Files\\");
		return s;
	}

	const std::string inputpath = getProjectPath() + "input\\";
	const std::string unk = "unknown";
}