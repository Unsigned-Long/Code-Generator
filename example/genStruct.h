/**
 * @brief cmd [structgenor Car provider:std::string price:float weight:double "color:unsigned char"]
 */

#include <iostream>
#include <string>

struct Car {
private:
  /**
   * @brief the members
   */
  std::string _provider;
  float _price;
  double _weight;
  unsigned char _color;

public:
  /**
   * @brief construct a new Car object
   */
  Car(const std::string &provider, const float &price, const double &weight,
      const unsigned char &color)
      : _provider(provider), _price(price), _weight(weight), _color(color) {}

  inline std::string &provider() { return this->_provider; }
  inline const std::string &provider() const { return this->_provider; }

  inline float &price() { return this->_price; }
  inline const float &price() const { return this->_price; }

  inline double &weight() { return this->_weight; }
  inline const double &weight() const { return this->_weight; }

  inline unsigned char &color() { return this->_color; }
  inline const unsigned char &color() const { return this->_color; }
};
/**
 * @brief override operator '<<' for type 'Car'
 */
std::ostream &operator<<(std::ostream &os, const Car &obj) {
  os << '{';
  os << "'provider': " << obj.provider() << ", 'price': " << obj.price()
     << ", 'weight': " << obj.weight() << ", 'color': " << obj.color();
  os << '}';
  return os;
}