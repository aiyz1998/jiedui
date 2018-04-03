#include "stdafx.h"
#include <ctime>
#include <cstdlib>
#include <assert.h>
#include <string>
#define random(a,b) (rand()%(b-a+1)+a)

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace Test_srand
{
	[TestClass]
	public ref class UnitTest
	{
	private:
		TestContext^ testContextInstance;

	public: 
		/// <summary>
		///获取或设置测试上下文，该上下文提供
		///有关当前测试运行及其功能的信息。
		///</summary>
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

		#pragma region Additional test attributes
		//
		// 编写测试时，可以使用以下附加特性: 
		//
		// 在运行类中的第一个测试之前使用 ClassInitialize 运行代码
		//[ClassInitialize()]
		//static void MyClassInitialize(TestContext^ testContext) {};
		//
		// 在类中的所有测试都已运行之后使用 ClassCleanup 运行代码
		//[ClassCleanup()]
		//static void MyClassCleanup() {};
		//
		//在运行每个测试之前，使用 TestInitialize 来运行代码
		//[TestInitialize()]
		//void MyTestInitialize() {};
		//
		//在每个测试运行完之后，使用 TestCleanup 来运行代码
		//[TestCleanup()]
		//void MyTestCleanup() {};
		//
		#pragma endregion 

		[TestMethod]
		void TestMethod1()
		{
			srand((unsigned)time(NULL));
			int i = 0, j = 0, k = 0;
			for (int i = 0; i < 10; i++) {
				j = random(1, 100);
				k = j <= 100 && j >= 0 ? 1 : 0;
				assert(k);
			}//end for
		};

		[TestMethod]
		void TestMethod2()
		{
			char*p = "+-*/^";
			int temp = strlen(p);
			assert(temp == 5);

		};
		[TestMethod]

		void TestMethod3()
		{
			int result = 0; 
			int i = 0, j = 0, k = 0;
			for (int i = 0; i < 10; i++) {
				j = srand_generator(5);
				k = j <= 4 && j >= 0 ? 1 : 0;
				assert(k);
			}//end for
			NNode sl;
		};
		[TestMethod]

		void TestMethod4()
		{
			int result = 0;
			int a = 128, b = 16;
			int c = 435, d = 165;
			assert(gcd(a, b) == 16);
			assert(gcd(c, d) == 15);
		};
			
			//
			// TODO:  在此处添加测试逻辑
			//
		
	};
}
