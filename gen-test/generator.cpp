#include <iostream>
#include <fstream>

int main()
{
    srand (time(NULL));
    int amount = 0;
    double min = 0, max = 0;
    std::cin >> amount;
    std::cin >> min;
    std::cin >> max;

    std::ofstream testDataFile;
    testDataFile.open ("test.dat", std::ios::trunc);
    
    testDataFile << amount << " ";


    for (int i = 0; i < amount; i++)
    {

        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                testDataFile << static_cast<double> (rand()) / RAND_MAX * (max - min) + min << " ";
    }
    
    testDataFile << std::endl;

    testDataFile.close();

    return 0;
}