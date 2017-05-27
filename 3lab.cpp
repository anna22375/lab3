// 3lab.cpp: ���������� ����� ����� ��� ����������� ����������.
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

int costMatrix[N][N];  //�������� �������
//���� ������ ���������
struct Node
{
	// ������ ������������ ���� �������� ����
	// �������� � ������������ ����, ����� ����� ������
	Node* parent;
	// �������� ��������� ��� �����-�������
	// ������� ������� ���� 
	int pathCost;
	// �������� �������� �������������� �������
	int cost;
	//��������� ����� ��������
	int workerID;
	// �������� ������������� ������
	int jobID;
	// ��������� ������, ������� ����� ���������
	// ���������� � ��������� ���������
	bool assigned[];
	
};

// ������� ��� ��������� ������ ���� ������ ������
// ����� ��������� x ����������� ������� y
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

// ������� ��� ���������� �������� �������������� ���������
// ���� ����� ����, ��� �������� x ��������� ������� y.
int calculateCost(int costMatrix[N][N], int x,
	int y, bool assigned[], int N2)
{
	int cost = 0;
    int N3 = N2;
	// ��� �������� ����������� �������
	bool *available = new bool[N3];
	for (int i = 0; i < N3; i++)
		available[N3] = true;

	// ����� �� ���������� ��������
	for (int i = x + 1; i < N3; i++)
	{
		int record = INT_MAX, minIndex = -1;
		

		// ������ ��� ������� �������
		for (int j = 0; j < N3; j++)
		{
			// ���� ������� �� ���������
			if (!assigned[j] && available[j] &&
				costMatrix[i][j] < record)
			{
				// ��������� ����� �������
				minIndex = j;

				// ������� ���������
				record = costMatrix[i][j];
			}
		}

		// ���������� ��������� ���������� ��������
		cost += record;

		// ������� ���������� �����������
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

// ������
void printAssignments(Node *min)
{
	if (min->parent == NULL)
		return;

	printAssignments(min->parent);
	cout << "��������� � " << min->workerID + 1
		<< " ��������� ������ � " << min->jobID+1 << endl;

}

// ������� ����������� ���������, ��������� ����� ������ � ������
void findMinCost1(int costMatrix[N][N], int N1)
{
	// ������� ������� ����������� ��� �������� ����� �����
	// ������ ������;
	priority_queue<Node*, std::vector<Node*>, comp> pq;
	
    int N2 = N1;
    //int costMatrix2[N2][N2];
    //memcpy(costMatrix2, costMatrix, sizeof(costMatrix2));
	// �������������
	bool assigned[N] = { false };
	Node* root = newNode(-1, -1, assigned, NULL);
	root->pathCost = root->cost = 0;
	root->workerID = -1;

	// �������� ��������� ���� � ������ ����� �����;
	pq.push(root);

	// ������� ����� ���� � ���������� ����������,
	// ���������� �������� ��������� � ������ �������� ����� �
	// ������������ ������� ��� �� ������.
	while (!pq.empty())
	{
		// ����� ����� ���� � ���������� ������� ���������
     	Node* min = pq.top();
		
		

		// ��������� ���� ��������� �� ������
		pq.pop();

        // i ������ ���������� ��������
		int i = min->workerID + 1;
		int k2 = min->jobID + 1;
		int k3 = min->pathCost;
		int k4 = min->cost;
		
		cout << "\n";
		cout <<"����� ��������: "<<  i  << " ����� ������: "<<  k2  << " ���������: "<<  k3 << endl;
		//cout <<"����� ��������: "<<  i  << " ����� ������: "<<  k2  << " ���������: "<<  k3  << " �����: "<<  k4  << endl;
		cout << "\n";
		cout <<"����� ��������: "<<  i + 1 << endl;
	

		// ���� ���� ���������� ��������� �������
		if (i == N2)
		{
			printAssignments(min);
			cout << "\n����������� ����� ���������: " << min->cost<< endl;
			return;
		}

		//��� ������� �������
		for (int j = 0; j < N2; j++)
		{
			// ���� �� ���������
			if (!min->assigned[j])
			{
				cout << "������������� ������ �: "<< j + 1 <<endl;
				
				// ������� ����� ���� ������
				Node* child = newNode(i, j, min->assigned, min);
				cout << "C������ ����� ���� ������: "<<"��������� ��������� "<< i + 1 << " �� ������ "<< j + 1<< endl;

				// ��������� ��� �����-�������, ������� ������� ����
				child->pathCost = min->pathCost + costMatrix[i][j];
				
				cout << "C�������� ��� �����-�������, ������� ������� ����: "<< child->pathCost <<endl;

			// ��������� ������ �������
				child->cost = child->pathCost +
					calculateCost(costMatrix, i, j, child->assigned, N2);
				//cout << "������ �������: "<< child->cost <<endl;
				

				// �������� �������� ������� � ������ �������� �����;
				pq.push(child);
				
				
			}
			
		}
	}
}


int main()
{
	
	setlocale(LC_ALL, "Russian");
	
	
	bool pr= false;
	int N1; // ����������� �������
	char menu;
	


		cout << "\n";
		cout << " -----------------------------------\n";
		cout << " ����\n";
		cout << " ��������� ������ ����������: \n";
		cout << " 1 - ���� � ����� \n";
		cout << " 2 - ���� � ���������� \n";
		cout << " -----------------------------------\n";
		cin >> menu;
		switch (menu)
		{
		case '1':
		{ 
		   //������� �������� ����� � ��������� ��� � ������


while (pr == false)
	{
		cout << "������� ����������� ������� N : " << endl;
		cin >> N1;
		if (N1<0 || N1==0 || N1>20) {
			cout << "������������ �����������! " << endl;
			pr = false;
			return 0;
		}
		else pr = true;
	}


        ifstream Proga("input.txt");    // ���� ������ �� �����
    //  double **a=new double *[n];
            for (int i = 0; i < N1; ++i)
                for (int j = 0; j < N1; ++j)
                    Proga>>costMatrix[i][j];


cout << "�������� �������: " << endl;   //������ �������
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
	        	cout << "������� ����������� ������� N : " << endl;
		        cin >> N1;
		        if (N1<0 || N1==0 || N1>20) {
			    cout << "������������ �����������! " << endl;
			     pr = false;
			     return 0;
		    }
	        	else pr = true;
      	}
	
	    cout << "������� �������: "<< endl;  //���� ������� � ����������
     	for (size_t i = 0; i < N1; ++i){
        for (size_t j = 0; j < N1; ++j){
        std::cin >> costMatrix[i][j];
		if(costMatrix[i][j]<0 || costMatrix[i][j]>10000) return 0;}}

       cout << "�������� �������: " << endl;   //������ �������
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
			cout << "�����������! \n";
			return 0;
		}
      
    cout << "�������:" << endl; 
    cout << "\n";
 
    findMinCost1(costMatrix, N1);
     cout << "\n";
	 system("pause");

	return 0;
}


