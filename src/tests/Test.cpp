#include "Test.h"
#include "imgui/imgui.h"

namespace test
{
    TestMenu::TestMenu(Test*& currentTestPointer)
        : curTest{currentTestPointer}
    {

    }

    TestMenu::~TestMenu()
    {
    }
    
    void TestMenu::OnImGuiRender()
    {
        for (auto& test : tests)
        {
            if (ImGui::Button(test.first.c_str()))
                curTest = test.second();
        }
    }
}