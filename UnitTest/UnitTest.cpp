#include "pch.h"
#include "CppUnitTest.h"
#include <chrono>
#include <thread>

#include "Application.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(PathGameTests)
	{
	public:
		static PathGame::Application* app;

	public:
		TEST_METHOD(InitTests)
		{
			app = new PathGame::Application(1280, 720, "Path");
		}
	};
}
