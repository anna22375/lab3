// 3lab.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iomanip>
#include <windows.h>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <stack>        
#include <vector>
#include <queue> 

using namespace std;
const int N = 7;

int costMatrix[N][N];  //исходная матрица
//узел дерева состояний
struct Node
{
	// хранит родительский узел текущего узла
	// помогает в отслеживании пути, когда ответ найден
	Node* parent;
	// содержит стоимость для узлов-предков
	// включая текущий узел 
	int pathCost;
	// содержит наименее многообещающие затраты
	int cost;
	//содержите число рабочего
	int workerID;
	// содержит идентификатор работы
	int jobID;
	// Булевский массив, который будет содержать
	// информацию о доступных вакансиях
	bool assigned[];
	
};

// Функция для выделения нового узла дерева поиска
// Здесь работнику x назначается задание y
Node* newNode(int x, int y, bool assigned[],
	Node* parent)
{
	Node* node = new Node;

	for (int j = 0; j < N; j++)
		node->assigned[j] = assigned[j];
	node->assigned[y] = true;

	node->parent = parent;
	node->workerID = x;
	node->jobID = y;

	return node;
}

// Функция для вычисления наименее многообещающей стоимости
// узла после того, как рабочему x назначено задание y.
int calculateCost(int costMatrix[N][N], int x,
	int y, bool assigned[], int N2)
{
	int cost = 0;
    int N3 = N2;
	// для хранения недоступных заданий
	bool *available = new bool[N3];
	for (int i = 0; i < N3; i++)
		available[N3] = true;

	// старт со следующего рабочего
	for (int i = x + 1; i < N3; i++)
	{
		int record = INT_MAX, minIndex = -1;
		

		// делать для каждого задания
		for (int j = 0; j < N3; j++)
		{
			// если задание не назначено
			if (!assigned[j] && available[j] &&
				costMatrix[i][j] < record)
			{
				// сохранить номер задания
				minIndex = j;

				// хранить стоимость
				record = costMatrix[i][j];
			}
		}

		// добавление стоимости следующего рабочего
		cost += record;

		// задание становится недоступным
		available[minIndex] = false;
	}

	return cost;
}


struct comp
{
	bool operator()(const Node* lhs,
		const Node* rhs) const
	{
		return lhs->cost > rhs->cost;
	}
};

// печать
void printAssignments(Node *min)
{
	if (min->parent == NULL)
		return;

	printAssignments(min->parent);
	cout << "Работнику № " << min->workerID + 1
		<< " назначена работа № " << min->jobID+1 << endl;

}

// Находит минимальную стоимость, используя метод ветвей и границ
void findMinCost1(int costMatrix[N][N], int N1)
{
	// Создаем очередь приоритетов для хранения живых узлов
	// поиска дерева;
	priority_queue<Node*, std::vector<Node*>, comp> pq;
	
    int N2 = N1;
    //int costMatrix2[N2][N2];
    //memcpy(costMatrix2, costMatrix, sizeof(costMatrix2));
	// инициализация
	bool assigned[N] = { false };
	Node* root = newNode(-1, -1, assigned, NULL);
	root->pathCost = root->cost = 0;
	root->workerID = -1;

	// Добавить фиктивный узел в список живых узлов;
	pq.push(root);

	// Находит живой узел с наименьшей стоимостью,
	// добавление дочерних элементов в список активных узлов и
	// окончательно удаляет его из списка.
	while (!pq.empty())
	{
		// Найти живой узел с наименьшей оценкой стоимости
     	Node* min = pq.top();
		
		

		// Найденный узел удаляется из списка
		pq.pop();

        // i хранит следующего рабочего
		int i = min->workerID + 1;
		int k2 = min->jobID + 1;
		int k3 = min->pathCost;
		int k4 = min->cost;
		
		cout << "\n";
		cout <<"Номер рабочего: "<<  i  << " Номер работы: "<<  k2  << " Стоимость: "<<  k3 << endl;
		//cout <<"Номер рабочего: "<<  i  << " Номер работы: "<<  k2  << " Стоимость: "<<  k3  << " МинСт: "<<  k4  << endl;
		cout << "\n";
		cout <<"Номер рабочего: "<<  i + 1 << endl;
	

		// если всем работникам назначено задание
		if (i == N2)
		{
			printAssignments(min);
			cout << "\nМинимальная общая стоимость: " << min->cost<< endl;
			return;
		}

		//для каждого задания
		for (int j = 0; j < N2; j++)
		{
			// Если не назначено
			if (!min->assigned[j])
			{
				cout << "Рассматриваем работу №: "<< j + 1 <<endl;
				
				// создаем новый узел дерева
				Node* child = newNode(i, j, min->assigned, min);
				cout << "Cоздаем новый узел дерева: "<<"назначаем работника "<< i + 1 << " на работу "<< j + 1<< endl;

				// стоимость для узлов-предков, включая текущий узел
				child->pathCost = min->pathCost + costMatrix[i][j];
				
				cout << "Cтоимость для узлов-предков, включая текущий узел: "<< child->pathCost <<endl;

			// вычисляем нижнюю границу
				child->cost = child->pathCost +
					calculateCost(costMatrix, i, j, child->assigned, N2);
				//cout << "Нижняя граница: "<< child->cost <<endl;
				

				// Добавить дочерний элемент в список активных узлов;
				pq.push(child);
				
				
			}
			
		}
	}
}


