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
	bool running = false;
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
	
	//FIFO no preemption
	int clock = 0;
	int finished_task = 0;
	bool done = false;
	while(done == false)
	{
		if(listofjob[finished_task].start_time == 0 && clock == 0)
		{
			listofjob[finished_task].start_time = 0;
			listofjob[finished_task].running = true;	
		}
		else if(listofjob[finished_task].start_time == 0 && finished_task != 0 && clock >= listofjob[finished_task].job_arrival)
		{
			listofjob[finished_task].start_time = clock;	
			listofjob[finished_task].running = true;
		}
		if(listofjob[finished_task].running == true)
		{
			
			if(listofjob[finished_task].remaining_time >= 0)
			{
				listofjob[finished_task].remaining_time--;
				if(listofjob[finished_task].remaining_time == 0)
				{
					listofjob[finished_task].finish_time = clock + 1;
					listofjob[finished_task].running = false;
					finished_task++;
					if(clock >= listofjob[finished_task].job_arrival)
					{
						listofjob[finished_task].start_time = clock+1;	
						listofjob[finished_task].running = true;
					}					
				}
			}
		}
		if(finished_task == counter)
		{
			done = true;
		}
		clock++;
	}
	
	std::cout<< std::endl << "FIFO: " << std::endl;
	for(int i = 0; i < counter; i++)
	{
		std::cout << listofjob[i].job_id<< " ";
		std::cout << listofjob[i].start_time << " ";
		std::cout << listofjob[i].finish_time << std::endl;
	} 
	
	//SJF no preemption
	//Reset values
	clock = 0;
	finished_task = 0;
	done = false;
	for(int i = 0; i < counter; i++)
	{
		listofjob[i].start_time = 0;
		listofjob[i].finish_time = 0;
		listofjob[i].remaining_time = listofjob[i].job_length;
	}
 
	//Resort vector
	std::sort(listofjob.begin(), listofjob.end(), compbySJF);
 
	while(done == false)
	{
		if(listofjob[finished_task].start_time == 0 && clock == 0)
		{
			listofjob[finished_task].start_time = 0;
			listofjob[finished_task].running = true;	
		}
		else if(listofjob[finished_task].start_time == 0 && finished_task != 0 && clock >= listofjob[finished_task].job_arrival)
		{
			listofjob[finished_task].start_time = clock;	
			listofjob[finished_task].running = true;
		}
		if(listofjob[finished_task].running == true)
		{
			
			if(listofjob[finished_task].remaining_time >= 0)
			{
				listofjob[finished_task].remaining_time--;
				if(listofjob[finished_task].remaining_time == 0)
				{
					listofjob[finished_task].finish_time = clock + 1;
					listofjob[finished_task].running = false;
					finished_task++;
					if(clock >= listofjob[finished_task].job_arrival)
					{
						listofjob[finished_task].start_time = clock+1;	
						listofjob[finished_task].running = true;
					}					
				}
			}
		}
		if(finished_task == counter)
		{
			done = true;
		}
		clock++;
	}

	std::cout<< std::endl << "SJF: " << std::endl;
	for(int i = 0; i < counter; i++)
	{
		std::cout << listofjob[i].job_id<< " ";
		std::cout << listofjob[i].start_time << " ";
		std::cout << listofjob[i].finish_time << std::endl;
	} 

	//BJF no preemption
	//Reset values
	clock = 0;
	finished_task = 0;
	done = false;
	for(int i = 0; i < counter; i++)
	{
		listofjob[i].start_time = 0;
		listofjob[i].finish_time = 0;
		listofjob[i].remaining_time = listofjob[i].job_length;
	} 
	//Resort vector
	std::sort(listofjob.begin(), listofjob.end(), compbyBJF);
	while(done == false)
	{
		if(listofjob[finished_task].start_time == 0 && clock == 0)
		{
			listofjob[finished_task].start_time = 0;
			listofjob[finished_task].running = true;	
		}
		else if(listofjob[finished_task].start_time == 0 && finished_task != 0 && clock >= listofjob[finished_task].job_arrival)
		{
			listofjob[finished_task].start_time = clock;	
			listofjob[finished_task].running = true;
		}
		if(listofjob[finished_task].running == true)
		{
			
			if(listofjob[finished_task].remaining_time >= 0)
			{
				listofjob[finished_task].remaining_time--;
				if(listofjob[finished_task].remaining_time == 0)
				{
					listofjob[finished_task].finish_time = clock + 1;
					listofjob[finished_task].running = false;
					finished_task++;
					if(clock >= listofjob[finished_task].job_arrival)
					{
						listofjob[finished_task].start_time = clock+1;	
						listofjob[finished_task].running = true;
					}					
				}
			}
		}
		if(finished_task == counter)
		{
			done = true;
		}
		clock++;
	}

	std::cout<< std::endl << "BJF: " << std::endl;
	for(int i = 0; i < counter; i++)
	{
		std::cout << listofjob[i].job_id<< " ";
		std::cout << listofjob[i].start_time << " ";
		std::cout << listofjob[i].finish_time << std::endl;
	} 


	return 0;
}
