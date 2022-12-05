#define _USE_MATH_DEFINES
#include "MyForm.h"
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace System;
using namespace System::Windows::Forms;
using namespace MySql::Data::MySqlClient;

//using namespace std;
[STAThreadAttribute]
void main(array<String^>^ args) { //��������� �����
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Project1::MyForm form;
	Application::Run(% form);
}

System::Void Project1::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e) //����� ����������� ��� ������� �� ������ '���������� ��������� ��������'
{
	
	setlocale(LC_ALL, "Russian");
	std::string lat = ConvertToString(textBox1->Text); //��������� ������
	if (lat.length() == 0)
	{
		MessageBox::Show("�� �� ����� ������!");
		return;
	}
	double lat_value = atof(lat.c_str());
	std::string lon = ConvertToString(textBox2->Text); //��������� �������
	if (lon.length() == 0)
	{
		MessageBox::Show("�� �� ����� �������!");
		return;
	}
	double lon_value = atof(lon.c_str());
	try
	{
		std::ifstream in("shops1.txt", std::ios::in);
	}
	catch (...)
	{
		MessageBox::Show("|||ERROR|||\n��� ������: 404\n��� ����� � ������� � ���������");
		return;
	}
	std::ifstream in("shops1.txt", std::ios::in); //��������� ���� � ������� � ���������
	std::string line;
	std::getline(in, line);
	Data data;
	std::vector<Data> shops;

	while (std::getline(in, line))  //��������� ������ � ��������� � ��������� ������
	{
		int ind = line.find(' ');
		data.card_id = atoi(line.substr(0, ind).c_str());
		line.erase(0, ind + 1);

		ind = line.find(' ');
		data.shop_id = atoi(line.substr(0, ind).c_str());
		line.erase(0, ind + 1);

		ind = line.find(' ');
		data.name = line.substr(0, ind);
		line.erase(0, ind + 1);

		ind = line.find(' ');
		data.address = line.substr(0, ind);
		line.erase(0, ind + 1);

		ind = line.find(' ');
		data.lat = atof(line.substr(0, ind).c_str());
		line.erase(0, ind + 1);

		ind = line.find(' ');
		data.lon = atof(line.substr(0, ind).c_str());
		line.erase(0, ind + 1);

		ind = line.find(' ');
		data.working_hour = line.substr(0, ind);
		line.erase(0, ind + 1);

		ind = line.find(' ');
		data.working_days = line.substr(0, ind);
		line.erase(0, ind + 1);

		ind = line.find(' ');
		data.floor = atoi(line.substr(0, ind).c_str());
		line.erase(0, ind + 1);

		shops.push_back(data);
	}

	double* distance = new double[shops.size()];
	int sizeDistance = shops.size();
	double d = 0;
	double min = 99999999;
	int min_id = -1;

	while (!shops.empty()) //������� �������� � ������� ����������� ����������
	{
		min = 999999999;
		min_id = -1;
		for (int i = 0; i < sizeDistance; i++)
		{
			distance[i] = 0;
		}
		for (int i = 0; i < shops.size(); i++)
		{
			//������� ��� ���������� ���������� ����� ����� ��������������� ������������
			d = acos(sin(lat_value * M_PI / 180) * sin(shops[i].lat * M_PI / 180) + cos(lat_value * M_PI / 180) * cos(shops[i].lat * M_PI / 180) * cos(lon_value * M_PI / 180 - shops[i].lon * M_PI / 180)) * 6372795;
			distance[i] = d;
			if (d < min)
			{
				min = d;
				min_id = i;
			}
		}
		//������� � listbox ��������
		listBox1->Items->Add(ConvertToString(shops[min_id].name + ". ���������� �� ��������: " + std::to_string(min) + " ������, �����: " + replaceSign(shops[min_id].address)));
		shops.erase(shops.begin() + min_id);
	}
	return System::Void();
}
//����� ��� �������������� string, ������� ������������ CLI, � ������� string
std::string Project1::ConvertToString(System::String^ s) 
{
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	std::string	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));

	return os;
}
//�� �� ����� ��� ������, ������ ��������
String^ Project1::ConvertToString(std::string& os)
{
	System::String^ s = gcnew System::String(os.c_str());

	return s;
}
//������ ���� & �� ������� � ������. ������ & ������������ ���� ��� ������������ ���� �� ������� �����
std::string Project1::replaceSign(std::string str)
{
	int sPos;
	while ((sPos = str.find("&", 0)) != std::string::npos)
		str.replace(sPos, 1, " ");
	return str;
}


