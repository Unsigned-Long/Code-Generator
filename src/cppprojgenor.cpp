/**
 * @file cppprojgenor.cpp
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2022-01-25
 * 
 * @copyright Copyright (c) 2022
 */

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <dirent.h>
#include <stdio.h>

#define STR(str) std::string(str)
#define FULLPATH(projpath, subdir) (projpath + STR("/") + STR(subdir))

int runCommand(const std::string &cmd)
{
    return system(cmd.c_str());
}

void handleParams(int argc, char const *argv[])
{
    if (argc == 1)
    {
        std::cout << "\nThis simple program is used to generate cpp project structure.\n\n";
        std::cout << "Usage: mycppprojGenor projectName\n\n";
        throw std::runtime_error("");
    }

    bool isHelp = false;
    if (std::string(argv[1]) == std::string("--help") ||
        std::string(argv[1]) == std::string("-H"))
    {
        std::cout << "This simple program is used to generate cpp project structure.\n\n";
        std::cout << "Usage: mycppprojGenor projectName\n\n";
        std::cout << "Here is an example:\n\n";
        std::cout << "typing 'mycppprojGenor test' will generate code project:\n\n";
        std::cout << "test/"
                     "\n├── bash"
                     "\n│   ├── cmake.sh"
                     "\n│   └── makerun.sh"
                     "\n├── bin"
                     "\n├── build"
                     "\n├── CMakeLists.txt"
                     "\n├── include"
                     "\n│   └── test.h"
                     "\n├── main.cpp"
                     "\n├── readme.md"
                     "\n└── src"
                     "\n    └── test.cpp"
                     "\n└── thirdparty"
                     "\n    ├── include"
                     "\n    └── lib"
                     "\n\n5 directories, 7 files"
                  << std::endl;
        throw std::runtime_error("");
    }
}

void writeContext(const std::string &filename, const std::string &str)
{
    std::ofstream ofs(filename, std::ios::app);
    ofs << str;
    ofs.close();
}

void genor(const std::string &projpath)
{
    auto pos = projpath.find_last_of('/');
    auto projname = projpath.substr(pos + 1);

    for (int i = 0; i != projname.size(); ++i)
        projname.at(i) = std::tolower(projname.at(i));

    // create project main fold
    runCommand("mkdir " + projpath);
    // create folders
    runCommand("mkdir " + FULLPATH(projpath, "src"));
    runCommand("mkdir " + FULLPATH(projpath, "include"));
    runCommand("mkdir " + FULLPATH(projpath, "build"));
    runCommand("mkdir " + FULLPATH(projpath, "bash"));
    runCommand("mkdir " + FULLPATH(projpath, "bin"));
    runCommand("mkdir " + FULLPATH(projpath, ".vscode"));
    runCommand("mkdir " + FULLPATH(projpath, "/thirdparty"));
    runCommand("mkdir " + FULLPATH(projpath, "/thirdparty/include"));
    runCommand("mkdir " + FULLPATH(projpath, "/thirdparty/lib"));
    // carete files
    std::string mainFilename = FULLPATH(projpath, "main.cpp");
    std::string headerFilename = FULLPATH(projpath, "include/" + projname + ".h");
    std::string sourceFilename = FULLPATH(projpath, "src/" + projname + ".cpp");
    std::string includeHeader = "#include \"" + projname + ".h\"";
    // main.cpp
    runCommand("touch " + mainFilename);
    writeContext(mainFilename, includeHeader + "\n\nint main(int argc, char const *argv[])\n"
                                               "{\n"
                                               "    std::cout << \"Hello, world.\" << std::endl;\n"
                                               "    return 0;\n"
                                               "}\n");
    // header file
    runCommand("touch " + headerFilename);
    writeContext(headerFilename, "#pragma once\n\n"
                                 "#include <iostream>\n\n"
                                 "namespace ns_proj\n{\n\n} // namespace ns_proj");
    // source file
    runCommand("touch " + sourceFilename);
    writeContext(sourceFilename, includeHeader + "\n\nnamespace ns_proj\n{\n\n} // namespace ns_proj");

    // .gitignore
    runCommand("touch " + FULLPATH(projpath, ".gitignore"));
    writeContext(FULLPATH(projpath, ".gitignore"), "/build\n"
                                                   "/.gitignore");

    // readme.md
    runCommand("touch " + FULLPATH(projpath, "readme.md"));
    // CMakeLists.txt
    std::string cmakefile = FULLPATH(projpath, "CMakeLists.txt");
    runCommand("touch " + cmakefile);
    writeContext(cmakefile, "# header\n"
                            "cmake_minimum_required(VERSION 3.10)\n\n");
    writeContext(cmakefile, "project(" + projname + " VERSION 1.0)\n\n");
    writeContext(cmakefile, "# settings\n"
                            "set(CMAKE_CXX_STANDARD 17)\n\n"
                            "set(CMAKE_CXX_STANDARD_REQUIRED true)\n\n"
                            "set(CMAKE_BUILD_TYPE \"Debug\")\n\n"
                            "# set(CMAKE_BUILD_TYPE \"Release\")\n\n"
                            "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)\n\n");
    writeContext(cmakefile, "# includes\n"
                            "include_directories(${CMAKE_SOURCE_DIR}/include)\n\n");
    writeContext(cmakefile, "# include_directories(${CMAKE_SOURCE_DIR}/thirdparty/include)\n\n");
    writeContext(cmakefile, "# link_directories(${CMAKE_SOURCE_DIR}/thirdparty/lib)\n\n");
    writeContext(cmakefile, "# source files\n"
                            "aux_source_directory(${CMAKE_SOURCE_DIR}/src SRC_FILES)\n\n");
    writeContext(cmakefile, "# add exe\n"
                            "add_executable(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/main.cpp ${SRC_FILES})\n\n");
    // bash files
    runCommand("touch " + FULLPATH(projpath, "bash/cmake.sh"));
    writeContext(FULLPATH(projpath, "bash/cmake.sh"), "cmake -S ../ -B ../build");

    runCommand("touch " + FULLPATH(projpath, "bash/makerun.sh"));
    writeContext(FULLPATH(projpath, "bash/makerun.sh"), "cmake --build ../build/\n"
                                                        "cd ../bin\n"
                                                        "./" +
                                                            projname +
                                                            "\ncd ../bash");
}

int main(int argc, char const *argv[])
{
    try
    {
        handleParams(argc, argv);
        genor(argv[1]);
    }
    catch (const std::runtime_error &e)
    {
        return 0;
    }
    return 0;
}
