#include<iostream>

using namespace std;

// текстовый редактор
class TextEditor
{
public:
    void CreateCode()
    {
        cout << "Working on code..." << endl;
        cout << "#include <iostream>" << endl << endl;
        cout << "int main() {" << endl;
        cout << "\tstd::cout << \"Hello world!\" << std::endl;" << endl;
        cout << "\treturn 0;" << endl;
        cout << "}" << endl;
    }
    void Save()
    {
        cout << "Saving code..." << endl;
    }
};

class Compiler
{
public:
    void Compile()
    {
        cout << "\nApplication compilation..." << endl;
    }
};
class CLR
{
public:
    void Execute()
    {
        int t;
        cout << "\nApplication executing..." << endl;
        cout << "Hello world!" << endl;
        cout << "\nPress e to exit" << endl;
        cin >> t;
    }
    void Finish()
    {
        cout << "\nApplication shutting dowm..." << endl;
    }
};

class VisualStudioFacade
{
    TextEditor textEditor;
    Compiler compiler;
    CLR clr;
public:
    VisualStudioFacade(TextEditor te, Compiler compil, CLR clr)
    {
        textEditor = te;
        compiler = compil;
        clr = clr;
    }
    void Start()
    {
        textEditor.CreateCode();
        textEditor.Save();
        compiler.Compile();
        clr.Execute();
    }
    void Stop()
    {
        clr.Finish();
    }
};

class Programmer
{
public:
    void CreateApplication(VisualStudioFacade facade)
    {
        facade.Start();
        facade.Stop();
    }
};

int main()
{
        TextEditor textEditor = TextEditor();
        Compiler compiler = Compiler();
        CLR clr = CLR();

        VisualStudioFacade ide = VisualStudioFacade(textEditor, compiler, clr);

        Programmer* programmer = new Programmer;
        programmer->CreateApplication(ide);
}
