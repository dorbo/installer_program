#ifndef _INSTALLATION_DIR_H
#define _INSTALLATION_DIR_H

#include <string>

class InstallationDir
{
protected:
	bool initialized;
	std::wstring dirPath;
	bool wasExists;
	bool createdOnDestination;
	bool createExecuted;
	bool *installationCompleted;

public:
	InstallationDir();
	InstallationDir(std::wstring dirPath, bool *installationCompleted);
	~InstallationDir();

	void Initialize(std::wstring dirPath, bool* installationCompleted);
	void Create();
	void Delete();
};

#endif // _INSTALLATION_DIR_H
