#include <string.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <poll.h>
#include "my_library.h"
#include <vector>

class Map 
{
    int object_position;
    std::string bit_map;
    public:
        size_t width;
        size_t height;
        void output_map();
        void update_player_position(std::vector<int>& block, int move_val);
        Map(size_t tmp_width, size_t tmp_hight);
};

void Map::output_map() 
{
    std::cout << bit_map;
    fflush(stdout);
    std::cout << "\033[17A";
    fflush(stdout);
}

void Map::update_player_position(std::vector<int>& block, int move_val) 
{
    for(int i = 0; i < 4; i++)
    {
        bit_map[object_position + block[i]] = ' ';
    }
    object_position += move_val;
    int a = block[0];
    int b = block[1];
    int c = block[2];
    int d = block[3];
    for(int i = 0; i < 4; i++)
    {
        bit_map[object_position + block[i]] = '*';
    }
}

Map::Map(size_t tmp_width, size_t tmp_hight) 
{
    width = tmp_width;
    height = tmp_hight;
    object_position = 2 * (tmp_width + 1) + 2;
    //total lines
    for(int i = 0; i < height; i++) 
    {
        //one line
        for(int j = 0; j <= width; j++) 
        {
            if(j == width) 
            {
                bit_map += '\n';
            }
            else if(i == 0 || i == height - 1)
            {
                bit_map += '#';
            }
            else if(j == 0 || j == width - 1)
            {
                bit_map += '#';
            }
            else 
            {
                bit_map += ' ';
            }
        }
    }
}

class Tetrimino 
{   
    std::vector<int> i_block;
    std::vector<int> j_block;
    std::vector<int> l_block;
    std::vector<int> o_block;
    std::vector<int> s_block;
    std::vector<int> t_block;
    std::vector<int> z_block;
    public:
        std::vector<int>& get_block(int block_type);
        int move(char move_key);
        Tetrimino(size_t map_width);
};

std::vector<int>& Tetrimino::get_block(int block_type)
{
    switch(block_type)
    {
        case 0:
            return i_block;
        case 1:
            return j_block;
        case 2:
            return l_block;
        case 3:
            return o_block;
        case 4:
            return s_block;
        case 5: 
            return t_block;
        case 6:
            return z_block;
    }
}

int Tetrimino::move(char move_key) 
{
    int ret_val = 0;
    switch(move_key) 
    {
        case 'a':
            ret_val = -1;
            break;
        case 'd':
            ret_val = 1;
            break;
    }
    return ret_val;
}

Tetrimino::Tetrimino(size_t map_width)
{
    t_block.push_back(-1);
    t_block.push_back(0);
    t_block.push_back(1);
    t_block.push_back(map_width + 1);
}

int main() 
{
    Map map1(15, 17);
    Tetrimino tetrimino(map1.width);
    map1.update_player_position(tetrimino.get_block(5), map1.width);
    map1.output_map();
    return 0;
}