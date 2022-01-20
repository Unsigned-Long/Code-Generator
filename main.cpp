#include <vector>
#include <algorithm>

struct MemInfo
{
    std::string _varName;
    std::string _varType;
};

MemInfo split(const std::string &str)
{
    MemInfo info;
    auto pos = str.find_first_of(':');
    info._varName = str.substr(0, pos);
    info._varType = str.substr(pos + 1);
    return info;
}

std::pair<std::string, std::vector<MemInfo>> init(int argc, char const *argv[])
{
    std::string structName = argv[1];

    std::vector<MemInfo> info(argc - 2);

    for (int i = 2; i != argc; ++i)
        info.at(i - 2) = split(argv[i]);

    for (auto &elem : info)
    {
        if (elem._varName.at(0) == '_')
            elem._varName = elem._varName.substr(1);
    }
    return std::make_pair(structName, info);
}

void genStruct(const std::string &structName, const std::vector<MemInfo> &info)
{
    STRUCT(structName)
    PRIVATE()
    BRIEF_MEMVERS()
    for (const auto &elem : info)
    {
        VAR_DECLARE(elem._varType, "_" + elem._varName)
    }
    OUTPUT_END()
    PUBLIC()
    BRIEF_CONSTRUCT(structName)
    CONSTRUCTOR(structName)
    for (int i = 0; i != info.size() - 1; ++i)
    {
        CONSTRUCT_PARAM(info[i]._varType, info[i]._varName)
        OUTPUT(", ")
    }
    CONSTRUCT_PARAM(info.back()._varType, info.back()._varName)
    CONSTRUCTOR_END()
    OUTPUT_INDENT()
    OUTPUT_INDENT()
    OUTPUT(": ")
    for (int i = 0; i != info.size() - 1; ++i)
    {
        PARAM_ASIGN("_" + info[i]._varName, info[i]._varName)
        OUTPUT(", ")
    }
    PARAM_ASIGN("_" + info.back()._varName, info.back()._varName)
    PARAM_ASIGN_END()
    for (const auto &elem : info)
    {
        OUTPUT_END()
        MEMBER_GETSET(elem._varType, elem._varName, "_" + elem._varName)
        MEMBER_GETSET_CONST(elem._varType, elem._varName, "_" + elem._varName)
    }
    STRUCT_END()
    OUTPUT_END()
    BRIEF_OUTPUT_OBERRIDE(structName)
    OUTPUT_OVERRIDE(structName)
    for (const auto &elem : info)
    {
        OUTPUT_OS_PARAM(elem._varName)
    }
    OUTPUT_OVERRIDE_END()
}

void handlerParams(int argc, char const *argv[])
{
    if (argc == 1)
    {
        std::cout << "\nThis simple program is used to generate cpp 'struct' source code.\n\n";
        std::cout << "Usage: StructName MemName1:MemType1 [MemName2:MemType2] ...\n\n";
        throw std::runtime_error("");
    }
    if (std::string(argv[1]) == std::string("--help") ||
        std::string(argv[1]) == std::string("-H"))
    {
        std::cout << "This simple program is used to generate cpp 'struct' source code.\n\n";
        std::cout << "Usage: StructName MemName1:MemType1 [MemName2:MemType2] ...\n\n";
        std::cout << "Here is an example:\n\n";
        std::cout << "typing 'structgenor Info id:uint' will generate code:\n\n";
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
                     "\n     * @brief Construct a new Info object"
                     "\n     */"
                     "\n    Info(const uint &id)"
                     "\n        : _id(id) {}"
                     "\n"
                     "\n    inline uint &id() { return this->_id; }"
                     "\n    inline const uint &id() const { return this->_id; }"
                     "\n};"
                     "\n"
                     "\n/**"
                     "\n* @brief override operator '<<' for type Info"
                     "\n*/"
                     "\nstd::ostream &operator<<(std::ostream &os, const Info &obj)"
                     "\n{"
                     "\n    os << obj.id();"
                     "\n    return os;"
                     "\n}"
                  << std::endl;
        throw std::runtime_error("");
    }
    if (argc < 3)
    {
        std::cout << "\nThis simple program is used to generate cpp 'struct' source code.\n\n";
        std::cout << "Usage: StructName MemName1:MemType1 [MemName2:MemType2] ...\n\n";
        throw std::runtime_error("");
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        handlerParams(argc, argv);
        auto [structName, info] = init(argc, argv);
        genStruct(structName, info);
    }
    catch (const std::runtime_error &e)
    {
        return 0;
    }
}