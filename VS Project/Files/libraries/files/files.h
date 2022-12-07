#pragma once
#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)
#include <string>
#include <fstream>
#include <iostream>
#include "../dirent.h" // ==== downloaded library ====
#include <filesystem>
#include <sstream>
#include <tgmath.h>
#include "../exceptions.h"
#include "../QOL.h"
#include "../parse/misc_parse.h"
using std::cout;
using std::endl;
using std::string;
using std::ios;
using std::fstream;
using std::istream;

namespace Files {

	class File {
	private:
		string name;
		int state;
		fstream file;

	public:
		File() { name = consts::unk; state = 0; }

		File(
			string inputname,
			int inputstate
		) {
			if (inputname != "") {
				parse::replaceSpaces(&inputname);
				name = inputname;
				state = inputstate;
				this->open(name, state, consts::inputpath);
			}
			else {
				cout << exc::file::inputnamenotvalid(inputname) << endl;
			}
		}

		File(
			File const& copy
		) {
			if (copy.name != "") {
				name = copy.name;
				state = copy.state;
				open(copy.name, copy.state, consts::inputpath);
			}
			else {
				cout << exc::file::inputnamenotvalid(copy.name) << endl;
			}

		}

		~File(
		) {
			if (file)
				file.close();
		}

		File& operator=(
			File copy
			) {
			if (this == &copy) {
				return *this;
			}
			this->state = copy.state;
			this->name.swap(copy.name);
			this->file.swap(copy.file);
			return *this;
		}
		void open(string inputname, int type, string path) {
			parse::replaceSpaces(&inputname);
			if (file) file.close();
			try {
				switch (type / 10) {
				case 1:
					switch (type % 10) {
					case 0:
						break;
					case 1:
						file.open(path + inputname + ".bin", ios::binary | ios::in);
						if (!file) throw exc::file::filenotvalid(inputname + ".bin");
						break;
					case 2:
						file.open(path + inputname + ".bin", ios::binary | ios::out);
						if (!file) throw exc::file::filenotvalid(inputname + ".bin");
						break;
					case 3:
						file.open(path + inputname + ".bin", ios::binary | ios::out | ios::app);
						if (!file) throw exc::file::filenotvalid(inputname + ".bin");
						break;
					default:
						throw exc::type::typenotvalid(type);
					}
					break;

				case 2:
					switch (type % 10) {
					case 0:
						break;
					case 1:
						file.open(path + inputname + ".txt", ios::in);
						if (!file) throw exc::file::filenotvalid(inputname + ".txt");
						break;
					case 2:
						file.open(path + inputname + ".txt", ios::out);
						if (!file) throw exc::file::filenotvalid(inputname + ".txt");
						break;
					case 3:
						file.open(path + inputname + ".txt", ios::out | ios::app);
						if (!file) throw exc::file::filenotvalid(inputname + ".txt");
						break;
					default:
						throw exc::type::typenotvalid(type);
					}
					break;

				default:
					throw exc::type::typenotvalid(type);
					break;
				}
			}
			catch (string exc) {
				cout << exc << endl;
			}
		}
	private:
		bool SkipBOM(istream& in)
		{
			char test[4] = { 0 };
			in.read(test, 3);
			if (strcmp(test, "\xEF\xBB\xBF") == 0)
				return true;
			in.seekg(0);
			return false;
		}
	public:

		string getName(
		) {
			return name;
		}

		void setName(
			string inputname
		) {
			if (inputname != "") {
				parse::replaceSpaces(&inputname);
				name = inputname;
			}
			else {
				cout << exc::file::inputnamenotvalid(inputname) << endl;
			}
		}

		fstream* getFile(
		) {
			return &file;
		}

		int getState(
		) {
			return state;
		}

	};

	class InputFile {
	private:
		File* allfiles;
		int noFiles;

	public:
		InputFile() {
			allfiles = nullptr;
			noFiles = 0;
		}

		InputFile(File& file) {
			allfiles = new File[1];
			allfiles[0] = file;
			noFiles = 1;
		}

		void operator+=(const File& file) {
			if (noFiles > 0 && allfiles != nullptr) {
				File* temp = new File[noFiles];
				for (int i(0); i < noFiles; i++) {
					temp[i] = allfiles[i];
				}
				delete[] allfiles;
				allfiles = new File[noFiles + 1];
				for (int i(0); i < noFiles; i++) {
					allfiles[i] = temp[i];
				}
				delete[] temp;
				allfiles[noFiles] = file;
				noFiles++;
			}
			else if (noFiles == 0 && allfiles == nullptr) {
				allfiles = new File[1];
				allfiles[0] = file;
				noFiles = 1;
			}
		}

		File& operator[](int i) {
			if (i < noFiles)
				return allfiles[i];
			else {
				cout << exc::file::outofbounds(i) << endl;
			}
		}

		File* getArgs() {
			return allfiles;
		}

		File getArg(int i) {
			return allfiles[i];
		}

		int getNoFiles() {
			return noFiles;
		}

