#pragma once
#include <string>
using std::string;

namespace consts {
	inline string getProjectPath() {
		string s = EXPAND(UNITTESTPRJ);
		s.erase(0, 1); // erase the first quote
		s.erase(s.size() - 2); // erase the last quote and the dot
		s.append("Files\\");
		return s;
	}

	const string outputpath = getProjectPath() + "tables\\";
	const string inputpath = getProjectPath() + "input\\";
	const string unk = "unknown";
}

namespace math {
	inline string addBinary(string bin1, string bin2)
	{
		string addRes = "";
		int len = bin1.size(), carry = 0, re;
		len = bin1.size();
		for (int i(len - 1); i > -1; i--) {
			re = carry;
			re += (bin1[i] == '1') ? 1 : 0;
			re += (bin2[i] == '1') ? 1 : 0;
			addRes = (re % 2 == 1) ? '1' + addRes : '0' + addRes;
			carry = (re < 2) ? 0 : 1;
		}
		if (carry != 0)
			addRes = '1' + addRes;
		return addRes;
	}
}