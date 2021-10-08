//
// Created by Nathan Goller-Deitsch on 9/20/21.
//

#include "Frame.h"

#include <boost/algorithm/string/join.hpp>
#include <vector>

std::string Kuka::Frame::compileKRL() {
  std::vector<std::string> unwrappedArguments;

  if (x) {
    unwrappedArguments.push_back("X " + std::to_string(x.value()));
  }
  if (y) {
    unwrappedArguments.push_back("Y " + std::to_string(y.value()));
  }
  if (z) {
    unwrappedArguments.push_back("Z " + std::to_string(z.value()));
  }
  if (a) {
    unwrappedArguments.push_back("A " + std::to_string(a.value()));
  }
  if (b) {
    unwrappedArguments.push_back("B " + std::to_string(b.value()));
  }
  if (c) {
    unwrappedArguments.push_back("C " + std::to_string(c.value()));
  }

  return "{" + boost::algorithm::join(unwrappedArguments, ",") + "}";
}

Kuka::Frame::Frame(const std::optional<float>& x, const std::optional<float>& y,
                   const std::optional<float>& z, const std::optional<float>& a,
                   const std::optional<float>& b, const std::optional<float>& c)
    : x(x), y(y), z(z), a(a), b(b), c(c) {}

Kuka::Frame::Frame()
        : x(std::nullopt), y(std::nullopt), z(std::nullopt), a(std::nullopt), b(std::nullopt), c(std::nullopt) {}

Kuka::Frame Kuka::Frame::operator+(const Kuka::Frame &input) {
    Kuka::Frame output;
    if(this->x && input.x){
        output.x = this->x.value() + input.x.value();
    }else if(this->x){
        output.x = this->x.value();
    }else if(input.x){
        output.x = input.x.value();
    }

    if(this->y && input.y){
        output.y = this->y.value() + input.y.value();
    }else if(this->y){
        output.y = this->y.value();
    }else if(input.y){
        output.y = input.y.value();
    }

    if(this->z && input.z){
        output.z = this->z.value() + input.z.value();
    }else if(this->z){
        output.z = this->z.value();
    }else if(input.z){
        output.z = input.z.value();
    }

    if(this->a && input.a){
        output.a = this->a.value() + input.a.value();
    }else if(this->a){
        output.a = this->a.value();
    }else if(input.a){
        output.a = input.a.value();
    }

    if(this->b && input.b){
        output.b = this->b.value() + input.b.value();
    }else if(this->b){
        output.b = this->b.value();
    }else if(input.b){
        output.b = input.b.value();
    }

    if(this->c && input.c){
        output.c = this->c.value() + input.c.value();
    }else if(this->c){
        output.c = this->c.value();
    }else if(input.c){
        output.c = input.c.value();
    }
    return output;
}
