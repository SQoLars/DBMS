//
//		SQoLars: DBMS
//		-> A light sqlite-like database management system.
//
//		Project realised by students:
//			Simion Cristina Florentina
//			Toma Andreea
//			Vlad Liviu Alexandru
//			Vlad Rares
//		- ASE CSIE I.E. Eng G 1068
//
//		Repository:
//		https://github.com/SQoLars/DBMS
//
//		Documentation:
//		https://github.com/SQoLars/DBMS#readme
//
//		Sections: (ctrl+f)
//			INCLUDE BLOCK
//			MAIN BLOCK
//          TESTING BLOCK

//=============== INCLUDE BLOCK ===============
#include "libraries/files/files.h"
#include "libraries/parse/misc_parse.h"
#include <iostream>

class idk {
public:
	float index;
	int a;
	std::string z;
};

//=============== MAIN BLOCK ===============
int main(
	int argc,
	char *argv[])
{
	Files::File* commands = Args::setArgs(argc, argv);

	//=============== TESTING BLOCK ===============	
	for (int i(0); i< argc-1; i++) {

		std::cout << commands[i].getName() << " " << commands[i].getState() << "\n";
	}

}
