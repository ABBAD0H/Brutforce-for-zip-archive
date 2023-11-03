#include <direct.h>
#include <iostream>
#include <Windows.h>

using namespace std;
//A-Z 65-90    a-z 97-122
string shablon = "7z x C:\\test.7z -oC:\\Users\\WARRIOR\\Desktop\\test -p";

void rec(short pos, short* count, string* pass, const char* command)
{
    pass->replace(pos, 1, string(1, 'a'));
    if (pos < *count-1)
    {
        while (pass->at(pos) < 123)
        {
            rec(pos + 1, count, pass, command);
            pass->replace(pos, 1, string(1, (pass->at(pos)+1)));
        }
    }
    else if(pos == *count - 1)
    {
        
        while (pass->at(pos) < 123)
        {
            string aaa = *pass;
            cout << *pass << endl;
            string str = shablon;
            str += *pass;
            command = str.c_str();
            system("rmdir /Q /S C:\\Users\\WARRIOR\\Desktop\\test");
            FILE* pipe = _popen(command, "r"); // запускаем команду "ls -l" и открываем поток для чтения вывода
            if (!pipe)
            {
                // ошибка при запуске команды
                pass->replace(pos, 1, string(1, (pass->at(pos) + 1)));
                Sleep(5000);
                continue;
            }
            char buffer[128];
            while (fgets(buffer, 128, pipe) != NULL)
            {
                // читаем вывод команды построчно
                str = string(buffer);
                int pp = str.find("Everything is Ok");
                if (pp != string::npos)
                {
                    cout << "password = " << pass << endl;
                    exit(0);
                }
            }
            pass->replace(pos, 1, string(1, (pass->at(pos)+1)));
        }
    }

    return;
}

void first_rec(short pos, short* count, string* pass, const char* command)
{
    while (*count < 11)
    {
        if (pos < *count)
        {
            while (pass->at(0) < 91)
            {
                rec(pos + 1, count, pass, command);
                pass->replace(0, 1, string(1, (pass->at(0) + 1)));
            }
            pass->replace(0, 1, string(1, 'a'));
            while (pass->at(0) < 123)
            {
                rec(pos + 1, count, pass, command);
                pass->replace(0, 1, string(1, (pass->at(0) + 1)));
            }
        }
        *pass = "A";
        for (int i = 0; i < *count; i++)
            *pass += 'a';
        *count += 1;
    }
    return;
}

int main() 
{
    short count = 2;
    short pos = 0;
    string pass= "A";
    _chdir("C:\\Program Files\\7-Zip");
    string str = "7z.exe";
    const char* command = str.c_str();
    if (count == 1)
    {
        for (unsigned short i = 0; i < 26; i++)
        {
            pass.replace(0, 1, string(1, ('A' + i)));
            str = shablon;
            str += pass;
            command = str.c_str();
            system("rmdir /Q /S C:\\Users\\WARRIOR\\Desktop\\test");
            FILE* pipe = _popen(command, "r"); // запускаем команду "ls -l" и открываем поток для чтения вывода
            if (!pipe)
            {
                // ошибка при запуске команды
                return -1;
            }
            char buffer[128];
            while (fgets(buffer, 128, pipe) != NULL)
            {
                // читаем вывод команды построчно
                str = string(buffer);
                int pp = str.find("Everything is Ok");
                if (pp != string::npos)
                {
                    cout << "password = " << pass << endl;
                    exit(0);
                }

            }
            _pclose(pipe); // закрываем поток
        }
        count++;
    }
    pass = "Aa";
    first_rec(pos, &count, &pass, command);


    return 0;
}