#include "MyForm.h"

System::Void Kursovaya::MyForm::MyForm_Load(System::Object^ sender, System::EventArgs^ e)
{
    diagram = gcnew Diagram();
	thisMagazin = new Magazin;
    table = gcnew DataTable();
    table->Columns->Add(gcnew DataColumn("Наименование", String::typeid));
    table->Columns->Add(gcnew DataColumn("Бренд", String::typeid));
    table->Columns->Add(gcnew DataColumn("Тип", String::typeid));
    table->Columns->Add(gcnew DataColumn("Диагональ экрана", String::typeid));
    table->Columns->Add(gcnew DataColumn("Разрешение экрана", String::typeid));
    table->Columns->Add(gcnew DataColumn("Тип матрицы", String::typeid));
    table->Columns->Add(gcnew DataColumn("Дополнительные особенности", String::typeid));
    table->Columns->Add(gcnew DataColumn("Цена", Single::typeid));
    table->Columns->Add(gcnew DataColumn("Количество в наличии", Int32::typeid));
    dataGridView1->DataSource = table;
    dataGridView1->Columns["Цена"]->DefaultCellStyle->Format = "C";
    minPriceLabel->Text = minPrice.ToString("C");
    maxPriceLabel->Text = maxPrice.ToString("C");
    fromPriceLabel->Text = fromPrice.ToString("C");
    toPriceLabel->Text = toPrice.ToString("C");
    for (int i = 0; i < dataGridView1->ColumnCount; i++)
    {
        dataGridView1->Columns[i]->SortMode = DataGridViewColumnSortMode::NotSortable;
    }
    manufList = gcnew System::ComponentModel::BindingList<String^>();
    manufList->Add("(выберите производителя)");
    manufBox->DataSource = manufList;
    diagram->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::DrawDiagram);
}

System::Void Kursovaya::MyForm::Add_Row(Magazin::laptop* laptop)
{
    DataRow^ row; 
    row = table->NewRow();
    row[0] = gcnew String(laptop->name.c_str());
    row[1] = gcnew String(laptop->brand.c_str());
    row[2] = gcnew String(laptop->type.c_str());
    if (laptop->screenSize >= 12)
        row[3] = floor(laptop->screenSize / 12) + "'" + (laptop->screenSize - 12 * floor(laptop->screenSize / 12)).ToString("##.##") + "\"";
    else
        row[3] = laptop->screenSize + "\"";
    row[4] = laptop->resolution->width + "x" + laptop->resolution->height;
    row[5] = gcnew String(laptop->matrixType.c_str());
    row[6] = gcnew String(laptop->additional.c_str());
    row[7] = laptop->price;
    row[8] = laptop->stock;
    table->Rows->Add(row);
}

System::Void Kursovaya::MyForm::CreateManufList()
{
    while (manufList->Count > 1)
    {
        manufList->RemoveAt(1);
    }
    Magazin::laptop* current = thisMagazin->GetHead();
    while (current)
    {
        if (!manufList->Contains(gcnew String(current->brand.c_str())))
        {
            manufList->Add(gcnew String(current->brand.c_str()));
        }
        current = current->next;
    }
}

System::Void Kursovaya::MyForm::ManufRemoved(std::string &manuf)
{
    if (manuf.empty())
        return;
    if (!thisMagazin->Contains(1, manuf.c_str()))
    {
        manufList->Remove(gcnew String(manuf.c_str()));
    }
}

System::Void Kursovaya::MyForm::NewPriceAdded(float price)
{
    if (price > maxPrice)
    {
        maxPrice = price;
        minPriceBar->Maximum = price;
        maxPriceBar->Maximum = price;
        maxPriceLabel->Text = price.ToString("C");
        maxPriceBar->Value = price;
        if (minPrice == 0.0f && !(thisMagazin->MinPrice() == 0.0f))
        {
            minPrice = price;
            minPriceBar->Value = price;
            minPriceBar->Minimum = price;
            maxPriceBar->Minimum = price;
            minPriceLabel->Text = price.ToString("C");
            this->ReadOnlyCheck();
        }
    }
    else if (price < minPrice)
    {
        minPrice = price;
        minPriceBar->Minimum = price;
        maxPriceBar->Minimum = price;
        minPriceLabel->Text = price.ToString("C");
        minPriceBar->Value = price;
    }
}

