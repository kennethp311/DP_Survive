#include <iostream>
#include <fstream>
#include <vector>
#include <cstring> // For strlen

constexpr int MAX_N = 100;

struct Tile {
    int t;
    int v;
};

void load_input_file(const std::string& file_name, int& n, int& H, std::vector<std::vector<Tile>>& tiles) {
    std::ifstream file(file_name);
    file >> n >> H;
    
    // Initialize the grid
    tiles.resize(n, std::vector<Tile>(n));

    for (int i = 0; i < n * n; i++) {
        if (i == 0) {
            continue; // The initial tile is zero type with zero value
        }
        Tile tile;
        int x,y;
        file >> x >> y >> tile.t >> tile.v;
        tiles[x][y] = tile;
    }
    
    file.close();
}

void print_tile_data(int n, const std::vector<std::vector<Tile>>& tiles) {
    std::cout << "Tile Types:\n";
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            std::cout << "[" << tiles[x][y].t << "] ";
        }
        std::cout << '\n';
    }

    std::cout << "\nTile Values:\n";
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            std::cout << "[" << tiles[x][y].v << "] ";
        }
        std::cout << '\n';
    }
}

// struct Data
// {
//     int h;
//     bool p;
//     bool m;
// };

bool DP(int n, int H, const std::vector<std::vector<Tile>>& tiles) {
    
    //Kenneth Park is super smart
    //std::vector<std::vector<Data>> T(n, std::vector<Data>(n, {-1, false, false}));

    std::vector<std::vector<int>> T(n, std::vector<int>(n, -1));  //T[i][j] = maximum health to get to destination [i][j].
    std::vector<std::vector<int>> P(n, std::vector<int>(n, -1));  //P[i][j] = maximum health to get to destination [i][j] while saving Protection Token.
    std::vector<std::vector<int>> M(n, std::vector<int>(n, -1));  //M[i][j] = maximum health to get to destination [i][j] while saving Multiplier Token.
    std::vector<std::vector<int>> PM(n, std::vector<int>(n, -1)); //PM[i][j] = maximum health to get to destination [i][j] while saving Protection and Multiplier Token.

    if (n > MAX_N)
        return false;
        
    if (H >= 0)
        T[0][0] = H;
    else
        return false;


    for (int i = 1; i <= n - 1; i++) 
    {
        if (tiles[i][0].t == 0 && tiles[i][0].v > 0) //Damage Tile
        {
            if (PM[i - 1][0] >= 0) //Update PM Table
            {
                if (PM[i - 1][0] >= tiles[i][0].v) 
                {
                    PM[i][0] = PM[i - 1][0] - tiles[i][0].v;
                }

                M[i][0] = std::max(PM[i - 1][0], M[i - 1][0] - tiles[i][0].v);
            }
           

            if (P[i - 1][0] >= tiles[i][0].v) //Update P Table
            {
                P[i][0] = P[i - 1][0] - tiles[i][0].v;
            }

            if (M[i - 1][0] >= tiles[i][0].v) //Update M Table
            {
                M[i][0] = std::max(M[i][0], M[i - 1][0] - tiles[i][0].v);
            }

            //(1) std::max(P[i - 1][0], PM[i - 1][0])
            //(2) T[i - 1][0] - tiles[i][0].v
            //(3) M[i - 1][0] - tiles[i][0].v

            if (T[i - 1][0] >= 0)
            {
                T[i][0] = std::max(std::max(P[i - 1][0], PM[i - 1][0]) , std::max(T[i - 1][0], M[i - 1][0]) - tiles[i][0].v); 
            }
            else
                T[i][0] = -1;

            if (T[i][0] < 0)
                T[i][0] = -1;

        }
        
        else if (tiles[i][0].t == 1) //Healing Tile
        {
            if (PM[i - 1][0] >= 0) //Update PM Table
            {
                PM[i][0] = PM[i - 1][0] + tiles[i][0].v;
                P[i][0] = std::max(P[i - 1][0] + tiles[i][0].v, PM[i - 1][0] + (2 * tiles[i][0].v));
            }

            if (P[i - 1][0] >= 0) //Update P Table
            {
                P[i][0] = std::max(P[i][0], P[i - 1][0] + tiles[i][0].v);
            }

            if (M[i - 1][0] >= 0) //Update M Table
            {
                M[i][0] = M[i - 1][0] + tiles[i][0].v;
            }
            
            //(1) T[i - 1][0] + tiles[i][0].v
            //(2) PM[i - 1][0] + (2 * tiles[i][0].v)
            //(3) M[i - 1][0] + (2 * tiles[i][0].v)
            //(4) P[i - 1][0] + tiles[i][0].v

            if (T[i - 1][0] >= 0)
            {
                if (PM[i - 1][0] >= 0 || M[i - 1][0] >= 0)
                {
                    T[i][0] = std::max(std::max(T[i - 1][0] , P[i - 1][0]) + tiles[i][0].v, std::max(PM[i - 1][0], M[i - 1][0]) + (2 * tiles[i][0].v)); 
                }
                else 
                {
                    T[i][0] = std::max(T[i - 1][0] , P[i - 1][0]) + tiles[i][0].v;
                }
            }
        }

        else if (tiles[i][0].t == 2) //Protection Tile
        {
            PM[i][0] = std::max(PM[i - 1][0], M[i - 1][0]);
            T[i][0] = T[i - 1][0]; 
            
            if (P[i - 1][0] >= 0) //Update P Table
            {
                P[i][0] = P[i - 1][0];
            }
            else
            {
                if (T[i - 1][0] >= 0 && T[i - 1][0] != M[i - 1][0] && T[i - 1][0] != PM[i - 1][0]) //if T[i - 1][0] doesnt have a protection/multiplier token and doesnt have a multiplier token 
                {
                    P[i][0] = T[i - 1][0];
                }
            }

        }

        else if (tiles[i][0].t == 3) //Multiplier Tile
        {
            PM[i][0] = std::max(PM[i - 1][0], P[i - 1][0]);
            T[i][0] = T[i - 1][0];
            

            if (M[i - 1][0] >= 0) //Update M Table
            {
                M[i][0] = M[i - 1][0];
            }
            else
            {
                if (T[i - 1][0] >= 0 && T[i - 1][0] != P[i - 1][0] && T[i - 1][0] != PM[i - 1][0])
                {
                    M[i][0] = T[i - 1][0];
                }
            }
    
        }

    }

    for (int j = 1; j <= n - 1; j++) 
    {
        if (tiles[0][j].t == 0 && tiles[0][j].v > 0) //Damage Tile
        {
            
            if (PM[0][j - 1] >= 0) //Update PM Table
            {
                if (PM[0][j - 1] >= tiles[0][j].v) 
                {
                    PM[0][j] = PM[0][j - 1] - tiles[0][j].v;
                }

                M[0][j] = std::max(PM[0][j - 1], M[0][j - 1] - tiles[0][j].v);
            }


            if (P[0][j - 1] >= tiles[0][j].v) //Update P Table
            {
                P[0][j] = P[0][j - 1] - tiles[0][j].v;
            }

            if (M[0][j - 1] >= tiles[0][j].v) //Update M Table
            {
                M[0][j] = std::max(M[0][j], M[0][j - 1] - tiles[0][j].v);
            }
           

            if (T[0][j - 1] >= 0)
            {
                T[0][j] = std::max(std::max(P[0][j - 1], PM[0][j - 1]) , std::max(T[0][j - 1], M[0][j - 1]) - tiles[0][j].v); 
            }
            else
                T[0][j] = -1;

            if (T[0][j] < 0)
                T[0][j] = -1;

        }

        
        else if (tiles[0][j].t == 1) //Healing Tile
        {
            if (PM[0][j - 1] >= 0) //Update PM Table
            {
                PM[0][j] = PM[0][j - 1] + tiles[0][j].v;
                P[0][j] = std::max(P[0][j - 1] + tiles[0][j].v , PM[0][j - 1] + (2 * tiles[0][j].v));
            }

            if (P[0][j - 1] >= 0) //Update P Table
            {
                P[0][j] = std::max(P[0][j], P[0][j - 1] + tiles[0][j].v);
            }

            if (M[0][j - 1] >= 0) //Update M Table
            {
                M[0][j] = M[0][j - 1] + tiles[0][j].v;
            }
            

            if (T[0][j - 1] >= 0)
            {
                if (PM[0][j - 1] >= 0 || M[0][j - 1] >= 0)
                {
                    T[0][j] = std::max(std::max(T[0][j - 1] , P[0][j - 1]) + tiles[0][j].v, std::max(PM[0][j - 1],M[0][j - 1]) + (2 * tiles[0][j].v)); 
                }
                else if (P[0][j - 1] >= 0)
                {
                    T[0][j] = std::max(T[0][j - 1] , P[0][j - 1]) + tiles[0][j].v;
                }
                else
                {
                    T[0][j] = T[0][j - 1] + tiles[0][j].v;
                }
            }
        }


        else if (tiles[0][j].t == 2) //Protection Tile
        {
            PM[0][j] = std::max(PM[0][j - 1], M[0][j - 1]);
           
            T[0][j] = T[0][j - 1];
           
            if (P[0][j - 1] >= 0) //Update P Table
            {
                P[0][j] = P[0][j - 1];
            }
            else
            {
                if (T[0][j - 1]  >= 0 && T[0][j - 1] != M[0][j - 1] && T[0][j - 1] != PM[0][j - 1])
                {
                    P[0][j] = T[0][j - 1];
                }
            }
        }

        
        else if (tiles[0][j].t == 3) //Multiplier Tile
        {
            PM[0][j] = std::max(PM[0][j - 1], P[0][j - 1]);

            T[0][j] = T[0][j - 1];

            if (M[0][j - 1] >= 0) //Update M Table
            {
                M[0][j] = M[0][j - 1];
            }
            else
            {
                if (T[0][j - 1]  >= 0 && T[0][j - 1] != P[0][j - 1] && T[0][j - 1] != PM[0][j - 1])
                {
                    M[0][j] = T[0][j - 1];
                }
            }
            
            
        }

    }
    
    int a,b,c,d = -1;

    for (int i = 1; i <= n - 1; i++)
    {
        for (int j = 1; j <= n - 1; j++)
        {
            
            if (tiles[i][j].t == 0 && tiles[i][j].v > 0) //Damage Tile
            {
              
                if (std::max(PM[i - 1][j], PM[i][j - 1]) >= 0) //Update PM Table
                {
                    if (std::max(PM[i - 1][j], PM[i][j - 1]) >= tiles[i][j].v) 
                    {
                        PM[i][j] = std::max(PM[i - 1][j], PM[i][j - 1]) - tiles[i][j].v;  
                    } 

                    M[i][j] = std::max(std::max(M[i - 1][j], M[i][j - 1]) - tiles[i][j].v, std::max(PM[i - 1][j], PM[i][j - 1]));

                }

                if (std::max(M[i - 1][j], M[i][j - 1]) >= 0) //Update M Table
                {
                    if (std::max(M[i - 1][j], M[i][j - 1]) >= tiles[i][j].v) 
                    {
                        M[i][j] = std::max(std::max(M[i - 1][j], M[i][j - 1]) - tiles[i][j].v, std::max(PM[i - 1][j], PM[i][j - 1]));
                    }
                }

                if (std::max(P[i - 1][j], P[i][j - 1]) >= tiles[i][j].v) //Update P Table
                {
                    P[i][j] = std::max(P[i - 1][j], P[i][j - 1]) - tiles[i][j].v;    
                }

                
                if (std::max(T[i - 1][j], T[i][j - 1]) >= 0)
                {
                    a = std::max(P[i - 1][j], P[i][j - 1]);
                    b = std::max(M[i - 1][j], M[i][j - 1]) - tiles[i][j].v;
                    c = std::max(PM[i - 1][j], PM[i][j - 1]);
                    d = std::max(T[i - 1][j], T[i][j - 1]) - tiles[i][j].v;

                    T[i][j] = std::max(std::max(a,b), std::max(c,d));

                }
                

                if (T[i][j] < 0)
                    T[i][j] = -1;

            }

            else if (tiles[i][j].t == 1) //Healing Tile
            {
                if (std::max(PM[i - 1][j], PM[i][j - 1]) >= 0) //Update PM Table
                {
                    PM[i][j] = std::max(PM[i - 1][j], PM[i][j - 1]) + tiles[i][j].v;

                    P[i][j] = std::max(std::max(P[i - 1][j], P[i][j - 1]) + tiles[i][j].v , std::max(PM[i - 1][j], PM[i][j - 1]) + (2 * tiles[i][j].v));
                }

                if (std::max(P[i - 1][j], P[i][j - 1]) >= 0) //Update P Table
                {
                    P[i][j] = std::max(P[i][j], std::max(P[i - 1][j], P[i][j - 1]) + tiles[i][j].v);
                }

                if (std::max(M[i - 1][j], M[i][j - 1]) >= 0) //Update M Table
                {
                    M[i][j] = std::max(M[i - 1][j], M[i][j - 1]) + tiles[i][j].v;
                }


                if (std::max(T[i - 1][j], T[i][j - 1]) >= 0)
                {
                    //(1) std::max(T[i - 1][j], T[i][j - 1]) + tiles[i][j].v
                    //(2) std::max(P[i - 1][j], P[i][j - 1]) + tiles[i][j].v
                    //(3) std::max(M[i - 1][j], M[i][j - 1]) + (2 * tiles[i][j].v)
                    //(4) std::max(PM[i - 1][j], PM[i][j - 1]) + (2 * tiles[i][j].v)

                    a = -1;
                    b = -1;
                    c = -1;
                    d = -1;

                    if (std::max(M[i - 1][j], M[i][j - 1]) >= 0)
                        a = std::max(M[i - 1][j], M[i][j - 1]) + (2 * tiles[i][j].v);
                   
                    if (std::max(PM[i - 1][j], PM[i][j - 1]) >= 0)
                        b = std::max(PM[i - 1][j], PM[i][j - 1]) + (2 * tiles[i][j].v);
                 
                    if (std::max(P[i - 1][j], P[i][j - 1]) >= 0)
                        c = std::max(P[i - 1][j], P[i][j - 1]) + tiles[i][j].v;

                    d = std::max(T[i - 1][j], T[i][j - 1]) + tiles[i][j].v;

                    T[i][j] = std::max(std::max(a,b), std::max(c,d));
                }
               

                    
            }

            else
            {
            
                if (tiles[i][j].t == 2) //Protection Tile
                {
                    if (std::max(M[i - 1][j], M[i][j - 1]) >= 0 || std::max(PM[i - 1][j], PM[i][j - 1]) >= 0) //Update PM
                    {
                        PM[i][j] = std::max(std::max(PM[i - 1][j], PM[i][j - 1]) , std::max(M[i - 1][j], M[i][j - 1]));
                    }

                    if (P[i - 1][j] >= 0 || P[i][j - 1] >= 0) 
                    {
                        P[i][j] = std::max(P[i - 1][j], P[i][j - 1]);
                    }

                    if (std::max(T[i - 1][j], T[i][j - 1]) >= 0)
                    {
                        T[i][j] = std::max(T[i][j - 1], T[i - 1][j]);

                        if (T[i][j] != PM[i][j]) //if T[i][j] has no multiplier
                        {
                            P[i][j] = std::max(std::max(P[i - 1][j], P[i][j - 1]), T[i][j]);
                        }
                    }

                }

                else if (tiles[i][j].t == 3) //Multiplier Tile
                {
                    if (std::max(P[i - 1][j], P[i][j - 1]) >= 0 || std::max(PM[i - 1][j], PM[i][j - 1]) >= 0) //Update PM
                    {
                        PM[i][j] = std::max(std::max(PM[i - 1][j], PM[i][j - 1]) , std::max(P[i - 1][j], P[i][j - 1]));
                    }

                    if (M[i - 1][j] >= 0 || M[i][j - 1] >= 0) //Update M Table
                    {
                        M[i][j] = std::max(M[i - 1][j], M[i][j - 1]);
                    }
 

                    if (std::max(T[i - 1][j], T[i][j - 1]) >= 0)
                    {
                        T[i][j] = std::max(T[i][j - 1], T[i - 1][j]);

                        if (T[i][j] != PM[i][j])
                        {
                            M[i][j] = std::max(std::max(M[i - 1][j], M[i][j - 1]), T[i][j]);
                        }
                    } 

                }
               
            }
        }
    }

    // std::cout << "Table T: " << std::endl;

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         std::cout << T[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << std::endl;

    // std::cout << "Table M: " << std::endl;
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
        
    //         std::cout << M[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << std::endl;

    // std::cout << "Table P: " << std::endl;
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
        
    //         std::cout << P[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    
    // std::cout << std::endl;

    // std::cout << "Table PM: " << std::endl;
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
        
    //         std::cout << PM[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    
    if (T[n - 1][n - 1] >= 0)
        return true;
    else
        return false;

    
   
}

void write_output_file(const std::string& output_file_name, bool result) {
    std::ofstream file(output_file_name);
    file << result;
    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " a_file_name.txt\n";
        return 1;
    }

    int n, H;
    std::vector<std::vector<Tile>> tiles;
    load_input_file(argv[1], n, H, tiles);
    print_tile_data(n, tiles);
    bool result = DP(n, H, tiles);
    std::cout << "Result: " << result << '\n';
    
    // Construct the output file name
    std::string output_file_name(argv[1]);
    output_file_name.insert(output_file_name.find_last_of('.'), "_out");
    std::ofstream outfile(output_file_name);
    outfile << result;
    outfile.close();

    return 0;
}
