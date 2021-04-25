#include "InstallationDir.h"

#include <iostream>
#include <windows.h>

InstallationDir::InstallationDir() {
	this->initialized = false;
}

InstallationDir::InstallationDir(std::wstring dirPath, bool *installationCompleted) {
	this->Initialize(dirPath, installationCompleted);
}

InstallationDir::~InstallationDir() {
	if (!this->initialized) {
		return;
	}
	std::wcout << L"Destructor Dir: " << this->dirPath << std::endl;
	if (!(this->createdOnDestination && !this->wasExists) ||
		*this->installationCompleted) {
		return;
	}
	
	try {
		this->Delete();
	}
	catch (const std::exception error) {
		std::wcerr << L"Failed to delete dir: " << this->dirPath << L" Error:" << error.what() << std::endl;
	}
}

void InstallationDir::Initialize(std::wstring dirPath, bool* installationCompleted) {
	this->dirPath = dirPath;
	this->createdOnDestination = false;
	this->installationCompleted = installationCompleted;
	this->initialized = true;
}

void InstallationDir::Create() {
	if (!this->initialized) {
		return;
	}
	std::wcout << L"Creating Dir: " << this->dirPath << std::endl;
	BOOL success = CreateDirectory(
		(LPCWSTR)this->dirPath.c_str(),
		NULL
	);
	if (!success) {
		DWORD lastError = GetLastError();
		if (lastError == ERROR_ALREADY_EXISTS) {
			this->wasExists = true;
			return;
		} else {
			throw std::exception("Couldn't create directory", lastError);
		}
	}
	this->wasExists = false;
	this->createdOnDestination = true;
}

void InstallationDir::Delete() {
	if (!this->initialized) {
		return;
	}
	std::wcout << L"Removing Dir: " << this->dirPath << std::endl;
	BOOL success = RemoveDirectory(
		(LPCWSTR)this->dirPath.c_str()
	);
	if (!success) {
		DWORD lastError = GetLastError();
		throw std::exception("Couldn't delete directory", lastError);
	}
}