System::Void Kursovaya::MyForm::PriceRemoved(float price)
{
    if (price == minPrice)
    {
        minPrice = thisMagazin->MinPrice();
        if (minPrice > minPriceBar->Minimum)
        {
            minPriceBar->Value = minPrice;
            minPriceBar->Minimum = minPrice;
        }
        else
        {
            minPriceBar->Minimum = minPrice;
            minPriceBar->Value = minPrice;
        }
        maxPriceBar->Minimum = minPrice;
        minPriceLabel->Text = minPrice.ToString("C");
        this->ReadOnlyCheck();
    }
    if (price == maxPrice)
    {
        maxPrice = thisMagazin->MaxPrice();
        minPriceBar->Maximum = maxPrice;
        maxPriceBar->Value = maxPrice;
        maxPriceBar->Maximum = maxPrice;
        maxPriceLabel->Text = maxPrice.ToString("C");
        this->ReadOnlyCheck();
    }
}

System::Void Kursovaya::MyForm::SetPriceLimits()
{
    minPrice = thisMagazin->MinPrice();
    minPriceBar->Minimum = minPrice;
    maxPriceBar->Minimum = minPrice;
    minPriceLabel->Text = minPrice.ToString("C");
    minPriceBar->Value = minPrice;
    maxPrice = thisMagazin->MaxPrice();
    minPriceBar->Maximum = maxPrice;
    maxPriceBar->Maximum = maxPrice;
    maxPriceLabel->Text = maxPrice.ToString("C");
    maxPriceBar->Value = maxPrice;
}

System::Void Kursovaya::MyForm::Show_Data()
{
    table->Clear();
    Magazin::laptop* currentLaptop = thisMagazin->GetHead();
    std::string name = msclr::interop::marshal_as<std::string>(searchField->Text);
    if (name == "название...")
        name = NullStr;
    std::string brand;
    if (manufBox->SelectedIndex == 0)
        brand = NullStr;
    else
        brand = msclr::interop::marshal_as<std::string>(manufBox->SelectedValue->ToString());
    while (currentLaptop)
    {
        if (currentLaptop->fitsCriteria(name, brand, fromPrice, toPrice, onlyOut))
            Add_Row(currentLaptop);
        
        currentLaptop = currentLaptop->next;
    }
}

System::Void Kursovaya::MyForm::ReadOnlyCheck()
{
    if ((searchField->Text == "" || searchField->Text == "название...") && manufBox->SelectedIndex == 0 && minPriceBar->Value == minPriceBar->Minimum && maxPriceBar->Value == maxPriceBar->Maximum && !onlyOut)
    {
        dataGridView1->ReadOnly = false;
        dataGridView1->AllowUserToDeleteRows = true;
        resetButton->Visible = false;
        saveButton->Enabled = true;
    }
    else
    {
        dataGridView1->ReadOnly = true;
        dataGridView1->AllowUserToDeleteRows = false;
        resetButton->Visible = true;
        saveButton->Enabled = false;
    }

}

System::Void Kursovaya::MyForm::saveButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog;
    
    if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
        pin_ptr<const wchar_t> fileName = PtrToStringChars(saveFileDialog->FileName);
        if (thisMagazin->Save((const wchar_t*) fileName) == 0)
            MessageBox::Show("Список успешно сохранён");
        else
            MessageBox::Show("Произошла ошибка");
    }
}

System::Void Kursovaya::MyForm::loadButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    this->resetButton->PerformClick();

    OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();

    if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
        pin_ptr<const wchar_t> fileName = PtrToStringChars(openFileDialog->FileName);
        if (thisMagazin->Load((const wchar_t*)fileName) == 0)
        {
            this->Show_Data();
            this->CreateManufList();
            this->SetPriceLimits();
            MessageBox::Show("Список успешно загружен");
        }
        else
            MessageBox::Show("Произошла ошибка");
    }

}

