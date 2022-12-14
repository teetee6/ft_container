#include "utility.hpp"
#include "iostream"
#include "string"

int main()
{
    {
        std::cout << "---------------------------------------------------------" << std::endl;
        std::pair<int, std::string> pr(3, "good"), br(1, "bad");
        std::pair<int, std::string> kr(pr);
        std::cout << pr.first << ", " << pr.second << std::endl;
        std::cout << br.first << ", " << br.second << std::endl;
        std::cout << kr.first << ", " << kr.second << std::endl;
        kr = br;
        std::cout << kr.first << ", " << kr.second << std::endl;
        std::cout << std::endl;

        std::pair<char, const char *> tr('a', "tatata!");
        kr = tr;
        std::cout << kr.first << ", " << kr.second << std::endl;
        std::cout << std::endl;

        kr.swap(pr);
        std::cout << kr.first << ", " << kr.second << std::endl;
        std::cout << pr.first << ", " << pr.second << std::endl;
        std::swap(kr, pr);
        std::cout << kr.first << ", " << kr.second << std::endl;
        std::cout << pr.first << ", " << pr.second << std::endl;
        std::cout << std::endl;
    }
    {
        std::cout << "---------------------------------------------------------" << std::endl;
        std::pair<int, std::string> pr(3, "good"), br(1, "bad");
        std::pair<int, std::string> kr(pr);
        std::pair<int, std::string> zr(3, "zzzz");
        std::cout << (kr == pr) << (kr != pr) << (kr < pr) << (kr > pr) << (kr >= pr) << (kr <= pr) << std::endl;
        std::cout << (br == pr) << (br != pr) << (br < pr) << (br > pr) << (br >= pr) << (br <= pr) << std::endl;
        std::cout << (pr == br) << (pr != br) << (pr < br) << (pr > br) << (pr >= br) << (pr <= br) << std::endl;
        std::cout << (pr == zr) << (pr != zr) << (pr < zr) << (pr > zr) << (pr >= zr) << (pr <= zr) << std::endl;
        std::cout << std::endl;
    }
    {
        std::cout << "---------------------------------------------------------" << std::endl;
        std::pair<int, std::string> pr(std::make_pair<int, std::string>(1111, "hello?"));
        std::cout << pr.first << ", " << pr.second << std::endl;
        std::pair<int, std::string> br(1, "bad");
        pr = br;
        std::cout << pr.first << ", " << pr.second << std::endl;
    }
}