#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>

#include "Installer.h"

int main() {
	std::vector<std::wstring> filePaths = {
		TEXT(".\\src\\a.txt"),
		TEXT(".\\src\\b.txt"),
		TEXT(".\\src\\c.txt")
	};
	std::wstring dstDirPath = TEXT(".\\dst\\");
	
	Installer installer(dstDirPath, filePaths);
	try {
		installer.Install();
	}
	catch (const std::exception error) {
		std::cout << "Error: " << error.what() << std::endl;
	}

	return 0;
}
