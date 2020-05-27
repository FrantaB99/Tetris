#include <string.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <poll.h>
#include "my_library.h"
#include <vector>

#define MAP_WIDTH 15
#define MAP_HIGHT 17

class Tetrimino 
{   
    public:
    std::vector<int> i_block;
    std::vector<int> j_block;
    std::vector<int> l_block;
    std::vector<int> o_block;
    std::vector<int> s_block;
    std::vector<int> t_block;
    std::vector<int> z_block;
    int block_type;
    int position;
    public:
        int get_block_size();
        int get_position();
        int get_dimension(int dimension);
        void move(char move_key, int map_width);
        Tetrimino(size_t map_width, int tmp_block_type);
};

int Tetrimino::get_block_size()
{
    switch(block_type)
    {
        case 0:
            return i_block.size();
        case 1:
            return j_block.size();
        case 2:
            return l_block.size();
        case 3:
            return o_block.size();
        case 4:
            return s_block.size();
        case 5: 
            return t_block.size();
        case 6:
            return z_block.size();
    } 
}

int Tetrimino::get_position()
{
    return position;
}

int Tetrimino::get_dimension(int dimension)
{
    switch(block_type)
    {
        case 0:
            return i_block[dimension];
        case 1:
            return j_block[dimension];
        case 2:
            return l_block[dimension];
        case 3:
            return o_block[dimension];
        case 4:
            return s_block[dimension];
        case 5: 
            return t_block[dimension];
        case 6:
            return z_block[dimension];
    }
}

void Tetrimino::move(char move_key, int map_width) 
{
    int ret_val = 0;

    switch(move_key) 
    {
        case 'a':
            position += -1;
            break;
        case 's':
            position += map_width + 1;
            break;
        case 'd':
            position += 1;
            break;
    }
}

Tetrimino::Tetrimino(size_t map_width, int tmp_block_type)
{
    //t_block initialization
    t_block.push_back(-1);
    t_block.push_back(0);
    t_block.push_back(1);
    t_block.push_back(-(map_width + 1));

    //chosen block type 
    block_type = tmp_block_type;

    //spawn position
    position = 2 * (map_width + 1) + 7;;
}

class Map 
{
    std::string bit_map;
    size_t width;
    size_t height;
    public:
        int get_width();
        int get_hight();
        void output_map();
        int move_object(Tetrimino& tetrimino, char move_key); 
        Map(size_t tmp_width, size_t tmp_hight);
};

int Map::get_width()
{
    return width;
}

int Map::get_hight()
{
    return height;
}

void Map::output_map() 
{
    std::cout << bit_map;
    fflush(stdout);
    std::cout << "\033[17A";
    fflush(stdout);
}

int move_key_value(char move_key, int map_width) 
{
    switch(move_key) 
    {
        case 'a':
            return -1;
        case 's':
            return map_width + 1;
        case 'd':
            return 1;
    }
}

int Map::move_object(Tetrimino& tetrimino, char move_key)
{
    int index;

    //delete the object in present position
    for(int i = 0; i < tetrimino.get_block_size(); i++)
    {
        index = tetrimino.get_position() + tetrimino.get_dimension(i);
        bit_map[index] = ' ';
    }

    //check if the object can be moved
    for(int i = 0; i < tetrimino.get_block_size(); i++)
    {
        index = tetrimino.get_position() + move_key_value(move_key, get_width()) + tetrimino.get_dimension(i);
        if(bit_map[index] == '#' || bit_map[index] == 'G')
        {
            for(int i = 0; i < tetrimino.get_block_size(); i++)
            {
                index = tetrimino.get_position() + tetrimino.get_dimension(i);
                bit_map[index] = 'G';
            }
            return 1;
        }
    }

    //update position of the object
    tetrimino.move(move_key, get_width());

    //write object in new location
    for(int i = 0; i < tetrimino.get_block_size(); i++)
    {
        index = tetrimino.get_position() + tetrimino.get_dimension(i);
        bit_map[index] = 'G';
    }
    return 0;
}

Map::Map(size_t tmp_width, size_t tmp_hight) 
{
    /*initialize dimensions of map excluding new lines,
    actual bit_map width with new lines is: width + 1*/
    width = tmp_width;
    height = tmp_hight;
    
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

int main() 
{
    //switch off input echo in terminal
    system("/bin/stty -echo");

    //hide cursor in terminal
    system("/usr/bin/setterm -cursor off");

    //switch stdout buffer to buffer until flushed
    char buf[BUFSIZ];
    setvbuf(stdout, buf, _IOFBF, BUFSIZ);

    //variables needed for object free fall
    struct timespec start, end;
    int wait_time = 1000;
    start.tv_sec = -wait_time;
    bool skipped = false;

    //other trash
    char input[2];
    Map map(MAP_WIDTH, MAP_HIGHT);
    Tetrimino *tetrimino_ptr = new Tetrimino(MAP_WIDTH, 5);
    //Tetrimino tetrimino(MAP_WIDTH, 5);
    map.move_object(*tetrimino_ptr, 'o');

    //main game loop, breaks out if '0' is input
    while(true) 
    {
        //user input to move left, right, spin or end game on '0'
        catch_input(input, 1);
        if(input[0] != '\0') 
        {
            map.move_object(*tetrimino_ptr, input[0]);
            //end game
            if(input[0] == '0')
            {
                break;
            }
            memset(input, '\0', 1);
        }

        //free fall once every set time
        clock_gettime(CLOCK_MONOTONIC, &end);
        int elapsed_time = end.tv_sec * 1000 - start.tv_sec * 1000;
        if(elapsed_time >= wait_time)
        {
            clock_gettime(CLOCK_MONOTONIC, &start);
            if(skipped)
            {
                if(map.move_object(*tetrimino_ptr, 's') == 1)
                {
                    delete tetrimino_ptr;
                    tetrimino_ptr = new Tetrimino(MAP_WIDTH, 5);
                } 
            }
            skipped = true;
        }

        //frame output to terminal
        map.output_map();
        //std::cout << tetrimino_ptr->t_block.size() << std::endl;
    }
    //revert all settings of terminal to a state before start of program
    system("/bin/stty echo");
    system("/usr/bin/setterm -cursor on");
    return 0;
}
