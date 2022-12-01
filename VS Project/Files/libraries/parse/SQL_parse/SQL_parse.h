#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "../../files/files.h"
#include "../misc_parse.h"

namespace SQL {
	class Commands {
	private:
		std::string str;

	public:
		static std::string GetCommands(Files::File fileobj) {
			std::string wholefilecontent;
			std::string temp;
			while (!fileobj.getFile()->eof()) {
				*fileobj.getFile() >> temp;
				wholefilecontent.append(temp);
				wholefilecontent.append(" ");
			}
			parse::RemoveByteOrderMarks(&wholefilecontent);
			return wholefilecontent;
		}

		Commands(std::string wholefilecontent) {
			if (wholefilecontent.length() > 0)
				str = wholefilecontent;
		}

		void Parse() {
			std::istringstream iss (str);
			std::string command, value, temp;
			while(!iss.eof()) {
				while (!iss.eof()) {
					iss >> temp;
					if (IsCommand(temp) || iss.eof()) {
						createCommand(value);
						value.clear();
						value.append(temp);
						value.append(" ");
						break;
					}
					value.append(temp);
					value.append(" ");
				}
			}
		}

		void createCommand(std::string value) {
			
		}

		static bool IsCommand(std::string word){
			std::string temp = word;
			parse::ToUpper(&temp);
			if (temp == "CREATE"
				|| temp == "DROP"
				|| temp == "DISPLAY"
				|| temp == "INSERT"
				|| temp == "SELECT"
				|| temp == "DELETE"
				|| temp == "UPDATE"
				) {
				return true;
			}
			return false;
		}
	};
}