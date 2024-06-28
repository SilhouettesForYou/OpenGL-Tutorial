#ifndef TEST
#define TEST
#include <functional>
#include <vector>
#include <string>
#include <iostream>

namespace test
{
    class Test
    {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}
    };

    class TestMenu : public Test
    {
    public:
        TestMenu(Test*& currentTestPointer);
        ~TestMenu();

        void OnImGuiRender() override;

        template<typename T>
        void RegisterTest(const std::string& name)
        {
            std::cout << "Registering test " << name << std::endl;
            tests.push_back(std::make_pair(name, []()
            {
                return new T();
            }));
        }
    private:
        Test*& curTest; // 因为要修改当前的Test所以要用指针的引用
        // 不想存储Test的实例，只是想在用的是能够构造Test的实例
        std::vector<std::pair<std::string, std::function<Test*()>>> tests;
    };
}
#endif