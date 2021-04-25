#include "Installer.h"

#include <iostream>
#include <vector>
#include <windows.h>

Installer::Installer(std::wstring dstDirPath, std::vector<std::wstring> filePaths) {
	this->installationCompleted = false;
	this->dstDirPath = dstDirPath;
	this->filePaths = filePaths;
}

Installer::~Installer() {}

void Installer::Install() {
	if (MAX_INSTALLATION_FILES < this->filePaths.size()) {
		throw std::exception("Too Many installation Files");
	}

	InstallationDir installationDir(this->dstDirPath, &(this->installationCompleted));
	InstallationFile installationFiles[MAX_INSTALLATION_FILES];
	
	installationDir.Create();
	for (size_t i = 0; i < this->filePaths.size(); i++)
	{
		std::wcout << "Initializing and Copying installation file: " << filePaths[i] << std::endl;
		installationFiles[i].Initialize(filePaths[i], this->dstDirPath, &(this->installationCompleted));
		installationFiles[i].CopyToDestination();
	}

	std::wcout << "Finished Installation" << std::endl;

	this->installationCompleted = true;
}
