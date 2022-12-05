#include "pch.h"
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void createForm(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	ConsoleApplication1::MyForm form;
	Application::Run(% form);
}

System::Void ConsoleApplication1::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	//MessageBox::Show("Smells like bebra", "Bebra");
	Client client;
	std::string position = "54.848064,83.092304";
	std::string resjson;
	//resjson = ;
	MessageBox::Show(ConvertToString(client.getResponse(position)), "BEBRA");
	return System::Void();
}

std::string ConsoleApplication1::ConvertToString(System::String^ s)
{
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	std::string	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));

	return os;
}

String^ ConsoleApplication1::ConvertToString(std::string& os)
{
	System::String^ s = gcnew System::String(os.c_str());

	return s;
}
