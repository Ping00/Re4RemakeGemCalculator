#include "Util.hpp"
#include <vector>
#include <iostream>
void Util::makeCombinationUtil(std::vector<std::vector<int> >& ans, std::vector<int>& tmp, int n, int left, int k)
{
    // Pushing this vector to a vector of vector
    if (k == 0) {
        ans.push_back(tmp);
        return;
    }

    // i iterates from left to n. First time
    // left will be 1
    for (int i = left; i <= n; ++i)
    {
        tmp.push_back(i);
        makeCombinationUtil(ans, tmp, n, i + 1, k - 1);

        // Popping out last inserted element
        // from the vector
        tmp.pop_back();
    }
}

std::vector<std::vector<int>> Util::make_combinations(int n, int k)
{
    std::vector<std::vector<int> > ans;
    std::vector<int> tmp;
    makeCombinationUtil(ans, tmp, n, 1, k);
    return ans;
}

void Util::print_combinations(std::vector<std::vector<int>> ans)
{
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++) {
            std::cout << ans.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
}
