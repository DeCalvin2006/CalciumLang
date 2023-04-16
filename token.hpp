#include <string>
#ifndef TOKEN_HPP
#define TOKEN_HPP

namespace Token {
using std::string;
enum class TokenType {
  RSV /*reserved*/,
  NUM,
  STR,
  OPER,
  IDENTY /*indentifier*/,
  NONE
};
enum class RsvWords {};
class Token {
private:
  const int line;
  const int col;
  const string raw;

public:
  Token(int ln, int c, const string &raw_string)
      : line(ln), col(c), raw(raw_string) {}
  Token(const Token &t) : line(t.getLine()), col(t.getCol()), raw(t.getRaw()) {}
  ~Token() {}
  virtual void *info() const = 0;
  virtual TokenType getType() const { return TokenType::NONE; };
  const string &getRaw() const { return raw; }
  const int getLine() const { return line; }
  const int getCol() const { return col; }
};
class Number : public Token {
  const int number;

public:
  Number(const Token &t, const int load) : Token(t), number(load) {}
  virtual TokenType getType() { return TokenType::NUM; };
  virtual void *info() { return (void *)&number; }
};
class String : public Token {

public:
  String(const Token &t) : Token(t) {}
  virtual TokenType getType() { return TokenType::STR; };
  virtual void *info() { return (void *)&getRaw(); }
};
class Reserved : public Token {

public:
  Reserved(const Token &t) : Token(t) {}
  virtual TokenType getType() { return TokenType::RSV; };
  virtual void *info() { return (void *)&getRaw(); }
};
}; // namespace Token

#endif
