#pragma once

#include "../QOL.h"
#include <string>
#include <fstream>
#include "../exceptions.h"
#include <iostream>

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
				this->open(name, state);
			}
		}

		File(
			File const& copy
		) {
			if (copy.name != "") {
				name = copy.name;
				state = copy.state;
				this->open(copy.name, copy.state);
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

	private:
		void open(std::string inputname, int type) {
			if (file) file.close();

			switch (type / 10) {
			case 1:
				switch (type % 10) {
				case 0:
					break;
				case 1:
					file.open(consts::inputpath + inputname, std::ios::binary | std::ios::in);
					if (!file) throw exc::file::filenotvalid(inputname);
					break;
				case 2:
					file.open(consts::inputpath + inputname, std::ios::binary | std::ios::out);
					if (!file) throw exc::file::filenotvalid(inputname);
					break;
				case 3:
					file.open(consts::inputpath + inputname, std::ios::binary | std::ios::out | std::ios::app);
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
					file.open(consts::inputpath + inputname, std::ios::in);
					//if (!file) throw exc::file::filenotvalid(inputname);
					break;
				case 2:
					file.open(consts::inputpath + inputname, std::ios::out);
					if (!file) throw exc::file::filenotvalid(inputname);
					break;
				case 3:
					file.open(consts::inputpath + inputname, std::ios::out | std::ios::app);
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
		File* _allfiles;
		int noFiles;

	public:
		InputFile() {
			_allfiles = nullptr;
			noFiles = 0;
		}

		InputFile(File& file) {
			_allfiles = new File[1];
			_allfiles[0] = file;
			noFiles = 1;
		}

		void operator+=(File& file) {
			if (noFiles > 0 && _allfiles != nullptr) {
				File* temp = new File[noFiles];
				for (int i(0); i < noFiles; i++) {
					temp[i] = _allfiles[i];
				}
				delete[] _allfiles;
				_allfiles = new File[++noFiles];
				for (int i(0); i < noFiles; i++) {
					_allfiles[i] = temp[i];
				}
				_allfiles[noFiles - 1] = file;
			}
			else if (noFiles == 0 && _allfiles == nullptr) {
				_allfiles = new File[1];
				_allfiles[0] = file;
			}			
		}

		File* getArgs() {
			return _allfiles;
		}

		File getArg(int i) {
			return _allfiles[i];
		}

		void setArgs(
			int argc,
			char* argv[]
		) {
			if (_allfiles == nullptr) {
				delete[] _allfiles;
			}
			_allfiles = new File[argc - 1];
			noFiles = argc - 1;
			for (int i(0); i < argc - 1; i++) {
				_allfiles[i] = File((std::string)argv[i + 1], 21);
			}

		}

	};
}