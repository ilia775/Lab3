#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\Administrator\source\repos\Lab3\Lab3\Lab3.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab3test
{
	int numoftests = 1, maxsize = 1000, maxrandint = 1000;
	TEST_CLASS(BinaryTreeTimeTests)
	{
		//int numoftests = 1, maxsize = 100000000, maxrandint = 1000;
		long long maxsizetime = 100000000, minsizetime = 10000000;
		TEST_METHOD(TestBalance)
		{
			srand((unsigned int)time(NULL));
			long long j = rand(minsizetime, maxsizetime);
			int* mass = new int[j];
			for (long long k = 0; k < j; k++)
			{
				mass[k] = rand(-maxrandint, maxrandint);
			}
			BinaryTree<int>* Tree = new BinaryTree<int>(mass, j);
			qsortRecursive<int>(mass, j);
			delete Tree;
			BinaryTree<int>* newtree = GenBalancedTree<int>(mass, j);
			Assert::IsTrue(newtree->GetMaxLVL() - newtree->GetMinLVL() <= 1);
			delete newtree;
			delete[] mass;
		}

		TEST_METHOD(TestMapSum)
		{
			srand((unsigned int)time(NULL));
			long long j = rand(10000000, maxsize);
			int* mass = new int[j];
			for (long long k = 0; k < j; k++)
			{
				mass[k] = rand(-maxrandint, maxrandint);
			}
			BinaryTree<int>* Tree = new BinaryTree<int>(mass, j);
			BinaryTree<int>* newtree = new BinaryTree<int>();
			int temp = rand(-maxrandint, maxrandint);
			map<int>(Tree, sum<int>, temp, newtree);
			j = newtree->GetSize();
			int* mass1 = new int[j];
			int* mass2 = new int[j];
			Tree->GetMass(mass1);
			newtree->GetMass(mass2);
			for (int k = 0; k < j; k++)
			{
				Assert::IsTrue(mass2[k] == mass1[k] + temp/*, to_string(mass1[k]) + "==" + to_string(mass2[k] - temp)*/);
			}
			delete newtree;
			delete Tree;
			delete[] mass;
			delete[] mass1;
			delete[] mass2;
		}
		TEST_METHOD(TestCheckElement)
		{
			srand((unsigned int)time(NULL));
			long long j = rand(minsizetime, maxsizetime);
			int* mass = new int[j];
			for (int k = 0; k < j; k++)
			{
				mass[k] = rand(-maxrandint, maxrandint);
			}
			int temp = mass[rand((long long)0, j - 1)];
			BinaryTree<int>* Tree = new BinaryTree<int>(mass, j);
			Assert::IsTrue(Tree->CheckElement(temp));
			delete Tree;
			delete[] mass;
		}
		TEST_METHOD(TestCheckSubTree)
		{
			srand((unsigned int)time(NULL));
			long long j = rand(minsizetime, maxsizetime);
			int* mass = new int[j];
			for (int k = 0; k < j; k++)
			{
				mass[k] = rand(-maxrandint, maxrandint);
			}
			int temp = mass[rand((long long)0, j - 1)];
			BinaryTree<int>* Tree = new BinaryTree<int>(mass, j);
			BinaryTree<int>* node = Tree->GetSubTree(temp);
			Assert::IsTrue(Tree->CheckSubTree(node));
			delete Tree;
			delete[] mass;
			delete node;
		}

		TEST_METHOD(TestDelteElem)
		{
			srand((unsigned int)time(NULL));
			long long j = rand(minsizetime, maxsizetime);
			int* mass = new int[j];
			for (long long k = 0; k < j; k++)
			{
				mass[k] = rand(-maxrandint, maxrandint);
			}
			BinaryTree<int>* Tree = new BinaryTree<int>(mass, j);
			int temp = mass[rand((long long)0, j - 1)];
			BinaryTree<int>* newtree = Tree->DeleteElem(temp);
			int newlen = newtree->GetSize();
			int* mass2 = new int[newlen];
			newtree->GetMass(mass2);
			for (int k = 0; k < newlen; k++)
			{
				Assert::IsTrue(mass2[k] != temp);
			}
			delete newtree;
			delete[] mass;
			delete[] mass2;
		}

		TEST_METHOD(TestGetSubTree)
		{
			srand((unsigned int)time(NULL));
			long long j = rand(minsizetime, maxsizetime);
			int* mass = new int[j];
			for (long long k = 0; k < j; k++)
			{
				mass[k] = rand(-maxrandint, maxrandint);
			}
			int temp = mass[rand((long long)0, j - 1)];
			BinaryTree<int>* Tree = new BinaryTree<int>(mass, j);
			BinaryTree<int>* node = Tree->GetSubTree(temp);
			Assert::IsTrue(((" " + Tree->ToString()).find(node->ToString()) > 0));
			delete Tree;
			delete[] mass;
			delete node;
		}
		TEST_METHOD(TestInsert)
		{
			srand((unsigned int)time(NULL));
			long long j = rand(minsizetime, maxsizetime);
			long long len = j;
			int* mass = new int[len];
			for (long long k = 0; k < len; k++)
			{
				mass[k] = rand(-maxrandint, maxrandint);
			}
			BinaryTree<int>* Tree = new BinaryTree<int>(mass, len);
			int temp = rand(-maxrandint, maxrandint);
			Tree->Insert(temp);
			len = Tree->GetSize();
			int* mass1 = new int[len];
			Tree->GetMass(mass1);
			for (long long k = 0; k < len; k++)
			{
				if (mass1[k] == temp)
				{
					Assert::IsTrue(true);
					break;
				}
				else if (k == len - 1)
				{
					Assert::IsTrue(false);
				}
			}
			delete Tree;
			delete[] mass;
			delete[] mass1;
		}
		TEST_METHOD(TestMerge)
		{
			srand((unsigned int)time(NULL));
			//long long j = rand(minsizetime, maxsizetime);
					long long len1 = rand(minsizetime, maxsizetime);
					long long len2 = rand(minsizetime, maxsizetime);
					int* mass1 = new int[len1];
					int* mass2 = new int[len2];
					for (long long k = 0; k < len1; k++)
					{
						mass1[k] = rand(-maxrandint, maxrandint);
					}
					for (long long k = 0; k < len2; k++)
					{
						mass2[k] = rand(-maxrandint, maxrandint);
					}
					BinaryTree<int>* Tree1 = new BinaryTree<int>(mass1, len1);
					Tree1->GetMass(mass1);
					len1 = Tree1->GetSize();
					BinaryTree<int>* Tree2 = new BinaryTree<int>(mass2, len2);
					Tree2->GetMass(mass2);
					len2 = Tree2->GetSize();
					BinaryTree<int>* newtree = MergeTrees(Tree1, Tree2);
					long long len3 = newtree->GetSize();
					int* mass3 = new int[len3];
					newtree->GetMass(mass3);
					bool not_in_first_tree = true;
					for (int k = 0; k < len3; k++)
					{
						not_in_first_tree = true;
						for (int i1 = 0; i1 < len1; i1++)
						{
							if (mass3[k] == mass1[i1])
							{
								Assert::IsTrue(true);
								not_in_first_tree = false;
								break;
							}
						}
						if (not_in_first_tree) for (int i2 = 0; i2 < len2; i2++)
						{
							if (mass3[k] == mass2[i2])
							{
								Assert::IsTrue(true);
								break;
							}
							if (i2 == len2 - 1)
							{
								Assert::IsTrue(false);
							}
						}
					}
					delete Tree1;
					delete Tree2;
					delete newtree;
					delete[] mass3;
					delete[] mass2;
					delete[] mass1;
		}
		TEST_METHOD(TestToString)
		{
			srand((unsigned int)time(NULL));
			long long j = rand(minsizetime, maxsizetime);
					int* mass = new int[j];
					for (int k = 0; k < j; k++)
					{
						mass[k] = rand(-maxrandint, maxrandint);
					}
					BinaryTree<int>* Tree = new BinaryTree<int>(mass, j);
					j = Tree->GetSize();
					string tree = " " + Tree->ToString();
					for (long long i1 = 0; i1 < j; i1++)
					{
						Assert::IsTrue(tree.find(to_string(mass[i1])));
					}
					delete Tree;
					delete[] mass;
		}

		TEST_METHOD(TestWhere)
		{
			srand((unsigned int)time(NULL));
			long long j = rand(minsizetime, maxsizetime);
			int* mass = new int[j];
			for (long long k = 0; k < j; k++)
			{
				mass[k] = rand(-maxrandint, maxrandint);
			}
			BinaryTree<int>* Tree = new BinaryTree<int>(mass, j);
			BinaryTree<int>* newtree = new BinaryTree<int>();
			int temp = rand(-maxrandint, maxrandint);
			where<int>(Tree, more_then<int>, temp, newtree);
			int* mass1 = new int[j];
			long long newlen = newtree->GetSize();
			int* mass2 = new int[newlen];
			Tree->GetMass(mass1);
			newtree->GetMass(mass2);
			for (long long k = 0; k < newlen; k++)
			{
				Assert::IsTrue(more_then<int>(mass2[k], temp)/*, to_string(mass1[k]) + "==" + to_string(mass2[k] - temp)*/);
			}
			delete newtree;
			delete Tree;
			delete[] mass;
			delete[] mass1;
			delete[] mass2;
		}
	};
	TEST_CLASS(BinaryTreeIntTests)
	{
	public:
		TEST_METHOD(TestBalance)
		{
			srand((unsigned int)time(NULL));
			for (int i = 0; i < numoftests; i++)
			{
				for (int j = 1; j < maxsize; j++)
				{
					int* mass = new int[j];
					for (int k = 0; k < j; k++)
					{
						mass[k] = rand(-maxrandint, maxrandint);
					}
					BinaryTree<int>* Tree = new BinaryTree<int>(mass, j);
					sort_arr<int>(mass, j);
					delete Tree;
					BinaryTree<int>* newtree = GenBalancedTree<int>(mass, j);
					Assert::IsTrue(newtree->GetMaxLVL() - newtree->GetMinLVL() <= 1);
					delete newtree;
					delete[] mass;
				}
			}
		}
		TEST_METHOD(TestMapSum)
		{
			srand((unsigned int)time(NULL));
			for (int i = 0; i < numoftests; i++)
			{
				for (int j = 1; j < maxsize; j++)
				{
					int len = j;
					int* mass = new int[len];
					for (int k = 0; k < len; k++)
					{
						mass[k] = rand(-maxrandint, maxrandint);
					}
					BinaryTree<int>* Tree = new BinaryTree<int>(mass, len);
					BinaryTree<int>* newtree = new BinaryTree<int>();
					int temp = rand(-maxrandint, maxrandint);
					map<int>(Tree, sum<int>, temp, newtree);
					len = newtree->GetSize();
					int* mass1 = new int[len];
					int* mass2 = new int[len];
					Tree->GetMass(mass1);
					newtree->GetMass(mass2);
					for (int k = 0; k < len; k++)
					{
						Assert::IsTrue(mass2[k] == mass1[k] + temp/*, to_string(mass1[k]) + "==" + to_string(mass2[k] - temp)*/);
					}
					delete newtree;
					delete Tree;
					delete[] mass;
					delete[] mass1;
					delete[] mass2;
				}
			}
		}

		//TEST_METHOD(TestMapMult)
		//{
		//	srand((unsigned int)time(NULL));
		//	for (int i = 0; i < numoftests; i++)
		//	{
		//		for (int j = 1; j < maxsize; j++)
		//		{
		//			int* mass = new int[j];
		//			for (int k = 0; k < j; k++)
		//			{
		//				mass[k] = rand(-maxrandint, maxrandint);
		//			}
		//			BinaryTree<int>* Tree = new BinaryTree<int>(mass, j);
		//			BinaryTree<int>* newtree = new BinaryTree<int>();
		//			int temp = rand(1, maxrandint);
		//			map<int>(Tree, mult<int>, temp, newtree);
		//			int* mass1 = new int[j];
		//			int* mass2 = new int[j];
		//			Tree->GetMass(mass1);
		//			newtree->GetMass(mass2);
		//			for (int k = 0; k < j; k++)
		//			{
		//				Assert::IsTrue(mass2[k] == mass1[k] * temp/*, to_string(mass1[k]) + "==" + to_string(mass2[k] - temp)*/);
		//			}
		//			delete newtree;
		//			delete Tree;
		//			delete[] mass;
		//			delete[] mass1;
		//			delete[] mass2;
		//		}
		//	}
		//}

		TEST_METHOD(TestWhere)
		{
			srand((unsigned int)time(NULL));
			for (int i = 0; i < numoftests; i++)
			{
				for (int j = 1; j < maxsize; j++)
				{
					int* mass = new int[j];
					for (int k = 0; k < j; k++)
					{
						mass[k] = rand(-maxrandint, maxrandint);
					}
					BinaryTree<int>* Tree = new BinaryTree<int>(mass, j);
					BinaryTree<int>* newtree = new BinaryTree<int>();
					int temp = rand(-maxrandint, maxrandint);
					where<int>(Tree, more_then<int>, temp, newtree);
					int* mass1 = new int[j];
					int newlen = newtree->GetSize();
					int* mass2 = new int[newlen];
					Tree->GetMass(mass1);
					newtree->GetMass(mass2);
					for (int k = 0; k < newlen; k++)
					{
						Assert::IsTrue(more_then<int>(mass2[k], temp)/*, to_string(mass1[k]) + "==" + to_string(mass2[k] - temp)*/);
					}
					delete newtree;
					delete Tree;
					delete[] mass;
					delete[] mass1;
					delete[] mass2;
				}
			}
		}

		TEST_METHOD(TestDelteElem)
		{
			srand((unsigned int)time(NULL));
			for (int i = 0; i < numoftests; i++)
			{
				for (int j = 1; j < maxsize; j++)
				{
					int* mass = new int[j];
					for (int k = 0; k < j; k++)
					{
						mass[k] = rand(-maxrandint, maxrandint);
					}
					BinaryTree<int>* Tree = new BinaryTree<int>(mass, j);
					int temp = mass[rand(0, j - 1)];
					BinaryTree<int>* newtree = Tree->DeleteElem(temp);
					int newlen = newtree->GetSize();
					int* mass2 = new int[newlen];
					newtree->GetMass(mass2);
					for (int k = 0; k < newlen; k++)
					{
						Assert::IsTrue(mass2[k] != temp);
					}
					delete newtree;
					delete[] mass;
					delete[] mass2;
				}
			}
		}

		TEST_METHOD(TestInsert)
		{
			srand((unsigned int)time(NULL));
			for (int i = 0; i < numoftests; i++)
			{
				for (int j = 1; j < maxsize; j++)
				{
					int len = j;
					int* mass = new int[len];
					for (int k = 0; k < len; k++)
					{
						mass[k] = rand(-maxrandint, maxrandint);
					}
					BinaryTree<int>* Tree = new BinaryTree<int>(mass, len);
					int temp = rand(-maxrandint, maxrandint);
					Tree->Insert(temp);
					len = Tree->GetSize();
					int* mass1 = new int[len];
					Tree->GetMass(mass1);
					for (int k = 0; k < len; k++)
					{
						if (mass1[k] == temp)
						{
							Assert::IsTrue(true);
							break;
						}
						else if (k == len - 1)
						{
							Assert::IsTrue(false);
						}
					}
					delete Tree;
					delete[] mass;
					delete[] mass1;
				}
			}
		}
		TEST_METHOD(TestMerge)
		{
			srand((unsigned int)time(NULL));
			for (int i = 0; i < numoftests; i++)
			{
				for (int j = 1; j < maxsize; j++)
				{
					int len1 = rand(1, j);
					int len2 = rand(1, j);
					int* mass1 = new int[len1];
					int* mass2 = new int[len2];
					for (int k = 0; k < len1; k++)
					{
						mass1[k] = rand(-maxrandint, maxrandint);
					}
					for (int k = 0; k < len2; k++)
					{
						mass2[k] = rand(-maxrandint, maxrandint);
					}
					BinaryTree<int>* Tree1 = new BinaryTree<int>(mass1, len1);
					Tree1->GetMass(mass1);
					len1 = Tree1->GetSize();
					BinaryTree<int>* Tree2 = new BinaryTree<int>(mass2, len2);
					Tree2->GetMass(mass2);
					len2 = Tree2->GetSize();
					BinaryTree<int>* newtree = MergeTrees(Tree1, Tree2);
					int len3 = newtree->GetSize();
					int* mass3 = new int[len3];
					newtree->GetMass(mass3);
					bool not_in_first_tree = true;
					for (int k = 0; k < len3; k++)
					{
						not_in_first_tree = true;
						for (int i1 = 0; i1 < len1; i1++)
						{
							if (mass3[k] == mass1[i1])
							{
								Assert::IsTrue(true);
								not_in_first_tree = false;
								break;
							}
						}
						if (not_in_first_tree) for (int i2 = 0; i2 < len2; i2++)
						{
							if (mass3[k] == mass2[i2])
							{
								Assert::IsTrue(true);
								break;
							}
							if (i2 == len2 - 1)
							{
								Assert::IsTrue(false);
							}
						}
					}
					delete Tree1;
					delete Tree2;
					delete newtree;
					delete[] mass3;
					delete[] mass2;
					delete[] mass1;
				}
			}
		}
		TEST_METHOD(TestGetSubTree)
		{
			srand((unsigned int)time(NULL));
			for (int i = 0; i < numoftests; i++)
			{
				for (int j = 1; j < maxsize; j++)
				{
					int* mass = new int[j];
					for (int k = 0; k < j; k++)
					{
						mass[k] = rand(-maxrandint, maxrandint);
					}
					int temp = mass[rand(0, j - 1)];
					BinaryTree<int>* Tree = new BinaryTree<int>(mass, j);
					BinaryTree<int>* node = Tree->GetSubTree(temp);
					Assert::IsTrue(((" " + Tree->ToString()).find(node->ToString()) > 0));
					delete Tree;
					delete[] mass;
					delete node;
				}
			}
		}

		TEST_METHOD(TestToString)
		{
			srand((unsigned int)time(NULL));
			for (int i = 0; i < numoftests; i++)
			{
				for (int j = 1; j < maxsize; j++)
				{
					int* mass = new int[j];
					for (int k = 0; k < j; k++)
					{
						mass[k] = rand(-maxrandint, maxrandint);
					}
					BinaryTree<int>* Tree = new BinaryTree<int>(mass, j);
					string tree = " " + Tree->ToString();
					for (int i1 = 0; i1 < j; i1++)
					{
						Assert::IsTrue(tree.find(to_string(mass[i1])));
					}
					delete Tree;
					delete[] mass;
				}
			}
		}
		TEST_METHOD(TestCheckSubTree)
		{
			srand((unsigned int)time(NULL));
			for (int i = 0; i < numoftests; i++)
			{
				for (int j = 1; j < maxsize; j++)
				{
					int* mass = new int[j];
					for (int k = 0; k < j; k++)
					{
						mass[k] = rand(-maxrandint, maxrandint);
					}
					int temp = mass[rand(0, j - 1)];
					BinaryTree<int>* Tree = new BinaryTree<int>(mass, j);
					BinaryTree<int>* node = Tree->GetSubTree(temp);
					Assert::IsTrue(Tree->CheckSubTree(node));
					delete Tree;
					delete[] mass;
					delete node;
				}
			}
		}
		TEST_METHOD(TestCheckElement)
		{
			srand((unsigned int)time(NULL));
			for (int i = 0; i < numoftests; i++)
			{
				for (int j = 1; j < maxsize; j++)
				{
					int* mass = new int[j];
					for (int k = 0; k < j; k++)
					{
						mass[k] = rand(-maxrandint, maxrandint);
					}
					int temp = mass[rand(0, j - 1)];
					BinaryTree<int>* Tree = new BinaryTree<int>(mass, j);
					Assert::IsTrue(Tree->CheckElement(temp));
					delete Tree;
					delete[] mass;
				}
			}
		}
		/*TEST_METHOD(TestGetSubTreeFromPass)
		{

			srand((unsigned int)time(NULL));
			for (int i = 0; i < numoftests; i++)
			{
				for (int j = 1; j < maxsize; j++)
				{
					int* mass = new int[j];
					for (int k = 0; k < j; k++)
					{
						mass[k] = rand(-maxrandint, maxrandint);
					}
					int temp = mass[rand(0, j - 1)];
					BinaryTree<int>* Tree = new BinaryTree<int>(mass, j);
					Assert::IsTrue(Tree->CheckElement(temp));
					delete Tree;
					delete[] mass;
				}
			}
		}*/
	};
}
