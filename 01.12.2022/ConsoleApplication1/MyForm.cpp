#include "pch.h"
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void createForm(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// ProjectName - name of your project
	// NameForm - name of the form to run
	ConsoleApplication1::MyForm form;
	Application::Run(% form);
}

System::Void ConsoleApplication1::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("Smells like bebra", "Bebra");
	return System::Void();
}
