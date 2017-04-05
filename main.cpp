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
	char* result = new char[input.size() + 1];
	for (auto step = 0; step < input.size(); step++)
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

void show_help()
{
	system("cls");
	cout << "这个小程序用来批量生成（完成）/删除（计划中）" << endl;
	cout << "制作Minecraft模组所需的物品、方块之类的的材质和渲染器信息" << endl;
	cout << "另外还能自动创建（复制）一个默认材质文件" << endl;
	cout << "不过现在受技术水平所限还不能生成高级的模型" << endl;
	cout << endl;
	cout << "数据文件格式:" << endl;
	cout << "模组名称" << endl;
	cout << "数据类型\t数据名称" << endl;
	cout << "..." << endl;
	cout << endl;
	cout << "可用的数据类型:" << endl;
	cout << "item\t:物品 如铁锭" << endl;
	cout << "block\t:方块 如泥土" << endl;
	cout << "fluid\t:液体 如水方块 （同时会生成对应桶）" << endl;
	cout << "tool\t:工具 如铁镐" << endl;
	cout << endl;
	cout << "在数据类型前加\"delete\"" << endl;
	cout << "如\"deleteitem\"即可删除相应数据" << endl;
	cout << endl;
	cout << "示例数据文件:" << endl;
	cout << "redstonepower" << endl;
	cout << "tool axe_redstone" << endl;
	cout << "block block_chargedRedstone" << endl;
	cout << "item item_chargedRedstone" << endl;
	cout << "deleteblock block_redstone" << endl;
	cout << endl;
	cout << endl;
}

void show_author()
{
	system("cls");
	cout << "作者:" << endl;
	cout << "\tFirok" << endl;
	cout << endl;
	cout << "Github:" << endl;
	cout << "\thttps://github.com/S2Lab/MinecraftModAssetsGenerator" << endl;
	cout << endl;
	cout << "\t\t“" << endl;
	cout << "\t\t\t使用之前请务必在心里默念3次 μ's Forever" << endl;
	cout << "\t\t\t否则极为容易由于信仰力不足生成各种乱码（大雾）" << endl;
	cout << "\t\t\t\t\t\t\t\t\t”" << endl;
	cout << endl;
	system("pause");
}

