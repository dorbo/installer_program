#ifndef _INSTALLATION_FILE_H
#define _INSTALLATION_FILE_H

#include <string>

class InstallationFile
{
protected:
	bool initialized;
	std::wstring filePath;
	std::wstring baseFileName;
	std::wstring dstDir;
	std::wstring dstFilePath;
	bool wasExists;
	bool copied;
	bool *installationCompleted;

	std::wstring getBaseFileNameFromPath(std::wstring filePath);

public:
	InstallationFile();
	InstallationFile(std::wstring filePath, std::wstring dstDir, bool *installationCompleted);
	~InstallationFile();

	void Initialize(std::wstring filePath, std::wstring dstDir, bool* installationCompleted);
	void CopyToDestination();
	void DeleteFromDestination();
};

#endif // _INSTALLATION_FILE_H
