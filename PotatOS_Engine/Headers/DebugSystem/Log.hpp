#pragma once

#include <DLLInclude.hpp>
#include <filesystem>
#include <fstream>
#include <string>

enum class LOG_LEVEL_TYPE : unsigned int
{
    None,
    Notification,
    Debug,
    Test,
    Warning,
    Critical
};

class POTATOS_ENGINE_API Log
{
    // Attributes
private:
    static std::ofstream logFile;

    // Methods
public:
    static void OpenFile(std::filesystem::path const& p_filenName);
    static void Print(const std::string& p_log, const LOG_LEVEL_TYPE& p_level = LOG_LEVEL_TYPE::Debug);
    static void CloseFile();
};

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

void POTATOS_ENGINE_API DebugLog(const std::string& p_filename, const unsigned int p_line, const std::string& p_functionName, const std::string p_log);

#define DEBUG_LOG(p_log) DebugLog(__FILENAME__, __LINE__, __FUNCTION__, p_log);
