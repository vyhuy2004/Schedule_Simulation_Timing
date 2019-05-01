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
	bool ready = false;
};

bool compbyarrival(const job& a, const job& b)
{
	return a.job_arrival < b.job_arrival;
}

bool compbylength(const job& a, const job& b)
{
	return a.remaining_time < b.remaining_time;
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

bool operator==(const job& a, const job& b)
{
    return a.job_id == b.job_id;
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
		std::cout << "Job " << listofjob[i].job_id<< " ";
		std::cout << "starts at " << listofjob[i].start_time << " ";
		std::cout << "ends at " << listofjob[i].finish_time << " ";
		std::cout << ". Turnaround time =  " << listofjob[i].finish_time - listofjob[i].start_time << " ";
		std::cout << ". Response time =  " << listofjob[i].start_time - listofjob[i].job_arrival << std::endl;
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
		std::cout << "Job " << listofjob[i].job_id<< " ";
		std::cout << "starts at " << listofjob[i].start_time << " ";
		std::cout << "ends at " << listofjob[i].finish_time << " ";
		std::cout << ". Turnaround time =  " << listofjob[i].finish_time - listofjob[i].start_time << " ";
		std::cout << ". Response time =  " << listofjob[i].start_time - listofjob[i].job_arrival << std::endl;
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
		std::cout << "Job " << listofjob[i].job_id<< " ";
		std::cout << "starts at " << listofjob[i].start_time << " ";
		std::cout << "ends at " << listofjob[i].finish_time << " ";
		std::cout << ". Turnaround time =  " << listofjob[i].finish_time - listofjob[i].start_time << " ";
		std::cout << ". Response time =  " << listofjob[i].start_time - listofjob[i].job_arrival << std::endl;
	} 


	//STCF
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
 	//Initialize new vector
 	std::vector<job> readyQ;
 	int runningtask = 0;
 	int readytask = 0;
	//Resort vector
	std::sort(listofjob.begin(), listofjob.end(), compbySJF);
	while(done == false)
	{
		//Set to ready
		for(int i = 0; i < counter; i++)
		{
			if (listofjob[i].job_arrival == clock)
			{
				listofjob[i].ready = true;
				readyQ.push_back(listofjob[i]);
				readytask++;
				std::sort(readyQ.begin(), readyQ.end(), compbylength);
			}
		}
		if(!readyQ.empty())
		{
			//Get current running task
			for(int i = 0; i < counter; i++)
			{
				if(listofjob[i] == readyQ[0])
				{
					runningtask = i;
					break;
				}
			}
			//Run task
			if(listofjob[runningtask].running == false && ((listofjob[runningtask].remaining_time == listofjob[runningtask].job_length && listofjob[runningtask].job_arrival == 0) || (listofjob[runningtask].job_arrival != 0)))
			{
				listofjob[runningtask].start_time = clock;	
				listofjob[runningtask].running = true;
			}
			if(listofjob[runningtask].remaining_time >= 0)
			{
				listofjob[runningtask].remaining_time--;
				readyQ[0].remaining_time--;
				if(listofjob[runningtask].remaining_time == 0)
				{
					listofjob[runningtask].finish_time = clock + 1;
					listofjob[runningtask].running = false;
					readyQ.erase(readyQ.begin());
					readytask--;
					std::sort(readyQ.begin(), readyQ.end(), compbylength);
					finished_task++;
					if((!readyQ.empty()) && clock >= readyQ[0].job_arrival)
					{
						for(int i = 0; i < counter; i++)
						{
							if(listofjob[i] == readyQ[0])
							{
								runningtask = i;
								break;
							}
						}
						if(listofjob[runningtask].job_arrival != 0)
						{
							listofjob[runningtask].start_time = clock+1;
						}	
						listofjob[runningtask].running = true;
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
	std::cout<< std::endl << "STCF: " << std::endl;
	for(int i = 0; i < counter; i++)
	{
		std::cout << "Job " << listofjob[i].job_id<< " ";
		std::cout << "starts at " << listofjob[i].start_time << " ";
		std::cout << "ends at " << listofjob[i].finish_time << " ";
		std::cout << ". Turnaround time =  " << listofjob[i].finish_time - listofjob[i].start_time << " ";
		std::cout << ". Response time =  " << listofjob[i].start_time - listofjob[i].job_arrival << std::endl;
	} 


	//RR
	//Reset values
	clock = 0;
	finished_task = 0;
	done = false;
	for(int i = 0; i < counter; i++)
	{
		listofjob[i].start_time = 0;
		listofjob[i].finish_time = 0;
		listofjob[i].remaining_time = listofjob[i].job_length;
		listofjob[i].running = false;
		listofjob[i].ready = false;
	}
 	//Reset n Initialize vector
 	std::vector<job> runningQ;
 	readyQ.clear();
 	int running_task = 0;
 	int readytasks = 0;
 	int runningtasks = 0;
	//Resort vector
	std::sort(listofjob.begin(), listofjob.end(), compbyarrival);
	while(done == false)
	{
		//Set to ready
		for(int i = 0; i < counter; i++)
		{
			if (listofjob[i].job_arrival == clock)
			{
				listofjob[i].ready = true;
				readyQ.push_back(listofjob[i]);
				readytasks++;
			}
		}
		
		//if readyQ has
		if(readytasks > 0)
		{
			//Get current task to run
			for(int i = 0; i < counter; i++)
			{
				if(listofjob[i] == readyQ[0])
				{
					running_task = i;
					break;
				}
			}
			//If nothing is on runningQ
			if(runningtasks == 0)
			{

				runningQ.push_back(readyQ[0]);
				runningtasks++;
				readyQ.erase(readyQ.begin());
				readyQ.shrink_to_fit();
				readytasks--;
			}
			//If there is something running
			else
			{
				//pop out of runningQ and put back to readyQ
				readyQ.push_back(runningQ[0]);
				readytasks++;
				runningQ.erase(runningQ.begin());
				runningQ.shrink_to_fit();
				runningtasks--;
				//Put new task to running Q
				runningQ.push_back(readyQ[0]);
				runningtasks++;
				readyQ.erase(readyQ.begin());
				readyQ.shrink_to_fit();
				readytasks--;
			}
		}
		//Run task
		if(runningtasks > 0)
		{
			if(runningQ[0].running == false && (runningQ[0].remaining_time == runningQ[0].job_length))
			{
				listofjob[running_task].start_time = clock;
				runningQ[0].start_time = clock;	
				runningQ[0].running = true;
			}
			if(runningQ[0].remaining_time >= 0)
			{
				runningQ[0].remaining_time--;
				if(runningQ[0].remaining_time == 0)
				{
					runningQ[0].finish_time = clock+1;
					listofjob[running_task].finish_time = clock+1;
					runningQ[0].running = false;
					runningQ.erase(runningQ.begin());
					runningQ.shrink_to_fit();
					runningtasks--;
					finished_task++;
				}
			}
		}
		//All tasks are done
		if(finished_task == counter)
		{
			done = true;
		}
		clock++;
	}
	std::cout<< std::endl << "RR: " << std::endl;
	for(int i = 0; i < counter; i++)
	{
		std::cout << "Job " << listofjob[i].job_id<< " ";
		std::cout << "starts at " << listofjob[i].start_time << " ";
		std::cout << "ends at " << listofjob[i].finish_time << " ";
		std::cout << ". Turnaround time =  " << listofjob[i].finish_time - listofjob[i].start_time << " ";
		std::cout << ". Response time =  " << listofjob[i].start_time - listofjob[i].job_arrival << std::endl;
	}
	return 0;
}
