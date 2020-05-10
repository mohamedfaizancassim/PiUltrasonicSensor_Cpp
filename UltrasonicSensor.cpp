#include "UltrasonicSensor.h"

std::chrono::_V2::system_clock::time_point  _echo_duration_end;
bool _isEchoed = false;

UltrasonicSensor::UltrasonicSensor(int trig_pin, int echo_pin, int timeout_ms)
{
	this->_trig_pin = trig_pin;
	this->_echo_pin = echo_pin;
	this->_timeout_ms = timeout_ms;

	
	//Set the pin modes
	gpioSetMode(this->_trig_pin, PI_OUTPUT);
	gpioSetMode(this->_echo_pin, PI_INPUT);
	
	//Set trig_pin low
	gpioWrite(this->_trig_pin, PI_LOW);
	
}

int UltrasonicSensor::Get_Distance_cm(int nSamples)
{
	vector<int> distances_list_cm;
	double temp_c = 33.5;
	for (int i = 0; i < nSamples; i++)
	{
		gpioWrite(this->_trig_pin, PI_HIGH);
		gpioDelay(10);
		gpioWrite(this->_trig_pin, PI_LOW);
		auto echoDuration_start = std::chrono::high_resolution_clock::now();

		while (gpioRead(this->_echo_pin) != PI_LOW)
		{
			//Wait for echo to come back;
		}
		auto echoDuration_end = std::chrono::high_resolution_clock::now();
		auto elapsed = echoDuration_end - echoDuration_start;
		auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

		int distance_cm =((1 / pow(10,4))*(331.3 + 0.606 * temp_c)*duration_us)/2;
		distances_list_cm.push_back(distance_cm);
	}
	int distance = *max_element(distances_list_cm.begin(), distances_list_cm.end());
	return (distance>0)? distance: -1;
}

int UltrasonicSensor::Get_Speed_cm_ms()
{
	auto time_speed_start= std::chrono::high_resolution_clock::now();
	int distance_start = this->Get_Distance_cm(5);
	gpioDelay(10);
	auto time_speed_end = std::chrono::high_resolution_clock::now();
	int distance_end = this->Get_Distance_cm(5);
	auto elapsed = time_speed_end - time_speed_start;
	auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

	int speed_cmus = (distance_start - distance_end) / duration_us;

	return speed_cmus;
}

void Echo_Signal_Recived(void)
{
	_echo_duration_end = std::chrono::high_resolution_clock::now();
	_isEchoed = true;
}
