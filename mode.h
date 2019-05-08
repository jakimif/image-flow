#ifndef MODE_H
#define MODE_H

#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>

class Mode {
public:
	Mode(const std::string& filter, const std::string& folder);
	const std::string& getFilter() const;
	const std::string& getFolder() const;
	virtual const std::string& getModeName() const = 0;
	void run();

protected:
	virtual void runImpl() = 0;
	std::vector<std::filesystem::path> getFiles(const std::filesystem::path& extension = "") const;

private:
	std::string m_filter;
	std::string m_folder;
};

namespace Args {
namespace Flags {
static constexpr const char* Help = "help";
static constexpr const char* Rename = "rename";
static constexpr const char* Convert = "convert";
static constexpr const char* Resize = "resize";
static constexpr const char* Scale = "scale";
} // namespace Flags
namespace Opts {
static constexpr const char* Folder = "folder";
static constexpr const char* Filter = "filter";
static constexpr const char* Width = "width";
static constexpr const char* Height = "height";
static constexpr const char* Amount = "amount";
static constexpr const char* Prefix = "prefix";
static constexpr const char* Start = "start";
static constexpr const char* From = "from";
static constexpr const char* To = "to";
} // namespace Opts
} // namespace Args

#endif