#include "hello_imgui/hello_imgui.h"
#include <Eigen/Dense>
#include <fmt/core.h>
#include <ylt/struct_pack.hpp>
#include <string>
#include <ylt/reflection/member_value.hpp>
#include <imgui.h>
#include <implot.h>
#include <vector>
#include <cmath>

// 定义一个可序列化的结构体
struct person
{
    int64_t id;
    std::string name;
    int age;
    double salary;
};

// 显示任意结构体信息的模板函数
template <typename T>
void display_person(const char *label, const T &obj)
{
    ImGui::Text("%s:", label);
    ImGui::Indent();
    ylt::reflection::for_each(obj, [](auto &&field, auto &&name)
                              { ImGui::Text("%s: %s", std::string(name).c_str(), fmt::format("{}", field).c_str()); });
    ImGui::Unindent();
}

// 序列化和反序列化测试函数
void test_serialization(const person &p)
{
    auto binary = struct_pack::serialize(p);
    auto decoded = struct_pack::deserialize<person>(binary);

    if (decoded.has_value())
    {
        display_person("Original", p);
        display_person("Decoded", decoded.value());
    }
}

// 显示矩阵的UI函数
void show_matrix(const Eigen::Matrix3d &matrix)
{
    ImGui::Text("Matrix:");
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            ImGui::SameLine();
            ImGui::Text("%.1f", matrix(i, j));
        }
        ImGui::NewLine();
    }
}

// 显示格式化值的UI函数
void show_formatted_value()
{
    static float value = 0.0f;
    ImGui::SliderFloat("Value", &value, 0.0f, 100.0f);
    ImGui::Text("%s", fmt::format("Formatted value: {:.2f}", value).c_str());
}

// 显示演示窗口的UI函数
void show_demo_windows()
{
    static bool show_demo = false;
    static bool show_implot_demo = false;

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("演示"))
        {
            ImGui::MenuItem("ImGui演示", nullptr, &show_demo);
            ImGui::MenuItem("ImPlot演示", nullptr, &show_implot_demo);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (show_demo)
        ImGui::ShowDemoWindow(&show_demo);
    if (show_implot_demo)
        ImPlot::ShowDemoWindow(&show_implot_demo);
}

// 主UI函数
void show_main_window(const Eigen::Matrix3d &matrix, const person &person1)
{
    ImGui::Text("Hello, ImGui!");
    show_matrix(matrix);
    show_formatted_value();
    test_serialization(person1);

    if (ImGui::Button("Click me!"))
    {
        ImGui::Text("Button clicked!");
    }
}

int main(int argc, char **argv)
{
    // 创建一个简单的矩阵
    Eigen::Matrix3d matrix;
    matrix << 1, 2, 3,
        4, 5, 6,
        7, 8, 9;

    // 创建一个person对象
    person person1{.id = 1, .name = "hello struct pack", .age = 20, .salary = 1024.42};

    // 运行应用程序
    HelloImGui::Run(
        [&matrix, &person1]()
        {
            show_demo_windows();
            show_main_window(matrix, person1);
        },
        "Hello ImGui Demo");
    return 0;
}