System::Void Kursovaya::MyForm::dataGridView1_RowsAdded(System::Object^ sender, System::Windows::Forms::DataGridViewRowsAddedEventArgs^ e)
{
    if (e->RowIndex > thisMagazin->Length())
    {
        thisMagazin->AddElement(new Magazin::laptop());
        deletingRow = true;
        this->NewPriceAdded(0.0f);
        deletingRow = false;
    }
}

System::Void Kursovaya::MyForm::dataGridView1_UserDeletingRow(System::Object^ sender, System::Windows::Forms::DataGridViewRowCancelEventArgs^ e)
{
        std::string oldManuf = thisMagazin->GetElement_Str(e->Row->Index, 1);
        float oldPrice = thisMagazin->GetElement_Flt(e->Row->Index, 7);
        thisMagazin->RemoveElement(e->Row->Index);
        this->ManufRemoved(oldManuf);
        deletingRow = true;
        this->PriceRemoved(oldPrice);
        deletingRow = false;
}

System::Void Kursovaya::MyForm::dataGridView1_CellValueChanged(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
{
    if (skipHandler)
    {
        skipHandler = false;
        return;
    }
    else
    {
        String^ input = dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value->ToString();
        IntPtr ptrToNativeString;
        char* value;
        int IValue1 = 0, IValue2 = 0;
        float inches = 0, FValue = 0, multiplier = 1;
        bool decimals = false, everythingAlright = false, changeFirstValue = true;
        std::string oldManuf;
        float oldPrice;
        switch (e->ColumnIndex)
        {
        case 0:
            ptrToNativeString = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(input);
            value = static_cast<char*>(ptrToNativeString.ToPointer());
            thisMagazin->EditElement(e->RowIndex, e->ColumnIndex, value);
            break;
        case 1:
            ptrToNativeString = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(input);
            value = static_cast<char*>(ptrToNativeString.ToPointer());
            oldManuf = thisMagazin->GetElement_Str(e->RowIndex, e->ColumnIndex);
            thisMagazin->EditElement(e->RowIndex, e->ColumnIndex, value);
            if (!manufList->Contains(input) && input != "")
            {
                manufList->Add(input);
            }
            this->ManufRemoved(oldManuf);
            break;
        case 2:
            ptrToNativeString = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(input);
            value = static_cast<char*>(ptrToNativeString.ToPointer());
            thisMagazin->EditElement(e->RowIndex, e->ColumnIndex, value);
            break;
        case 3:
            for (int i = 0; i < input->Length; i++)
            {
                if (decimals)
                    multiplier /= 10;
                if (input[i] == '\'')
                {
                    inches = FValue * 12;
                    FValue = 0;
                }
                else if (input[i] == '"')
                {
                    inches += FValue;
                    everythingAlright = true;
                }
                else if (input[i] == '.' || input[i] == ',')
                    decimals = true;
                else if (input[i] >= '0' && input[i] <= '9')
                    if (!decimals)
                        FValue = FValue * 10 + (input[i] - '0');
                    else
                        FValue += multiplier * (input[i] - '0');
                else
                {
                    everythingAlright = false;
                    break;
                }
            }
            if (everythingAlright)
                thisMagazin->EditElement(e->RowIndex, e->ColumnIndex, inches);
            else
            {
                skipHandler = true;
                dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value = "";
            }
            break;
        case 4:
            for (int i = 0; i < input->Length; i++)
            {
                if (input[i] == 'x')
                {
                    changeFirstValue = false;
                    everythingAlright = true;
                }
                else if (input[i] >= '0' && input[i] <= '9')
                    if (changeFirstValue)
                        IValue1 = IValue1 * 10 + (input[i] - '0');
                    else
                        IValue2 = IValue2 * 10 + (input[i] - '0');
                else
                {
                    everythingAlright = false;
                    break;
                }
            }
            if (everythingAlright)
                thisMagazin->EditElement(e->RowIndex, e->ColumnIndex, new struct Magazin::laptop::resolution(IValue1, IValue2));
            else
            {
                skipHandler = true;
                dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value = "";
            }
            break;
        case 5:
            ptrToNativeString = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(input);
            value = static_cast<char*>(ptrToNativeString.ToPointer());
            thisMagazin->EditElement(e->RowIndex, e->ColumnIndex, value);
            break;
        case 6:
            ptrToNativeString = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(input);
            value = static_cast<char*>(ptrToNativeString.ToPointer());
            thisMagazin->EditElement(e->RowIndex, e->ColumnIndex, value);
            break;
        case 7:
            everythingAlright = true;
            for (int i = 0; i < input->Length; i++)
            {
                if (decimals)
                    multiplier /= 10;
                if (input[i] == '.' || input[i] == ',')
                    decimals = true;
                else if (input[i] >= '0' && input[i] <= '9')
                    if (!decimals)
                        FValue = FValue * 10 + (input[i] - '0');
                    else
                        FValue += multiplier * (input[i] - '0');
                else
                {
                    everythingAlright = false;
                    break;
                }
            }
            if (!everythingAlright)
            {
                FValue = 0.0f;
                skipHandler = true;
                dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value = 0;
            }
            oldPrice = thisMagazin->GetElement_Flt(e->RowIndex, e->ColumnIndex);
            this->NewPriceAdded(FValue);
            thisMagazin->EditElement(e->RowIndex, e->ColumnIndex, FValue);
            this->Show_Data();
            this->PriceRemoved(oldPrice);
            break;
        case 8:
            everythingAlright = true;
            for (int i = 0; i < input->Length; i++)
            {
                if (input[i] >= '0' && input[i] <= '9')
                    IValue1 = IValue1 * 10 + (input[i] - '0');
                else
                {
                    everythingAlright = false;
                    break;
                }
            }
            if (everythingAlright)
                thisMagazin->EditElement(e->RowIndex, e->ColumnIndex, IValue1);
            else
            {
                skipHandler = true;
                dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value = 0;
                thisMagazin->EditElement(e->RowIndex, e->ColumnIndex, 0);
            }
            break;
        }
    }
}

System::Void Kursovaya::MyForm::searchField_Enter(System::Object^ sender, System::EventArgs^ e)
{
    if (searchField->Text == "название...")
    {
        searchField->Text = "";
        searchField->ForeColor = SystemColors::ActiveCaptionText;
    }
}

System::Void Kursovaya::MyForm::searchField_Leave(System::Object^ sender, System::EventArgs^ e)
{
    if (searchField->Text == "")
    {
        searchField->Text = "название...";
        searchField->ForeColor = SystemColors::GrayText;
    }
}

System::Void Kursovaya::MyForm::searchField_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
    this->ReadOnlyCheck();
    this->Show_Data();
}

