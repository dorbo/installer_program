#ifndef _INSTALLER_H
#define _INSTALLER_H

#include <vector>

#include "InstallationDir.h"
#include "InstallationFile.h"

constexpr int MAX_INSTALLATION_FILES = 30;

class Installer
{
protected:
	std::wstring dstDirPath;
	std::vector<std::wstring> filePaths;
	bool installationCompleted;

public:
	Installer(std::wstring dstDirPath, std::vector<std::wstring> filePaths);
	~Installer();
	
	void Install();
};

#endif // _INSTALLER_H
