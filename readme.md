# Cpp Source Code Generator
>___Author : csl___  
>___E-Mail : 3079625093@qq.com___
## Override
This is a program for automatically generating cpp code. At present, it can automatically generate "struct" and "enum".
## Struct Generator
### Usage
```
StructName MemName1:MemType1 [MemName2:MemType2] ...
```
### Example
```bash
structgenor Info id:uint
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
EnumName Option1 [Option2] ...
```
### Example
```bash
enumgenor Color red green blue
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
## Other Examples
___[generator 'Car' struct](./example/genStruct.h)___

___[generator 'Color' enum](./example/genEnum.h)___
