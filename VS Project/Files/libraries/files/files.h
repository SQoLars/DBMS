#pragma once
#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)
#include "../QOL.h"
#include <string>
#include <fstream>
#include "../exceptions.h"
#include <iostream>
#include "../dirent.h" // ==== downloaded library ====

namespace Files {

	class File {
	private:
		std::string name;
		int state;
		std::fstream file;

	public:
		File() { name = consts::unk; state = 0; }

		File(
			std::string inputname,
			int inputstate
		) {
			if (inputname != "") {
				name = inputname;
				state = inputstate;
				this->open(name, state, consts::inputpath);
			}
		}

		File(
			File const& copy
		) {
			if (copy.name != "") {
				name = copy.name;
				state = copy.state;
				this->open(copy.name, copy.state, consts::inputpath);

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
		// TO CHANGE INPUTPATH
	private:
		void open(std::string inputname, int type, std::string path) {
			if (file) file.close();

			switch (type / 10) {
			case 1:
				switch (type % 10) {
				case 0:
					break;
				case 1:
					file.open(path + inputname, std::ios::binary | std::ios::in); 
					if (!file) throw exc::file::filenotvalid(inputname);
					break;
				case 2:
					file.open(path + inputname, std::ios::binary | std::ios::out);
					if (!file) throw exc::file::filenotvalid(inputname);
					break;
				case 3:
					file.open(path + inputname, std::ios::binary | std::ios::out | std::ios::app);
					if (!file) throw exc::file::filenotvalid(inputname);
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
					file.open(path + inputname, std::ios::in);
					//if (!file) throw exc::file::filenotvalid(inputname);
					break;
				case 2:
					file.open(path + inputname, std::ios::out);
					if (!file) throw exc::file::filenotvalid(inputname);
					break;
				case 3:
					file.open(path + inputname, std::ios::out | std::ios::app);
					if (!file) throw exc::file::filenotvalid(inputname);
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

		bool SkipBOM(std::istream& in)
		{
			char test[4] = { 0 };
			in.read(test, 3);
			if (strcmp(test, "\xEF\xBB\xBF") == 0)
				return true;
			in.seekg(0);
			return false;
		}
	public:

		std::string getName(
		) {
			return name;
		}

		void setName(
			std::string inputname
		) {
			if (inputname != "") // TO ADD REGEX
				name = inputname;
		}

		std::fstream* getFile(
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
					allfiles[i] = File((std::string)argv[i + 1], 21);
				}
			}
			else if (argc == 1) {
				std::string s = getWinProjectPath();
				s.append("Files\\\\input\\\\");
				int i;
				DIR* directory;
				struct dirent* entry;
				std::string x;
				if ((directory = opendir(getWinProjectPath().append("Files\\input\\").c_str())) != NULL) {
					while ((entry = readdir(directory)) != NULL) {
						if (entry->d_type == DT_REG && ((x = entry->d_name) != "." || (x = entry->d_name) != "..")) {
							*this += File(x, 21);
						}
					}
				}
			}


		}
	private:
		inline std::string getProjectPath() {
			std::string s = EXPAND(UNITTESTPRJ);
			s.erase(0, 1); // erase the first quote
			s.erase(s.size() - 2); // erase the last quote and the dot
			return s;
		}
		inline std::string getWinProjectPath() {
			std::string s = EXPAND(UNITTESTPRJ);
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