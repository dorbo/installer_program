#include "InstallationFile.h"

#include <iostream>
#include <vector>
#include <windows.h>
#include <stdlib.h>

InstallationFile::InstallationFile() {
	this->initialized = false;
}

std::wstring InstallationFile::getBaseFileNameFromPath(std::wstring filePath) {
	std::vector<wchar_t> baseFileName(100);
	std::vector<wchar_t> extension(50);
	errno_t err = _wsplitpath_s(
		filePath.c_str(),
		nullptr, 0,
		nullptr, 0,
		baseFileName.data(), baseFileName.size(),
		extension.data(), extension.size()
	);
	if (err) {
		throw std::exception("Couldn't split path", err);
	}

	std::wstring baseFileNameWStr(baseFileName.data());
	std::wstring extensionWStr(extension.data());
	return baseFileNameWStr + extensionWStr;
}

InstallationFile::InstallationFile(std::wstring filePath, std::wstring dstDir, bool* installationCompleted) {
	this->Initialize(filePath, dstDir, installationCompleted);
}

InstallationFile::~InstallationFile() {
	if (!this->initialized) {
		return;
	}
	std::wcout << L"Destructor File: " << this->baseFileName << std::endl;
	if (!(this->copied && !this->wasExists) ||
		*this->installationCompleted) {
		return;
	}
	try {
		this->DeleteFromDestination();
	}
	catch (const std::exception error) {
		std::wcerr << L"Failed to delete file: " << this->baseFileName << L" Error number:" << error.what() << std::endl;
	}
}

void InstallationFile::Initialize(std::wstring filePath, std::wstring dstDir, bool* installationCompleted) {
	this->filePath = filePath;
	this->dstDir = dstDir;
	this->baseFileName = this->getBaseFileNameFromPath(filePath);
	this->copied = false;
	this->installationCompleted = installationCompleted;
	this->initialized = true;
}

void InstallationFile::CopyToDestination() {
	if (!this->initialized) {
		return;
	}
	std::wcout << L"Copying File: " << this->baseFileName<< std::endl;
	this->dstFilePath = this->dstDir + this->baseFileName;
	
	BOOL success = CopyFile(
		(LPCTSTR)this->filePath.c_str(),
		(LPCTSTR)this->dstFilePath.c_str(),
		TRUE // Fail if exists
	);
	
	if (!success) {
		DWORD lastError = GetLastError();
		if (lastError == ERROR_FILE_EXISTS) {
			this->wasExists = true;
			return;
		}
		else {
			throw std::exception("Couldn't copy file", lastError);
		}
	}
	
	this->wasExists = false;
	this->copied = true;
}

void InstallationFile::DeleteFromDestination() {
	if (!this->initialized) {
		return;
	}
	std::wcout << L"Deleting File: " << this->baseFileName << std::endl;
	BOOL success = DeleteFile((LPCTSTR)this->dstFilePath.c_str());
	if (!success) {
		DWORD lastError = GetLastError();
		throw std::exception("Couldn't delete file", lastError);
	}
}
