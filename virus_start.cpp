//import
//import
//https://en.cppreference.com/w
//http://www.cplusplus.com/reference/stl/?kw=stl

//insert interval
//https://www.cnblogs.com/ariel-dreamland/p/9149303.html

//c cpp search
//https://www.cnblogs.com/Senchuangdianzi/p/12076544.html

//heap
//https://www.cnblogs.com/sevenPP/p/3620020.html

//algorithmalgorithm
//https://github.com/nonstriater/Learn-Algorithms

#if 0
// virus reproduction
int count;
	cin >> count;

	while (count--)
	{
		int a1, a2;
		cin >> a1;
		cin >> a2;

		vector<int> normal;
		vector<int> unnormal;

		normal.push_back(0);
		unnormal.push_back(0);
		for (int i = 1; i <= a2; i++)
		{
			if (i == 1)
			{
				if (a1 == 1)
				{
					normal.push_back(1);
					unnormal.push_back(1);
				}
				else
				{
					normal.push_back(1);
					unnormal.push_back(0);
				}

			}
			
			int tmp1 = 0;
			int tmp2 = 0;
			if (i > 1 && i <= a1)
			{
				//cout << normal.size() << endl;
				tmp1 = normal[i-1]*2;
				//cout << tmp1 << endl;
				normal.push_back(tmp1);
				unnormal.push_back(0);
			}
			
			if (i == (a1 + 1))
			{
				tmp1 = (normal[i - 1] - 1) * 2 + 1;
				normal.push_back(tmp1);
				unnormal.push_back(1);
			}
			
			if (i > (a1 + 1))
			{
				int tmp2 = 0;

				tmp1 = normal[i - 1] * 2;
				//cout << "tmp1" << tmp1 << endl;
				tmp2 = unnormal[i - 1] * 2 + unnormal[i - 1];
				normal.push_back(tmp1);
				unnormal.push_back(tmp2);
			}
		}

		int size1 = normal.size();
		int size2 = unnormal.size();
		//cout << "unnormal[size2 - 1])" << unnormal[size2 - 1] << " " << normal[size1 - 1]<<endl;
		float result = ((float)(unnormal[size2 - 1]) / (float)(normal[size1 - 1] + unnormal[size1 - 1])) * 100;
		printf("%.2f\%%", result);
		printf("\n");


		//printf("%d,%d\n", a1, a2);
	}
	//system("pause");

	return 0;