void main()
{
	cout << "我的世界模组资源文件生成器" << endl << endl << endl;
	cout << "按任意键继续" << endl;

	string path_config;
	string path_img;
	char flag_temp;

	bool flag_main = true;
	while (flag_main)
	{
		system("cls");
		cout << "1.生成数据" << endl;
		cout << "2.帮助" << endl;
		cout << "3.关于" << endl;
		cout << "4.退出" << endl;
		flag_temp = _getch();
		ifstream ifs_config;
		ifstream ifs_img;
		switch (flag_temp)
		{
		case '1':

			system("cls");
			cout << "请输入配置文件路径" << endl;
			cin >> path_config;
			cout << "请输入默认材质路径" << endl;
			cin >> path_img;


			ifs_config.open(path_config);
			ifs_img.open(path_img);
			if (ifs_config.good() && ifs_img.good())
			{
				cout << endl << "已找到配置文件" << endl;

				string word, line;
				string name_mod;
				string name_item;
				string path_output;

				getline(ifs_config, line);
				istringstream iss(line);

				iss >> name_mod;
				cout << "模组名称\t" << name_mod << endl;

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
				cout << "目录生成完成" << endl;


				cout << endl << "开始生成数据" << endl;
				while (ifs_config.good())
				{
					getline(ifs_config, line);
					istringstream iss_ing(line);

					iss_ing >> word >> name_item;
					if (word == "item") // 普通物品类型 // 比如铁锭
					{
						path_output = ".\\assets\\" + name_mod + "\\models\\item\\" + name_item + ".json";
						ofstream ofs_output(path_output, ofstream::out);

						ofs_output << "{\n\t\"parent\": \"builtin/generated\",\n\t\"textures\": {\n\t\t\"layer0\": \"" << name_mod << ":items/" << name_item << "\"\n\t},\n\t\"display\": {\n\t\t\"thirdperson\": {\n\t\t\t\"rotation\": [ -90, 0, 0 ],\n\t\t\t\"translation\": [ 0, 1, -2 ],\n\t\t\t\"scale\": [ 0.55, 0.55, 0.55 ]\n\t\t},\n\t\t\t\"firstperson\": {\n\t\t\t\"rotation\": [ 0, -135, 25 ],\n\t\t\t\"translation\": [ 0, 4, 2 ],\n\t\t\t\"scale\": [ 1.7, 1.7, 1.7 ]\n\t\t}\n\t}\n}";

						path_output = ".\\assets\\" + name_mod + "\\textures\\items\\" + name_item + ".png";
						system(_cmd("copy " + path_img + " " + path_output));

						cout << "已生成物品\t" << name_item << endl;

					}
					else if (word == "tool") // 工具类型 // 比如铁斧
					{
						path_output = ".\\assets\\" + name_mod + "\\models\\item\\" + name_item + ".json";
						ofstream ofs_output(path_output, ofstream::out);

						ofs_output <<"{\n\t\"parent\": \"builtin/generated\",\n\t\"textures\": {\n\t\t\"layer0\": \""<<name_mod<<":items/"<<name_item<<"\"\n\t},\n\t\"display\": {\n\t\t\"thirdperson\": {\n\t\t\t\"rotation\": [ 0, 90, -35 ],\n\t\t\t\"translation\": [ 0, 1.25, -3.5 ],\n\t\t\t\"scale\": [ 0.85, 0.85, 0.85 ]\n\t\t},\n\t\t\"firstperson\": {\n\t\t\t\"rotation\": [ 0, -135, 25 ],\n\t\t\t\"translation\": [ 0, 4, 2 ],\n\t\t\t\"scale\": [ 1.7, 1.7, 1.7 ]\n\t\t}\n\t}\n}";
						
						path_output = ".\\assets\\" + name_mod + "\\textures\\items\\" + name_item + ".png";
						system(_cmd("copy " + path_img + " " + path_output));
						
						cout << "已生成工具\t" << name_item << endl;

					}
					else if (word == "block") // 方块类型 // 比如泥土 // 会同时在block文件夹生成数据
					{
						path_output = ".\\assets\\" + name_mod + "\\models\\block\\" + name_item + ".json";
						ofstream ofs_output(path_output, ofstream::out);
						ofs_output << "{\n\t\"parent\": \"block/cube_all\",\n\t\"textures\": {\n\t\t\"all\": \"" << name_mod << ":blocks/" << name_item << "\"\n\t}\n}";

						path_output = ".\\assets\\" + name_mod + "\\models\\item\\" + name_item + ".json";
						ofstream ofs_output2(path_output, ofstream::out);
						ofs_output2<< "{\n\t\"parent\": \""<<name_mod<<":block/"<<name_item<<"\",\n\t \"display\": {\n\t\t\"thirdperson\": {\n\t\t\t\"rotation\": [ 10, -45, 170 ],\n\t\t\t\"translation\": [ 0, 1.5, -2.75 ],\n\t\t\t\"scale\": [ 0.375, 0.375, 0.375 ]\n\t\t}\n\t}\n}";

						path_output = ".\\assets\\" + name_mod + "\\blockstates\\" + name_item + ".json";
						ofstream ofs_output3(path_output, ofstream::out);
						ofs_output3 << "{\n\t\"variants\": {\n\t\t\"normal\": { \"model\": \""<<name_mod<<":"<<name_item<<"\" }\n\t}\n}";

						path_output = ".\\assets\\" + name_mod + "\\textures\\blocks\\" + name_item + ".png";
						system(_cmd("copy " + path_img + " " + path_output));

						cout << "已生成方块\t" << name_item << endl;

					}
					else if (word == "fluid") // 液体类型
					{
						path_output = ".\\assets\\" + name_mod + "\\textures\\fluid\\" + name_item + "_still.png.mcmeta";
						ofstream ofs_output(path_output, ofstream::out);
						ofs_output << "{\n\t\"animation\": {\n\t\t\"frametime\": 2\n\t}\n}";

						path_output = ".\\assets\\" + name_mod + "\\textures\\fluid\\" + name_item + "_flow.png.mcmeta";
						ofstream ofs_output2(path_output, ofstream::out);
						ofs_output2 << "{\n\t\"animation\": {}\n}";

						path_output = ".\\assets\\" + name_mod + "\\blockstates\\fluid_" + name_item + ".json";
						ofstream ofs_output3(path_output, ofstream::out);
						ofs_output3 << "{\n\t\"forge_marker\": 1,\n\t\"variants\": {\n\t\t\"fluid\": {\n\t\t\t\"model\": \"forge:fluid\",\n\t\t\"custom\": { \"fluid\": \""<<name_item<<"\" }\n\t\t}\n\t}\n}";

						path_output = ".\\assets\\" + name_mod + "\\models\\item\\bucket_" + name_item + ".json";
						ofstream ofs_output4(path_output, ofstream::out);
						ofs_output4 << "{\n\t\"parent\": \"builtin/generated\",\n\t\"textures\": {\n\t\t\"layer0\": \""<<name_mod<<":items/bucket_"<<name_item<<"\"\n\t},\n\t\"display\": {\n\t\t\"thirdperson\": {\n\t\t\t\"rotation\": [ -90, 0, 0 ],\n\t\t\t\"translation\": [ 0, 1, -3 ],\n\t\t\t\"scale\": [ 0.55, 0.55, 0.55 ]\n\t\t},\n\t\t\"firstperson\": {\n\t\t\t\"rotation\": [ 0, -135, 25 ],\n\t\t\t\"translation\": [ 0, 4, 2 ],\n\t\t\t\"scale\": [ 1.7, 1.7, 1.7 ]\n\t\t}\n\t}\n}";
						
						path_output = ".\\assets\\" + name_mod + "\\textures\\fluid\\" + name_item + "_still.png";
						system(_cmd("copy " + path_img + " " + path_output));

						path_output = ".\\assets\\" + name_mod + "\\textures\\fluid\\" + name_item + "_flow.png";
						system(_cmd("copy " + path_img + " " + path_output));
						
						cout<<"已生成液体\t"<<name_item<<"\t及对应桶"<<endl;

					}


					else if (word == "deleteitem") // 删除物品
					{
						;
						// cout<<"已删除物品\t"<<name_item<<endl;
					}
					else if (word == "deletetool") // 删除工具
					{
						;
						// cout<<"已删除工具\t"<<name_item<<endl;
					}
					else if (word == "deleteblock") // 删除方块
					{
						;

						// cout<<"已删除方块\t"<<name_item<<endl;
					}
					else if (word == "deletefluid") // 删除液体
					{
						;

						// cout<<"已删除液体\t"<<name_item<<endl;
					}


					else
					{
						cout << "类型错误 跳过.."<<endl;
					}
				}


			}
			else
			{
				if(!ifs_config.good())
					cout << endl << "未找到配置文件" << endl;
				if (!ifs_img.good())
					cout << endl << "未找到图片文件" << endl;
			}

			break;
		case '2':
			show_help();
			break;

		case '3':
			show_author();
			break;

		case '4':
			flag_main = false;
			break;


		}

		system("pause");

	}


}
