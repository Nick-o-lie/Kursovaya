#include "Magazin.h"

Magazin::Magazin() {
	first = new Magazin::laptop;
	first = NULL;
}

Magazin::laptop* Magazin::GetHead()
{
    return this->first;
}

int Magazin::Length() 
{
    int number = 0;
    laptop* current = first;
    while (current)
    {
        current = current->next;
        number++;
    }
    return number;
}

int Magazin::InStock()
{
    int number = 0;
    laptop* current = first;
    while (current)
    {
        if (current->stock > 0)
            number++;
        current = current->next;
    }
    return number;
}

void Magazin::AddElement(laptop* laptop)
{
    struct laptop* current = first;
    if (current)
    {
        while (current->next)
        {
            current = current->next;
        }
        current->next = laptop;
    }
    else
        first = laptop;
}

void Magazin::FormatOutput(std::string &toFormat)
{
    if (toFormat[0] == '\0')
    {
        toFormat = "\"\"";
    }
    else
    {
        toFormat.insert(0, 1, '"');
        int i = 0;
        while (toFormat[++i] != '\0')
        {
            if (toFormat[i] == '"')
            {
                toFormat.insert(i++, 1, '"');
            }
        }
        toFormat.insert(i, 1, '"');
    }
}

int Magazin::Save(const wchar_t* fileName)
{
    std::ofstream file(fileName); // Открываем файл
    if (file.is_open()) // Проверка на то, что файл открылся
    {
        laptop* current = first;
        std::string output;
        while (current)
        { // Записываем по ноутбуку за раз, разделяя запятыми и пропусками строк
            output = current->name;
            FormatOutput(output);
            file << output << ',';
            output = current->brand;
            FormatOutput(output);
            file << output << ',';
            output = current->type;
            FormatOutput(output);
            file << output << ',';
            file << current->screenSize << ','
                << current->resolution->width << ','
                << current->resolution->height << ',';
            output = current->matrixType;
            FormatOutput(output);
            file << output << ',';
            output = current->additional;
            FormatOutput(output);
            file << output << ',';
            file << current->price << ','
                << current->stock << ",\n";
            current = current->next;
        }
        // Сообщение об успешном вводе
        return 0;
    }
    else return 1;
}

int Magazin::Load(const wchar_t* fileName)
{
    std::ifstream file(fileName);
    if (file.is_open())
    {
        this->Clear();
        laptop* newElement;
        char ch;
        bool inQuotes = false, firstCharacter = true, lastWasQuote = false;
        while (file.get(ch))
        {
            newElement = new laptop();
            firstCharacter = true;
            for (int i = 0; i < 3; i++)
            {
                while (ch != ',' || inQuotes)
                {
                    if (ch == '"')
                    {
                        if (firstCharacter)
                        {
                            inQuotes = true;
                        }
                        else if (inQuotes)
                        {
                            if (lastWasQuote)
                            {
                                newElement->field(i) += ch;
                                lastWasQuote = false;
                            }
                            else
                            {
                                lastWasQuote = true;
                            }
                        }
                        else
                        {
                            newElement->field(i) += ch;
                        }
                        file.get(ch);
                    }
                    else if (ch == ',' && lastWasQuote)
                    {
                        inQuotes = false;
                        lastWasQuote = false;
                    }
                    else
                    {
                        newElement->field(i) += ch;
                        file.get(ch);
                    }
                    firstCharacter = false;
                }
                if (i < 2)
                    file.get(ch);
                firstCharacter = true;
            }
            file >> newElement->screenSize;
            file.ignore(1, ',');
            file >> newElement->resolution->width;
            file.ignore(1, ',');
            file >> newElement->resolution->height;
            file.ignore(1, ',');
            file.get(ch);
            for (int i = 3; i < 5; i++)
            {
                while (ch != ',' || inQuotes)
                {
                    if (ch == '"')
                    {
                        if (firstCharacter)
                        {
                            inQuotes = true;
                        }
                        else if (inQuotes)
                        {
                            if (lastWasQuote)
                            {
                                newElement->field(i) += ch;
                                lastWasQuote = false;
                            }
                            else
                            {
                                lastWasQuote = true;
                            }
                        }
                        else
                        {
                            newElement->field(i) += ch;
                        }
                        file.get(ch);
                    }
                    else if (ch == ',' && lastWasQuote)
                    {
                        inQuotes = false;
                        lastWasQuote = false;
                    }
                    else
                    {
                        newElement->field(i) += ch;
                        file.get(ch);
                    }
                    firstCharacter = false;
                }
                if (i < 4)
                    file.get(ch);
                firstCharacter = true;
            }
            file >> newElement->price;
            file.ignore(1, ',');
            file >> newElement->stock;
            file.ignore(1, ',');
            file.get(ch);
            newElement->next = NULL;
            this->AddElement(newElement);
        }
        return 0;
    }
    return 1;
}

