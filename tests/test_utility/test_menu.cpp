#include "test_menu.h"

#include "imgui/imgui.h"

namespace test {
    test_menu::test_menu(test*& p_current_test) : m_pr_current_test(p_current_test){}

    void test_menu::on_imgui_render()
    {
        for (auto& test : m_tests)
        {
            if (ImGui::Button(test.first.c_str()))
            {
                m_pr_current_test = test.second();
            }
        }
    }
}


