#pragma once

#include "../QOL.h"
#include <string>
#include <fstream>

namespace Files {

	class File {
	protected:
		std::string name;
		std::fstream file;

	public:	
		File() {}

		File(
			std::string inputname
		) {
			if (inputname != "") {
				name = inputname;
				if (!file)
					file.open(consts::path + inputname);
			}
		}

		~File(
		) {
			name = "";
			if (file)
				file.close();
		}

		File(
			File const& copy
		) {
			if (copy.name != "") {
				name = copy.name;
				if (!file)
					file.open(consts::path + copy.name);
			}
			
		}

		File& operator=(
			File copy
		) {
			if (this == &copy) {
				return *this;
			}
			this->name.swap(copy.name);
			this->file.swap(copy.file);
			return *this;
		}

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

		bool getStatus(
		) {
			return (file) ? true : false;
		}

	};
}

namespace Args {
	Files::File* setArgs(
		int argc,
		char* argv[]
	) {

		Files::File* commands = new Files::File[argc-1];

		for (int i(0); i < argc - 1; i++) {
			commands[i] = Files::File((std::string)argv[i + 1]);
		}
		return commands;
	}
}