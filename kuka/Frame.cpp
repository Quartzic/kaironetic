//
// Created by Nathan Goller-Deitsch on 9/20/21.
//

#include "Frame.h"

#include <boost/algorithm/string/join.hpp>
#include <vector>

std::string Kuka::Frame::compileKRL(){

  std::vector<std::string> unwrappedArguments;

  if(x){unwrappedArguments.push_back("X " + std::to_string(x.value()));}
  if(y){unwrappedArguments.push_back("Y " + std::to_string(y.value()));}
  if(z){unwrappedArguments.push_back("Z " + std::to_string(z.value()));}
  if(a){unwrappedArguments.push_back("A " + std::to_string(a.value()));}
  if(b){unwrappedArguments.push_back("B " + std::to_string(b.value()));}
  if(c){unwrappedArguments.push_back("C " + std::to_string(c.value()));}

  return "{" + boost::algorithm::join(unwrappedArguments, ",") + "}";

}

Kuka::Frame::Frame(const std::optional<float>& x, const std::optional<float>& y,
                   const std::optional<float>& z, const std::optional<float>& a,
                   const std::optional<float>& b, const std::optional<float>& c)
    : x(x), y(y), z(z), a(a), b(b), c(c) {}
