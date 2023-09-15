#include <iostream>
#include <fstream>
#include <random>
using namespace std;

int generateRandomInt(int min, int max) 
{
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max); 
    return dist(gen); 
}


int main() 
{
    int n, H, t, v, min, max, file_num;
    min = 1;
    max = 100;

    std::filesystem::path dir = "Generated_Tests";

    if (!std::filesystem::exists(dir)) 
    {
        std::filesystem::create_directory(dir);
    }
    
    std::cout << "Input the number of test files you want to generate: "; 
    std::cin >> file_num;

    for (int i = 0; i < file_num; ++i) 
    {
        std::filesystem::path filename = dir / ("test" + std::to_string(i) + ".txt"); // Construct the filename

        std::ofstream outfile(filename); // Open the file for writing

        n = generateRandomInt(min, max);
        H = generateRandomInt(min, max);

        if (outfile.is_open()) 
        {
            outfile << n << " " << H << "\n"; 

            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    outfile << j << " " << k << " ";
                    t = generateRandomInt(0, 3);

                    switch(t)
                    {
                        case 0: //Damage Tile
                            v = generateRandomInt(1, H);
                            break;
                        case 1: //Healing Tile
                            v = generateRandomInt(1, H);
                            break;
                        case 2: //Protection Tile
                            v = 0;
                            break;
                        case 3: //Multiplier Tile
                            v = 0;
                            break;
                    }
                    outfile << t << " " << v << "\n";

                }
            }
            
            outfile.close(); // Close the file
        } 
        else 
        {
            std::cerr << "Unable to open file " << filename << std::endl;
            return 1;
        }
    }

    return 0;
}