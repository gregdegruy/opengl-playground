#ifndef TEST_H
#define TEST_H

namespace test
{
	class Test
	{
		public:
			Test() {}
			virtual ~Test() {}
		
			virtual void on_update(float delta_time) {}
			virtual void on_render() {}
			virtual void on_imgui_render() {}
	};
}

#endif /* TEST_H */