void Magazin::RemoveElement(int index)
{
    if (!first)
        return;
    laptop* toDelete;
    if (index == 0)
    {
        if (first->next)
        {
            toDelete = first;
            first = first->next;
            delete toDelete;
        }
        else
            first = NULL;
    }
    else
    {
        laptop* previous = first;
        for (int i = 1; i < index; i++)
            previous = previous->next;
        toDelete = previous->next;
        previous->next = toDelete->next;
        delete toDelete;
    }
}

void Magazin::EditElement(int elemIndex, int fieldIndex, char* newValue)
{
    laptop* current = first;
    for (int i = 0; i < elemIndex; i++)
        current = current->next;
    switch (fieldIndex)
    {
    case 5:
        fieldIndex = 3;
        break;
    case 6:
        fieldIndex = 4;
        break;
    }
    current->field(fieldIndex) = newValue;
}

void Magazin::EditElement(int elemIndex, int fieldIndex, float newValue)
{
    laptop* current = first;
    for (int i = 0; i < elemIndex; i++)
        current = current->next;
    switch (fieldIndex)
    {
    case 3: 
        current->screenSize = newValue;
        break;
    case 7:
        current->price = newValue;
        break;
    }
}

void Magazin::EditElement(int elemIndex, int fieldIndex, int newValue)
{
    laptop* current = first;
    for (int i = 0; i < elemIndex; i++)
        current = current->next;
    switch (fieldIndex)
    {
    case 8:
        current->stock = newValue;
        break;
    }
}

void Magazin::EditElement(int elemIndex, int fieldIndex, struct laptop::resolution* newValue)
{
    laptop* current = first;
    for (int i = 0; i < elemIndex; i++)
        current = current->next;
    delete current->resolution;
    current->resolution = newValue;
}

std::string& Magazin::GetElement_Str(int elemIndex, int fieldIndex)
{
    if (!first)
        return NullStr;
    laptop* current = first;
    for (int i = 0; i < elemIndex; i++)
        current = current->next;
    switch (fieldIndex)
    {
    case 5:
        fieldIndex = 3;
        break;
    case 6:
        fieldIndex = 4;
        break;
    }
    return current->field(fieldIndex);
}

float Magazin::GetElement_Flt(int elemIndex, int fieldIndex)
{
    if (!first)
        return 0.0f;
    laptop* current = first;
    for (int i = 0; i < elemIndex; i++)
        current = current->next;
    switch (fieldIndex)
    {
    case 3:
        return current->screenSize;
        break;
    case 7:
        return current->price;
        break;
    }
}

void Magazin::Clear()
{
    if (first)
    {
        laptop* currentLaptop = first, * toDelete;
        while (currentLaptop)
        {
            toDelete = currentLaptop;
            currentLaptop = currentLaptop->next;
            delete toDelete;
        }
        first = new laptop();
        first = NULL;
    }
}

bool Magazin::Contains(int elemIndex, const char* value)
{
    laptop* current = first;
    switch (elemIndex)
    {
    case 5:
        elemIndex = 3;
        break;
    case 6:
        elemIndex = 4;
        break;
    }
    while (current)
    {
        if (strcmp(current->field(elemIndex).c_str(), value) == 0)
            return true;
        current = current->next;
    }
    return false;
}

float Magazin::MinPrice()
{
    if (!first)
        return 0.0f;
    float minPrice = FLT_MAX;
    laptop* current = first;
    while (current)
    {
        if (current->price < minPrice)
            minPrice = current->price;
        current = current->next;
    }
    return minPrice;
}

float Magazin::MaxPrice()
{
    float maxPrice = 0.0f;
    laptop* current = first;
    while (current)
    {
        if (current->price > maxPrice)
            maxPrice = current->price;
        current = current->next;
    }
    return maxPrice;
}