System::Void Kursovaya::MyForm::manufBox_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
{
    if (manufBox->SelectedValue == nullptr)
    {
        manufBox->SelectedIndex = 0;
    }
}

System::Void Kursovaya::MyForm::manufBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
    this->ReadOnlyCheck();
    this->Show_Data();
}

System::Void Kursovaya::MyForm::minPriceBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    if (minPriceBar->Value > maxPriceBar->Value)
        minPriceBar->Value = maxPriceBar->Value;
    else
    {
        fromPrice = static_cast<float>(minPriceBar->Value);
        fromPriceLabel->Text = fromPrice.ToString("C");
        if (!deletingRow)
        {
            this->ReadOnlyCheck();
            this->Show_Data();
        }
    }
}

System::Void Kursovaya::MyForm::maxPriceBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    if (maxPriceBar->Value < minPriceBar->Value)
        maxPriceBar->Value = minPriceBar->Value;
    else
    {
        toPrice = static_cast<float>(maxPriceBar->Value);
        toPriceLabel->Text = toPrice.ToString("C");
        if (!deletingRow)
        {
            this->ReadOnlyCheck();
            this->Show_Data();
        }
    }
}

System::Void Kursovaya::MyForm::checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
    onlyOut = checkBox1->Checked;
    this->ReadOnlyCheck();
    this->Show_Data();
}

System::Void Kursovaya::MyForm::dataGridView1_CellEndEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
{
    if (e->ColumnIndex == 7)
        if (dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value == DBNull::Value)
            NewPriceAdded(0.0f);
}

