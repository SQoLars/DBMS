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
#include "libraries/parse/SQL_parse/SQL_parse.h"
#include <iostream>
#include <cstring>  
using std::cout; using std::string; using std::endl;
//=============== MAIN BLOCK ===============
int main(
	int argc,
	char *argv[])
{
	Files::InputFile InputFiles;
	InputFiles.setArgs(argc, argv);
	
	//=============== TESTING BLOCK ===============
	std::string wholefilecontent;
	wholefilecontent = SQL::Commands::GetCommands(InputFiles[0]);
	SQL::Commands x(wholefilecontent);
	x.Parse();

	//system("pause");
	return 0;
}
