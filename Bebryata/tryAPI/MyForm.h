#pragma once

#include <boost/beast.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>

namespace ConsoleApplication1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// —водка дл€ MyForm
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
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ CheckLocation;


	protected:

	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->CheckLocation = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// CheckLocation
			// 
			this->CheckLocation->Location = System::Drawing::Point(35, 80);
			this->CheckLocation->Name = L"CheckLocation";
			this->CheckLocation->Size = System::Drawing::Size(129, 74);
			this->CheckLocation->TabIndex = 0;
			this->CheckLocation->Text = L"Check Location";
			this->CheckLocation->UseVisualStyleBackColor = true;
			this->CheckLocation->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(856, 513);
			this->Controls->Add(this->CheckLocation);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
	};

	std::string ConvertToString(System::String^ s);		
	String^ ConvertToString(std::string& os);

	const static std::string MAIN_API = "https://geocode-maps.yandex.ru";
	const static std::string API_ARGUMENTS = "/1.x/?apikey=061d76ef-ebbb-43d7-a84f-2f21aa5366c9&geocode=";
	namespace http = boost::beast::http;
	//класс дл€ API запроса
	class Client 
	{
	public:
		std::string getResponse(std::string ip)
		{

			std::string geo = ip;
			//https://geocode-maps.yandex.ru/1.x/?apikey=ваш API-ключ&geocode=37.611347,55.760241

			boost::asio::io_context io;
			boost::asio::ip::tcp::resolver resolver(io);
			boost::asio::ip::tcp::socket socket(io);

			boost::asio::connect(socket, resolver.resolve(MAIN_API, "80"));

			geo = API_ARGUMENTS + geo;
			http::request<http::string_body> req(http::verb::get, geo, 11);

			req.set(http::field::host, MAIN_API);
			req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

			http::write(socket, req);
			std::string response;
			{
				boost::beast::flat_buffer buffer;
				http::response<http::dynamic_body> res;
				http::read(socket, buffer, res);
				response = boost::beast::buffers_to_string(res.body().data());
			}

			socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
			return response;
		}
	};
}
