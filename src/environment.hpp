#define SASS_ENVIRONMENT

#include <string>
#include <map>
#include "boilerplate_macros.hpp"

namespace Sass {
  using std::string;
  using std::map;

  template <typename T>
  class Environment {
    // TODO: test with unordered_map
    map<string, T> current_frame_;
    ADD_PROPERTY(Environment*, parent);

    Environment() : current_frame_(map<string, T>()), parent_(0) { }

    void link(Environment& env) { parent_ = &env; }
    void link(Environment* env) { parent_ = env; }

    bool has(const string& key) const
    {
      if (current_frame_.count(key))  return true;
      else if (parent_)               return parent_->has(key);
      else                            return false;
    }

    bool current_frame_has(const string& key) const
    { return current_frame_.count(key); }

    T& operator[](const string& key)
    {
      if (current_frame_.count(key))  return current_frame_[key];
      else if (parent_)               return (*parent_)[key];
      else                            return current_frame_[key];
    }
  };
}