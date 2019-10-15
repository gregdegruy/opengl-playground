#include "Renderer.h"

#include "Test.h"
#include "TestClearColor.h"

#include "imgui_v_1_60\imgui.h"

namespace test
{
	TestClearColor::TestClearColor() 
		: m_clear_color{ 0.2f, 0.3f, 0.8f, 1.0f } 
	{ }

	TestClearColor::~TestClearColor() 
	{ }

	void TestClearColor::on_update(float delta_time)
	{
	}

	void TestClearColor::on_render()
	{
		MyGLCall(glClearColor(m_clear_color[0], m_clear_color[1], m_clear_color[2], m_clear_color[3]));
		MyGLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
	
	void TestClearColor::on_imgui_render()
	{
		ImGui::ColorEdit4("Clear color", m_clear_color);
	}
}