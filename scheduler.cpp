#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "string.h"
#include <algorithm>

struct job
{
	int job_id;
	int job_arrival;
	int job_length;
	int start_time = 0;
	int finish_time = 0;
	int remaining_time = 0;
};

bool compbyarrival(const job& a, const job& b)
{
	return a.job_arrival < b.job_arrival;
}

bool compbySJF(const job& a, const job& b)
{
	if(a.job_arrival == b.job_arrival)
	{
		return a.job_length < b.job_length;
	}
	else
	return a.job_arrival < b.job_arrival;
}

bool compbyBJF(const job& a, const job& b)
{
	if(a.job_arrival == b.job_arrival)
	{
		return a.job_length > b.job_length;
	}
	else
	return a.job_arrival < b.job_arrival;
}

int main()
{
	std::vector<job> listofjob;
	job testjob;
	std::string buffer;
	std::ifstream myfile("jobs.dat");
	int counter = 0;
	while(std::getline(myfile, buffer))
	{
		std::istringstream element(buffer);
		element >> testjob.job_id;
		element >> testjob.job_arrival;
		element >> testjob.job_length;
		testjob.remaining_time =  testjob.job_length;
		listofjob.push_back(testjob);
		std::cout << listofjob[counter].job_id<< " ";
		std::cout << listofjob[counter].job_arrival << " ";
		std::cout << listofjob[counter].job_length << " ";
		std::cout << listofjob[counter].remaining_time << std::endl;
		counter++;
	}
	std::cout << std::endl;
	std::sort(listofjob.begin(), listofjob.end(), compbyarrival);
	
	for(int i = 0; i < counter; i++)
	{
		std::cout << listofjob[i].job_id<< " ";
		std::cout << listofjob[i].job_arrival << " ";
		std::cout << listofjob[i].job_length << std::endl;
	} 
	std::cout << std::endl;
	//FIFO no preemption
	int clock = 0;
	int finished_task = 0;
	bool done = false;
	while(done == false)
	{
		//std::cout <<"Start";
		if(listofjob[finished_task].start_time == 0 && clock == 0)
		{
			listofjob[finished_task].start_time = 0;	
		}
		else if(listofjob[finished_task].start_time == 0 && finished_task != 0)
		{
			listofjob[finished_task].start_time = clock - 1;	

		}
		listofjob[finished_task].finish_time = clock; 
		if(listofjob[finished_task].remaining_time != 0)
		{
			listofjob[finished_task].remaining_time--;
		}
		else
		{
			finished_task++;
		}
		if(finished_task == counter)
		{
			done = true;
		}
		clock++;
	}
	
	
	for(int i = 0; i < counter; i++)
	{
		std::cout << listofjob[i].job_id<< " ";
		std::cout << listofjob[i].start_time << " ";
		std::cout << listofjob[i].finish_time << std::endl;
	} 
	return 0;
}
