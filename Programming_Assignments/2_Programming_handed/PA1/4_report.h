/* 
 * File name: report.h
 * Linked File: 3_appointment1.cpp
 * Creat Date: 2021.4.3
 * Created By: Guanshujie Fu
 * 
 * Mainly: this file contains  decalerations of functions
 *         used for reporting.
 * 
 */
#ifndef REPORT_H
#define REPORT_H

#include "3_appointment1.cpp"
#include <fstream>




/*
 * weekly_report
 * INPUT: queue<Appoint_People*> treated_q, queue<Appoint_People*> treating_q, queue<Appoint_People*> waiting_q
 * OUTPUT: None
 * 
 * This function will generate weekly report.
 * 
 */
void weekly_report(queue<Appoint_People*> &treated_q, queue<Appoint_People*> &treating_q, 
                   queue<Appoint_People*> &waiting_q, int day_offset, string filename, int sort);

void sort_name(Appoint_People **list, int num_people);
void sort_profession(Appoint_People **list, int num_people);
void sort_age(Appoint_People **list, int num_people);

/*
 * monthly_report
 * INPUT: queue<Appoint_People*> treated_q, queue<Appoint_People*> treating_q, queue<Appoint_People*> waiting_q
 * OUTPUT: None
 * 
 * This function will generate monthly report.
 * 
 */
void monthly_report(int regester_num, int withdraw_num, int fib_size, queue<Appoint_People*> &waiting_q, 
                    queue<Appoint_People*> &treating_q, queue<Appoint_People*> &treated_q, string filename);





#endif