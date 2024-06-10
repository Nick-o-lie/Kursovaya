#pragma once

namespace Kursovaya {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ Diagram
	/// </summary>
	public ref class Diagram : public System::Windows::Forms::Form
	{
	public:
		Diagram(void)
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
		~Diagram()
		{
			if (components)
			{
				delete components;
			}
		}

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
			this->SuspendLayout();
			// 
			// Diagram
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(606, 261);
			this->MinimumSize = System::Drawing::Size(622, 300);
			this->Name = L"Diagram";
			this->Text = L"ƒиаграмма";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Diagram::Diagram_FormClosing);
			this->SizeChanged += gcnew System::EventHandler(this, &Diagram::Diagram_SizeChanged);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Diagram_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		e->Cancel = true;
		this->Hide();
	}
	private: System::Void Diagram_SizeChanged(System::Object^ sender, System::EventArgs^ e) {
		this->Refresh();
	}
	};
}
