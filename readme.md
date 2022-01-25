# Cpp Source Code Generator
>___Author : csl___  
>___E-Mail : 3079625093@qq.com___
## Override
This is a program for automatically generating cpp code. At present, it can automatically generate ___"struct"___ ___"enum"___ and ___"cpp project struct"___.
## Struct Generator
### Usage
```
mystructGenor StructName MemName1:MemType1 [MemName2:MemType2] ...
```
### Example
```bash
mystructGenor Info id:uint
```
```cpp
struct Info
{
private:
    /**
     * @brief the members
     */
    uint _id;

public:
    /**
     * @brief construct a new Info object
     */
    Info(const uint &id)
        : _id(id) {}

    inline uint &id() { return this->_id; }
    inline const uint &id() const { return this->_id; }

};
/**
 * @brief override operator '<<' for type 'Info'
 */
std::ostream &operator<<(std::ostream &os, const Info &obj)
{
    os << '{';
    os << " 'id' : " << obj.id();
    os << '}';
    return os;
}
```
## Enum Generator
### Usage
```
myenumGenor EnumName Option1 [Option2] ...
```
### Example
```bash
myenumGenor Color red green blue
```
```cpp
enum class Color
{
    /**
     * @brief options
     */
    RED,
    GREEN,
    BLUE
};
/**
 * @brief override operator '<<' for type 'Color'
 */
std::ostream &operator<<(std::ostream &os, const Color &obj)
{
    switch (obj)
    {
    case Color::RED:
        os << " RED ";
        break;
    case Color::GREEN:
        os << " GREEN ";
        break;
    case Color::BLUE:
        os << " BLUE ";
        break;
    }
    return os;
};
```
## CppProj Generator
### Usage
```
mycppprojGenor projectName
```
### Example
```bash
mystructGenor test
```
```log
test/
├── bash
│   ├── cmake.sh
│   └── makerun.sh
├── bin
├── build
├── CMakeLists.txt
├── include
│   └── test.h
├── main.cpp
├── readme.md
└── src
    └── test.cpp

5 directories, 7 files
```
## Other Examples
___[generator 'Car' struct](./example/genStruct.h)___

___[generator 'Color' enum](./example/genEnum.h)___
