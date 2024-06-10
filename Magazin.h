#pragma once
#include <string>
#include <fstream>

static std::string NullStr("");
class Magazin
{
public:
	struct laptop
	{
		std::string name; // index = 0
		std::string brand; // index = 1
		std::string type; // index = 2
		float screenSize;
		struct resolution {
			int width;
			int height;

			resolution() {}

			resolution(int width, int height) {
				this->width = width;
				this->height = height;
			}
		};
		resolution* resolution;
		std::string matrixType; // index = 3
		std::string additional; // index = 4
		float price;
		int stock;
		laptop* next;

		laptop() { 
			screenSize = NULL;
			resolution = new struct laptop::resolution;
			resolution->width = NULL;
			resolution->height = NULL;
			price = NULL;
			stock = NULL;
			next = NULL;
		}

		laptop(char* name, char* brand, char* type, float screenSize, struct laptop::resolution* resolution, char* matrixType, char* additional, float price, int stock) {
			this->name = name;
			this->brand = brand;
			this->type = type;
			this->screenSize = screenSize;
			this->resolution = resolution;
			this->matrixType = matrixType;
			this->additional = additional;
			this->price = price;
			this->stock = stock;
			next = NULL;
		}

		std::string& field(int index)
		{
			switch (index)
			{
			case 0:
				return this->name;
			case 1:
				return this->brand;
			case 2:
				return this->type;
			case 3:
				return this->matrixType;
			case 4:
				return this->additional;
			}
		}

		bool fitsCriteria(std::string& name, std::string& brand, float minPrice, float maxPrice, bool areOut)
		{
			if (this->name.find(name) != std::string::npos)
				if ((brand == "") || (this->brand == brand))
					if (this->price >= minPrice && this->price <= maxPrice)
						if ((this->stock <= 0) || !areOut)
							return true;
			return false;
		}

		~laptop()
		{
			delete resolution;
		}
	};
private:
	laptop* first;
public:
	Magazin();

	laptop* GetHead();

	int Length();

	int InStock();

	void AddElement(laptop* laptop);

	int Save(const wchar_t* fileName);

	void FormatOutput(std::string &toFormat);

	int Load(const wchar_t* fileName);

	void RemoveElement(int index);

	void EditElement(int elemIndex, int fieldIndex, char* newValue);

	void EditElement(int elemIndex, int fieldIndex, float newValue);

	void EditElement(int elemIndex, int fieldIndex, int newValue);

	void EditElement(int elemIndex, int fieldIndex, struct laptop::resolution* newValue);

	std::string& GetElement_Str(int elemIndex, int fieldIndex);

	float GetElement_Flt(int elemIndex, int fieldIndex);

	bool Contains(int elemIndex, const char* value);

	float MinPrice();

	float MaxPrice();

	void Clear();
};

