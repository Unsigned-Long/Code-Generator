#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

static std::ofstream *ofs;

#define OUTPUT(argv) (*ofs) << argv;
#define OUTPUT_WITH_END(argv) (*ofs) << argv << std::endl;

void handleParams(int argc, char const *argv[]) {
  bool isHelp = false;
  if (argc > 1)
    isHelp = std::string(argv[1]) == std::string("--help") ||
             std::string(argv[1]) == std::string("-H");
  if (argc == 1 || (argc == 2 && !isHelp)) {
    std::cout << "\nThis simple program is used to generate cpp 'enum' source "
                 "code.\n\n";
    std::cout << "Usage: myenumGenor EnumName Option1 [Option2] ...\n\n";
    throw std::runtime_error("");
  }
  if (isHelp) {
    std::cout << "This simple program is used to generate cpp 'struct' source "
                 "code.\n\n";
    std::cout << "Usage: myenumGenor EnumName Option1 [Option2] ...\n\n";
    std::cout << "Here is an example:\n\n";
    std::cout
        << "typing 'myenumGenor Color red green blue' will generate code:\n\n";
    std::cout
        << "enum class Color"
           "\n{"
           "\n    /**"
           "\n     * @brief options"
           "\n     */"
           "\n    RED,"
           "\n    GREEN,"
           "\n    BLUE"
           "\n};"
           "\n/**"
           "\n * @brief override operator '<<' for type 'Color'"
           "\n */"
           "\nstd::ostream &operator<<(std::ostream &os, const Color &obj)"
           "\n{"
           "\n    switch (obj)"
           "\n    {"
           "\n    case Color::RED:"
           "\n        os << \" RED \";"
           "\n        break;"
           "\n    case Color::GREEN:"
           "\n        os << \" GREEN \";"
           "\n        break;"
           "\n    case Color::BLUE:"
           "\n        os << \" BLUE \";"
           "\n        break;"
           "\n    }"
           "\n    return os;"
           "\n};"
        << std::endl;
    throw std::runtime_error("");
  }
}

std::pair<std::string, std::vector<std::string>> init(int argc,
                                                      char const *argv[]) {
  std::vector<std::string> options;
  std::string enumName = argv[1];
  for (int i = 2; i != argc; ++i) {
    std::string option = argv[i];
    std::for_each(option.begin(), option.end(),
                  [](char &c) -> void { c = std::toupper(c); });
    options.push_back(option);
  }
  return {enumName, options};
}

void genEnum(const std::string &enumName,
             const std::vector<std::string> &options) {
  OUTPUT_WITH_END("enum " << enumName << " : int ")
  OUTPUT_WITH_END("{")
  OUTPUT_WITH_END("/**")
  OUTPUT_WITH_END(" * @brief options")
  OUTPUT_WITH_END(" */")
  for (int i = 0; i != options.size() - 1; ++i)
    OUTPUT_WITH_END(options.at(i) << " = 1 << " << i << ",")
  OUTPUT_WITH_END(options.back() << " = 1 << " << options.size() - 1)
  OUTPUT_WITH_END("};")
  for (int i = 0; i != options.size(); ++i) {
    OUTPUT_WITH_END("bool is" << enumName << "With" << options.at(i) << "(int obj)")
    OUTPUT_WITH_END("{")
    OUTPUT_WITH_END("return (" << enumName << "::" << options.at(i) << "==("
                               << enumName << "::" << options.at(i) << " & obj));")
    OUTPUT_WITH_END("}")
  }

  OUTPUT_WITH_END("/**")
  OUTPUT_WITH_END(" * @brief override operator '<<' for type '" + enumName +
                  "'")
  OUTPUT_WITH_END(" */")
  OUTPUT_WITH_END("std::ostream &operator<<(std::ostream &os, const " +
                  enumName + " &obj)")
  OUTPUT_WITH_END("{")
  OUTPUT_WITH_END("switch (obj)")
  OUTPUT_WITH_END("{")
  for (const auto &elem : options) {
    OUTPUT_WITH_END("case " + enumName + "::" + elem + ":")
    OUTPUT_WITH_END("os << \"" + elem + "\";")
    OUTPUT_WITH_END("break;")
  }
  OUTPUT_WITH_END("}")
  OUTPUT_WITH_END("return os;")
  OUTPUT_WITH_END("};")
}

int runCommand(const std::string &cmd) { return system(cmd.c_str()); }

int main(int argc, char const *argv[]) {
  ::ofs = new std::ofstream("./temp.log");

  try {
    handleParams(argc, argv);
    auto [enumName, options] = init(argc, argv);
    genEnum(enumName, options);
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