int main()
{
	
	setlocale(LC_ALL, "Russian");
	
	
	bool pr= false;
	int N1; // размарность матрицы
	char menu;
	


		cout << "\n";
		cout << " -----------------------------------\n";
		cout << " Меню\n";
		cout << " явыберите способ заполнения: \n";
		cout << " 1 - Ввод с файла \n";
		cout << " 2 - Ввод с клавиатуры \n";
		cout << " -----------------------------------\n";
		cin >> menu;
		switch (menu)
		{
		case '1':
		{ 
		   //Создаем файловый поток и связываем его с файлом


while (pr == false)
	{
		cout << "Введите размерность матрицы N : " << endl;
		cin >> N1;
		if (N1<0 || N1==0 || N1>20) {
			cout << "Неправильная размерность! " << endl;
			pr = false;
			return 0;
		}
		else pr = true;
	}


        ifstream Proga("input.txt");    // ввод данных из файла
    //  double **a=new double *[n];
            for (int i = 0; i < N1; ++i)
                for (int j = 0; j < N1; ++j)
                    Proga>>costMatrix[i][j];


cout << "Исходная матрица: " << endl;   //печать матрицы
          for(int i = 0; i < N1; i++) 
     { 
          for(int j = 0; j < N1; j++)
     {
            std::cout << costMatrix[i][j] << " ";
      }
             std::cout << std::endl;
      }
     
      cout << "\n";
			break;
		}

		case '2':
		{  
		while (pr == false)	{
	        	cout << "Введите размерность матрицы N : " << endl;
		        cin >> N1;
		        if (N1<0 || N1==0 || N1>20) {
			    cout << "Неправильная размерность! " << endl;
			     pr = false;
			     return 0;
		    }
	        	else pr = true;
      	}
	
	    cout << "Введите матрицу: "<< endl;  //ввод матрицы с клавиатуры
     	for (size_t i = 0; i < N1; ++i){
        for (size_t j = 0; j < N1; ++j){
        std::cin >> costMatrix[i][j];
		if(costMatrix[i][j]<0 || costMatrix[i][j]>10000) return 0;}}

       cout << "Исходная матрица: " << endl;   //печать матрицы
       for(int i = 0; i < N1; i++) 
       {
         for(int j = 0; j < N1; j++)
       {
        std::cout << costMatrix[i][j] << " ";
       }
         std::cout << std::endl;
       }
     
      cout << "\n";
		    
			break;
		}

			
		default:
			cout << "Неправильно! \n";
			return 0;
		}
      
    cout << "Процесс:" << endl; 
    cout << "\n";
 
    findMinCost1(costMatrix, N1);
     cout << "\n";
	 system("pause");

	return 0;
}


