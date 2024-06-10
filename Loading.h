#include "MyForm.h"
#include <chrono>
#include <thread>
#pragma once

namespace Kursovaya {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ Loading
	/// </summary>
	public ref class Loading : public System::Windows::Forms::Form
	{
	public:
		Loading(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~Loading()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
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
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(715, 151);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// Loading
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(715, 151);
			this->Controls->Add(this->pictureBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Loading";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Loading";
			this->Load += gcnew System::EventHandler(this, &Loading::Loading_Load);
			this->Shown += gcnew System::EventHandler(this, &Loading::Loading_Shown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
		MyForm^ MainForm;
		Timer clock;
	private: System::Void Loading_Shown(System::Object^ sender, System::EventArgs^ e) {
		MainForm = gcnew MyForm();
		MainForm->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Kursovaya::Loading::OnFormClosed);
		clock.Interval = 3000;
		clock.Tick += gcnew EventHandler(this, &Kursovaya::Loading::OpenProgram);
		clock.Start();
	}
	void OnFormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e)
	{
		this->Close();
	}
	void OpenProgram(System::Object^ sender, System::EventArgs^ e)
	{
		MainForm->Show();
		this->Hide();
		clock.Stop();
	}
	private: System::Void Loading_Load(System::Object^ sender, System::EventArgs^ e) {
		pictureBox1->Image = Image::FromFile(Application::StartupPath + "\\laptop.png");
	}
	};
}
