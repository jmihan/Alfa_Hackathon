#pragma once
#include <string>
namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}
		
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ textBox2;
	protected:
	
	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(495, 167);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(220, 103);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Определить ближайшие магазины";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(450, 126);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(137, 20);
			this->textBox1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(512, 25);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(176, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Введите координаты в формате: ";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(544, 59);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(112, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"54,848064 83,092304";
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(87, 306);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(1121, 225);
			this->listBox1->TabIndex = 4;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(296, 94);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(613, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"(Не обязательно именно столько знаков после запятой, важно, что должна быть запят"
				L"ая отделяющая дробную часть)";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(370, 129);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(48, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Широта:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(658, 129);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(53, 13);
			this->label5->TabIndex = 8;
			this->label5->Text = L"Долгота:";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(738, 126);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(137, 20);
			this->textBox2->TabIndex = 7;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1327, 542);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);

	};
	class Data
	{
	public:
		int card_id;
		int shop_id;
		std::string name;
		std::string address;
		double lon; //longitude
		double lat; //latitude
		std::string working_hour;
		std::string working_days;
		int floor;
	};
	std::string ConvertToString(System::String^ s);
	String^ ConvertToString(std::string& os);
	std::string replaceSign(std::string str);
}
