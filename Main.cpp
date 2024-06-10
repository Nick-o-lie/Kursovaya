#include "Loading.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThread]
void Main(array<System::String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Kursovaya::Loading form;
	Application::Run(% form);
}