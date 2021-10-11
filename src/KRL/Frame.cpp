#include "Frame.h"

#include <boost/algorithm/string/join.hpp>
#include <vector>

std::string Kaironetic::KRL::Frame::compileKRL() {
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

Kaironetic::KRL::Frame::Frame(const std::optional<float> &x, const std::optional<float> &y,
                              const std::optional<float> &z, const std::optional<float> &a,
                              const std::optional<float> &b, const std::optional<float> &c)
        : x(x), y(y), z(z), a(a), b(b), c(c) {}

Kaironetic::KRL::Frame::Frame()
        : x(std::nullopt), y(std::nullopt), z(std::nullopt), a(std::nullopt), b(std::nullopt), c(std::nullopt) {}

Kaironetic::KRL::Frame Kaironetic::KRL::Frame::operator+(const Frame &rhs) {
    Frame output;
    if (this->x && rhs.x) {
        output.x = this->x.value() + rhs.x.value();
    } else if (this->x) {
        output.x = this->x.value();
    } else if (rhs.x) {
        output.x = rhs.x.value();
    }

    if (this->y && rhs.y) {
        output.y = this->y.value() + rhs.y.value();
    } else if (this->y) {
        output.y = this->y.value();
    } else if (rhs.y) {
        output.y = rhs.y.value();
    }

    if (this->z && rhs.z) {
        output.z = this->z.value() + rhs.z.value();
    } else if (this->z) {
        output.z = this->z.value();
    } else if (rhs.z) {
        output.z = rhs.z.value();
    }

    if (this->a && rhs.a) {
        output.a = this->a.value() + rhs.a.value();
    } else if (this->a) {
        output.a = this->a.value();
    } else if (rhs.a) {
        output.a = rhs.a.value();
    }

    if (this->b && rhs.b) {
        output.b = this->b.value() + rhs.b.value();
    } else if (this->b) {
        output.b = this->b.value();
    } else if (rhs.b) {
        output.b = rhs.b.value();
    }

    if (this->c && rhs.c) {
        output.c = this->c.value() + rhs.c.value();
    } else if (this->c) {
        output.c = this->c.value();
    } else if (rhs.c) {
        output.c = rhs.c.value();
    }
    return output;
}

bool Kaironetic::KRL::Frame::operator==(const Kaironetic::KRL::Frame &rhs) {
    return (
            x == rhs.x &&
            y == rhs.y &&
            z == rhs.z &&
            a == rhs.a &&
            b == rhs.b &&
            c == rhs.c
    );
}
