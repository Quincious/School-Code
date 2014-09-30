	/**   CS515 Assignment12
	File: climber.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 11/26/13 
	Collaboration Declaration: 
	*/

#include <iostream>
#include <string>
#include <sstream>
#include <cfloat>
#include <queue>
#include <limits.h>
using namespace std;

struct post{
	pair<int,int> vertex;
	int weight;
};

bool operator<(const post& p1, const post& p2) {
  return p1.weight < p2.weight;
};

int square(int a)
{
	return a*a;
}

int main()
{
	string input;

	while(getline(cin, input))
	{
		priority_queue<post> queue;
		int numberOfPosts;
		stringstream ssInput(input);
		ssInput >> numberOfPosts;

		post start, end;

		ssInput >> start.vertex.first; 
		ssInput >> start.vertex.second;
		start.weight = 0;
		queue.push(start);

		ssInput >> end.vertex.first; 
		ssInput >> end.vertex.second;
		end.weight = INT_MIN;
		queue.push(end);

		for(int i = 2; i < numberOfPosts; i++)
		{
			post newPost;
			ssInput >> newPost.vertex.first; 
			ssInput >> newPost.vertex.second;
			newPost.weight = INT_MIN;
			queue.push(newPost);
		}

		/*priority_queue<post> temp = queue;
		while(!queue.empty())
		{			
			cout << "(" << queue.top().vertex.first << "," << queue.top().vertex.second << ") = " << queue.top().weight << endl;
			queue.pop();
		}
		queue = temp;*/

		while(!queue.empty())
		{
			priority_queue<post> visited;

			post curPost = queue.top();
			queue.pop();

			//cout << "(" << curPost.vertex.first << "," << curPost.vertex.second << ") = " << curPost.weight << endl;

			while(!queue.empty())
			{
				post checkPost = queue.top();
				queue.pop();

				//cout << "(" << checkPost.vertex.first << "," << checkPost.vertex.second << ") = " << checkPost.weight << endl;

				int ropeNeed = square(checkPost.vertex.first - curPost.vertex.first) + 
					square(checkPost.vertex.second - curPost.vertex.second);

				ropeNeed *= -1;

				if(ropeNeed > curPost.weight)
					ropeNeed = curPost.weight;
				if(ropeNeed > checkPost.weight)
					checkPost.weight = ropeNeed;

				if(checkPost.vertex == end.vertex)
					end.weight = checkPost.weight;

				visited.push(checkPost);
			}

			queue = visited;
		}

		cout << "Rope Needed: " << end.weight * -1 << endl;

	}

	return 0;
}