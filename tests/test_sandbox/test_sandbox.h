#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include "test_utility/test.h"
#include "shader/shader.h"
#include "texture/texture.h"

namespace test {
    class test_sandbox : public test
    {
    public:
        test_sandbox();
        ~test_sandbox() override;

        void on_render() override;
        void on_imgui_render() override;
        std::string get_test_name() override { return "Sandbox"; };
    private:
    };
}
