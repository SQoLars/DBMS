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
			else
				cout << exc::parsing::emptyfile() << endl;
		}

		void Parse() {
			std::istringstream iss (str);
			std::string command, value, temp;
			while(!iss.eof()) {
				while (!iss.eof()) {
					iss >> temp;
					if (IsCommand(temp) || iss.eof()) {
						createCommand(value); //===============================================//
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

	class SQLCommands {
		static enum class Type {
			NONE,
			CREATE,
			DROP,
			DISPLAY,
			INSERT,
			SELECT,
			DEL,
			UPDATE
		};
		std::string commandatr;
		Type type;
		
	public:
		SQLCommands() {
			commandatr = "";
			type = Type::NONE;
		}
		SQLCommands(std::string value) {
			commandatr = value;
			std::istringstream iss(value);
			std::string temp;
			iss >> temp;
			parse::ToUpper(&temp);
			if (temp == "CREATE") { type = Type::CREATE; parseCREATE(); }
			else if (temp == "DROP") { type = Type::DROP; parseDROP(); }
			else if (temp == "DISPLAY") { type = Type::DISPLAY; parseDISPLAY(); }
			else if (temp == "INSERT") { type = Type::INSERT; parseINSERT(); }
			else if (temp == "SELECT") { type = Type::SELECT; parseSELECT(); }
			else if (temp == "DELETE") { type = Type::DEL; parseDELETE(); }
			else if (temp == "UPDATE") { type = Type::UPDATE; parseUPDATE(); }
		}
	private:
		void parseCREATE() {
			// to be continued
		}
		void parseDROP() {

		}
		void parseDISPLAY() {

		}
		void parseINSERT() {

		}
		void parseSELECT() {

		}
		void parseDELETE() {

		}
		void parseUPDATE() {

		}
	};
}

namespace SQLConsts {
	const enum class datatypes {

	};
}