		void setArgs(
			int argc,
			char* argv[]
		) {
			if (allfiles != nullptr) {
				delete[] allfiles;
			}
			if (argc > 1) {
				allfiles = new File[argc - 1];
				noFiles = argc - 1;
				for (int i(0); i < argc - 1; i++) {
					allfiles[i] = File((string)argv[i + 1], 21);
				}
			}
			else if (argc == 1) {
				string s = getWinProjectPath();
				s.append("Files\\\\input\\\\");
				int i;
				DIR* directory;
				struct dirent* entry;
				string x, temp;
				bool skip = true;
				try {
					if ((directory = opendir(getWinProjectPath().append("Files\\input\\").c_str())) == NULL)
						throw;
				}
				catch (...) {
					cout << exc::file::dirnotvalid(getWinProjectPath().append("Files\\input\\").c_str()) << endl;
				}
				if ((directory = opendir(getWinProjectPath().append("Files\\input\\").c_str())) != NULL) {
					while ((entry = readdir(directory)) != NULL) {
						if (entry->d_type == DT_REG && ((x = entry->d_name) != "." || (x = entry->d_name) != "..")) {
							skip = true;
							for (int i(0); i < x.length(); i++) {
								if (x[i] == '.')
									skip = false;
								if (skip)
									temp.push_back(x[i]);
							}
							*this += File(temp, 21);
						}
					}
				}

			}
		}
	private:
		inline string getProjectPath() {
			string s = EXPAND(UNITTESTPRJ);
			s.erase(0, 1); // erase the first quote
			s.erase(s.size() - 2); // erase the last quote and the dot
			return s;
		}
		inline string getWinProjectPath() {
			string s = EXPAND(UNITTESTPRJ);
			s.erase(0, 1); // erase the first quote
			s.erase(s.size() - 2); // erase the last quote and the dot
			for (int i(0); i < s.size(); i++) {
				if (s[i] == '\\') {
					s.insert(i++, "\\");
				}
			}
			return s;
		}

	};
}

namespace Database {
	enum class Datatype {
		NONE,
		CHAR, VARCHAR,
		BINARY,	VARBINARY, HEX, INTEGER, INT, FLOAT, DOUBLE, BOOL,
		ENUM, SET,
		DATE, TIME, DATETIME, YEAR,	MONTH,
		MONEY
	};
	class Entry {
		string value;
		Datatype datatype;
		int datatype_size;
	public:
		Entry(){
			value = "";
			datatype = Datatype::NONE;
			datatype_size = 0;
		}
		Entry(string val, Datatype dtype, int size) {
			parse::replaceSpaces(&val);
			value = val;
			datatype = dtype;
			datatype_size = size;
		}

		// OPERATORS
		inline Entry* operator=(const Entry* copy) {
			this->value = copy->value;
			this->datatype = copy->datatype;
			this->datatype_size = copy->datatype_size;
			return this;
		}
		inline bool operator==(const Entry* copy) {
			return (copy->datatype == this->datatype && copy->value == this->value) ? true: false;
		}
		inline char operator[](int index) {
			return (index < value.length()) ? value[index] : 0x0;
		}
		Entry* operator+(Entry* copy) {
			if (copy->datatype == this->datatype) {
				parse::undoSpaces(&(this->value));
				parse::undoSpaces(&(copy->value));
				int isum;
				float fsum;
				double dsum;
				switch (this->datatype)
				{
				case Datatype::NONE:
					break;
				case Datatype::CHAR:
				case Datatype::VARCHAR:
					if (this->datatype_size <= this->value.length() + copy->value.length())
						this->value.append(copy->value);
					break;
				case Datatype::BINARY:
				case Datatype::VARBINARY: {
					string addition(math::addBinary(this->value, copy->value));
					if (addition.length() < this->datatype_size)
						this->value = addition;
					break;
				}
				case Datatype::HEX: {
					std::stringstream temp;
					isum = std::stoi(this->value, 0, 16) + std::stoi(copy->value, 0, 16);
					temp << std::hex << isum;
					this->value = temp.str();
					break;
				}
				case Datatype::INT:
				case Datatype::INTEGER:
					isum = std::atoi(this->value.c_str()) + std::atoi(copy->value.c_str());
					if (datatype_size > 0) {
						if (std::ceil(std::log10(isum)) < this->datatype_size)
							this->value = std::to_string(isum);
					}
					else
						this->value = std::to_string(isum);

					break;
				case Datatype::FLOAT:
					fsum = std::stof(this->value.c_str()) + std::stof(copy->value.c_str());;
					if (datatype_size > 0) {
						if (std::ceil(std::log10(fsum)) < this->datatype_size)
							this->value = std::to_string(fsum);
					}
					else
						this->value = std::to_string(fsum);
					break;
				case Datatype::DOUBLE:
					dsum = std::stod(this->value.c_str()) + std::stod(copy->value.c_str());;
					if (datatype_size > 0) {
						if (std::ceil(std::log10(dsum)) < this->datatype_size)
							this->value = std::to_string(dsum);
					}
					else
						this->value = std::to_string(dsum);
					break;
				case Datatype::BOOL:
					if (
						this->value == "1" ||
						parse::ToUpper(this->value) == "TRUE" ||
						copy->value == "1" ||
						parse::ToUpper(copy->value) == "TRUE"
						) {
						this->value = "TRUE";
					}
					else
						this->value = "FALSE";
					break;
				default:
					break;
				}
				parse::replaceSpaces(&(this->value));
				parse::replaceSpaces(&(copy->value));
			}

		}
		void WriteTo(const Files::File* file) {
			
		}
		void Read() {

		}

	};

	class Table {
	public:
		string name;
		Files::File table;
		Files::File info;
		int info_size;
	public:

		Table() {}
		Table(string Name) {
			parse::replaceSpaces(&Name);
			name = Name;
			table.setName(name);
			table.open(name, 13, consts::outputpath);
			info.setName(name+"_info");
			info.open(name + "_info", 22, consts::outputpath);
		}
		
		void Create(string* columns, string* datatypes, int size) {
			parse::replaceSpaces(columns, size);
			parse::replaceSpaces(datatypes, size);
			for (int i(0); i < size; i++) {
				info.getFile()->write(columns[i].c_str(), columns[i].length());
				info.getFile()->write(" ", 1);
				info.getFile()->write(datatypes[i].c_str(), datatypes[i].length());
				info.getFile()->write(" ", 1);
			}
		}
	};
}