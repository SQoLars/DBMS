#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "../../files/files.h"

namespace SQL {
	std::string whole;
	std::string temp;
	std::string GetCommands(Files::File fileobj) {
		while (!fileobj.getFile()->eof()) {
			*fileobj.getFile() >> temp;
			whole.append(temp);
			whole.append(" ");
		}
		return whole;
	}

	class commands {
	private:
		std::string x;

	public:
		void GetCommands(Files::File file) {

		}
	};
}