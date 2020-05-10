#pragma once
#include<pigpio.h>
#include <chrono>
#include<stdio.h>
#include<iostream>
#include<vector>
#include <algorithm>
#include <math.h>
using namespace std;



void Echo_Signal_Recived(void);
class UltrasonicSensor
{
private:
	int _trig_pin = 0;
	int _echo_pin = 0;
	int _timeout_ms = 0;
public:
	UltrasonicSensor(int trig_pin, int echo_pin, int timeout_ms);
	int Get_Distance_cm(int nSamples);
	int Get_Speed_cm_ms();

};

