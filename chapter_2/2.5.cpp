#include <list>
#include <iostream>
#include <random>
#include <cmath>

////////////////////////////////////////
std::list<int> genRandomList(int length)
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 9);
    std::list<int> lst;
    for (int i{}; i < length; ++i) {
        lst.push_back(dist(rd));
    }
    return lst;
}

////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const std::list<int>& lst)
{
    for (auto it{ lst.begin() }; it != lst.end(); ++it) {
        os << *it;
        if (std::next(it) != lst.end()) {
            os << " -> ";
        }
    }
    return os;
}

////////////////////////////////////////
std::list<int> reverseSum(const std::list<int>& lstA, const std::list<int>& lstB)
{
    int lstANum{}, lstBNum{};
    int lstAExp{1}, lstBExp{1};

    for (int x : lstA) {
        lstANum += lstAExp * x;
        lstAExp *= 10;
    }

    for (int x : lstB) {
        lstBNum += lstBExp * x;
        lstBExp *= 10;
    }

    int sum{ lstANum + lstBNum };
    std::list<int> result;
    while (sum) {
        int digit{ sum % 10 };
        result.push_back(digit);
        sum /= 10;
    }
    return result;
}

////////////////////////////////////////
std::list<int> forwardSum(const std::list<int>& lstA, const std::list<int>& lstB)
{
    int lstANum{}, lstBNum{};
    int lstAExp{ static_cast<int>(std::pow(10, lstA.size() - 1)) };
    int lstBExp{ static_cast<int>(std::pow(10, lstB.size() - 1)) };

    for (int x : lstA) {
        lstANum += lstAExp * x;
        lstAExp /= 10;
    }

    for (int x : lstB) {
        lstBNum += lstBExp * x;
        lstBExp /= 10;
    }

    int sum{ lstANum + lstBNum };
    std::list<int> result;
    while (sum) {
        int digit{ sum % 10 };
        result.push_front(digit);
        sum /= 10;
    }
    return result;
}

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc > 2) {
        int listALength{ std::atoi(argv[1]) };
        int listBLength{ std::atoi(argv[2]) };
        if (listALength < 1 || listBLength < 1) {
            std::cout << "at least one of the lengths is invalid\n";
        }
        else {
            std::list<int> listA{ genRandomList(listALength) };
            std::list<int> listB{ genRandomList(listBLength) };
            std::cout << '(' << listA << ')';
            std::cout << " + ";
            std::cout << '(' << listB << ')';
            std::cout << " = [reverse sum] ";
            std::cout << '(' << reverseSum(listA, listB) << ")\n";
            std::cout << '(' << listA << ')';
            std::cout << " + ";
            std::cout << '(' << listB << ')';
            std::cout << " = [forward sum] ";
            std::cout << '(' << forwardSum(listA, listB) << ")\n";
        }
    }
    else {
        std::cout << "Usage: " << argv[0] << " <listA length> <listB length>\n";
    }
}
