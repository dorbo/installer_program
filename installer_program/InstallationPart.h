#ifndef _INSTALLATION_PART_H
#define _INSTALLATION_PART_H

class InstallationPart
{
public:
	virtual void Install() {};
	virtual void Revert() {};
};

#endif
