#pragma once
#include "baseProject.h"

class AndroidStudioProject : public baseProject
{
public:
    AndroidStudioProject(std::string target);

    bool createProjectFile();
    void addInclude(std::string includeName){}
    void addLibrary(const LibraryBinary & lib){}
    void addSrc(std::string srcFile, std::string folder, SrcType type=DEFAULT){};
	bool loadProjectFile() { return false; };
    bool saveProjectFile(){ return false; };
    static std::string LOG_NAME;

};
