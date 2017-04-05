#include <iostream>
using namespace std;
#include <sstream>
using namespace std;
#include <fstream>
using namespace std;
#include <string>
using namespace std;
#include <windows.h>
#include <conio.h>

#define endl '\n'

inline void cmd(string input)
{
	char* result = new char[input.size()+1];
	for (auto step = 0; step < input.size();step++)
	{
		result[step] = input.at(step);
	}
	result[input.size()] = '\n';

	system(result);
}
inline char* _cmd(string input)
{
	char* result = new char[input.size() + 1];
	for (auto step = 0; step < input.size(); step++)
	{
		result[step] = input.at(step);
	}
	result[input.size()] = '\n';

	return result;
}


void main()
{
	cout << "我的世界模组资源文件生成器" << endl<<endl<<endl;
	cout << "按任意键继续" << endl;

	string path_config;

	bool flag_main = true;
	while (flag_main)
	{
		system("cls");
		cout << "请输入配置文件路径" << endl;
		cin >> path_config;


		ifstream ifs_config(path_config);
		if (ifs_config.good())
		{
			cout <<endl<< "已找到配置文件" << endl;

			string word, line;
			string name_mod;
			string name_item;
			string path_output;

			getline(ifs_config, line);
			istringstream iss(line);

			iss >> name_mod;
			cout << "模组名称\t" << name_mod << endl;

			cout << "开始生成目录" << endl;
			system("mkdir assets");
			system(_cmd("mkdir assets\\" + name_mod));
			// system(_cmd("mkdir assets\\" + name_mod + "\\lang"));
			system(_cmd("mkdir assets\\" + name_mod + "\\models"));
			system(_cmd("mkdir assets\\" + name_mod + "\\models\\item"));
			system(_cmd("mkdir assets\\" + name_mod + "\\models\\block"));
			system(_cmd("mkdir assets\\" + name_mod + "\\textures"));
			system(_cmd("mkdir assets\\" + name_mod + "\\textures\\blocks"));
			system(_cmd("mkdir assets\\" + name_mod + "\\textures\\items"));
			system(_cmd("mkdir assets\\" + name_mod + "\\textures\\fluid"));
			system(_cmd("mkdir assets\\" + name_mod + "\\blockstates"));

			

			cout <<endl<< "开始生成" << endl;
			while (ifs_config.good())
			{
				getline(ifs_config, line);
				istringstream iss_ing(line);

				iss_ing >> word >> name_item;
				if (word == "item") // 普通物品类型 // 比如铁锭
				{
					path_output = ".\\assets\\" + name_mod + "\\models\\item\\" + name_item+".json";
					ofstream ofs_output(path_output, ofstream::out);

					ofs_output << "{\n\t\"parent\": \"builtin/generated\",\n\t\"textures\": {\n\t\t\"layer0\": \""<<name_mod<<":items/"<<name_item<<"\"\n\t},\n\t\"display\": {\n\t\t\"thirdperson\": {\n\t\t\t\"rotation\": [ -90, 0, 0 ],\n\t\t\t\"translation\": [ 0, 1, -2 ],\n\t\t\t\"scale\": [ 0.55, 0.55, 0.55 ]\n\t\t},\n\t\t\t\"firstperson\": {\n\t\t\t\"rotation\": [ 0, -135, 25 ],\n\t\t\t\"translation\": [ 0, 4, 2 ],\n\t\t\t\"scale\": [ 1.7, 1.7, 1.7 ]\n\t\t}\n\t}\n}";
					
					cout << "已生成物品\t" << name_item << endl;
				}
				else if (word == "tool") // 工具类型 // 比如铁斧
				{
					path_output = ".\\assets\\" + name_mod + "\\models\\item\\" + name_item + ".json";
					ofstream ofs_output(path_output, ofstream::out);
					;
				}
				else if (word == "bucket") // 桶类型 // 比如水桶
				{
					path_output = ".\\assets\\" + name_mod + "\\models\\item\\" + name_item + ".json";
					ofstream ofs_output(path_output, ofstream::out);
				}
				else if (word == "block") // 方块类型 // 比如泥土 // 会同时在block文件夹生成数据
				{
					path_output = ".\\assets\\" + name_mod + "\\models\\block\\" + name_item + ".json";
					ofstream ofs_output(path_output, ofstream::out);
				}
				else if (word == "fluid") // 液体类型
				{
					cout << "未添加液体类型数据 跳过.." << endl;
				}
			}


		}
		else
		{
			cout << endl << "未找到配置文件" << endl;
		}

		cout  << endl << "是否继续生成?" << endl;
		cout << "y / Y / 1" << endl;

		char flag_temp = _getch();

		switch (flag_temp)
		{
		case 'y':case 'Y':case '1':
			cout << endl << "继续下一次输入.." << endl; break;
		default:
			flag_main = false;
			cout << endl << "停止输入.." << endl;
		}

	}


}

