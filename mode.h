#ifndef MODE_H
#define MODE_H

#include <string>

class Mode {
public:
	Mode(const std::string& filter, std::string& folder);
	const std::string& getFilter() const;
	const std::string& getFolder() const;
	virtual const std::string& getModeName() const = 0;
	void run();

protected:
	std::string m_filter;
	std::string m_folder;
	virtual void runImpl() = 0;
};

#endif