#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

static std::ofstream *ofs;

#define OUTPUT(argv) (*ofs) << argv;
#define OUTPUT_WITH_END(argv) (*ofs) << argv << std::endl;

struct MemInfo {
  std::string _varName;
  std::string _varType;
};

MemInfo split(const std::string &str) {
  MemInfo info;
  auto pos = str.find_first_of(':');
  info._varName = str.substr(0, pos);
  info._varType = str.substr(pos + 1);
  return info;
}

std::pair<std::string, std::vector<MemInfo>> init(int argc,
                                                  char const *argv[]) {
  std::string structName = argv[1];

  std::vector<MemInfo> info(argc - 2);

  for (int i = 2; i != argc; ++i)
    info.at(i - 2) = split(argv[i]);

  return std::make_pair(structName, info);
}

void handleParams(int argc, char const *argv[]) {
  bool isHelp = false;
  if (argc > 1)
    isHelp = std::string(argv[1]) == std::string("--help") ||
             std::string(argv[1]) == std::string("-H");
  if (argc == 1 || (argc == 2 && !isHelp)) {
    std::cout << "\nThis simple program is used to generate cpp 'struct' "
                 "source code.\n\n";
    std::cout << "Usage: mystructGenor StructName MemName1:MemType1 "
                 "[MemName2:MemType2] ...\n\n";
    throw std::runtime_error("");
  }
  if (isHelp) {
    std::cout << "This simple program is used to generate cpp 'struct' source "
                 "code.\n\n";
    std::cout << "Usage: mystructGenor StructName MemName1:MemType1 "
                 "[MemName2:MemType2] ...\n\n";
    std::cout << "Here is an example:\n\n";
    std::cout << "typing 'mystructGenor Info id:uint' will generate code:\n\n";
    std::cout << "struct Info"
                 "\n{"
                 "\nprivate:"
                 "\n    /**"
                 "\n     * @brief the members"
                 "\n     */"
                 "\n    uint _id;"
                 "\n"
                 "\npublic:"
                 "\n    /**"
                 "\n     * @brief construct a new Info object"
                 "\n     */"
                 "\n    Info(const uint &id)"
                 "\n        : _id(id) {}"
                 "\n"
                 "\n    inline uint &id() { return this->_id; }"
                 "\n    inline const uint &id() const { return this->_id; }"
                 "\n"
                 "\n};"
                 "\n/**"
                 "\n * @brief override operator '<<' for type 'Info'"
                 "\n */"
                 "\nstd::ostream &operator<<(std::ostream &os, const Info &obj)"
                 "\n{"
                 "\n    os << '{';"
                 "\n    os << \" 'id' : \" << obj.id();"
                 "\n    os << '}';"
                 "\n    return os;"
                 "\n}"
              << std::endl;
    throw std::runtime_error("");
  }
}

void genStruct(const std::string &structName,
               const std::vector<MemInfo> &info) {
  OUTPUT_WITH_END("struct " + structName)
  OUTPUT_WITH_END("{")
  OUTPUT_WITH_END("public:")
  OUTPUT_WITH_END("/**")
  OUTPUT_WITH_END(" * @brief the members")
  OUTPUT_WITH_END(" */")
  for (const auto &elem : info)
    OUTPUT_WITH_END(elem._varType + " " + elem._varName + ";")
  OUTPUT_WITH_END("")
  OUTPUT_WITH_END("public:")
  OUTPUT_WITH_END("/**")
  OUTPUT_WITH_END(" * @brief construct a new " + structName + " object")
  OUTPUT_WITH_END(" */")
  OUTPUT(structName + "(")
  for (int i = 0; i != info.size() - 1; ++i)
    OUTPUT("const " + info.at(i)._varType + " &" + info.at(i)._varName + ", ")
  OUTPUT("const " + info.back()._varType + " &" + info.back()._varName)
  OUTPUT_WITH_END(")")
  OUTPUT(": ")
  for (int i = 0; i != info.size() - 1; ++i)
    OUTPUT(info.at(i)._varName + "(" + info.at(i)._varName + "), ")
  OUTPUT(info.back()._varName + "(" + info.back()._varName + ")")
  OUTPUT_WITH_END(" {}")
  OUTPUT_WITH_END("};")
  OUTPUT_WITH_END("/**")
  OUTPUT_WITH_END(" * @brief override operator '<<' for type '" + structName +
                  "'")
  OUTPUT_WITH_END(" */")
  OUTPUT_WITH_END("std::ostream &operator<<(std::ostream &os, const " +
                  structName + " &obj)")
  OUTPUT_WITH_END("{")
  OUTPUT_WITH_END("os << '{';");
  OUTPUT("os ")
  OUTPUT(std::string("<< ") + "\"'" + info.front()._varName + "': \" << obj." +
         info.front()._varName)
  for (int i = 1; i != info.size(); ++i)
    OUTPUT(std::string(" << ") + "\", '" + info.at(i)._varName +
           "': \" << obj." + info.at(i)._varName)
  OUTPUT_WITH_END(";")
  OUTPUT_WITH_END("os << '}';");
  OUTPUT_WITH_END("return os;")
  OUTPUT_WITH_END("}")

  return;
}

int runCommand(const std::string &cmd) { return system(cmd.c_str()); }

int main(int argc, char const *argv[]) {
  ::ofs = new std::ofstream("./temp.log");
  try {
    handleParams(argc, argv);
    auto [structName, info] = init(argc, argv);
    genStruct(structName, info);
  } catch (const std::runtime_error &e) {
    return 0;
  }
  ofs->close();
  delete ofs;
  ::runCommand(
      "clang-format ./temp.log "
      "--style=Google");
  ::runCommand("rm ./temp.log");
  return 0;
}