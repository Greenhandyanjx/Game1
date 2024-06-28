#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <string>

// 定义游戏地图
const int MAP_SIZE = 5;

std::vector<std::vector<char>> level1 = {
    {'S', '.', '.', '.', '.'},
    {'.', '#', '.', '#', '.'},
    {'.', '#', '.', '#', '.'},
    {'.', '.', '.', '#', '.'},
    {'.', '#', '.', '.', 'E'}
};
// 定义角色位置
std::vector<std::vector<char>> level2 = {
    {'S', '.', '#', '.', 'E'},
    {'.', '#', '.', '#', '.'},
    {'#', '.', '.', '.', '#'},
    {'.', '#', '#', '#', '.'},
    {'.', '.', '.', '.', '.'}
};

std::vector<std::vector<char>> level3 = {
    {'S', '.', '#', '.', 'E'},
    {'.', '#', '.', '#', '.'},
    {'.', '.', '.', '.', '#'},
    {'#', '#', '#', '#', '.'},
    {'.', '.', '.', '.', '.'}
};

std::vector<std::vector<std::vector<char>>> levels = { level1, level2, level3 };

// 定义角色位置和道具系统
struct Player {
    int x, y;
    int keys; // 用于解锁门的钥匙数量
};

Player player;

void printMap(const std::vector<std::vector<char>>& map) {
    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            if (i == player.x && j == player.y) {
                std::cout << 'P' << ' ';
            }
            else {
                std::cout << map[i][j] << ' ';
            }
        }
        std::cout << std::endl;
    }
}

void movePlayer(char direction, std::vector<std::vector<char>>& map) {
    int newX = player.x;
    int newY = player.y;

    switch (direction) {
    case 'w': newX--; break;
    case 's': newX++; break;
    case 'a': newY--; break;
    case 'd': newY++; break;
    default: std::cout << "Invalid move!" << std::endl; return;
    }

    if (newX >= 0 && newX < MAP_SIZE && newY >= 0 && newY < MAP_SIZE) {
        if (map[newX][newY] == '#') {
            std::cout << "Move not allowed! Obstacle in the way." << std::endl;
        }
        else if (map[newX][newY] == 'K') {
            player.keys++;
            map[newX][newY] = '.';
            player.x = newX;
            player.y = newY;
            std::cout << "You picked up a key! Total keys: " << player.keys << std::endl;
        }
        else {
            player.x = newX;
            player.y = newY;
        }
    }
    else {
        std::cout << "Move not allowed! Out of bounds." << std::endl;
    }
}

int main() {
    for (size_t level = 0; level < levels.size(); ++level) {
        std::vector<std::vector<char>> map = levels[level];
        player = { 0, 0, 0 }; // 初始化角色位置和钥匙数量

        std::cout << "Level " << level + 1 << std::endl;
        printMap(map);

        std::string moves;
        std::cout << "Enter your moves (w = up, s = down, a = left, d = right): ";
        std::cin >> moves;

        for (char move : moves) {
            movePlayer(move, map);
            printMap(map);
            std::cout << std::endl;

            // 检查是否到达终点
            if (map[player.x][player.y] == 'E') {
                std::cout << "Congratulations! You completed the level!" << std::endl;
                break;
            }
        }

        if (map[player.x][player.y] != 'E') {
            std::cout << "Level failed! Try again." << std::endl;
            break;
        }
    }

    std::cout << "Game Over!" << std::endl;
    return 0;
}