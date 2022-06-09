/* Author: Suyash Pandit
Date: June 2022
This is a Graph Creator, the final project in C++ Data Structures
*/

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

struct edge;

struct node {
  char label[20];
  vector <edge*> edges;
};

struct edge {
  node* start;
  node* end;
  int weight;
};

bool check_connection(node* n1, node* n2);

int main() {
  vector <node*> nodes;
  char action[20];
  char newlabel[20];
  int newweight;
  while (true) {
    cout << "What would you like to do? (ADD, REMOVE, PATH, PRINT, QUIT) "; cin >> action;
    if (strcmp(action, "ADD") == 0) {
      cout << "What would you like to add? (VERTEX, EDGE) "; cin >> action;
      if (strcmp(action, "VERTEX") == 0) {
	cout << "Enter the label for the new vertex: "; cin >> newlabel;
	node* n = new node();
	strcpy(n->label, newlabel);
	nodes.push_back(n);
      }
      else if (strcmp(action, "EDGE") == 0) {
	node* start = NULL;
	node* end = NULL;
	while (true) {
	  cout << "Enter the starting node: "; cin >> newlabel;
	  for (int i=0; i<nodes.size(); i++) {
	    if (strcmp(nodes[i]->label,newlabel) == 0) {
	      start = nodes[i];
	    }
	  }
	  if (start == NULL) {
	    cout << "No node has that label." << endl;
	  }
	  else {
	    break;
	  }
	}
	while (true) {
	  cout << "Enter the end node: "; cin >> newlabel;
	  for (int i=0; i<nodes.size(); i++) {
	    if (strcmp(nodes[i]->label,newlabel) == 0) {
	      end = nodes[i];
	    }
	  }
	  if (end == NULL) {
	    cout << "No node has that label." << endl;
	  }
	  else {
	    break;
	  }
	}
	cout << "Enter the weight of the edge: "; cin >> newweight;
	edge* e = new edge();
	e->start = start;
	e->end = end;
	e->weight = newweight;
	start->edges.push_back(e);
      }
    }
    else if (strcmp(action, "REMOVE") == 0) {
      cout << "What would you like to remove? (VERTEX, EDGE) "; cin >> action;
      if (strcmp(action, "VERTEX") == 0) {
	node* removal = NULL;
	int index;
	cout << "Enter the vertex to delete: "; cin >> newlabel;
	for (int i=0; i<nodes.size(); i++) {
	  if (strcmp(nodes[i]->label,newlabel) == 0) {
	    removal = nodes[i];
	    index = i;
	  }
	}
	for (int i=0; i<nodes.size(); i++) {
	  if (check_connection(nodes[i],removal) == true) {
	    for (int j=0; j<nodes[i]->edges.size(); j++) {
	      if (nodes[i]->edges[j]->end == removal) {
		nodes[i]->edges.erase(nodes[i]->edges.begin()+i);
		break;
	      }
	    }
	  }
	}
	nodes.erase(nodes.begin()+index);
      }
      else if (strcmp(action, "EDGE") == 0) {
	node* start = NULL;
	node* end = NULL;
        while (true) {
          cout << "Enter the starting node of the edge to delete: "; cin >> newlabel;
          for (int i=0; i<nodes.size(); i++) {
            if (strcmp(nodes[i]->label,newlabel) == 0) {
              start = nodes[i];
            }
          }
          if (start == NULL) {
            cout << "No node has that label." << endl;
          }
          else {
            break;
          }
        }
        while (true) {
          cout << "Enter the end node if tge edge to delete: "; cin >> newlabel;
          for (int i=0; i<nodes.size(); i++) {
            if (strcmp(nodes[i]->label,newlabel) == 0) {
              end = nodes[i];
            }
          }
          if (end == NULL) {
            cout << "No node has that label." << endl;
          }
          else {
            break;
          }
        }
	if (check_connection(start, end) == false) {
	  cout << "There's no connection between those vertices." << endl;
	}
	else {
	  for (int i=0; i<start->edges.size(); i++) {
	    if (start->edges[i]->end == end) {
	      start->edges.erase(start->edges.begin()+i);
	      break;
	    }
	  }
	}

      }
    }
    else if (strcmp(action, "PRINT") == 0) {
      // print the adjacency matrix (for debugging purposes)
      for (int i=0; i<nodes.size(); i++) {
	cout << nodes[i]->label;
	for (int j=0; j<nodes.size(); j++) {
	  cout << "\t";
	  if (i == j) {
	    cout << "X";
	  }
	  else if (check_connection(nodes[i],nodes[j]) == true) {
	    cout << "T";
	  }
	  else {
	    cout << "F";
	  }
	}
	cout << endl;
      }
    }
    else if (strcmp(action, "PATH") == 0) {
    }
    else if (strcmp(action, "QUIT") == 0) {
      break;
    }
  }
  return 0;
}

bool check_connection(node* n1, node* n2) {
  // checks if a directed edge from n1 to n2 exists
  for (int i=0; i<n1->edges.size(); i++) {
    if (n1->edges[i]->end == n2) {
      return true;
    }
  }
  return false;
}