System::Void Kursovaya::MyForm::diagramButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    stock = thisMagazin->InStock();
    delete matrixTypes;
    delete matrixTypeNum;
    matrixTypes = gcnew array<String^>(stock);
    matrixTypeNum = gcnew array<int>(stock);
    Magazin::laptop* current = thisMagazin->GetHead();
    int i = 0;
    while (current)
    {
        if (current->stock > 0)
        {
            String^ newType = gcnew String(current->matrixType.c_str());
            if (newType == "")
                newType = "(не указано)";
            bool alreadyHas = false;
            for (int j = 0; j < i; j++)
            {
                if (matrixTypes[j] == newType)
                {
                    alreadyHas = true;
                    matrixTypeNum[j] += current->stock;
                }
            }
            if (!alreadyHas)
            {
                matrixTypes[i] = newType;
                matrixTypeNum[i] = current->stock;
                i++;
            }
            else
                stock--;
        }
        current = current->next;
    }

    numsCombined = 0;
    maxNum = 0;
    for (int i = 0; i < stock; i++)
    {
        numsCombined += matrixTypeNum[i];
        if (matrixTypeNum[i] > maxNum)
            maxNum = matrixTypeNum[i];
    }
    diagram->ShowDialog();
}

System::Void Kursovaya::MyForm::DrawDiagram(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
{
    System::Drawing::Graphics^ graphics = e->Graphics;
    System::Drawing::Font^ hFont = gcnew System::Drawing::Font("Tahoma", 12);
    int w = (int)graphics->MeasureString(header, hFont).Width;
    int x = (diagram->ClientSize.Width - w) / 2;
    graphics->DrawString(header, hFont, Brushes::Black, x, 10);

    int x0 = 30;
    int y0 = diagram->ClientSize.Height - 30;

    int maxHeight = diagram->ClientSize.Height - 30 - 50;
    int maxWidth = diagram->ClientSize.Width - 30 - 30;
    int width = maxWidth / (stock + stock - 1);
    int height;

    System::Drawing::Brush^ fBrush;
    System::Drawing::Font^ lFont = gcnew System::Drawing::Font("Tahoma", 9);
    StringFormat^ legendFormat = gcnew StringFormat;
    legendFormat->LineAlignment = StringAlignment::Center;
    legendFormat->Alignment = StringAlignment::Center;

    for (int i = 0; i < stock; i++)
    {
        height = matrixTypeNum[i] * maxHeight / maxNum;
        switch (i % 9)
        {
        case 0: fBrush = Brushes::Gold; break;
        case 1: fBrush = Brushes::Silver; break;
        case 2: fBrush = Brushes::DarkGoldenrod; break;
        case 3: fBrush = Brushes::Azure; break;
        case 4: fBrush = Brushes::OrangeRed; break;
        case 5: fBrush = Brushes::RoyalBlue; break;
        case 6: fBrush = Brushes::SteelBlue; break;
        case 7: fBrush = Brushes::Chocolate; break;
        case 8: fBrush = Brushes::LightGray; break;
        }
        graphics->FillRectangle(fBrush, x0, y0 - height, width, height);

        graphics->DrawString(matrixTypes[i], lFont, Brushes::Black, x0 + width / 2, y0 + 8, legendFormat);
        graphics->DrawString((static_cast<float>(matrixTypeNum[i]) / numsCombined).ToString("P"), lFont, Brushes::Black, x0 + width / 2, y0 - height - 10, legendFormat);

        x0 += width * 2;
    }
}

System::Void Kursovaya::MyForm::resetButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    searchField->Text = "название...";
    searchField->ForeColor = SystemColors::GrayText;
    manufBox->SelectedIndex = 0;
    minPriceBar->Value = minPriceBar->Minimum;
    maxPriceBar->Value = maxPriceBar->Maximum;
    checkBox1->Checked = false;
}

System::Void Kursovaya::MyForm::dataGridView1_DataError(System::Object^ sender, System::Windows::Forms::DataGridViewDataErrorEventArgs^ e)
{
    MessageBox::Show("Были введены некорректные данные", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
}