#pragma once

namespace test {
    class test
    {
    public:
        test() = default;
        virtual ~test() = default;
        virtual void on_render(){};
        virtual void on_imgui_render(){};
    };
}