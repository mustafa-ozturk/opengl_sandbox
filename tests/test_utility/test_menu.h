#pragma once

#include <functional>
#include <iostream>
#include "test.h"

namespace test {
    class test_menu : public test
    {
    public:
        explicit test_menu(test*& p_current_test);

        void on_imgui_render() override;

        template<typename T>
        void register_test(const std::string& name)
        {
            std::cout << "Registering test " << name << std::endl;
            m_tests.push_back(std::make_pair(name, [](){ return new T();}));
        }
    private:
        test*& m_pr_current_test;
        // vector of pairs, each pair contains a string and a function that returns a Test pointer
        std::vector<std::pair<std::string, std::function<test*()>>> m_tests;
    };
}