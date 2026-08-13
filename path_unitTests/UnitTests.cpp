#include "pch.h"
#include "CppUnitTest.h"
#include <chrono>
#include <thread>

#include "Application.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AIE02UnitTests
{
	TEST_CLASS(AIE02UnitTests)
	{
	public:
		static MathLibrary::Application* app;

	public:
		TEST_CLASS_INITIALIZE(InitialiseTests)
		{
			app = new MathLibrary::Application(800, 420, "Critters");
		}

	private:
	};

	MathLibrary::Application* AIE02UnitTests::app = nullptr;
}