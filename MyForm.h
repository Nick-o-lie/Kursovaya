#include "Magazin.h"
#include "Diagram.h"
#include <string>
#include <Windows.h>
#include <vcclr.h>
#include <msclr/marshal_cppstd.h>
#pragma once

namespace Kursovaya {

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
			//
			//TODO: добавьте код конструктора
			//
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
	private: System::Windows::Forms::Button^ saveButton;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::Button^ loadButton;
	private: System::Windows::Forms::TextBox^ searchField;


	private: System::Windows::Forms::ComboBox^ manufBox;
	private: System::Windows::Forms::TrackBar^ minPriceBar;
	private: System::Windows::Forms::TrackBar^ maxPriceBar;
	private: System::Windows::Forms::Label^ minPriceLabel;
	private: System::Windows::Forms::Label^ maxPriceLabel;
	private: System::Windows::Forms::Label^ fromPriceLabel;
	private: System::Windows::Forms::Label^ toPriceLabel;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Button^ diagramButton;
	private: System::Windows::Forms::Button^ resetButton;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
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
			this->saveButton = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->loadButton = (gcnew System::Windows::Forms::Button());
			this->searchField = (gcnew System::Windows::Forms::TextBox());
			this->manufBox = (gcnew System::Windows::Forms::ComboBox());
			this->minPriceBar = (gcnew System::Windows::Forms::TrackBar());
			this->maxPriceBar = (gcnew System::Windows::Forms::TrackBar());
			this->minPriceLabel = (gcnew System::Windows::Forms::Label());
			this->maxPriceLabel = (gcnew System::Windows::Forms::Label());
			this->fromPriceLabel = (gcnew System::Windows::Forms::Label());
			this->toPriceLabel = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->diagramButton = (gcnew System::Windows::Forms::Button());
			this->resetButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->minPriceBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->maxPriceBar))->BeginInit();
			this->SuspendLayout();
			// 
			// saveButton
			// 
			this->saveButton->Location = System::Drawing::Point(12, 12);
			this->saveButton->Name = L"saveButton";
			this->saveButton->Size = System::Drawing::Size(75, 23);
			this->saveButton->TabIndex = 0;
			this->saveButton->Text = L"Сохранить";
			this->saveButton->UseVisualStyleBackColor = true;
			this->saveButton->Click += gcnew System::EventHandler(this, &MyForm::saveButton_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(12, 105);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(692, 144);
			this->dataGridView1->TabIndex = 1;
			this->dataGridView1->CellEndEdit += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::dataGridView1_CellEndEdit);
			this->dataGridView1->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::dataGridView1_CellValueChanged);
			this->dataGridView1->DataError += gcnew System::Windows::Forms::DataGridViewDataErrorEventHandler(this, &MyForm::dataGridView1_DataError);
			this->dataGridView1->RowsAdded += gcnew System::Windows::Forms::DataGridViewRowsAddedEventHandler(this, &MyForm::dataGridView1_RowsAdded);
			this->dataGridView1->UserDeletingRow += gcnew System::Windows::Forms::DataGridViewRowCancelEventHandler(this, &MyForm::dataGridView1_UserDeletingRow);
			// 
			// loadButton
			// 
			this->loadButton->Location = System::Drawing::Point(93, 12);
			this->loadButton->Name = L"loadButton";
			this->loadButton->Size = System::Drawing::Size(75, 23);
			this->loadButton->TabIndex = 2;
			this->loadButton->Text = L"Загрузить";
			this->loadButton->UseVisualStyleBackColor = true;
			this->loadButton->Click += gcnew System::EventHandler(this, &MyForm::loadButton_Click);
			// 
			// searchField
			// 
			this->searchField->ForeColor = System::Drawing::SystemColors::GrayText;
			this->searchField->Location = System::Drawing::Point(191, 14);
			this->searchField->Name = L"searchField";
			this->searchField->Size = System::Drawing::Size(100, 20);
			this->searchField->TabIndex = 3;
			this->searchField->Text = L"название...";
			this->searchField->TextChanged += gcnew System::EventHandler(this, &MyForm::searchField_TextChanged);
			this->searchField->Enter += gcnew System::EventHandler(this, &MyForm::searchField_Enter);
			this->searchField->Leave += gcnew System::EventHandler(this, &MyForm::searchField_Leave);
			// 
			// manufBox
			// 
			this->manufBox->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::SuggestAppend;
			this->manufBox->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::ListItems;
			this->manufBox->FormattingEnabled = true;
			this->manufBox->Location = System::Drawing::Point(297, 14);
			this->manufBox->Name = L"manufBox";
			this->manufBox->Size = System::Drawing::Size(121, 21);
			this->manufBox->TabIndex = 5;
			this->manufBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::manufBox_SelectedIndexChanged);
			this->manufBox->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::manufBox_Validating);
			// 
			// minPriceBar
			// 
			this->minPriceBar->Location = System::Drawing::Point(424, 12);
			this->minPriceBar->Maximum = 0;
			this->minPriceBar->Name = L"minPriceBar";
			this->minPriceBar->Size = System::Drawing::Size(185, 45);
			this->minPriceBar->TabIndex = 6;
			this->minPriceBar->ValueChanged += gcnew System::EventHandler(this, &MyForm::minPriceBar_ValueChanged);
			// 
			// maxPriceBar
			// 
			this->maxPriceBar->Location = System::Drawing::Point(424, 54);
			this->maxPriceBar->Maximum = 0;
			this->maxPriceBar->Name = L"maxPriceBar";
			this->maxPriceBar->Size = System::Drawing::Size(185, 45);
			this->maxPriceBar->TabIndex = 7;
			this->maxPriceBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->maxPriceBar->ValueChanged += gcnew System::EventHandler(this, &MyForm::maxPriceBar_ValueChanged);
			// 
			// minPriceLabel
			// 
			this->minPriceLabel->Location = System::Drawing::Point(387, 41);
			this->minPriceLabel->Name = L"minPriceLabel";
			this->minPriceLabel->Size = System::Drawing::Size(100, 13);
			this->minPriceLabel->TabIndex = 8;
			this->minPriceLabel->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// maxPriceLabel
			// 
			this->maxPriceLabel->Location = System::Drawing::Point(546, 41);
			this->maxPriceLabel->Name = L"maxPriceLabel";
			this->maxPriceLabel->Size = System::Drawing::Size(100, 13);
			this->maxPriceLabel->TabIndex = 9;
			this->maxPriceLabel->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// fromPriceLabel
			// 
			this->fromPriceLabel->AutoSize = true;
			this->fromPriceLabel->Location = System::Drawing::Point(635, 17);
			this->fromPriceLabel->Name = L"fromPriceLabel";
			this->fromPriceLabel->Size = System::Drawing::Size(0, 13);
			this->fromPriceLabel->TabIndex = 10;
			// 
			// toPriceLabel
			// 
			this->toPriceLabel->AutoSize = true;
			this->toPriceLabel->Location = System::Drawing::Point(635, 66);
			this->toPriceLabel->Name = L"toPriceLabel";
			this->toPriceLabel->Size = System::Drawing::Size(0, 13);
			this->toPriceLabel->TabIndex = 11;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(297, 65);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(105, 17);
			this->checkBox1->TabIndex = 12;
			this->checkBox1->Text = L"закончившиеся";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox1_CheckedChanged);
			// 
			// diagramButton
			// 
			this->diagramButton->Location = System::Drawing::Point(93, 61);
			this->diagramButton->Name = L"diagramButton";
			this->diagramButton->Size = System::Drawing::Size(75, 23);
			this->diagramButton->TabIndex = 13;
			this->diagramButton->Text = L"Диаграмма";
			this->diagramButton->UseVisualStyleBackColor = true;
			this->diagramButton->Click += gcnew System::EventHandler(this, &MyForm::diagramButton_Click);
			// 
			// resetButton
			// 
			this->resetButton->Location = System::Drawing::Point(191, 61);
			this->resetButton->Name = L"resetButton";
			this->resetButton->Size = System::Drawing::Size(100, 23);
			this->resetButton->TabIndex = 14;
			this->resetButton->Text = L"Сброс фильтров";
			this->resetButton->UseVisualStyleBackColor = true;
			this->resetButton->Click += gcnew System::EventHandler(this, &MyForm::resetButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(611, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(23, 13);
			this->label1->TabIndex = 15;
			this->label1->Text = L"От:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(611, 66);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(25, 13);
			this->label2->TabIndex = 16;
			this->label2->Text = L"До:";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(716, 261);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->resetButton);
			this->Controls->Add(this->diagramButton);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->toPriceLabel);
			this->Controls->Add(this->fromPriceLabel);
			this->Controls->Add(this->maxPriceLabel);
			this->Controls->Add(this->minPriceLabel);
			this->Controls->Add(this->maxPriceBar);
			this->Controls->Add(this->minPriceBar);
			this->Controls->Add(this->manufBox);
			this->Controls->Add(this->searchField);
			this->Controls->Add(this->loadButton);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->saveButton);
			this->MinimumSize = System::Drawing::Size(732, 300);
			this->Name = L"MyForm";
			this->Text = L"Ноутбуки";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->minPriceBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->maxPriceBar))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		Magazin* thisMagazin;
		DataTable^ table;
		float minPrice = 0.0f, maxPrice = 0.0f;
		float fromPrice = 0.0f, toPrice = 0.0f;
		bool onlyOut = false;
		bool skipHandler = false;
		bool deletingRow = false;
		System::ComponentModel::BindingList<String^>^ manufList;
		Diagram^ diagram;
		String^ header = "Процентное соотношение ноутбуков в наличии по типу матрицы";
		int stock, numsCombined, maxNum;
		array<String^>^ matrixTypes;
		array<int>^ matrixTypeNum;
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Show_Data();
	private: System::Void Add_Row(Magazin::laptop* laptop);
	private: System::Void CreateManufList();
	private: System::Void ManufRemoved(std::string &manuf);
	private: System::Void NewPriceAdded(float price);
	private: System::Void PriceRemoved(float price);
	private: System::Void SetPriceLimits();
	private: System::Void ReadOnlyCheck();
	private: System::Void DrawDiagram(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
	
	private: System::Void saveButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void dataGridView1_RowsAdded(System::Object^ sender, System::Windows::Forms::DataGridViewRowsAddedEventArgs^ e);
	private: System::Void dataGridView1_CellValueChanged(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
	private: System::Void loadButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void searchField_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void manufBox_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);
	private: System::Void manufBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void minPriceBar_ValueChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void maxPriceBar_ValueChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void dataGridView1_UserDeletingRow(System::Object^ sender, System::Windows::Forms::DataGridViewRowCancelEventArgs^ e);
	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void dataGridView1_CellEndEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
	private: System::Void diagramButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void resetButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void searchField_Enter(System::Object^ sender, System::EventArgs^ e);
	private: System::Void searchField_Leave(System::Object^ sender, System::EventArgs^ e);
	private: System::Void dataGridView1_DataError(System::Object^ sender, System::Windows::Forms::DataGridViewDataErrorEventArgs^ e);
};
}