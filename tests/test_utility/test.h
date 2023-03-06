#pragma once

#include <iostream>

namespace test {
    class test
    {
    public:
        test() = default;
        virtual ~test() = default;
        virtual void on_render(){};
        virtual void on_imgui_render(){};
        virtual std::string get_test_name(){};
    };
}