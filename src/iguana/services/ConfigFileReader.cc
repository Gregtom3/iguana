#include "ConfigFileReader.h"
#include <filesystem>

namespace iguana {

  ConfigFileReader::ConfigFileReader(std::string_view name)
      : Object(name)
  {
    // add config files from installation prefix
    AddDirectory(GetConfigInstallationPrefix());
  }

  std::string ConfigFileReader::GetConfigInstallationPrefix()
  {
    return IGUANA_ETC;
  }

  void ConfigFileReader::AddDirectory(std::string const& dir)
  {
    if(dir == "")
      return; // handle unset directory name
    m_log->Trace("Add directory {}", dir);
    m_directories.push_front(dir);
  }

  void ConfigFileReader::AddFile(std::string const& name)
  {
    if(name == "")
      return; // handle unset file name
    auto full_name = FindFile(name);
    m_log->Trace("  ===> Add file {}", full_name);
    m_files.push_front(full_name);
  }

  void ConfigFileReader::PrintDirectories(Logger::Level const level)
  {
    if(m_log->GetLevel() <= level) {
      m_log->Print(level, "{:=^60}", " Configuration file search path order: ");
      m_log->Print(level, " - ./");
      for(auto const& dir : m_directories)
        m_log->Print(level, " - {}", dir);
      m_log->Print(level, "{:=^60}", "");
    }
  }

  std::string ConfigFileReader::FindFile(std::string const& name)
  {
    if(name == "")
      return ""; // handle unset file name
    m_log->Trace("Searching for file '{}' in:", name);
    // first try `./` or assume `name` is a relative or absolute path + filename
    auto found_local = std::filesystem::exists(name);
    m_log->Trace("  - ./{}", found_local ? " - FOUND" : "");
    if(found_local)
      return name;
    // then search each entry of `m_directories`
    for(auto const& dir : m_directories) {
      std::string filename = dir + "/" + name;
      auto found           = std::filesystem::exists(filename);
      m_log->Trace("  - {}{}", dir, found ? " - FOUND" : "");
      if(found)
        return filename;
    }
    // throw exception if not found anywhere
    m_log->Error("Cannot find configuration file named '{}'", name);
    PrintDirectories(Logger::error);
    throw std::runtime_error("configuration file not found");
  }

  std::string ConfigFileReader::ConvertAlgoNameToConfigName(std::string_view algo_name, std::string_view ext)
  {
    std::string result        = std::string(algo_name);
    std::string::size_type it = 0;
    while((it = result.find("::", it)) != std::string::npos)
      result.replace(it, 2, "/");
    return "algorithms/" + result + "/Config." + std::string(ext);
  }

}
