#include "TexturePacking.h"
int rec[maxsize][4];

void RandomRectangles(int width, int height, int recnum)
{
	int size = 1;
	rec[0][0] = height;
	rec[0][1] = width;
	rec[0][2] = 0;
	rec[0][3] = 0;
	int type = 0;
	for (int i = 1; i < recnum; i++)
	{
		int chosen_to_devide = rand() % (size);
		type = type + 1;
		int count = 0;
		if (type % 2 == 0) //wide devide
		{
			int devide_height = rand() % rec[chosen_to_devide][0];
			while (devide_height < 0.3 * rec[chosen_to_devide][0] || devide_height > 0.7 * rec[chosen_to_devide][0])
			{
				devide_height = rand() % rec[chosen_to_devide][0];
				count++;
				if (count > 10)
					break;
			}
			if (devide_height < 0.3 * rec[chosen_to_devide][0] || devide_height > 0.7 * rec[chosen_to_devide][0])
			{
				i--;
				continue;
			}
			rec[size][0] = rec[chosen_to_devide][0] - devide_height;
			rec[size][1] = rec[chosen_to_devide][1];
			rec[size][2] = rec[chosen_to_devide][2];
			rec[size][3] = rec[chosen_to_devide][3] + devide_height;
			rec[chosen_to_devide][0] = devide_height;
			size++;
		}
		else //height devide
		{
			int devide_width = rand() % rec[chosen_to_devide][1];
			while (devide_width < 0.3 * rec[chosen_to_devide][1] || devide_width > 0.7 * rec[chosen_to_devide][1])
			{
				devide_width = rand() % rec[chosen_to_devide][1];
				count++;
				if (count > 10)
					break;
			}
			if (devide_width < 0.3 * rec[chosen_to_devide][1] || devide_width > 0.7 * rec[chosen_to_devide][1])
			{
				i--;
				continue;
			}
			rec[size][1] = rec[chosen_to_devide][1] - devide_width;
			rec[size][0] = rec[chosen_to_devide][0];
			rec[size][2] = rec[chosen_to_devide][2] + devide_width;
			rec[size][3] = rec[chosen_to_devide][3];

			rec[chosen_to_devide][1] = devide_width;
			size++;
		}
	}
	ofstream myfile("random.txt", ios::out); //example.txt是你要输出的文件的名字
	myfile << width << " " << recnum << endl;
	for (int j = 0; j < recnum; j++)
	{
		myfile << rec[j][0] << " " << rec[j][1] << endl;
	}

	ofstream anotherfile("optimal.txt", ios::out);

	anotherfile << width << " " << recnum << endl;
	for (int j = 0; j < recnum; j++)
	{
		anotherfile << rec[j][2] << " " << rec[j][3] << endl;
	}
	anotherfile.close();
	myfile.close();
}
